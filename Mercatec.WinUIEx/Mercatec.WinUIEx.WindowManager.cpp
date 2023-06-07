#include "pch.h"
#include "Mercatec.WinUIEx.WindowManager.h"
#if __has_include("WindowManager.g.cpp")
# include "WindowManager.g.cpp"
#endif

#include "Mercatec.WinUIEx.Windows.Win32.hpp"
#include "Mercatec.WinUIEx.WindowState.hpp"
#include "Mercatec.WinUIEx.BackdropType.hpp"
#include "Mercatec.WinUIEx.WindowExtensions.hpp"
#include "Mercatec.WinUIEx.SystemBackdrop.hpp"

using Mercatec::WinUIEx::WindowExtensions;
using Mercatec::WinUIEx::Messaging::WindowMessageMonitor;
using winrt::Mercatec::WinUIEx::WindowState;
using winrt::Mercatec::WinUIEx::ZOrderInfo;
using winrt::Mercatec::WinUIEx::Messaging::WindowMessageEventArgs;
using winrt::Mercatec::WinUIEx::Messaging::WindowsMessages;
using winrt::Microsoft::UI::Windowing::AppWindow;
using winrt::Microsoft::UI::Windowing::AppWindowChangedEventArgs;
using winrt::Microsoft::UI::Windowing::AppWindowPresenter;
using winrt::Microsoft::UI::Windowing::AppWindowPresenterKind;
using winrt::Microsoft::UI::Windowing::OverlappedPresenter;
using winrt::Microsoft::UI::Windowing::OverlappedPresenterState;
using winrt::Windows::Foundation::EventHandler;
using winrt::Windows::Foundation::TypedEventHandler;
using winrt::Windows::Graphics::PointInt32;

using std::make_shared;
using std::make_unique;
using std::shared_ptr;
using std::unique_ptr;
using std::weak_ptr;

using namespace winrt::Microsoft::UI::Xaml;
using namespace winrt::Microsoft::UI::Composition;

namespace winrt::Mercatec::WinUIEx::implementation
{
    /// <summary>
    ///     A deeper dive into winrt::resume_foreground
    ///     https://learn.microsoft.com/en-us/windows/uwp/cpp-and-winrt-apis/concurrency-2#a-deeper-dive-into-winrtresume_foreground
    /// </summary>
    struct WindowsSystemDispatcherQueueHelper
    {
        winrt::Windows::System::DispatcherQueueController DispatcherQueueController;

        void EnsureWindowsSystemDispatcherQueueController()
        {
            if ( winrt::Windows::System::DispatcherQueue::GetForCurrentThread() != nullptr )
            {
                return;
            }

            if ( DispatcherQueueController == nullptr )
            {
                DispatcherQueueOptions Options{ sizeof(DispatcherQueueOptions), DQTYPE_THREAD_CURRENT, DQTAT_COM_STA };

                ABI::Windows::System::IDispatcherQueueController* Pointer{};
                winrt::check_hresult(CreateDispatcherQueueController(Options, &Pointer));
                DispatcherQueueController = winrt::Windows::System::DispatcherQueueController{ Pointer, winrt::take_ownership_from_abi };
            }
        }
    };

