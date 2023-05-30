#pragma once

#include "Mercatec.WinUIEx.Exports.Api.hpp"
#include "Mercatec.WinUIEx.Messaging.WindowMessageMonitor.hpp"
#include "Mercatec.WinUIEx.Windows.Win32.hpp"
#include "Mercatec.WinUIEx.WindowState.hpp"
#include "Mercatec.WinUIEx.BackdropType.hpp"

#include <winrt/Mercatec.WinUIEx.h>
#include <winrt/Mercatec.WinUIEx.Messaging.h>

#include <winrt/Windows.Foundation.h>
#include <winrt/Windows.Foundation.Collections.h>
#include <winrt/Windows.Graphics.h>
#include <winrt/Windows.Storage.h>

#include <winrt/Microsoft.UI.h>
#include <winrt/Microsoft.UI.Xaml.h>
#include <winrt/Microsoft.UI.Windowing.h>
#include <winrt/Microsoft.UI.Composition.h>
#include <winrt/Microsoft.UI.Composition.SystemBackdrops.h>

#include <any>
#include <map>
#include <memory>
#include <vector>
#include <optional>

#pragma warning(push)
//! Compiler Warning (level 1) C4251
//! 'type' : class 'type1' needs to have dll-interface to be used by clients of class 'type2'
//! https://learn.microsoft.com/en-us/cpp/error-messages/compiler-warnings/compiler-warning-level-1-c4251?view=msvc-170
#pragma warning(disable : 4251)

namespace Mercatec::WinUIEx
{
    /// <summary>
    ///     Manages Window sizes, persists location and size across application sessions, simplifies backdrop configurations etc.
    ///     Use this class instead of <see cref="WindowEx"/> if you just want to extend an existing window with functionality, without having to change the baseclass.
    /// </summary>
    class MERCATEC_WINUIEX_API WindowManager : public std::enable_shared_from_this<WindowManager>
    {
    private:
        struct WindowManagerImpl;
        std::unique_ptr<WindowManagerImpl> Impl;

        static bool TryGetWindowManager(const winrt::Microsoft::UI::Xaml::Window& Window, std::shared_ptr<WindowManager>& Manager);

    public:
        /// <summary>
        ///     Gets (or creates) a window manager for the specific window.
        /// </summary>
        /// <param name="Window"></param>
        /// <returns></returns>
        [[nodiscard]] static std::shared_ptr<WindowManager> Get(const winrt::Microsoft::UI::Xaml::Window& Window);

        WindowManager(const WindowManager&)            = delete;
        WindowManager(WindowManager&&)                 = default;
        WindowManager& operator=(const WindowManager&) = delete;
        WindowManager& operator=(WindowManager&&)      = default;
        ~WindowManager();

    private:
        /// <summary>
        /// Initializes a new instance of the <see cref="WindowManager"/> class.
        /// </summary>
        /// <param name="window"></param>
        WindowManager(const winrt::Microsoft::UI::Xaml::Window& Window);
        WindowManager(const winrt::Microsoft::UI::Xaml::Window& Window, const winrt::com_ptr<Messaging::WindowMessageMonitor>& Monitor);

        void Window_VisibilityChanged(const winrt::IInspectable& Sender, const winrt::Microsoft::UI::Xaml::WindowVisibilityChangedEventArgs& Args);

    public:
        /// <summary>
        ///     Gets a reference to the AppWindow for the app.
        /// </summary>
        winrt::Microsoft::UI::Windowing::AppWindow GetAppWindow() const noexcept;
        __declspec(property(get = GetAppWindow)) winrt::Microsoft::UI::Windowing::AppWindow AppWindow;

        /// <summary>
        ///     Gets or sets the width of the window.
        /// </summary>
        /// <value>The window width in device independent pixels.</value>
        /// <seealso cref="MinWidth"/>
        /// <seealso cref="MaxWidth"/>
        double_t GetWidth() const noexcept;
        void     SetWidth(const double_t Width) noexcept;
        __declspec(property(get = GetWidth, put = SetWidth)) double_t Width;

