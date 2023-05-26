#pragma once

#include "Mercatec.WinUIEx.Exports.Api.hpp"
#include "Mercatec.WinUIEx.Windows.Win32.hpp"
#include "Mercatec.WinUIEx.WindowStyle.h"
#include "Mercatec.WinUIEx.Icon.hpp"

#include <winrt/Microsoft.UI.h>

#include <Windows.h>

#include <string_view>
#include <optional>

namespace Mercatec::WinUIEx
{
    /// <summary>
    /// A set of HWND Helper Methods
    /// </summary>
    struct MERCATEC_WINUIEX_API HwndExtensions sealed abstract
    {
        /// <summary>Returns the dots per inch (dpi) value for the associated window.</summary>
        /// <param name = "hwnd">The window you want to get information about.</param>
        /// <returns>The DPI for the window which depends on the <a href = "/windows/desktop/api/windef/ne-windef-dpi_awareness">DPI_AWARENESS</a> of the window. See the Remarks for more information. An invalid <i>hwnd</i> value will result in a return value of 0.</returns>
        /// <remarks>
        /// <para><see href = "https://docs.microsoft.com/windows/win32/api//winuser/nf-winuser-getdpiforwindow">Learn more about this API from docs.microsoft.com</see>.</para>
        /// </remarks>
        static UINT GetDpiForWindow(HWND Hwnd) noexcept;

        /// <summary>
        /// Gets the DPI for the monitor that the Window is on
        /// </summary>
        /// <param name="hwnd"></param>
        /// <returns></returns>
        static UINT GetDpiForWindowsMonitor(HWND Hwnd) noexcept;

        /// <summary>Brings the thread that created the specified window into the foreground and activates the window.</summary>
        /// <param name="hWnd">
        /// <para>A handle to the window that should be activated and brought to the foreground.</para>
        /// </param>
        /// <returns>
        /// <para><c>true</c> if the window was brought to the foreground.</para>
        /// <para><c>false</c> if the window was not brought to the foreground.</para>
        /// </returns>
        /// <remarks>
        /// <para><see href = "https://docs.microsoft.com/windows/win32/api//winuser/nf-winuser-setforegroundwindow">Learn more about this API from docs.microsoft.com</see>.</para>
        /// </remarks>
        static bool SetForegroundWindow(HWND Hwnd) noexcept;

        /// <summary>Retrieves the window handle to the active window attached to the calling thread's message queue.</summary>
        /// <returns>
        /// <para>The return value is the handle to the active window attached to the calling thread's message queue. Otherwise, the return value is <b>IntPtr.Zero</b>.</para>
        /// </returns>
        /// <remarks>
        /// <para><see href = "https://docs.microsoft.com/windows/win32/api//winuser/nf-winuser-getactivewindow">Learn more about this API from docs.microsoft.com</see>.</para>
        /// </remarks>
        static HWND GetActiveWindow() noexcept;

        /// <summary>Retrieves a handle to the desktop window. The desktop window covers the entire screen. The desktop window is the area on top of which other windows are painted.</summary>
        /// <returns>
        /// <para>The return value is a handle to the desktop window.</para>
        /// </returns>
        /// <remarks>
        /// <para><see href = "https://docs.microsoft.com/windows/win32/api//winuser/nf-winuser-getdesktopwindow">Learn more about this API from docs.microsoft.com</see>.</para>
        /// </remarks>
        static HWND GetDesktopWindow() noexcept;

        /// <summary>
        /// Configures whether the window should always be displayed on top of other windows or not
        /// </summary>
        /// <param name="hwnd">Window handle</param>
        /// <param name="enable">Whether to display on top</param>
        static void SetAlwaysOnTop(HWND Hwnd, const bool Enable);

        static HWND UpdateLayeredWindow(HWND Hwnd);

        /// <summary>
        /// Centers the window on the current monitor
        /// </summary>
        /// <param name="hwnd">Window handle</param>
        /// <param name="width">Width of the window in device independent pixels, or <c>null</c> if keeping the current size</param>
        /// <param name="height">Height of the window in device independent pixels, or <c>null</c> if keeping the current size</param>
        static void CenterOnScreen(HWND Hwnd, const std::optional<double> Width = std::nullopt, const std::optional<double> Height = std::nullopt);