    struct WindowManager::WindowManagerImpl
    {
        com_ptr<::Mercatec::WinUIEx::Messaging::WindowMessageMonitor>            Monitor                   = nullptr;
        Microsoft::UI::Xaml::Window                                              Window                    = nullptr;
        Microsoft::UI::Windowing::OverlappedPresenter                            OverlappedPresenter       = nullptr;
        Microsoft::UI::Composition::SystemBackdrops::ISystemBackdropController   CurrentController         = nullptr;
        Microsoft::UI::Composition::SystemBackdrops::SystemBackdropConfiguration BackdropConfiguration     = nullptr;
        WindowsSystemDispatcherQueueHelper                                       DispatcherQueueController = { nullptr };
        winrt::Mercatec::WinUIEx::BackdropType                                   BackdropType              = Mercatec::WinUIEx::BackdropType::DefaultColor;
        bool                                                                     IsInitialized             = false; // Set to true on first activation. Used to track persistence restore.
        double_t                                                                 MinWidth                  = 136;
        double_t                                                                 MinHeight                 = 39;
        double_t                                                                 MaxWidth                  = 0;
        double_t                                                                 MaxHeight                 = 0;
        winrt::Mercatec::WinUIEx::WindowState                                    WindowState               = WindowState::Normal;
        winrt::hstring                                                           PersistenceId             = L"";
        bool                                                                     RestoringPersistence      = false; // Flag used to avoid WinUI DPI adjustment
        bool                                                                     IsTitleBarVisible         = true;
        event_token                                                              AppWindowChangedToken;
        event_token                                                              WindowClosedToken;
        event_token                                                              WindowClosedSavePersistenceToken;
        event_token                                                              WindowActivatedToken;
        event_token                                                              WindowThemeChangedToken;
        event<TypedEventHandler<WinUIEx::WindowManager, WinUIEx::WindowState>>   StateChanged;
        event<TypedEventHandler<WinUIEx::WindowManager, WindowMessageEventArgs>> WindowMessageReceived;
        event<TypedEventHandler<WinUIEx::WindowManager, PointInt32>>             PositionChanged;
        event<TypedEventHandler<WinUIEx::WindowManager, AppWindowPresenter>>     PresenterChanged;
        event<TypedEventHandler<WinUIEx::WindowManager, ZOrderInfo>>             ZOrderChanged;
        static std::map<HWND, winrt::weak_ref<WinUIEx::WindowManager>>           Managers;
        static LocalSettings                                                     PersistenceStorage;
    };

    std::map<HWND, winrt::weak_ref<WinUIEx::WindowManager>> WindowManager::WindowManagerImpl::Managers;
    LocalSettings                                           WindowManager::WindowManagerImpl::PersistenceStorage = nullptr;

    bool WindowManager::TryGetWindowManager(const Window& Window, WinUIEx::WindowManager& Manager)
    {
        if ( Window == nullptr )
        {
            throw winrt::hresult_invalid_argument(L"Argument Null Exception: Window");
        }

        HWND Handle = WindowExtensions::GetWindowHandle(Window);

        if ( auto It = WindowManagerImpl::Managers.find(Handle); It != std::end(WindowManagerImpl::Managers) )
        {
            Manager = It->second.get();
            return static_cast<bool>(Manager);
        }

        Manager = nullptr;
        return false;
    }

    [[nodiscard]] WinUIEx::WindowManager WindowManager::Get(const Window& Window)
    {
        if ( WinUIEx::WindowManager Manager{ nullptr }; TryGetWindowManager(Window, Manager) )
        {
            return Manager;
        }

        return winrt::make<WindowManager>(Window);
    }

    WindowManager::~WindowManager()
    {
        HWND Handle = WindowExtensions::GetWindowHandle(Impl->Window);

        if ( WindowManagerImpl::Managers.contains(Handle) )
        {
            WindowManagerImpl::Managers.erase(Handle);
        }

        AppWindow().Changed(Impl->AppWindowChangedToken);
        Impl->Window.Closed(Impl->WindowClosedSavePersistenceToken);
    }

    WindowManager::WindowManager(const Window& Window)
      : WindowManager(Window, winrt::make_self<WindowMessageMonitor>(Window))
    {
    }

