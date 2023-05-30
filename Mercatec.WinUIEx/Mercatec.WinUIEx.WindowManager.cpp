#include "pch.h"
#include "Internal/Mercatec.WinUIEx.Internal.WindowManager.hpp"

namespace Mercatec::WinUIEx
{
    bool WindowManager::TryGetWindowManager(const Window& Window, shared_ptr<WindowManager>& Manager)
    {
        if ( Window == nullptr )
        {
            throw winrt::hresult_invalid_argument(L"Argument Null Exception: Window");
        }

        HWND Handle = WindowExtensions::GetWindowHandle(Window);

        if ( auto It = WindowManagerImpl::Managers.find(Handle); Manager = It->second.lock() )
        {
            return true;
        }

        Manager = nullptr;
        return false;
    }

    [[nodiscard]] shared_ptr<WindowManager> WindowManager::Get(const Window& Window)
    {
        shared_ptr<WindowManager> Manager;

        if ( TryGetWindowManager(Window, Manager) )
        {
            return Manager;
        }

        return make_shared<WindowManager>(Window);
    }

    WindowManager::~WindowManager()
    {
        HWND Handle = WindowExtensions::GetWindowHandle(Impl->Window);

        if ( WindowManagerImpl::Managers.contains(Handle) )
        {
            WindowManagerImpl::Managers.erase(Handle);
        }

        AppWindow.Changed(Impl->AppWindowChangedToken);
        Impl->Window.Closed(Impl->WindowClosedSavePersistenceToken);
    }

    WindowManager::WindowManager(const Window& Window)
      : WindowManager(Window, winrt::make_self<Messaging::WindowMessageMonitor>(Window))
    {
    }

    WindowManager::WindowManager(const Window& Window, const winrt::com_ptr<Messaging::WindowMessageMonitor>& Monitor)
      : Impl{ make_unique<WindowManagerImpl>() }
    {
        if ( Window == nullptr )
        {
            throw winrt::hresult_invalid_argument(L"Argument Null Exception: Window");
        }

        if ( shared_ptr<WindowManager> OldMonitor; TryGetWindowManager(Window, OldMonitor) )
        {
            throw winrt::hresult_error(winrt::impl::error_fail, L"Invalid Operation Exception: Only one window manager can be attached to a Window.");
        }

        Impl->Monitor = Monitor;
        Impl->Monitor->WindowMessageReceived({ this, &WindowManager::OnWindowMessage });

        Impl->Window                           = Window;
        Impl->WindowClosedSavePersistenceToken = Impl->Window.Closed([](const auto&, const auto&) { SavePersistence(); });
        Impl->Window.VisibilityChanged({ this, &WindowManager::Window_VisibilityChanged });

        Impl->AppWindowChangedToken = AppWindow.Changed({ this, &WindowManager::AppWindow_Changed });

        WindowManagerImpl::Managers[WindowExtensions::GetWindowHandle(Window)] = weak_from_this();

        Impl->OverlappedPresenter = winrt::unbox_value_or<OverlappedPresenter>(AppWindow.Presenter(), OverlappedPresenter::Create());

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
        this->BackdropType = BackdropType::DesktopAcrylic;
    }

    void WindowManager::Window_VisibilityChanged(const winrt::IInspectable& Sender, const WindowVisibilityChangedEventArgs& Args)
    {
        if ( Args.Visible() and Impl->CurrentController == nullptr )
        {
            Impl->DispatcherQueueController.EnsureWindowsSystemDispatcherQueueController();
            this->BackdropType = BackdropType::DesktopAcrylic;
        }
    }

    winrt::Microsoft::UI::Windowing::AppWindow WindowManager::GetAppWindow() const noexcept
    {
        return Impl->Window.AppWindow();
    }

    double_t WindowManager::GetWidth() const noexcept
    {
        return AppWindow.Size().Width / (WindowExtensions::GetDpiForWindow(Impl->Window) / 96.0);
    }

    void WindowManager::SetWidth(const double_t Width) noexcept
    {
        WindowExtensions::SetWindowSize(Impl->Window, Width, Height);
    }

    double_t WindowManager::GetHeight() const noexcept
    {
        return AppWindow.Size().Height / (WindowExtensions::GetDpiForWindow(Impl->Window) / 96.0);
    }

    void WindowManager::SetHeight(const double_t Height) noexcept
    {
        WindowExtensions::SetWindowSize(Impl->Window, Width, Height);
    }

    double_t WindowManager::GetMinWidth() const noexcept
    {
        return Impl->MinWidth;
    }

