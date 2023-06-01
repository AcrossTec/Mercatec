#pragma once

#include "WindowEx.g.h"

#include <winrt/Microsoft.UI.Xaml.h>
#include <winrt/Microsoft.UI.Xaml.Controls.h>
#include <winrt/Microsoft.UI.Windowing.h>

namespace winrt::Mercatec::WinUIEx::implementation
{
    /// <summary>
    ///     A custom WinUI Window with more convenience methods.
    /// </summary>
    struct WindowEx : WindowExT<WindowEx>
    {
    public:
        template <typename T>
        using EventHandler = Windows::Foundation::EventHandler<T>;

        /// <summary>
        ///     Initializes a new instance of the <see cref="WindowEx"/> class.
        /// </summary>
        WindowEx();

        /// <summary>
        ///     Shows a message dialog.
        /// </summary>
        /// <param name="Content">The message displayed to the user.</param>
        /// <param name="Title">The title to display on the dialog, if any.</param>
        /// <returns>An object that represents the asynchronous operation.</returns>
        Windows::Foundation::IAsyncAction ShowMessageDialogAsync(const std::wstring_view Content);
        Windows::Foundation::IAsyncAction ShowMessageDialogAsync(const std::wstring_view Content, const std::wstring_view Title);

        /// <summary>
        ///     Shows a message dialog.
        /// </summary>
        /// <param name="Content">The message displayed to the user.</param>
        /// <param name="Commands">an array of commands that appear in the command bar of the message dialog. These commands makes the dialog actionable.</param>
        /// <param name="DefaultCommandIndex">The index of the command you want to use as the default. This is the command that fires by default when users press the ENTER key.</param>
        /// <param name="CancelCommandIndex">The index of the command you want to use as the cancel command. This is the command that fires when users press the ESC key.</param>
        /// <param name="Title">The title to display on the dialog, if any.</param>
        /// <returns>An object that represents the asynchronous operation.</returns>
        Windows::Foundation::IAsyncOperation<Windows::UI::Popups::IUICommand> ShowMessageDialogAsync(const std::wstring_view Content, const IVector<Windows::UI::Popups::IUICommand>& Commands);
        Windows::Foundation::IAsyncOperation<Windows::UI::Popups::IUICommand> ShowMessageDialogAsync(const std::wstring_view Content, const IVector<Windows::UI::Popups::IUICommand>& Commands, const std::wstring_view Title);
        Windows::Foundation::IAsyncOperation<Windows::UI::Popups::IUICommand> ShowMessageDialogAsync(const std::wstring_view Content, const IVector<Windows::UI::Popups::IUICommand>& Commands, const uint32_t DefaultCommandIndex);
        Windows::Foundation::IAsyncOperation<Windows::UI::Popups::IUICommand> ShowMessageDialogAsync(const std::wstring_view Content, const IVector<Windows::UI::Popups::IUICommand>& Commands, const uint32_t DefaultCommandIndex, const std::wstring_view Title);
        Windows::Foundation::IAsyncOperation<Windows::UI::Popups::IUICommand> ShowMessageDialogAsync(const std::wstring_view Content, const IVector<Windows::UI::Popups::IUICommand>& Commands, const uint32_t DefaultCommandIndex, const uint32_t CancelCommandIndex);
        Windows::Foundation::IAsyncOperation<Windows::UI::Popups::IUICommand> ShowMessageDialogAsync(const std::wstring_view Content, const IVector<Windows::UI::Popups::IUICommand>& Commands, const uint32_t DefaultCommandIndex, const uint32_t CancelCommandIndex, const std::wstring_view Title);

        /*
            /// <summary>
            ///     Gets a reference to the AppWindow for the app.
            ///     Kept here for binary compatibility.
            /// </summary>
            Microsoft::UI::Windowing::AppWindow AppWindow() const noexcept;
        */

        /// <summary>
        ///     Brings the window to the front.
        /// </summary>
        /// <returns></returns>
        bool BringToFront() const noexcept;

        /// <summary>
        ///     Gets or sets the task bar icon.
        /// </summary>
        Icon TaskBarIcon() const noexcept;
        void TaskBarIcon(const Icon& Value) noexcept;

        /*
            /// <summary>
            ///     Gets or sets the window title.
            ///     Old Workaround for https://github.com/microsoft/microsoft-ui-xaml/issues/3689.
            ///     Needs to stay for binary compat
            /// </summary>
            hstring Title() const noexcept;
            void    Title(const std::wstring_view Value) noexcept;
        */

        /// <summary>
        ///     Gets or sets a unique ID used for saving and restoring window size and position across sessions.
        /// </summary>
        /// <remarks>
        ///     The ID must be set before the window activates.
        ///     The window size and position will only be restored if the monitor layout hasn't changed between application settings.
        ///     The property uses ApplicationData storage, and therefore is currently only functional for packaged applications.
        /// </remarks>
        hstring PersistenceId() const noexcept;
        void    PersistenceId(const std::wstring_view Value) noexcept;