    WindowManager::WindowManager(const Window& Window, const winrt::com_ptr<WindowMessageMonitor>& Monitor)
      : Impl{ make_unique<WindowManagerImpl>() }
    {
        if ( Window == nullptr )
        {
            throw winrt::hresult_invalid_argument(L"Argument Null Exception: Window");
        }

        if ( WinUIEx::WindowManager OldMonitor{ nullptr }; TryGetWindowManager(Window, OldMonitor) )
        {
            throw winrt::hresult_error(winrt::impl::error_fail, L"Invalid Operation Exception: Only one window manager can be attached to a Window.");
        }

        Impl->Monitor = Monitor;
        Impl->Monitor->WindowMessageReceived({ this, &WindowManager::OnWindowMessage });

        Impl->Window                           = Window;
        Impl->WindowClosedSavePersistenceToken = Impl->Window.Closed([this](const auto&, const auto&) { SavePersistence(); });
        Impl->Window.VisibilityChanged({ this, &WindowManager::Window_VisibilityChanged });

        Impl->AppWindowChangedToken = AppWindow().Changed({ this, &WindowManager::AppWindow_Changed });

        WindowManagerImpl::Managers[WindowExtensions::GetWindowHandle(Window)] = make_weak<WinUIEx::WindowManager>(*this);

        Impl->OverlappedPresenter = winrt::unbox_value_or<OverlappedPresenter>(AppWindow().Presenter(), OverlappedPresenter::Create());

        switch ( Impl->OverlappedPresenter.State() )
        {
            case OverlappedPresenterState::Restored:
            {
                Impl->WindowState = WindowState::Normal;
                break;
            }
            case OverlappedPresenterState::Minimized:
            {
                Impl->WindowState = WindowState::Minimized;
                break;
            }
            case OverlappedPresenterState::Maximized:
            {
                Impl->WindowState = WindowState::Maximized;
                break;
            }
        }

        Impl->DispatcherQueueController.EnsureWindowsSystemDispatcherQueueController();
        BackdropType(BackdropType::DefaultColor);
    }

    void WindowManager::Window_VisibilityChanged([[maybe_unused]] const winrt::IInspectable& Sender, const WindowVisibilityChangedEventArgs& Args)
    {
        if ( Args.Visible() and Impl->CurrentController == nullptr )
        {
            Impl->DispatcherQueueController.EnsureWindowsSystemDispatcherQueueController();
            BackdropType(BackdropType::DefaultColor);
        }
    }

    winrt::Microsoft::UI::Windowing::AppWindow WindowManager::AppWindow() const noexcept
    {
        return Impl->Window.AppWindow();
    }

    double_t WindowManager::Width() const noexcept
    {
        return AppWindow().Size().Width / (WindowExtensions::GetDpiForWindow(Impl->Window) / 96.0);
    }

    void WindowManager::Width(const double_t Width) noexcept
    {
        WindowExtensions::SetWindowSize(Impl->Window, Width, Height());
    }

    double_t WindowManager::Height() const noexcept
    {
        return AppWindow().Size().Height / (WindowExtensions::GetDpiForWindow(Impl->Window) / 96.0);
    }

    void WindowManager::Height(const double_t Height) noexcept
    {
        WindowExtensions::SetWindowSize(Impl->Window, Width(), Height);
    }

    double_t WindowManager::MinWidth() const noexcept
    {
        return Impl->MinWidth;
    }

    void WindowManager::MinWidth(const double_t MinWidth) noexcept
    {
        Impl->MinWidth = MinWidth;

        if ( Width() < MinWidth )
        {
            Width(MinWidth);
        }
    }

    double_t WindowManager::MinHeight() const noexcept
    {
        return Impl->MinHeight;
    }

    void WindowManager::MinHeight(const double_t MinHeight) noexcept
    {
        Impl->MinHeight = MinHeight;

        if ( Height() < MinHeight )
        {
            Height(MinHeight);
        }
    }

    double_t WindowManager::MaxWidth() const noexcept
    {
        return Impl->MaxWidth;
    }

    void WindowManager::MaxWidth(const double_t MaxWidth)
    {
        if ( MaxWidth <= 0 )
        {
            throw winrt::hresult_out_of_bounds(L"Argument Out Of Range Exception: MaxWidth");
        }

        Impl->MaxWidth = MaxWidth;

        if ( Width() > MaxWidth )
        {
            Width(MaxWidth);
        }
    }

    double_t WindowManager::MaxHeight() const noexcept
    {
        return Impl->MaxHeight;
    }

