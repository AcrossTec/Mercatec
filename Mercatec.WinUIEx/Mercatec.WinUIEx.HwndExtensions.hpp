#pragma once

#include "Mercatec.WinUIEx.Exports.Api.hpp"
#include "Mercatec.WinUIEx.Windows.Win32.hpp"
#include "Mercatec.WinUIEx.Icon.hpp"

#include <winrt/Microsoft.UI.h>

#include <Windows.h>

#include <string_view>
#include <optional>

namespace Mercatec::WinUIEx
{
    /// <summary>
    /// Flags used for ToggleWindowStyle method
    /// </summary>
    enum struct WindowStyle;

    /// <summary>
    /// A set of HWND Helper Methods
    /// </summary>
    class MERCATEC_WINUIEX_API HwndExtensions sealed abstract
    {
    public:
        /// <summary>Returns the dots per inch (dpi) value for the associated window.</summary>
        /// <param name = "hwnd">The window you want to get information about.</param>
        /// <returns>The DPI for the window which depends on the <a href = "/windows/desktop/api/windef/ne-windef-dpi_awareness">DPI_AWARENESS</a> of the window. See the Remarks for more information. An invalid <i>hwnd</i> value will result in a return value of 0.</returns>
        /// <remarks>
        /// <para><see href = "https://docs.microsoft.com/windows/win32/api//winuser/nf-winuser-getdpiforwindow">Learn more about this API from docs.microsoft.com</see>.</para>
        /// </remarks>
        static UINT GetDpiForWindow(HWND hwnd);

        /// <summary>
        /// Gets the DPI for the monitor that the Window is on
        /// </summary>
        /// <param name="hwnd"></param>
        /// <returns></returns>
        static UINT GetDpiForWindowsMonitor(HWND hwnd);

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
        static bool SetForegroundWindow(HWND hWnd);

        /// <summary>Retrieves the window handle to the active window attached to the calling thread's message queue.</summary>
        /// <returns>
        /// <para>The return value is the handle to the active window attached to the calling thread's message queue. Otherwise, the return value is <b>IntPtr.Zero</b>.</para>
        /// </returns>
        /// <remarks>
        /// <para><see href = "https://docs.microsoft.com/windows/win32/api//winuser/nf-winuser-getactivewindow">Learn more about this API from docs.microsoft.com</see>.</para>
        /// </remarks>
        static HWND GetActiveWindow();

        /// <summary>Retrieves a handle to the desktop window. The desktop window covers the entire screen. The desktop window is the area on top of which other windows are painted.</summary>
        /// <returns>
        /// <para>The return value is a handle to the desktop window.</para>
        /// </returns>
        /// <remarks>
        /// <para><see href = "https://docs.microsoft.com/windows/win32/api//winuser/nf-winuser-getdesktopwindow">Learn more about this API from docs.microsoft.com</see>.</para>
        /// </remarks>
        static HWND GetDesktopWindow();

        /// <summary>
        /// Configures whether the window should always be displayed on top of other windows or not
        /// </summary>
        /// <param name="hwnd">Window handle</param>
        /// <param name="enable">Whether to display on top</param>
        static void SetAlwaysOnTop(HWND hwnd, const bool enable);

    private:
        static void SetWindowPosOrThrow(HWND hWnd, HWND hWndInsertAfter, int X, int Y, int cx, int cy, Windows::Win32::UI::WindowsAndMessaging::SetWindowPosFlags uFlags);

    public:
        static HWND UpdateLayeredWindow(HWND hwnd);

        /// <summary>
        /// Centers the window on the current monitor
        /// </summary>
        /// <param name="hwnd">Window handle</param>
        /// <param name="width">Width of the window in device independent pixels, or <c>null</c> if keeping the current size</param>
        /// <param name="height">Height of the window in device independent pixels, or <c>null</c> if keeping the current size</param>
        static void CenterOnScreen(HWND hwnd, std::optional<double> width = std::nullopt, std::optional<double> height = std::nullopt);

        /// <summary>
        /// Sets the icon for the window, using the specified icon ID.
        /// </summary>
        /// <param name="hwnd">Window handle</param>
        /// <param name="iconId">The ID of the icon.</param>

        static void SetIcon(HWND hwnd, const winrt::Microsoft::UI::IconId& iconId);

