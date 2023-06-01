#pragma once

#include "Mercatec.WinUIEx.Exports.Api.hpp"
#include "Internal/Mercatec.WinUIEx.Internal.Icon.hpp"

#include <winrt/Microsoft.UI.Xaml.h>
#include <winrt/Microsoft.UI.Windowing.h>

#include <winrt/Windows.UI.h>
#include <winrt/Windows.UI.Popups.h>
#include <winrt/Windows.Storage.Pickers.h>

#include <Windows.h>

#include <optional>
#include <string_view>

namespace Mercatec::WinUIEx
{
    /// <summary>
    /// WinUI Window Extension Methods
    /// </summary>
    struct MERCATEC_WINUIEX_API WindowExtensions sealed abstract
    {
        /// <summary>
        /// Gets the AppWindow from the handle
        /// </summary>
        /// <param name="window"></param>
        /// <returns></returns>
        static winrt::Microsoft::UI::Windowing::AppWindow GetAppWindow(const winrt::Microsoft::UI::Xaml::Window& Window) noexcept;

        /// <summary>Returns the dots per inch (dpi) value for the associated window.</summary>
        /// <param name = "window">The window you want to get information about.</param>
        /// <returns>The DPI for the window which depends on the <a href = "/windows/desktop/api/windef/ne-windef-dpi_awareness">DPI_AWARENESS</a> of the window. See the Remarks for more information. An invalid <i>hwnd</i> value will result in a return value of 0.</returns>
        /// <remarks>
        /// <para><see href = "https://docs.microsoft.com/windows/win32/api//winuser/nf-winuser-getdpiforwindow">Learn more about this API from docs.microsoft.com</see>.</para>
        /// </remarks>
        static UINT GetDpiForWindow(const winrt::Microsoft::UI::Xaml::Window& Window) noexcept;

        /// <summary>Brings the thread that created the specified window into the foreground and activates the window.</summary>
        /// <param name="window">
        /// <para>The window that should be activated and brought to the foreground.</para>
        /// </param>
        /// <returns>
        /// <para><c>true</c> if the window was brought to the foreground.</para>
        /// <para><c>false</c> if the window was not brought to the foreground.</para>
        /// </returns>
        static bool SetForegroundWindow(const winrt::Microsoft::UI::Xaml::Window& Window) noexcept;

        /// <summary>
        /// Configures whether the window should always be displayed on top of other windows or not
        /// </summary>
        /// <remarks>The presenter must be an overlapped presenter.</remarks>
        /// <exception cref="NotSupportedException">Throw if the AppWindow Presenter isn't an overlapped presenter.</exception>
        /// <param name="window">Window</param>
        /// <param name="enable">Whether to display on top</param>
        static void SetIsAlwaysOnTop(const winrt::Microsoft::UI::Xaml::Window& Window, const bool Enable) noexcept;

        /// <summary>
        /// Gets a value indicating whether this window is on top or not.
        /// </summary>
        /// <param name="window">window</param>
        /// <returns><c>True</c> if the overlapped presenter is on top, otherwise <c>false</c>.</returns>
        static bool GetIsAlwaysOnTop(const winrt::Microsoft::UI::Xaml::Window& Window) noexcept;

        /// <summary>
        /// Enables or disables the ability to resize the window.
        /// </summary>
        /// <remarks>The presenter must be an overlapped presenter.</remarks>
        /// <exception cref="NotSupportedException">Throw if the AppWindow Presenter isn't an overlapped presenter.</exception>
        /// <param name="window"></param>
        /// <param name="enable"></param>
        static void SetIsResizable(const winrt::Microsoft::UI::Xaml::Window& Window, const bool Enable) noexcept;

        /// <summary>
        /// Gets a value indicating whether this resizable or not.
        /// </summary>
        /// <param name="window">window</param>
        /// <returns><c>True</c> if the overlapped presenter is resizeable, otherwise <c>false</c>.</returns>
        static bool GetIsResizable(const winrt::Microsoft::UI::Xaml::Window& Window) noexcept;

        /// <summary>
        /// </summary>
        /// <remarks>The presenter must be an overlapped presenter.</remarks>
        /// <exception cref="NotSupportedException">Throw if the AppWindow Presenter isn't an overlapped presenter.</exception>
        /// <param name="window">window</param>
        /// <param name="enable"><c>true</c> if this window should be maximizable.</param>
        static void SetIsMaximizable(const winrt::Microsoft::UI::Xaml::Window& Window, const bool Enable) noexcept;

        /// <summary>
        /// Gets a value indicating whether this window is maximizeable or not.
        /// </summary>
        /// <param name="window">window</param>
        /// <returns><c>True</c> if the overlapped presenter is on maximizable, otherwise <c>false</c>.</returns>
        static bool GetIsMaximizable(const winrt::Microsoft::UI::Xaml::Window& Window) noexcept;

