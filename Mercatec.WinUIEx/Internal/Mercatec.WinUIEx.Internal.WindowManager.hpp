#pragma once

#include "Mercatec.WinUIEx.WindowManager.hpp"
#include "Mercatec.WinUIEx.WindowExtensions.hpp"
#include "Mercatec.WinUIEx.SystemBackdrop.hpp"

using winrt::Mercatec::WinUIEx::WindowState;
using winrt::Mercatec::WinUIEx::ZOrderInfo;
using winrt::Mercatec::WinUIEx::Messaging::WindowMessageEventArgs;
using winrt::Mercatec::WinUIEx::Messaging::WindowsMessages;
using winrt::Microsoft::UI::Windowing::AppWindowPresenter;
using winrt::Microsoft::UI::Windowing::OverlappedPresenter;
using winrt::Microsoft::UI::Windowing::OverlappedPresenterState;
using winrt::Windows::Foundation::EventHandler;
using winrt::Windows::Graphics::PointInt32;

using std::make_shared;
using std::make_unique;
using std::shared_ptr;
using std::unique_ptr;
using std::weak_ptr;

using namespace winrt::Microsoft::UI::Xaml;
using namespace winrt::Microsoft::UI::Composition;

namespace Mercatec::WinUIEx
{
    /// <summary>
    ///     A deeper dive into winrt::resume_foreground
    ///     https://learn.microsoft.com/en-us/windows/uwp/cpp-and-winrt-apis/concurrency-2#a-deeper-dive-into-winrtresume_foreground
    /// </summary>
    struct WindowsSystemDispatcherQueueHelper
    {
        winrt::Windows::System::DispatcherQueueController DispatcherQueueController;
        void                                              EnsureWindowsSystemDispatcherQueueController();
    };

    struct WindowManager::WindowManagerImpl
    {
        winrt::com_ptr<Messaging::WindowMessageMonitor>            Monitor                   = nullptr;
        winrt::Microsoft::UI::Xaml::Window                         Window                    = nullptr;
        winrt::Microsoft::UI::Windowing::OverlappedPresenter       OverlappedPresenter       = nullptr;
        SystemBackdrops::ISystemBackdropController                 CurrentController         = nullptr;
        SystemBackdrops::SystemBackdropConfiguration               BackdropConfiguration     = nullptr;
        WindowsSystemDispatcherQueueHelper                         DispatcherQueueController = { nullptr };
        winrt::Mercatec::WinUIEx::BackdropType                     BackdropType              = winrt::Mercatec::WinUIEx::BackdropType::DefaultColor;
        bool                                                       IsInitialized             = false; // Set to true on first activation. Used to track persistence restore.
        double_t                                                   MinWidth                  = 136;
        double_t                                                   MinHeight                 = 39;
        double_t                                                   MaxWidth                  = 0;
        double_t                                                   MaxHeight                 = 0;
        winrt::Mercatec::WinUIEx::WindowState                      WindowState               = WindowState::Normal;
        std::optional<winrt::hstring>                              PersistenceId             = std::nullopt;
        bool                                                       RestoringPersistence      = false; // Flag used to avoid WinUI DPI adjustment
        bool                                                       IsTitleBarVisible         = true;
        winrt::event_token                                         AppWindowChangedToken;
        winrt::event_token                                         WindowClosedToken;
        winrt::event_token                                         WindowClosedSavePersistenceToken;
        winrt::event_token                                         WindowActivatedToken;
        winrt::event_token                                         WindowThemeChangedToken;
        winrt::event<EventHandler<Mercatec::WinUIEx::WindowState>> StateChanged;
        winrt::event<EventHandler<WindowMessageEventArgs>>         WindowMessageReceived;
        winrt::event<EventHandler<PointInt32>>                     PositionChanged;
        winrt::event<EventHandler<AppWindowPresenter>>             PresenterChanged;
        winrt::event<EventHandler<ZOrderInfo>>                     ZOrderChanged;
        static std::map<HWND, std::weak_ptr<WindowManager>>        Managers;
        static std::shared_ptr<std::map<std::wstring, std::any>>   PersistenceStorage;
    };
} // namespace Mercatec::WinUIEx