        /// <summary>
        ///     Gets or sets the Window content.
        /// </summary>
        /// <value>The window content.</value>
        IInspectable WindowContent() const noexcept;
        void         WindowContent(const IInspectable& Content) noexcept;

        /// <summary>
        ///     Gets or sets a value indicating whether the default title bar is visible or not.
        /// </summary>
        bool IsTitleBarVisible() const noexcept;
        void IsTitleBarVisible(const bool Value) noexcept;

        /// <summary>
        ///     Gets or sets a value indicating whether the minimize button is visible.
        /// </summary>
        bool IsMinimizable() const noexcept;
        void IsMinimizable(const bool Value) noexcept;

        /// <summary>
        ///     Gets or sets a value indicating whether the maximimze button is visible.
        /// </summary>
        bool IsMaximizable() const noexcept;
        void IsMaximizable(const bool Value) noexcept;

        /// <summary>
        ///     Gets or sets a value indicating whether the window can be resized.
        /// </summary>
        bool IsResizable() const noexcept;
        void IsResizable(const bool Value) noexcept;

        /// <summary>
        ///     Gets or sets a value indicating whether the window is modal or not.
        /// </summary>
        bool IsModal() const noexcept;
        void IsModal(const bool Value) noexcept;

        /// <summary>
        ///     Gets or sets a value indicating whether this window is shown in task switchers.
        /// </summary>
        bool IsShownInSwitchers() const noexcept;
        void IsShownInSwitchers(const bool Value) noexcept;

        /// <summary>
        ///     Gets or sets a value indicating whether this window is always on top.
        /// </summary>
        bool IsAlwaysOnTop() const noexcept;
        void IsAlwaysOnTop(const bool Value) noexcept;

        /// <summary>
        ///     Gets the presenter for the current window.
        /// </summary>
        /// <seealso cref="PresenterKind"/>
        /// <seealso cref="PresenterChanged"/>
        Microsoft::UI::Windowing::AppWindowPresenter Presenter() const noexcept;

        /// <summary>
        ///     Gets or sets the presenter kind for the current window
        /// </summary>
        /// <seealso cref="Presenter"/>
        /// <seealso cref="PresenterChanged"/>
        Microsoft::UI::Windowing::AppWindowPresenterKind PresenterKind() const noexcept;
        void                                             PresenterKind(const Microsoft::UI ::Windowing::AppWindowPresenterKind Value) noexcept;

        /// <summary>
        ///     Gets or sets the width of the window.
        /// </summary>
        double_t Width() const noexcept;
        void     Width(const double_t Value) noexcept;

        /// <summary>
        ///     Gets or sets the height of the window.
        /// </summary>
        double_t Height() const noexcept;
        void     Height(const double_t Value) noexcept;

        /// <summary>
        ///     Gets or sets the minimum width of this window.
        /// </summary>
        /// <value>The minimum window width in device independent pixels.</value>
        /// <remarks>A window is currently set to a minimum of 139 pixels.</remarks>
        /// <seealso cref="MaxWidth"/>
        /// <seealso cref="MinHeight"/>
        double_t MinWidth() const noexcept;
        void     MinWidth(const double_t Value) noexcept;

        /// <summary>
        ///     Gets or sets the minimum height of this window.
        /// </summary>
        /// <value>The minimum window height in device independent pixels.</value>
        /// <remarks>A window is currently set to a minimum of 39 pixels.</remarks>
        /// <seealso cref="MaxHeight"/>
        /// <seealso cref="MinWidth"/>
        double_t MinHeight() const noexcept;
        void     MinHeight(const double_t Value) noexcept;

        /// <summary>
        ///     Gets or sets the maximum width of this window.
        /// </summary>
        /// <value>The maximum window width in device independent pixels.</value>
        /// <remarks>The default is 0, which means no limit. If the value is less than <see cref="MinWidth"/>, the <c>MinWidth</c> will also be used as the maximum width.</remarks>
        /// <seealso cref="MaxHeight"/>
        /// <seealso cref="MinWidth"/>
        double_t MaxWidth() const noexcept;
        void     MaxWidth(const double_t Value) noexcept;

        /// <summary>
        ///     Gets or sets the maximum height of this window.
        /// </summary>
        /// <value>The maximum window height in device independent pixels.</value>
        /// <remarks>The default is 0, which means no limit. If the value is less than <see cref="MinHeight"/>, the <c>MinHeight</c> will also be used as the maximum height.</remarks>
        /// <seealso cref="MaxWidth"/>
        /// <seealso cref="MinHeight"/>
        double_t MaxHeight() const noexcept;
        void     MaxHeight(const double_t Value) noexcept;