    void WindowManager::SetMinWidth(const double_t MinWidth) noexcept
    {
        Impl->MinWidth = MinWidth;

        if ( Width < MinWidth )
        {
            Width = MinWidth;
        }
    }

    double_t WindowManager::GetMinHeight() const noexcept
    {
        return Impl->MinHeight;
    }

    void WindowManager::SetMinHeight(const double_t MinHeight) noexcept
    {
        Impl->MinHeight = MinHeight;

        if ( Height < MinHeight )
        {
            Height = MinHeight;
        }
    }

    double_t WindowManager::GetMaxWidth() const noexcept
    {
        return Impl->MaxWidth;
    }

    void WindowManager::SetMaxWidth(const double_t MaxWidth)
    {
        if ( MaxWidth <= 0 )
        {
            throw winrt::hresult_out_of_bounds(L"Argument Out Of Range Exception: MaxWidth");
        }

        Impl->MaxWidth = MaxWidth;

        if ( Width > MaxWidth )
        {
            Width = MaxWidth;
        }
    }

    double_t WindowManager::GetMaxHeight() const noexcept
    {
        return Impl->MaxHeight;
    }

    void WindowManager::SetMaxHeight(const double_t MaxHeight)
    {
        if ( MaxHeight <= 0 )
        {
            throw winrt::hresult_out_of_bounds(L"Argument Out Of Range Exception: MaxHeight");
        }

        Impl->MaxHeight = MaxHeight;

        if ( Height > MaxHeight )
        {
            Height = MaxHeight;
        }
    }

    void WindowManager::OnWindowMessage(const winrt::IInspectable& Sender, const WindowMessageEventArgs& Args)
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
                      this->BackdropType = BackdropType::DesktopAcrylic;
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
                    if ( not ::isnan(MaxWidth) and MaxWidth > 0 )
                    {
                        // If minwidth < maxwidth, minwidth will take presedence
                        Rect2->ptMaxSize.x = LONG(std::min(std::max(MaxWidth, MinWidth) * (CurrentDpi / 96.0), double_t(Rect2->ptMaxSize.x)));
                    }