        /// <summary>
        /// Sets the icon for the window, using the specified icon ID.
        /// </summary>
        /// <param name="hwnd">Window handle</param>
        /// <param name="iconId">The ID of the icon.</param>
        static void SetIcon(HWND Hwnd, const winrt::Microsoft::UI::IconId& IconId) noexcept;

        /// <summary>
        /// Sets the icon for the window, using the specified icon path.
        /// </summary>
        /// <param name="hwnd">Window handle</param>
        /// <param name="iconPath">The path of the icon.</param>
        static void SetIcon(HWND Hwnd, const std::wstring_view IconPath) noexcept;

        /// <summary>
        /// Positions and resizes the window
        /// </summary>
        /// <param name="hwnd">Window handle</param>
        /// <param name="x">Left side of the window in device independent pixels</param>
        /// <param name="y">Top  side of the window in device independent pixels</param>
        /// <param name="width">Width of the window in device independent pixels, or <c>null</c> if keeping the current size</param>
        /// <param name="height">Height of the window in device independent pixels, or <c>null</c> if keeping the current size</param>
        static void SetWindowPositionAndSize(HWND Hwnd, const double_t X, const double_t Y, const double_t Width, const double_t Height);

        /// <summary>
        /// Sets the width and height of the window in device-independent pixels
        /// </summary>
        /// <param name="hwnd"></param>
        /// <param name="width"></param>
        /// <param name="height"></param>
        static void SetWindowSize(HWND Hwnd, const double_t Width, const double_t Height);

        /// <summary>
        /// Sets the task bar icon to the provided icon
        /// </summary>
        /// <param name="hWnd">Window handle</param>
        /// <param name="icon">Icon</param>
        static void SetTaskBarIcon(HWND Hwnd, const std::optional<Icon>& Icon) noexcept;

        /// <summary>
        /// Activates the window and displays it in its current size and position.
        /// </summary>
        /// <param name="hWnd">Window handle</param>
        /// <returns><c>true</c> if the window was previously visible, or <c>false</c> if the window was previously hidden.</returns>
        static bool ShowWindow(HWND Hwnd) noexcept;

        /// <summary>
        /// Hides the window and activates another window.
        /// </summary>
        /// <param name="hWnd">Window handle</param>
        /// <returns><c>true</c> if the window was previously visible, or <c>false</c> if the window was previously hidden.</returns>
        static bool HideWindow(HWND Hwnd) noexcept;

        /// <summary>
        /// Maximizes the specified window.
        /// </summary>
        /// <param name="hWnd">Window handle</param>
        /// <returns><c>true</c> if the window was previously visible, or <c>false</c> if the window was previously hidden.</returns>
        static bool MaximizeWindow(HWND Hwnd) noexcept;

        /// <summary>
        /// Minimizes the specified window and activates the next top-level window in the Z order.
        /// </summary>
        /// <param name="hWnd">Window handle</param>
        /// <returns><c>true</c> if the window was previously visible, or <c>false</c> if the window was previously hidden.</returns>
        static bool MinimizeWindow(HWND Hwnd) noexcept;

        /// <summary>
        /// Activates and displays the window. If the window is minimized or maximized, the system restores
        /// it to its original size and position. An application should specify this flag when restoring a minimized window.
        /// </summary>
        /// <param name="hWnd">Window handle</param>
        /// <returns><c>true</c> if the window was previously visible, or <c>false</c> if the window was previously hidden.</returns>
        static bool RestoreWindow(HWND Hwnd) noexcept;

        /// <summary>
        /// Gets the current window style
        /// </summary>
        /// <param name="hWnd"></param>
        /// <returns></returns>
        static WindowStyle GetWindowStyle(HWND Hwnd) noexcept;

        /// <summary>
        /// Disables or enables the window style
        /// </summary>
        /// <param name="hWnd"></param>
        /// <param name="visible"></param>
        /// <param name="style"></param>
        static void ToggleWindowStyle(HWND Hwnd, const bool Visible, const WindowStyle Style);

        /// <summary>
        /// Sets the current window style
        /// </summary>
        /// <param name="hWnd">Window handle</param>
        /// <param name="newStyle"></param>
        static void SetWindowStyle(HWND Hwnd, const WindowStyle NewStyle);
    };

} // namespace Mercatec::WinUIEx