        /// <summary>
        /// Sets the icon for the window, using the specified icon path.
        /// </summary>
        /// <param name="hwnd">Window handle</param>
        /// <param name="iconPath">The path of the icon.</param>

        static void SetIcon(HWND hwnd, const std::wstring_view iconPath);

        /// <summary>
        /// Positions and resizes the window
        /// </summary>
        /// <param name="hwnd">Window handle</param>
        /// <param name="x">Left side of the window in device independent pixels</param>
        /// <param name="y">Top  side of the window in device independent pixels</param>
        /// <param name="width">Width of the window in device independent pixels, or <c>null</c> if keeping the current size</param>
        /// <param name="height">Height of the window in device independent pixels, or <c>null</c> if keeping the current size</param>

        static void SetWindowPositionAndSize(HWND hwnd, double x, double y, double width, double height);

        /// <summary>
        /// Sets the width and height of the window in device-independent pixels
        /// </summary>
        /// <param name="hwnd"></param>
        /// <param name="width"></param>
        /// <param name="height"></param>

        static void SetWindowSize(HWND hwnd, double width, double height);

        /// <summary>
        /// Sets the task bar icon to the provided icon
        /// </summary>
        /// <param name="hWnd">Window handle</param>
        /// <param name="icon">Icon</param>
        static void SetTaskBarIcon(HWND hWnd, std::optional<Icon> icon);

        /// <summary>
        /// Activates the window and displays it in its current size and position.
        /// </summary>
        /// <param name="hWnd">Window handle</param>
        /// <returns><c>true</c> if the window was previously visible, or <c>false</c> if the window was previously hidden.</returns>

        static bool ShowWindow(HWND hWnd);

        /// <summary>
        /// Hides the window and activates another window.
        /// </summary>
        /// <param name="hWnd">Window handle</param>
        /// <returns><c>true</c> if the window was previously visible, or <c>false</c> if the window was previously hidden.</returns>

        static bool HideWindow(HWND hWnd);

        /// <summary>
        /// Maximizes the specified window.
        /// </summary>
        /// <param name="hWnd">Window handle</param>
        /// <returns><c>true</c> if the window was previously visible, or <c>false</c> if the window was previously hidden.</returns>

        static bool MaximizeWindow(HWND hWnd);

        /// <summary>
        /// Minimizes the specified window and activates the next top-level window in the Z order.
        /// </summary>
        /// <param name="hWnd">Window handle</param>
        /// <returns><c>true</c> if the window was previously visible, or <c>false</c> if the window was previously hidden.</returns>

        static bool MinimizeWindow(HWND hWnd);

        /// <summary>
        /// Activates and displays the window. If the window is minimized or maximized, the system restores
        /// it to its original size and position. An application should specify this flag when restoring a minimized window.
        /// </summary>
        /// <param name="hWnd">Window handle</param>
        /// <returns><c>true</c> if the window was previously visible, or <c>false</c> if the window was previously hidden.</returns>

        static bool RestoreWindow(HWND hWnd);

        /// <summary>
        /// Gets the current window style
        /// </summary>
        /// <param name="hWnd"></param>
        /// <returns></returns>

        static WindowStyle GetWindowStyle(HWND hWnd);

        /// <summary>
        /// Disables or enables the window style
        /// </summary>
        /// <param name="hWnd"></param>
        /// <param name="visible"></param>
        /// <param name="style"></param>

        static void ToggleWindowStyle(HWND hWnd, bool visible, WindowStyle style);

        /// <summary>
        /// Sets the current window style
        /// </summary>
        /// <param name="hWnd">Window handle</param>
        /// <param name="newStyle"></param>

        static void SetWindowStyle(HWND hWnd, WindowStyle newStyle);
    };

    /// <summary>
    /// Flags used for ToggleWindowStyle method
    /// </summary>
    enum struct WindowStyle : int32_t
    {
        /// <summary>The window has a thin-line border.</summary>
        Border = 0x00800000,

        /// <summary>The window has a title bar (includes the BORDER style).</summary>
        Caption = 0x00C00000,

        /// <summary>The window is a child window. A window with this style cannot have a menu bar. This style cannot be used with the POPUP style.</summary>
        Child = 0x40000000,

        /// <summary>Same as the <see cref="Child"/> style.</summary>
        ChildWindow = 0x40000000,