        /// <summary>
        ///     Gets or sets the height of the window.
        /// </summary>
        /// <value>The window height in device independent pixels.</value>
        /// <seealso cref="MinHeight"/>
        /// <seealso cref="MaxHeight"/>
        double_t GetHeight() const noexcept;
        void     SetHeight(const double_t Height) noexcept;
        __declspec(property(get = GetHeight, put = SetHeight)) double_t Height;

        /// <summary>
        ///     Gets or sets the minimum width of this window.
        /// </summary>
        /// <value>The minimum window width in device independent pixels.</value>
        /// <remarks>A window is currently set to a minimum of 139 pixels.</remarks>
        /// <seealso cref="MaxWidth"/>
        /// <seealso cref="MinHeight"/>
        double_t GetMinWidth() const noexcept;
        void     SetMinWidth(const double_t MinWidth) noexcept;
        __declspec(property(get = GetMinWidth, put = SetMinWidth)) double_t MinWidth;

        /// <summary>
        ///     Gets or sets the minimum height of this window
        /// </summary>
        /// <value>The minimum window height in device independent pixels.</value>
        /// <remarks>A window is currently set to a minimum of 39 pixels.</remarks>
        /// <seealso cref="MaxHeight"/>
        /// <seealso cref="MinWidth"/>
        double_t GetMinHeight() const noexcept;
        void     SetMinHeight(const double_t MinHeight) noexcept;
        __declspec(property(get = GetMinHeight, put = SetMinHeight)) double_t MinHeight;

        /// <summary>
        ///     Gets or sets the maximum width of this window
        /// </summary>
        /// <value>The maximum window width in device independent pixels.</value>
        /// <remarks>The default is 0, which means no limit. If the value is less than <see cref="MinWidth"/>, the <c>MinWidth</c> will also be used as the maximum width.</remarks>
        /// <seealso cref="MaxHeight"/>
        /// <seealso cref="MinWidth"/>
        double_t GetMaxWidth() const noexcept;
        void     SetMaxWidth(const double_t MaxWidth);
        __declspec(property(get = GetMaxWidth, put = SetMaxWidth)) double_t MaxWidth;

        /// <summary>
        ///     Gets or sets the maximum height of this window
        /// </summary>
        /// <value>The maximum window height in device independent pixels.</value>
        /// <remarks>The default is 0, which means no limit. If the value is less than <see cref="MinHeight"/>, the <c>MinHeight</c> will also be used as the maximum height.</remarks>
        /// <seealso cref="MaxWidth"/>
        /// <seealso cref="MinHeight"/>
        double_t GetMaxHeight() const noexcept;
        void     SetMaxHeight(const double_t MaxHeight);
        __declspec(property(get = GetMaxHeight, put = SetMaxHeight)) double_t MaxHeight;

    private:
        void OnWindowMessage(const winrt::IInspectable& Sender, const winrt::Mercatec::WinUIEx::Messaging::WindowMessageEventArgs& Args);

    public:
        /// <summary>
        ///     Gets or sets the current window state.
        /// </summary>
        /// <remarks>
        /// <para>When the <see cref="WindowState"/> property is changed, <see cref="StateChanged"/> is raised.</para>
        /// <note>
        ///     This property only has affect when using the OverlappedPresenter.
        /// </note>
        /// </remarks>
        /// <value>A <see cref="WindowState"/> that determines whether a window is restored, minimized, or maximized.
        /// The default is <see cref="WindowState.Normal"/> (restored).</value>
        /// <seealso cref="WindowManager.StateChanged"/>
        /// <seealso cref="PresenterKind"/>
        WindowState GetWindowState() const noexcept;
        void        SetWindowState(const WindowState& State) noexcept;
        __declspec(property(get = GetWindowState, put = SetWindowState)) WindowState WindowState;