        /// <summary>
        /// </summary>
        /// <remarks>The presenter must be an overlapped presenter.</remarks>
        /// <exception cref="NotSupportedException">Throw if the AppWindow Presenter isn't an overlapped presenter.</exception>
        /// <param name="window">window</param>
        /// <param name="enable"><c>true</c> if this window should be minimizable.</param>
        static void SetIsMinimizable(const winrt::Microsoft::UI::Xaml::Window& Window, const bool Enable) noexcept;

        /// <summary>
        /// Gets a value indicating whether this window is minimizeable or not.
        /// </summary>
        /// <param name="window">window</param>
        /// <returns><c>True</c> if the overlapped presenter is on minimizable, otherwise <c>false</c>.</returns>
        static bool GetIsMinimizable(const winrt::Microsoft::UI::Xaml::Window& Window) noexcept;

        /// <summary>
        /// Enables or disables showing the window in the task switchers.
        /// </summary>
        /// <param name="window">window</param>
        /// <param name="enable"><c>true</c> if this window should be shown in the task switchers, otherwise <c>false</c>.</param>
        static void SetIsShownInSwitchers(const winrt::Microsoft::UI::Xaml::Window& Window, const bool Enable) noexcept;

        /// <summary>
        /// Sets the icon for the window, using the specified icon ID.
        /// </summary>
        /// <param name="window">Window</param>
        /// <param name="iconId">The ID of the icon.</param>
        static void SetIcon(const winrt::Microsoft::UI::Xaml::Window& Window, const winrt::Microsoft::UI::IconId& IconId) noexcept;

        /// <summary>
        /// Centers the window on the current monitor
        /// </summary>
        /// <param name="window">Window</param>
        /// <param name="width">Width of the window in device independent pixels, or <c>null</c> if keeping the current size</param>
        /// <param name="height">Height of the window in device independent pixels, or <c>null</c> if keeping the current size</param>
        static void CenterOnScreen(const winrt::Microsoft::UI::Xaml::Window& Window, const std::optional<double_t>& Width = std::nullopt, const std::optional<double_t>& Height = std::nullopt) noexcept;

        /// <summary>
        /// Positions and resizes the window
        /// </summary>
        /// <param name="window">Window</param>
        /// <param name="x">Left side of the window</param>
        /// <param name="y">Top side of the window</param>
        /// <param name="width">Width of the window in device independent pixels.</param>
        /// <param name="height">Height of the window in device independent pixels.</param>
        static void MoveAndResize(const winrt::Microsoft::UI::Xaml::Window& Window, const double_t X, const double_t Y, const double_t Width, const double_t Height) noexcept;

        /// <summary>
        /// Positions the window
        /// </summary>
        /// <param name="window">Window</param>
        /// <param name="x">Left side of the window</param>
        /// <param name="y">Top side of the window</param>
        static void Move(const winrt::Microsoft::UI::Xaml::Window& Window, const int32_t X, const int32_t Y) noexcept;

        /// <summary>
        /// Sets the width and height of the window in device-independent pixels.
        /// </summary>
        /// <param name="window">Window to set the size for.</param>
        /// <param name="width">Width of the window in device-independent units.</param>
        /// <param name="height">Height of the window in device-independent units.</param>
        static void SetWindowSize(const winrt::Microsoft::UI::Xaml::Window& Window, const double_t Width, const double_t Height) noexcept;

        /// <summary>
        /// Sets the window presenter kind used.
        /// </summary>
        /// <param name="window"></param>
        /// <param name="kind"></param>
        /// <returns></returns>
        static void SetWindowPresenter(const winrt::Microsoft::UI::Xaml::Window& Window, const winrt::Microsoft::UI::Windowing::AppWindowPresenterKind Kind) noexcept;

        /// <summary>
        /// Gets the native HWND pointer handle for the window
        /// </summary>
        /// <param name="window">The window to return the handle for</param>
        /// <returns>HWND handle</returns>
        static HWND GetWindowHandle(const winrt::Microsoft::UI::Xaml::Window& Window);

        static HRESULT GetWindowHandleFromWindowId(const winrt::Microsoft::UI::WindowId& WindowId, HWND* Result) noexcept;

        /// <summary>
        /// Gets the window HWND handle from a Window ID.
        /// </summary>
        /// <param name="windowId">Window ID to get handle from</param>
        /// <returns>Window HWND handle</returns>
        static HWND GetWindowHandle(const winrt::Microsoft::UI::WindowId& WindowId) noexcept;