        /// <summary>
        ///     Gets or sets the system backdrop for the window.
        ///     Note: Windows 10 doesn't support these, so will fall back to default backdrop.
        /// </summary>
        /// <seealso cref="MicaSystemBackdrop"/>
        /// <seealso cref="AcrylicSystemBackdrop"/>
        Mercatec::WinUIEx::BackdropType BackdropType() const noexcept;
        void                            BackdropType(const Mercatec::WinUIEx::BackdropType Value) noexcept;

#pragma region Window events and corresponding virtual methods

        /// <summary>
        ///     Raised if the window position changes.
        /// </summary>
        /// <seealso cref="Microsoft.UI.Windowing.AppWindow.Position"/>
        event_token PositionChanged(const Windows::Foundation::EventHandler<Windows::Graphics::PointInt32>& Handler);
        void        PositionChanged(const event_token& Token) noexcept;

        /// <summary>
        ///     Called when the window position changed.
        /// </summary>
        /// <param name="position">The current position of the window in screen coordinates.</param>
        /// <seealso cref="Microsoft.UI.Windowing.AppWindow.Position"/>
        void OnPositionChanged(const Windows::Graphics::PointInt32& Position);

        /// <summary>
        ///     Raised if the presenter for the window changed.
        /// </summary>
        /// <seealso cref="Presenter"/>
        /// <seealso cref="PresenterKind"/>
        event_token PresenterChanged(const Windows::Foundation::EventHandler<Microsoft::UI::Windowing::AppWindowPresenter>& Handler);
        void        PresenterChanged(const event_token& Token) noexcept;

        /// <summary>
        ///     Called when the presenter for the window changed.
        /// </summary>
        /// <param name="newPresenter">The new presenter.</param>
        /// <seealso cref="Presenter"/>
        /// <seealso cref="PresenterKind"/>
        /// <seealso cref="Microsoft.UI.Windowing.AppWindow.Presenter"/>
        void OnPresenterChanged(const Microsoft::UI::Windowing::AppWindowPresenter& NewPresenter);

        /// <summary>
        ///     Raised if the Z order of the window changed.
        /// </summary>
        event_token ZOrderChanged(const Windows::Foundation::EventHandler<ZOrderInfo>& Handler);
        void        ZOrderChanged(const event_token& Token) noexcept;

        /// <summary>
        /// Called when the Z order of the window changed.
        /// </summary>
        /// <param name="info">Object describing the current new ZOrder of the window</param>
        void OnZOrderChanged(const ZOrderInfo& Info);

        /// <summary>
        ///     Called when the size of the window changes.
        /// </summary>
        /// <param name="newSize">The new size of the window in device independent units.</param>
        /// <returns>True if the resize event should be marked handled.</returns>
        /// <remarks>
        /// While this event is equivalent to the <see cref="Window.SizeChanged"/> event,
        /// the units provided here are in device independent units and not screen pixels.
        /// </remarks>
        bool OnSizeChanged(const Windows::Foundation::Size& NewSize);

        /// <summary>
        ///     Called when the actual theme changes
        /// </summary>
        /// <param name="theme">The new theme</param>
        /// <seealso cref="FrameworkElement.ActualTheme"/>
        /// <seealso cref="ActualTheme"/>
        void OnThemeChanged(const Microsoft::UI::Xaml::ElementTheme Theme);

        /// <summary>
        ///     The actual theme for the window
        /// </summary>
        /// <seealso cref="OnThemeChanged(ElementTheme)"/>
        Microsoft::UI::Xaml::ElementTheme ActualTheme() const noexcept;

#pragma endregion Window events and corresponding virtual methods

    private:
        void RequestedThemePropertyChanged(const Microsoft::UI::Xaml::DependencyObject& Sender, const Microsoft::UI::Xaml::DependencyProperty& Property);
        void OnSizeChanged(const Microsoft::UI::Xaml::WindowSizeChangedEventArgs& Args);

    private:
        Icon                                                              m_TaskBarIcon;
        int64_t                                                           m_PropChangedCallbackId;
        Microsoft::UI::Xaml::Controls::Grid                               m_TitleBarArea;
        Microsoft::UI::Xaml::Controls::Image                              m_IconArea;
        Microsoft::UI::Xaml::Controls::ContentControl                     m_TitleBarContainer;
        Microsoft::UI::Xaml::Controls::ContentControl                     m_WindowArea;
        Mercatec::WinUIEx::WindowManager                                  m_Manager;
        event<EventHandler<Windows::Graphics::PointInt32>>                m_PositionChanged;
        event<EventHandler<Microsoft::UI::Windowing::AppWindowPresenter>> m_PresenterChanged;
        event<EventHandler<ZOrderInfo>>                                   m_ZOrderChanged;
    };
} // namespace winrt::Mercatec::WinUIEx::implementation

namespace winrt::Mercatec::WinUIEx::factory_implementation
{
    struct WindowEx : WindowExT<WindowEx, implementation::WindowEx>
    {
    };
} // namespace winrt::Mercatec::WinUIEx::factory_implementation