    void WindowManager::MaxHeight(const double_t MaxHeight)
    {
        if ( MaxHeight <= 0 )
        {
            throw winrt::hresult_out_of_bounds(L"Argument Out Of Range Exception: MaxHeight");
        }

        Impl->MaxHeight = MaxHeight;

        if ( Height() > MaxHeight )
        {
            Height(MaxHeight);
        }
    }

    void WindowManager::OnWindowMessage([[maybe_unused]] const winrt::IInspectable& Sender, const WindowMessageEventArgs& Args)
    {
        if ( (Args.MessageType() == WindowsMessages::WmShowWindow) and (Args.Message().WParam() == 1) )
        {
            if ( not Impl->IsInitialized )
            {
                Impl->IsInitialized = true;
                LoadPersistence();

                Impl->Window.DispatcherQueue().TryEnqueue( //
                  winrt::Microsoft::UI::Dispatching::DispatcherQueuePriority::High,
                  [this]
                  {
                      Impl->DispatcherQueueController.EnsureWindowsSystemDispatcherQueueController();
                      BackdropType(BackdropType::DefaultColor);
                  }
                );
            }
        }

        Impl->WindowMessageReceived(*this, Args);

        if ( Args.Handled() )
        {
            return;
        }

        switch ( Args.MessageType() )
        {
            case WindowsMessages::WmGetMinMaxInfo:
            {
                MINMAXINFO* Rect2      = reinterpret_cast<MINMAXINFO*>(Args.Message().LParam());
                double_t    CurrentDpi = WindowExtensions ::GetDpiForWindow(Impl->Window);

                if ( Impl->RestoringPersistence )
                {
                    // Only restrict maxsize during restore
                    if ( not ::isnan(MaxWidth()) and MaxWidth() > 0 )
                    {
                        // If minwidth < maxwidth, minwidth will take presedence
                        Rect2->ptMaxSize.x = LONG(std::min(std::max(MaxWidth(), MinWidth()) * (CurrentDpi / 96.0), double_t(Rect2->ptMaxSize.x)));
                    }

                    if ( not ::isnan(MaxHeight()) and MaxHeight() > 0 )
                    {
                        // If minheight < maxheight, minheight will take presedence
                        Rect2->ptMaxSize.y = LONG(std::min(std::max(MaxHeight(), MinHeight()) * (CurrentDpi / 96.0), double_t(Rect2->ptMaxSize.y)));
                    }
                }
                else
                {
                    // Restrict min-size
                    Rect2->ptMinTrackSize.x = LONG(std::max(MinWidth() * (CurrentDpi / 96.0), double_t(Rect2->ptMinTrackSize.x)));
                    Rect2->ptMinTrackSize.y = LONG(std::max(MinHeight() * (CurrentDpi / 96.0), double_t(Rect2->ptMinTrackSize.y)));

                    // Restrict max-size
                    if ( not ::isnan(MaxWidth()) and MaxWidth() > 0 )
                    {
                        // If minwidth < maxwidth, minwidth will take presedence
                        Rect2->ptMaxTrackSize.x = LONG(std::min(std::max(MaxWidth(), MinWidth()) * (CurrentDpi / 96.0), double_t(Rect2->ptMaxTrackSize.x)));
                    }

                    if ( not ::isnan(MaxHeight()) and MaxHeight() > 0 )
                    {
                        // If minheight < maxheight, minheight will take presedence
                        Rect2->ptMaxTrackSize.y = LONG(std::min(std::max(MaxHeight(), MinHeight()) * (CurrentDpi / 96.0), double_t(Rect2->ptMaxTrackSize.y)));
                    }
                }
                break;
            }

            case WindowsMessages::WmDpiChanged:
            {
                if ( Impl->RestoringPersistence )
                {
                    // Don't let WinUI resize the window due to a dpi change caused by restoring window position - we got this.
                    Args.Handled(true);
                }
                break;
            }

            case WindowsMessages::WmSize:
            {
                // https://learn.microsoft.com/en-us/windows/win32/winmsg/wm-size
                WinUIEx::WindowState State;

                switch ( Args.Message().WParam() )
                {
                    case 0:
                    {
                        State = WindowState::Normal;
                        break;
                    }
                    case 1:
                    {
                        State = WindowState::Minimized;
                        break;
                    }
                    case 2:
                    {
                        State = WindowState::Maximized;
                        break;
                    }
                    default:
                    {
                        return;
                    }
                }

                if ( State != Impl->WindowState )
                {
                    Impl->WindowState = State;
                    Impl->StateChanged(*this, State);
                }

                break;
            }
        }
    }