        /// <summary>Excludes the area occupied by child windows when drawing occurs within the parent window. This style is used when creating the parent window.</summary>
        ChildChildren = 0x02000000,

        /// <summary>Clips child windows relative to each other; that is, when a particular child window receives a WM_PAINT message, the CLIPSIBLINGS style clips all other overlapping child windows out of the region of the child window to be updated. If CLIPSIBLINGS is not specified and child windows overlap, it is possible, when drawing within the client area of a child window, to draw within the client area of a neighboring child
        /// window.</summary>
        ClipSiblings = 0x04000000,

        /// <summary>The window is initially disabled. A disabled window cannot receive input from the user. To change this after a window has been created, use the EnableWindow function.</summary>
        Disabled = 0x08000000,

        /// <summary>The window has a border of a style typically used with dialog boxes. A window with this style cannot have a title bar.</summary>
        DlgFrame = 0x00400000,

        /// <summary>The window is the first control of a group of controls. The group consists of this first control and all controls defined after it, up to the next control with the GROUP style. The first control in each group usually has the TABSTOP style so that the user can move from group to group. The user can subsequently change the keyboard focus from one control in the group to the next control in the group by using the direction
        ///    keys.
        /// You can turn this style on and off to change dialog box navigation. To change this style after a window has been created, use the SetWindowLong function.</summary>
        Group = 0x00020000,

        /// <summary>The window has a horizontal scroll bar.</summary>
        HScroll = 0x00100000,

        /// <summary>The window is initially minimized. Same as the MINIMIZE style.</summary>
        Iconic = 0x20000000,

        /// <summary>The window is initially maximized.</summary>
        Maximize = 0x01000000,

        /// <summary>The window has a maximize button. Cannot be combined with the EX_CONTEXTHELP style. The SYSMENU style must also be specified.</summary>
        MaximizeBox = 0x00010000,

        /// <summary>The window is initially minimized. Same as the ICONIC style.</summary>
        Minimize = 0x20000000,

        /// <summary>The window has a minimize button. Cannot be combined with the EX_CONTEXTHELP style. The SYSMENU style must also be specified.</summary>
        MinimizeBox = 0x00020000,

        /// <summary>The window is an overlapped window. An overlapped window has a title bar and a border. Same as the TILED style.</summary>
        Overlapped = 0x00000000,

        /// <summary>The window is an overlapped window. Same as the TILEDWINDOW style.</summary>
        // TODO: OverlappedWindow = (Overlapped | Caption | SysMenu | ThickFrame | MinimizeBox | MaximizeBox),

        // <summary>The window is a pop-up window. This style cannot be used with the CHILD style.</summary>
        // POPUP = 0x80000000,
        // <summary>The window is a pop-up window. The CAPTION and POPUPWINDOW styles must be combined to make the window menu visible.</summary>
        // POPUPWINDOW = (POPUP | BORDER | SYSMENU),
        /// <summary>The window has a sizing border. Same as the THICKFRAME style.</summary>
        SizeBox = 0x00040000,

        /// <summary>The window has a window menu on its title bar. The CAPTION style must also be specified.</summary>
        SysMenu = 0x00080000,

        /// <summary>The window is a control that can receive the keyboard focus when the user presses the TAB key. Pressing the TAB key changes the keyboard focus to the next control with the TABSTOP style.
        /// You can turn this style on and off to change dialog box navigation. To change this style after a window has been created, use the SetWindowLong function. For user-created windows and modeless dialogs to work with tab stops, alter the message loop to call the IsDialogMessage function.</summary>
        TabStop = 0x00010000,

        /// <summary>The window has a sizing border. Same as the SIZEBOX style.</summary>
        ThickFrame = 0x00040000,

        /// <summary>The window is an overlapped window. An overlapped window has a title bar and a border. Same as the OVERLAPPED style.</summary>
        Tiled = 0x00000000,

        /// <summary>The window is an overlapped window. Same as the OVERLAPPEDWINDOW style.</summary>
        TiledWindow = (Overlapped | Caption | SysMenu | ThickFrame | MinimizeBox | MaximizeBox),

        /// <summary>The window is initially visible.
        /// This style can be turned on and off by using the ShowWindow or SetWindowPos function.</summary>
        Visible = 0x10000000,

        /// <summary>The window has a vertical scroll bar.</summary>
        VScroll = 0x00200000,
    };
} // namespace Mercatec::WinUIEx