        /// <summary>
        ///     Occurs when the window's <see cref="WindowState"/> property changes.
        /// </summary>
        /// <remarks>
        ///     <note>
        ///         This event only has affect when using the OverlappedPresenter.
        ///     </note>
        /// </remarks>
        /// <seealso cref="WindowManager.WindowState"/>
        /// <seealso cref="PresenterChanged"/>
        winrt::event_token StateChanged(const winrt::Windows::Foundation::EventHandler<Mercatec::WinUIEx::WindowState>& Handler);
        void               StateChanged(const winrt::event_token& Token) noexcept;

        /// <summary>
        ///     Event raised when a windows message is received.
        /// </summary>
        winrt::event_token WindowMessageReceived(const winrt::Windows::Foundation::EventHandler<winrt::Mercatec::WinUIEx::Messaging::WindowMessageEventArgs>& Handler);
        void               WindowMessageReceived(const winrt::event_token& Token) noexcept;

#pragma region Persistence
        /// <remarks>
        ///     The ID must be set before the window activates. The window size and position
        ///     will only be restored if the monitor layout hasn't changed between application settings.
        ///
        ///     The property uses ApplicationData storage, and therefore is currently only functional for
        ///     packaged applications.
        ///
        ///     By default the property uses <see cref="ApplicationData"/> storage, and therefore is currently only functional for
        ///     packaged applications. If you're using an unpackaged application, you must also set the <see cref="PersistenceStorage"/>
        ///     property and manage persisting this across application settings.
        /// </remarks>
        /// <seealso cref="PersistenceStorage"/>
        std::optional<winrt::hstring> GetPersistenceId() const noexcept;
        void                          SetPersistenceId(const std::optional<winrt::hstring>& PersistenceId) noexcept;
        __declspec(property(get = GetPersistenceId, put = SetPersistenceId)) std::optional<winrt::hstring> PersistenceId;

        /// <summary>
        ///     Gets or sets the persistence storage for maintaining window settings across application settings.
        /// </summary>
        /// <remarks>
        ///     For a packaged application, this will be initialized automatically for you, and saved with the application identity using <see cref="ApplicationData"/>.
        ///     However for an unpackaged application, you will need to set this and serialize the property to/from disk between application sessions.
        ///     The provided dictionary is automatically written to when the window closes, and should be initialized before any window with persistence opens.
        /// </remarks>
        /// <seealso cref="PersistenceId"/>
        static std::shared_ptr<std::map<std::wstring, std::any>> PersistenceStorage() noexcept;
        static void                                              PersistenceStorage(const std::shared_ptr<std::map<std::wstring, std::any>>& PersistenceStorage) noexcept;

    private:
        static std::shared_ptr<std::map<std::wstring, std::any>> GetPersistenceStorage(const bool CreateIfMissing) noexcept;

        void LoadPersistence();
        void SavePersistence();
#pragma endregion

        void AppWindow_Changed(const winrt::Microsoft::UI::Windowing::AppWindow& Sender, const winrt::Microsoft::UI::Windowing::AppWindowChangedEventArgs& Args);

    public:
        /// <summary>
        ///     Gets or sets a value indicating whether the default title bar is visible or not.
        /// </summary>
        bool GetIsTitleBarVisible() const noexcept;
        void SetIsTitleBarVisible(const bool IsTitleBarVisible) noexcept;
        __declspec(property(get = GetIsTitleBarVisible, put = SetIsTitleBarVisible)) bool IsTitleBarVisible;

        /// <summary>
        ///     Gets or sets a value indicating whether the minimize button is visible
        /// </summary>
        bool GetIsMinimizable() const noexcept;
        void SetIsMinimizable(const bool IsMinimizable) noexcept;
        __declspec(property(get = GetIsMinimizable, put = SetIsMinimizable)) bool IsMinimizable;