    WindowState WindowManager::WindowState() const noexcept
    {
        return Impl->WindowState;
    }

    void WindowManager::WindowState(const WinUIEx::WindowState& State) noexcept
    {
        if ( Impl->WindowState != State )
        {
            switch ( State )
            {
                case WindowState::Normal:
                {
                    Impl->OverlappedPresenter.Restore();
                    break;
                }
                case WindowState::Minimized:
                {
                    Impl->OverlappedPresenter.Minimize();
                    break;
                }
                case WindowState::Maximized:
                {
                    Impl->OverlappedPresenter.Maximize();
                    break;
                }
            }
        }
    }

    winrt::event_token WindowManager::StateChanged(const TypedEventHandler<WinUIEx::WindowManager, Mercatec::WinUIEx::WindowState>& Handler)
    {
        return Impl->StateChanged.add(Handler);
    }

    void WindowManager::StateChanged(const winrt::event_token& Token) noexcept
    {
        Impl->StateChanged.remove(Token);
    }

    winrt::event_token WindowManager::WindowMessageReceived(const TypedEventHandler<WinUIEx::WindowManager, WindowMessageEventArgs>& Handler)
    {
        return Impl->WindowMessageReceived.add(Handler);
    }

    void WindowManager::WindowMessageReceived(const winrt::event_token& Token) noexcept
    {
        Impl->WindowMessageReceived.remove(Token);
    }

    winrt::hstring WindowManager::PersistenceId() const noexcept
    {
        return Impl->PersistenceId;
    }

    void WindowManager::PersistenceId(const std::wstring_view PersistenceId) noexcept
    {
        Impl->PersistenceId = PersistenceId;
    }

    LocalSettings WindowManager::PersistenceStorage() noexcept
    {
        return WindowManagerImpl::PersistenceStorage;
    }

    void WindowManager::PersistenceStorage(const LocalSettings& PersistenceStorage) noexcept
    {
        WindowManagerImpl::PersistenceStorage = PersistenceStorage;
    }

    LocalSettings WindowManager::GetPersistenceStorage([[maybe_unused]] const bool CreateIfMissing)
    {
        if ( PersistenceStorage() != nullptr )
            return PersistenceStorage();

        try
        {
            //!
            //! TODO: Implementar: winrt::Windows::Storage::ApplicationData::Current().LocalSettings()
            //!

            return LocalSettings();
        }
        catch ( ... )
        {
        }

        return nullptr;
    }

    void WindowManager::LoadPersistence()
    {
        //!
        //! TODO: Implementar: winrt::Windows::Storage::ApplicationData::Current().LocalSettings()
        //!
    }

    void WindowManager::SavePersistence()
    {
        //!
        //! TODO: Implementar: winrt::Windows::Storage::ApplicationData::Current().LocalSettings()
        //!
    }