        /// <summary>
        /// Gets the AppWindow from an HWND
        /// </summary>
        /// <param name="hwnd"></param>
        /// <returns>AppWindow</returns>
        static winrt::Microsoft::UI::Windowing::AppWindow GetAppWindowFromWindowHandle(HWND Hwnd);

        /// <summary>
        /// Activates the window and displays it in its current size and position.
        /// </summary>
        /// <param name="window">Window</param>
        /// <returns><c>true</c> if the window was previously visible, or <c>false</c> if the window was previously hidden.</returns>
        static bool Show(const winrt::Microsoft::UI::Xaml::Window& Window) noexcept;

        /// <summary>
        /// Hides the window and activates another window.
        /// </summary>
        /// <param name="window">Window</param>
        /// <returns><c>true</c> if the window was previously visible, or <c>false</c> if the window was previously hidden.</returns>
        static bool Hide(const winrt::Microsoft::UI::Xaml::Window& Window) noexcept;

        /// <summary>
        /// Maximizes the specified window.
        /// </summary>
        /// <remarks>The presenter must be an overlapped presenter.</remarks>
        /// <exception cref="NotSupportedException">Throw if the AppWindow Presenter isn't an overlapped presenter.</exception>
        /// <param name="window">Window</param>
        static void Maximize(const winrt::Microsoft::UI::Xaml::Window& Window) noexcept;

        /// <summary>
        /// Minimizes the specified window and activates the next top-level window in the Z order.
        /// </summary>
        /// <remarks>The presenter must be an overlapped presenter.</remarks>
        /// <exception cref="NotSupportedException">Throw if the AppWindow Presenter isn't an overlapped presenter.</exception>
        /// <param name="window">Window</param>
        static void Minimize(const winrt::Microsoft::UI::Xaml::Window& Window) noexcept;

        /// <summary>
        /// Activates and displays the window. If the window is minimized or maximized, the system restores
        /// it to its original size and position.
        /// </summary>
        /// <remarks>The presenter must be an overlapped presenter.</remarks>
        /// <exception cref="NotSupportedException">Throw if the AppWindow Presenter isn't an overlapped presenter.</exception>
        /// <param name="window">Window</param>
        static void Restore(const winrt::Microsoft::UI::Xaml::Window& Window) noexcept;

        /// <summary>
        /// Sets the icon for the window, using the specified icon path.
        /// </summary>
        /// <param name="window">Window</param>
        /// <param name="iconPath">The path of the icon.</param>
        static void SetIcon(const winrt::Microsoft::UI::Xaml::Window& Window, const std::wstring_view IconPath) noexcept;

        /// /// <summary>
        /// Sets the task bar icon to the provided icon
        /// </summary>
        /// <param name="window">Window</param>
        /// <param name="icon">Icon</param>
        static void SetTaskBarIcon(const winrt::Microsoft::UI::Xaml::Window& Window, const Internal::Icon* Icon) noexcept;

        /// <summary>
        /// Gets the background color for the title bar and all its buttons and their states.
        /// </summary>
        /// <param name="window">window</param>
        /// <param name="color">color</param>
        static void SetTitleBarBackgroundColors(const winrt::Microsoft::UI::Xaml::Window& Window, const winrt::Windows::UI::Color& Color) noexcept;

        /// <summary>
        /// Initializes a new instance of the MessageDialog class with the provided window as a parent to display a titled message
        /// dialog that can be used to ask your user simple questions.
        /// </summary>
        /// <param name="window">Parent window</param>
        /// <param name="content">The message displayed to the user.</param>
        /// <param name="title">The title you want displayed on the dialog.</param>
        /// <returns>Message dialog</returns>
        static winrt::Windows::UI::Popups::MessageDialog CreateMessageDialog(const winrt::Microsoft::UI::Xaml::Window& Window, const std::wstring_view Content, const std::wstring_view Title = L"") noexcept;

        /// <summary>
        /// Creates a new instance of a FileOpenPicker with the provided window as a parent.
        /// </summary>
        /// <param name="window">Parent window</param>
        /// <returns>FileOpenPicker</returns>
        static winrt::Windows::Storage::Pickers::FileOpenPicker CreateOpenFilePicker(const winrt::Microsoft::UI::Xaml::Window& Window) noexcept;

        /// <summary>
        /// Creates a new instance of a FileSavePicker with the provided window as a parent.
        /// </summary>
        /// <param name="window">Parent window</param>
        /// <returns>SaveFilePicker</returns>
        static winrt::Windows::Storage::Pickers::FileSavePicker CreateSaveFilePicker(const winrt::Microsoft::UI::Xaml::Window& Window) noexcept;
    };
} // namespace Mercatec::WinUIEx