                    if ( not ::isnan(MaxHeight) and MaxHeight > 0 )
                    {
                        // If minheight < maxheight, minheight will take presedence
                        Rect2->ptMaxSize.y = LONG(std::min(std::max(MaxHeight, MinHeight) * (CurrentDpi / 96.0), double_t(Rect2->ptMaxSize.y)));
                    }
                }
                else
                {
                    // Restrict min-size
                    Rect2->ptMinTrackSize.x = LONG(std::max(MinWidth * (CurrentDpi / 96.0), double_t(Rect2->ptMinTrackSize.x)));
                    Rect2->ptMinTrackSize.y = LONG(std::max(MinHeight * (CurrentDpi / 96.0), double_t(Rect2->ptMinTrackSize.y)));

                    // Restrict max-size
                    if ( not ::isnan(MaxWidth) and MaxWidth > 0 )
                    {
                        // If minwidth < maxwidth, minwidth will take presedence
                        Rect2->ptMaxTrackSize.x = LONG(std::min(std::max(MaxWidth, MinWidth) * (CurrentDpi / 96.0), double_t(Rect2->ptMaxTrackSize.x)));
                    }

                    if ( not ::isnan(MaxHeight) and MaxHeight > 0 )
                    {
                        // If minheight < maxheight, minheight will take presedence
                        Rect2->ptMaxTrackSize.y = LONG(std::min(std::max(MaxHeight, MinHeight) * (CurrentDpi / 96.0), double_t(Rect2->ptMaxTrackSize.y)));
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

    WindowState WindowManager::GetWindowState() const noexcept
    {
        return Impl->WindowState;
    }

    void WindowManager::SetWindowState(const Mercatec::WinUIEx::WindowState& State) noexcept
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

    winrt::event_token WindowManager::StateChanged(const winrt::Windows::Foundation::EventHandler<Mercatec::WinUIEx::WindowState>& Handler)
    {
        return Impl->StateChanged.add(Handler);
    }

    void WindowManager::StateChanged(const winrt::event_token& Token) noexcept
    {
        Impl->StateChanged.remove(Token);
    }

    winrt::event_token WindowManager::WindowMessageReceived(const winrt::Windows::Foundation::EventHandler<WindowMessageEventArgs>& Handler)
    {
        return Impl->WindowMessageReceived.add(Handler);
    }

    void WindowManager::WindowMessageReceived(const winrt::event_token& Token) noexcept
    {
        Impl->WindowMessageReceived.remove(Token);
    }

    std::optional<winrt::hstring> WindowManager::GetPersistenceId() const noexcept
    {
        return Impl->PersistenceId;
    }

    void WindowManager::SetPersistenceId(const std::optional<winrt::hstring>& PersistenceId) noexcept
    {
        Impl->PersistenceId = PersistenceId;
    }

    std::shared_ptr<std::map<std::wstring, std::any>> WindowManager::PersistenceStorage() noexcept
    {
        return WindowManagerImpl::PersistenceStorage;
    }

    void WindowManager::PersistenceStorage(const std::shared_ptr<std::map<std::wstring, std::any>>& PersistenceStorage) noexcept
    {
        WindowManagerImpl::PersistenceStorage = PersistenceStorage;
    }

    std::shared_ptr<std::map<std::wstring, std::any>> WindowManager::GetPersistenceStorage(const bool CreateIfMissing)
    {
        if ( PersistenceStorage() != nullptr )
            return PersistenceStorage();

        try
        {
            //!
            //! TODO: Implementar: winrt::Windows::Storage::ApplicationData::Current().LocalSettings()
            //!

            auto Container = winrt::Windows::Storage::ApplicationData:: //
                             Current()
                               .LocalSettings()
                               .Containers()
                               .TryLookup(L"WinUIEx");

            if ( Container == nullptr and CreateIfMissing )
            {
                Container = winrt::Windows::Storage::ApplicationData:: //
                            Current()
                              .LocalSettings()
                              .CreateContainer( //
                                L"WinUIEx",
                                winrt::Windows::Storage::ApplicationDataCreateDisposition::Always
                              );
            }

            auto Result = make_shared<std::map<std::wstring, std::any>>();

            for ( const auto& Value : Container.Values() )
            {
                Result->insert_or_assign(Value.Key().c_str(), Value.Value());
            }

            return Result;
        }
        catch ( ... )
        {
        }

        return nullptr;
    }

    void WindowManager::LoadPersistence()
    {
    }

    void WindowManager::SavePersistence()
    {
    }

    void WindowManager::AppWindow_Changed(const winrt::Microsoft::UI::Windowing::AppWindow& Sender, const winrt::Microsoft::UI::Windowing::AppWindowChangedEventArgs& Args)
    {
    }

    bool WindowManager::GetIsTitleBarVisible() const noexcept
    {
        return false;
    }

    void WindowManager::SetIsTitleBarVisible(const bool IsTitleBarVisible) noexcept
    {
    }

    bool WindowManager::GetIsMinimizable() const noexcept
    {
        return false;
    }

    void WindowManager::SetIsMinimizable(const bool IsMinimizable) noexcept
    {
    }

    bool WindowManager::GetIsMaximizable() const noexcept
    {
        return false;
    }

    void WindowManager::SetIsMaximizable(const bool) noexcept
    {
    }

    bool WindowManager::GetIsResizable() const noexcept
    {
        return false;
    }

    void WindowManager::SetIsResizable(const bool IsResizable) noexcept
    {
    }

    bool WindowManager::GetIsAlwaysOnTop() const noexcept
    {
        return false;
    }

    void WindowManager::SetIsAlwaysOnTop(const bool IsAlwaysOnTop) noexcept
    {
    }

    winrt::Microsoft::UI::Windowing::AppWindowPresenterKind WindowManager::GetPresenterKind() const noexcept
    {
        return winrt::Microsoft::UI::Windowing::AppWindowPresenterKind();
    }

    void WindowManager::SetPresenterKind(const winrt::Microsoft::UI::Windowing::AppWindowPresenterKind PresenterKind) noexcept
    {
    }

    winrt::event_token WindowManager::PositionChanged(const winrt::Windows::Foundation::EventHandler<winrt::Windows::Graphics::PointInt32>& Handler)
    {
        return winrt::event_token();
    }

    void WindowManager::PositionChanged(const winrt::event_token& Token) noexcept
    {
    }

    winrt::event_token WindowManager::PresenterChanged(const winrt::Windows::Foundation::EventHandler<winrt::Microsoft::UI::Windowing::AppWindowPresenter>& Handler)
    {
        return winrt::event_token();
    }

    void WindowManager::PresenterChanged(const winrt::event_token& Token) noexcept
    {
    }

    winrt::event_token WindowManager::ZOrderChanged(const winrt::Windows::Foundation::EventHandler<winrt::Mercatec::WinUIEx::ZOrderInfo>& Handler)
    {
        return winrt::event_token();
    }

    void WindowManager::ZOrderChanged(const winrt::event_token& Token) noexcept
    {
    }
} // namespace Mercatec::WinUIEx