    void WindowManager::AppWindow_Changed(const Microsoft::UI::Windowing::AppWindow& Sender, const AppWindowChangedEventArgs& Args)
    {
        if ( Args.DidPositionChange() )
        {
            Impl->PositionChanged(*this, Sender.Position());
        }

        if ( Args.DidPresenterChange() )
        {
            if ( OverlappedPresenter Presenter = AppWindow().Presenter().try_as<OverlappedPresenter>(); Presenter and Presenter != Impl->OverlappedPresenter )
            {
                Impl->OverlappedPresenter = Presenter;
                Impl->IsTitleBarVisible   = Presenter.HasTitleBar();
            }

            Impl->PresenterChanged(*this, Sender.Presenter());
        }

        if ( Args.DidZOrderChange() )
        {
            ZOrderInfo Info;
            Info.IsZOrderAtTop(Args.IsZOrderAtTop());
            Info.IsZOrderAtBottom(Args.IsZOrderAtBottom());
            Info.ZOrderBelowWindowId(Args.ZOrderBelowWindowId());

            Impl->ZOrderChanged(*this, Info);
        }
    }

    bool WindowManager::IsTitleBarVisible() const noexcept
    {
        return Impl->IsTitleBarVisible;
    }

    void WindowManager::IsTitleBarVisible(const bool IsTitleBarVisible) noexcept
    {
        Impl->IsTitleBarVisible = IsTitleBarVisible;
        Impl->OverlappedPresenter.SetBorderAndTitleBar(true, IsTitleBarVisible);
    }

    bool WindowManager::IsMinimizable() const noexcept
    {
        return Impl->OverlappedPresenter.IsMinimizable();
    }

    void WindowManager::IsMinimizable(const bool IsMinimizable) noexcept
    {
        Impl->OverlappedPresenter.IsMinimizable(IsMinimizable);
    }

    bool WindowManager::IsMaximizable() const noexcept
    {
        return Impl->OverlappedPresenter.IsMaximizable();
    }

    void WindowManager::IsMaximizable(const bool IsMaximizable) noexcept
    {
        Impl->OverlappedPresenter.IsMaximizable(IsMaximizable);
    }

    bool WindowManager::IsResizable() const noexcept
    {
        return Impl->OverlappedPresenter.IsResizable();
    }

    void WindowManager::IsResizable(const bool IsResizable) noexcept
    {
        Impl->OverlappedPresenter.IsResizable(IsResizable);
    }

    bool WindowManager::IsAlwaysOnTop() const noexcept
    {
        return Impl->OverlappedPresenter.IsAlwaysOnTop();
    }

    void WindowManager::IsAlwaysOnTop(const bool IsAlwaysOnTop) noexcept
    {
        Impl->OverlappedPresenter.IsAlwaysOnTop(IsAlwaysOnTop);
    }

    AppWindowPresenterKind WindowManager::PresenterKind() const noexcept
    {
        return AppWindow().Presenter().Kind();
    }

    void WindowManager::PresenterKind(const AppWindowPresenterKind PresenterKind) noexcept
    {
        if ( PresenterKind == AppWindowPresenterKind::Overlapped )
        {
            AppWindow().SetPresenter(Impl->OverlappedPresenter);
        }
        else
        {
            AppWindow().SetPresenter(PresenterKind);
        }
    }

    winrt::event_token WindowManager::PositionChanged(const TypedEventHandler<WinUIEx::WindowManager, winrt::Windows::Graphics::PointInt32>& Handler)
    {
        return Impl->PositionChanged.add(Handler);
    }

    void WindowManager::PositionChanged(const winrt::event_token& Token) noexcept
    {
        Impl->PositionChanged.remove(Token);
    }

    winrt::event_token WindowManager::PresenterChanged(const TypedEventHandler<WinUIEx::WindowManager, winrt::Microsoft::UI::Windowing::AppWindowPresenter>& Handler)
    {
        return Impl->PresenterChanged.add(Handler);
    }

    void WindowManager::PresenterChanged(const winrt::event_token& Token) noexcept
    {
        Impl->PresenterChanged.remove(Token);
    }

    winrt::event_token WindowManager::ZOrderChanged(const TypedEventHandler<WinUIEx::WindowManager, winrt::Mercatec::WinUIEx::ZOrderInfo>& Handler)
    {
        return Impl->ZOrderChanged.add(Handler);
    }

    void WindowManager::ZOrderChanged(const winrt::event_token& Token) noexcept
    {
        Impl->ZOrderChanged.remove(Token);
    }