        /// <summary>
        ///     Gets or sets a value indicating whether the maximimze button is visible
        /// </summary>
        bool GetIsMaximizable() const noexcept;
        void SetIsMaximizable(const bool) noexcept;
        __declspec(property(get = GetIsMaximizable, put = SetIsMaximizable)) bool IsMaximizable;

        /// <summary>
        ///     Gets or sets a value indicating whether the window can be resized.
        /// </summary>
        bool GetIsResizable() const noexcept;
        void SetIsResizable(const bool IsResizable) noexcept;
        __declspec(property(get = GetIsResizable, put = SetIsResizable)) bool IsResizable;

        /// <summary>
        ///     Gets or sets a value indicating whether this window is always on top.
        /// </summary>
        bool GetIsAlwaysOnTop() const noexcept;
        void SetIsAlwaysOnTop(const bool IsAlwaysOnTop) noexcept;
        __declspec(property(get = GetIsAlwaysOnTop, put = SetIsAlwaysOnTop)) bool IsAlwaysOnTop;

        /// <summary>
        ///     Gets or sets the presenter kind for the current window
        /// </summary>
        /// <seealso cref="AppWindow.Presenter"/>
        /// <seealso cref="PresenterChanged"/>
        winrt::Microsoft::UI::Windowing::AppWindowPresenterKind GetPresenterKind() const noexcept;
        void                                                    SetPresenterKind(const winrt::Microsoft::UI::Windowing::AppWindowPresenterKind PresenterKind) noexcept;
        __declspec(property(get = GetPresenterKind, put = SetPresenterKind)) winrt::Microsoft::UI::Windowing::AppWindowPresenterKind PresenterKind;

        /// <summary>
        ///     Raised if the window position changes.
        /// </summary>
        winrt::event_token PositionChanged(const winrt::Windows::Foundation::EventHandler<winrt::Windows::Graphics::PointInt32>& Handler);
        void               PositionChanged(const winrt::event_token& Token) noexcept;

        /// <summary>
        ///     Raised if the presenter for the window changes.
        /// </summary>
        winrt::event_token PresenterChanged(const winrt::Windows::Foundation::EventHandler<winrt::Microsoft::UI::Windowing::AppWindowPresenter>& Handler);
        void               PresenterChanged(const winrt::event_token& Token) noexcept;

        /// <summary>
        ///     Raised if the Z order of the window changes.
        /// </summary>
        winrt::event_token ZOrderChanged(const winrt::Windows::Foundation::EventHandler<winrt::Mercatec::WinUIEx::ZOrderInfo>& Handler);
        void               ZOrderChanged(const winrt::event_token& Token) noexcept;

    public:
        /// <summary>
        ///     Gets or sets the system backdrop for the window.
        ///     Note: Windows 10 doesn't support Acrylic, so will fall back to default backdrop.
        /// </summary>
        /// <seealso cref="MicaSystemBackdrop"/>
        /// <seealso cref="AcrylicSystemBackdrop"/>
        winrt::Mercatec::WinUIEx::BackdropType GetBackdropType() const noexcept;
        void                                   SetBackdropType(const winrt::Mercatec::WinUIEx::BackdropType BackdropType) noexcept;
        __declspec(property(get = GetBackdropType, put = SetBackdropType)) winrt::Mercatec::WinUIEx::BackdropType BackdropType;

    private:
        void Window_ThemeChanged(const winrt::Microsoft::UI::Xaml::FrameworkElement& Sender, const winrt::IInspectable& Args);
        void Window_Activated(const winrt::IInspectable& Sender, const winrt::Microsoft::UI::Xaml::WindowActivatedEventArgs& Args);
        void Window_Closed(const winrt::IInspectable& Sender, const winrt::Microsoft::UI::Xaml::WindowEventArgs& Args);

        void SetConfigurationSourceTheme() noexcept;
        bool TrySetMicaBackdrop(const bool UseMicaAlt) noexcept;
        bool TrySetAcrylicBackdrop() noexcept;
    };
} // namespace Mercatec::WinUIEx

#pragma warning(pop)