    void WindowManager::Window_ThemeChanged([[maybe_unused]] const FrameworkElement& Sender, [[maybe_unused]] const winrt::IInspectable& Args)
    {
        if ( Impl->BackdropConfiguration != nullptr )
        {
            SetConfigurationSourceTheme();
        }
    }

    void WindowManager::Window_Activated([[maybe_unused]] const winrt::IInspectable& Sender, const WindowActivatedEventArgs& Args)
    {
        if ( Impl->BackdropConfiguration != nullptr )
        {
            Impl->BackdropConfiguration.IsInputActive(Args.WindowActivationState() != WindowActivationState::Deactivated);
        }
    }

    void WindowManager::Window_Closed([[maybe_unused]] const winrt::IInspectable& Sender, [[maybe_unused]] const WindowEventArgs& Args)
    {
        // Make sure any Mica/Acrylic controller is disposed so it doesn't try to se this closed window.
        if ( Impl->CurrentController != nullptr )
        {
            Impl->CurrentController.Close();
            Impl->CurrentController = nullptr;
        }

        Impl->Window.Activated(Impl->WindowActivatedToken);
        Impl->BackdropConfiguration = nullptr;
    }

    winrt::Mercatec::WinUIEx::BackdropType WindowManager::BackdropType() const noexcept
    {
        return Impl->BackdropType;
    }

    void WindowManager::BackdropType(winrt::Mercatec::WinUIEx::BackdropType BackdropType) noexcept
    {
        if ( BackdropType == Impl->BackdropType )
        {
            return;
        }

        // Reset to default color. If the requested type is supported, we'll update to that.
        // Note: This sample completely removes any previous controller to reset to the default
        //       state. This is done so this sample can show what is expected to be the most
        //       common pattern of an app simply choosing one controller type which it sets at
        //       startup. If an app wants to toggle between Mica and Acrylic it could simply
        //       call RemoveSystemBackdropTarget() on the old controller and then setup the new
        //       controller, reusing any existing Impl->BackdropConfiguration and Activated/Closed
        //       event handlers.

        if ( Impl->CurrentController != nullptr )
        {
            Impl->CurrentController.Close();
            Impl->CurrentController = nullptr;
        }

        Impl->Window.Closed(Impl->WindowClosedToken);
        Impl->Window.Activated(Impl->WindowActivatedToken);

        if ( auto Element = Impl->Window.try_as<FrameworkElement>() )
        {
            Element.ActualThemeChanged(Impl->WindowThemeChangedToken);
        }

        Impl->BackdropType          = BackdropType::DefaultColor;
        Impl->BackdropConfiguration = nullptr;

        if ( BackdropType == BackdropType::Mica )
        {
            if ( TrySetMicaBackdrop(false) )
            {
                Impl->BackdropType = BackdropType;
                return;
            }
            else
            {
                // Mica isn't supported. Try Acrylic.
                BackdropType = BackdropType::DesktopAcrylic;
            }
        }

        if ( BackdropType == BackdropType::MicaAlt )
        {
            if ( TrySetMicaBackdrop(true) )
            {
                Impl->BackdropType = BackdropType;
                return;
            }
            else
            {
                // MicaAlt isn't supported. Try Acrylic.
                BackdropType = BackdropType::DesktopAcrylic;
            }
        }

        if ( BackdropType == BackdropType::DesktopAcrylic )
        {
            if ( TrySetAcrylicBackdrop() )
            {
                Impl->BackdropType = BackdropType;
                return;
            }
            else
            {
                // Acrylic isn't supported, so take the next option, which is DefaultColor, which is already set.
                // Acrylic isn't supported. Switching to default color.
            }
        }
    }

    void WindowManager::SetConfigurationSourceTheme() noexcept
    {
        if ( auto Element = Impl->Window.Content().try_as<FrameworkElement>() )
        {
            switch ( Element.ActualTheme() )
            {
                case ElementTheme::Dark:
                {
                    Impl->BackdropConfiguration.Theme(SystemBackdrops::SystemBackdropTheme::Dark);
                    break;
                }
                case ElementTheme::Light:
                {
                    Impl->BackdropConfiguration.Theme(SystemBackdrops::SystemBackdropTheme::Light);
                    break;
                }
                case ElementTheme::Default:
                {
                    Impl->BackdropConfiguration.Theme(SystemBackdrops::SystemBackdropTheme::Default);
                    break;
                }
            }
        }
    }

    bool WindowManager::TrySetMicaBackdrop(const bool UseMicaAlt) noexcept
    {
        if ( winrt::Microsoft::UI::Composition::SystemBackdrops::MicaController::IsSupported() )
        {
            // Hooking up the policy object.
            Impl->BackdropConfiguration = winrt::Microsoft::UI::Composition::SystemBackdrops::SystemBackdropConfiguration();

            Impl->WindowClosedToken    = Impl->Window.Closed({ this, &WindowManager::Window_Closed });
            Impl->WindowActivatedToken = Impl->Window.Activated({ this, &WindowManager::Window_Activated });

            if ( auto Element = Impl->Window.Content().try_as<FrameworkElement>() )
            {
                Impl->WindowThemeChangedToken = Element.ActualThemeChanged({ this, &WindowManager::Window_ThemeChanged });
            }

            // Initial configuration state.
            Impl->BackdropConfiguration.IsInputActive(true);
            SetConfigurationSourceTheme();

            winrt::Microsoft::UI::Composition::SystemBackdrops::MicaController MicaController;
            MicaController.Kind(
              UseMicaAlt //
                ? winrt::Microsoft::UI::Composition::SystemBackdrops::MicaKind::BaseAlt
                : winrt::Microsoft::UI::Composition::SystemBackdrops::MicaKind::Base
            );

            // Enable the system backdrop.
            // Note: Be sure to have "using WinRT;" to support the Window.As<...>() call.
            MicaController.AddSystemBackdropTarget(Impl->Window.as<winrt::Microsoft::UI::Composition::ICompositionSupportsSystemBackdrop>());
            MicaController.SetSystemBackdropConfiguration(Impl->BackdropConfiguration);

            Impl->CurrentController = MicaController;
            return true; // Succeeded.
        }

        return false; // Mica is not supported on this system.
    }

    bool WindowManager::TrySetAcrylicBackdrop() noexcept
    {
        if ( winrt::Microsoft::UI::Composition::SystemBackdrops::DesktopAcrylicController::IsSupported() )
        {
            // Hooking up the policy object.
            Impl->BackdropConfiguration = winrt::Microsoft::UI::Composition::SystemBackdrops::SystemBackdropConfiguration();

            Impl->WindowClosedToken    = Impl->Window.Closed({ this, &WindowManager::Window_Closed });
            Impl->WindowActivatedToken = Impl->Window.Activated({ this, &WindowManager::Window_Activated });

            if ( auto Element = Impl->Window.Content().try_as<FrameworkElement>() )
            {
                Impl->WindowThemeChangedToken = Element.ActualThemeChanged({ this, &WindowManager::Window_ThemeChanged });
            }

            // Initial configuration state.
            Impl->BackdropConfiguration.IsInputActive(true);
            SetConfigurationSourceTheme();

            winrt::Microsoft::UI::Composition::SystemBackdrops::DesktopAcrylicController AcrylicController;

            // Enable the system backdrop.
            // Note: Be sure to have "using WinRT;" to support the Window.As<...>() call.
            AcrylicController.AddSystemBackdropTarget(Impl->Window.as<winrt::Microsoft::UI::Composition::ICompositionSupportsSystemBackdrop>());
            AcrylicController.SetSystemBackdropConfiguration(Impl->BackdropConfiguration);

            Impl->CurrentController = AcrylicController;
            return true; // Succeeded.
        }

        return false; // Acrylic is not supported on this system
    }
} // namespace winrt::Mercatec::WinUIEx::implementation
