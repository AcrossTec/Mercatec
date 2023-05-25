#pragma once

#include <Windows.h>
#include "Mercatec.WinUIEx.Enum.hpp"

namespace Mercatec::WinUIEx::Messaging
{
    // Good list of message numbers: https://wiki.winehq.org/List_Of_Windows_Messages

    /// <summary>
    /// This enum defines the windows messages we respond to.
    /// See more on Windows messages <a href="https://docs.microsoft.com/en-us/windows/win32/learnwin32/window-messages">here</a>
    /// </summary>
    enum struct WindowsMessages : UINT
    {
        /// <summary>
        /// Sent after a window has been moved.
        /// See <a href="https://docs.microsoft.com/en-us/windows/win32/winmsg/wm-move">WM_MOVE message</a>.
        /// </summary>
        WmMove = WM_MOVE,

        /// <summary>
        /// Sent as a signal that a window or an application should terminate.
        /// </summary>
        /// <seealso href="https://docs.microsoft.com/en-us/windows/win32/winmsg/wm-close">Microsoft Docs</seealso>
        WmClose = WM_CLOSE,

        /// <summary>
        /// A window receives this message when the user chooses a command from the Window menu (formerly known as the
        /// system or control menu) or when the user chooses the maximize button, minimize button, restore button, or
        /// close button.
        /// </summary>
        /// <seealso href="https://docs.microsoft.com/en-us/windows/win32/menurc/wm-syscommand">Microsoft Docs</seealso>
        WmSysCommand = WM_SYSCOMMAND,

        /// <summary>
        /// Sent to a window if the mouse causes the cursor to move within a window and mouse input is not captured.
        /// </summary>
        /// <seealso href="https://docs.microsoft.com/en-us/windows/win32/menurc/wm-setcursor">Microsoft Docs</seealso>
        WmSetCursor = WM_SETCURSOR,

        /// <summary>
        /// Posted to a window when the cursor is moved within the nonclient area of the window. This message is posted
        /// to the window that contains the cursor. If a window has captured the mouse, this message is not posted.
        /// </summary>
        /// <seealso href="https://docs.microsoft.com/en-us/windows/win32/inputdev/wm-ncmousemove">Microsoft Docs</seealso>
        WmNcMouseMove = WM_NCMOUSEMOVE,

        /// <summary>
        /// Sent to both the window being activated and the window being deactivated. If the windows use the same input queue,
        /// the message is sent synchronously, first to the window procedure of the top-level window being deactivated, then
        /// to the window procedure of the top-level window being activated. If the windows use different input queues, the
        /// message is sent asynchronously, so the window is activated immediately.
        /// </summary>
        /// <seealso href="https://docs.microsoft.com/en-us/windows/win32/inputdev/wm-activate">Microsoft Docs</seealso>
        WmActivate = WM_ACTIVATE,

        /// <summary>
        /// Sent when a window belonging to a different application than the active window is about to be activated. The
        /// message is sent to the application whose window is being activated and to the application whose window is
        /// being deactivated.
        /// </summary>
        /// <seealso href="https://docs.microsoft.com/en-us/windows/win32/winmsg/wm-activateapp">Microsoft Docs</seealso>
        WmActivateApp = WM_ACTIVATEAPP,

        /// <summary>
        /// Sent to a window when the window is about to be hidden or shown.
        /// </summary>
        /// <seealso href="https://docs.microsoft.com/en-us/windows/win32/winmsg/wm-showwindow"/>
        WmShowWindow = WM_SHOWWINDOW,

        /// <summary>
        /// Sent to a window whose size, position, or place in the Z order is about to change as a result of a call to
        /// the SetWindowPos function or another window-management function.
        /// </summary>
        /// <seealso href="https://docs.microsoft.com/en-us/windows/win32/winmsg/wm-windowposchanging">Microsoft Docs</seealso>
        WmWindowPosChanging = WM_WINDOWPOSCHANGING,

        /// <summary>
        /// Sent to a window whose size, position, or place in the Z order has changed as a result of a call to the SetWindowPos function or another window-management function.
        /// </summary>
        /// <seealso href="https://docs.microsoft.com/en-us/windows/win32/winmsg/wm-windowposchanged">Microsoft Docs</seealso>
        WmWindowPosChanged = WM_WINDOWPOSCHANGED,

        /// <summary>
        /// Sets the text of a window.
        /// </summary>
        /// <seealso href="https://docs.microsoft.com/en-us/windows/win32/winmsg/wm-settext">Microsoft Docs</seealso>
        WmSetText = WM_SETTEXT,

        /// <summary>
        /// Copies the text that corresponds to a window into a buffer provided by the caller.
        /// </summary>
        /// <seealso href="https://docs.microsoft.com/en-us/windows/win32/winmsg/wm-gettext">Microsoft Docs</seealso>
        WmGetText = WM_GETTEXT,

        /// <summary>
        /// Determines the length, in characters, of the text associated with a window.
        /// </summary>
        /// <seealso href="https://docs.microsoft.com/en-us/windows/win32/winmsg/wm-gettextlength">Microsoft Docs</seealso>
        WmGetTextLength = WM_GETTEXTLENGTH,

        /// <summary>
        /// Sent to a window when its nonclient area needs to be changed to indicate an active or inactive state.
        /// </summary>
        /// <seealso href="https://docs.microsoft.com/en-us/windows/win32/winmsg/wm-ncactivate">Microsoft Docs</seealso>
        WmNcActivate = WM_NCACTIVATE,

        /// <summary>
        /// Sent to the window that is losing the mouse capture.
        /// </summary>
        /// <seealso href="https://docs.microsoft.com/en-us/windows/win32/inputdev/wm-capturechanged">Microsoft Docs</seealso>
        WmCaptureChanged = WM_CAPTURECHANGED,

        /// <summary>
        /// Posted to a window when the cursor leaves the nonclient area of the window specified in a prior call to TrackMouseEvent.
        /// </summary>
        /// <seealso href="https://docs.microsoft.com/en-us/windows/win32/inputdev/wm-ncmouseleave">Microsoft Docs</seealso>
        WmNcMouseLeave = WM_NCMOUSELEAVE,

        /// <summary>
        /// Sent after a window has been moved.
        /// See <a href="https://docs.microsoft.com/en-us/windows/win32/winmsg/wm-moving">WM_MOVING message</a>.
        /// </summary>
        WmMoving = WM_MOVING,

        /// <summary>
        /// Sent to a window after its size has changed.
        /// See <a href="https://docs.microsoft.com/en-us/windows/win32/winmsg/wm-size">WM_SIZE message</a>.
        /// </summary>
        WmSize = WM_SIZE,

        /// <summary>
        /// Sent to a window that the user is resizing. By processing this message, an application can monitor the size and position of the drag rectangle and, if needed, change its size or position.
        /// See <a href="https://docs.microsoft.com/en-us/windows/win32/winmsg/wm-sizing">WM_SIZING message</a>.
        /// </summary>
        WmSizing = WM_SIZING,

        /// <summary>
        /// Sent to a window when the size or position of the window is about to change. An application can use this message to override the window's default maximized size and position, or its default minimum or maximum tracking size.
        /// See <a href="https://docs.microsoft.com/en-us/windows/win32/winmsg/wm-getminmaxinfo">WM_GETMINMAXINFO message</a>.
        /// </summary>
        WmGetMinMaxInfo = WM_GETMINMAXINFO,

        /// <summary>
        /// Sent when an application changes the enabled state of a window. It is sent to the window whose enabled state is changing. This message is sent before the <a href="https://docs.microsoft.com/en-us/windows/win32/api/winuser/nf-winuser-enablewindow">EnableWindow</a> function returns, but after the enabled state (WS_DISABLED style bit) of the window has changed.
        /// See <a href="https://docs.microsoft.com/en-us/windows/win32/winmsg/wm-enable">WM_ENABLE message</a>.
        /// </summary>
        WmEnable = WM_ENABLE,

        /// <summary>
        /// Sent one time to a window after it enters the moving or sizing modal loop. The window enters the moving or sizing modal loop when the user clicks the window's title bar or sizing border, or when the window passes the WM_SYSCOMMAND message to the DefWindowProc function and the wParam parameter of the message specifies the SC_MOVE or SC_SIZE value.
        /// See <a href="https://docs.microsoft.com/en-us/windows/win32/winmsg/wm-entersizemove">WM_ENTERSIZEMOVE message</a>.
        /// </summary>
        WmEnterSizeMove = WM_ENTERSIZEMOVE,

        /// <summary>
        /// ent one time to a window, after it has exited the moving or sizing modal loop. The window enters the moving or sizing modal loop when the user clicks the window's title bar or sizing border, or when the window passes the WM_SYSCOMMAND message to the DefWindowProc function and the wParam parameter of the message specifies the SC_MOVE or SC_SIZE value.
        /// See <a href="https://docs.microsoft.com/en-us/windows/win32/winmsg/wm-exitsizemove">WM_EXITSIZEMOVE message</a>.
        /// </summary>
        WmExitSizeMove = WM_EXITSIZEMOVE,

        /// <summary>
        /// Notifies a window that the user clicked the right mouse button (right-clicked) in the window.
        /// See <a href="https://docs.microsoft.com/en-us/windows/win32/menurc/wm-contextmenu">WM_CONTEXTMENU message</a>
        ///
        /// In case of a notify icon:
        /// If a user selects a notify icon's shortcut menu with the keyboard, the Shell now sends the associated application a WM_CONTEXTMENU message. Earlier versions send WM_RBUTTONDOWN and WM_RBUTTONUP messages.
        /// See <a href="https://docs.microsoft.com/en-us/windows/win32/api/shellapi/nf-shellapi-shell_notifyiconw">Shell_NotifyIcon function</a>
        /// </summary>
        WmContextMenu = WM_CONTEXTMENU,

        /// <summary>
        /// Posted to a window when the cursor moves.
        /// If the mouse is not captured, the message is posted to the window that contains the cursor.
        /// Otherwise, the message is posted to the window that has captured the mouse.
        ///
        /// See <a href="https://docs.microsoft.com/en-us/windows/win32/inputdev/wm-mousemove">WM_MOUSEMOVE message</a>
        /// </summary>
        WmMouseMove = WM_MOUSEMOVE,

        /// <summary>
        /// Posted when the user presses the left mouse button while the cursor is in the client area of a window.
        /// If the mouse is not captured, the message is posted to the window beneath the cursor.
        /// Otherwise, the message is posted to the window that has captured the mouse.
        ///
        /// See <a href="https://docs.microsoft.com/en-us/windows/win32/inputdev/wm-lbuttondown">WM_LBUTTONDOWN message</a>
        /// </summary>
        WmLButtonDown = WM_LBUTTONDOWN,

        /// <summary>
        /// Posted when the user releases the left mouse button while the cursor is in the client area of a window.
        /// If the mouse is not captured, the message is posted to the window beneath the cursor.
        /// Otherwise, the message is posted to the window that has captured the mouse.
        ///
        /// See <a href="https://docs.microsoft.com/en-us/windows/win32/inputdev/wm-lbuttonup">WM_LBUTTONUP message</a>
        /// </summary>
        WmLButtonUp = WM_LBUTTONUP,

        /// <summary>
        /// Posted when the user double-clicks the left mouse button while the cursor is in the client area of a window.
        /// If the mouse is not captured, the message is posted to the window beneath the cursor.
        /// Otherwise, the message is posted to the window that has captured the mouse.
        ///
        /// See <a href="https://docs.microsoft.com/en-us/windows/win32/inputdev/wm-lbuttondblclk">WM_LBUTTONDBLCLK message</a>
        /// </summary>
        WmLButtonDblClk = WM_LBUTTONDBLCLK,

        /// <summary>
        /// Posted when the user presses the right mouse button while the cursor is in the client area of a window.
        /// If the mouse is not captured, the message is posted to the window beneath the cursor.
        /// Otherwise, the message is posted to the window that has captured the mouse.
        ///
        /// See <a href="https://docs.microsoft.com/en-us/windows/win32/inputdev/wm-rbuttondown">WM_RBUTTONDOWN message</a>
        /// </summary>
        WmRButtonDown = WM_RBUTTONDOWN,

        /// <summary>
        /// Posted when the user releases the right mouse button while the cursor is in the client area of a window.
        /// If the mouse is not captured, the message is posted to the window beneath the cursor.
        /// Otherwise, the message is posted to the window that has captured the mouse.
        ///
        /// See <a href="https://docs.microsoft.com/en-us/windows/win32/inputdev/wm-rbuttonup">WM_RBUTTONUP message</a>
        /// </summary>
        WmRButtonUp = WM_RBUTTONUP,

        /// <summary>
        /// Posted when the user double-clicks the right mouse button while the cursor is in the client area of a window.
        /// If the mouse is not captured, the message is posted to the window beneath the cursor.
        /// Otherwise, the message is posted to the window that has captured the mouse.
        ///
        /// See <a href="https://docs.microsoft.com/en-us/windows/win32/inputdev/wm-rbuttondblclk">WM_RBUTTONDBLCLK message</a>
        /// </summary>
        WmRButtonDblClk = WM_RBUTTONDBLCLK,

        /// <summary>
        /// Posted when the user presses the middle mouse button while the cursor is in the client area of a window.
        /// If the mouse is not captured, the message is posted to the window beneath the cursor.
        /// Otherwise, the message is posted to the window that has captured the mouse.
        ///
        /// See <a href="https://docs.microsoft.com/en-us/windows/win32/inputdev/wm-mbuttondown">WM_MBUTTONDOWN message</a>
        /// </summary>
        WmMButtonDown = WM_MBUTTONDOWN,

        /// <summary>
        /// Posted when the user releases the middle mouse button while the cursor is in the client area of a window.
        /// If the mouse is not captured, the message is posted to the window beneath the cursor.
        /// Otherwise, the message is posted to the window that has captured the mouse.
        ///
        /// See <a href="https://docs.microsoft.com/en-us/windows/win32/inputdev/wm-mbuttonup">WM_MBUTTONUP message</a>
        /// </summary>
        WmMButtonUp = WM_MBUTTONUP,

        /// <summary>
        /// Posted when the user double-clicks the middle mouse button while the cursor is in the client area of a window.
        /// If the mouse is not captured, the message is posted to the window beneath the cursor.
        /// Otherwise, the message is posted to the window that has captured the mouse.
        ///
        /// See <a href="https://docs.microsoft.com/en-us/windows/win32/inputdev/wm-mbuttondblclk">WM_MBUTTONDBLCLK message</a>
        /// </summary>
        WmMButtonDblClk = WM_MBUTTONDBLCLK,

        /// <summary>
        /// Used to define private messages for use by private window classes, usually of the form WM_USER+x, where x is an integer value.
        /// </summary>
        WmUser = WM_USER,

        WmGetIcon = WM_GETICON,

        /// <summary>
        /// Associates a new large or small icon with a window. The system displays the large icon in the ALT+TAB dialog box, and the small icon in the window caption.
        /// </summary>
        WmSetIcon = WM_SETICON,

        /// <summary>
        /// Sent when the effective dots per inch (dpi) for a window has changed.
        /// See <a href="https://docs.microsoft.com/en-us/windows/win32/hidpi/wm-dpichanged">WM_DPICHANGED message</a>.
        /// </summary>
        WmDpiChanged = WM_DPICHANGED,

        /// <summary>
        /// The WM_DISPLAYCHANGE message is sent to all windows when the display resolution has changed.
        /// See <a href="https://docs.microsoft.com/en-us/windows/win32/gdi/wm-displaychange">WM_DISPLAYCHANGE message</a>.
        /// </summary>
        WmDisplayChange = WM_DISPLAYCHANGE,

        /// <summary>
        /// A message that is sent to all top-level windows when the SystemParametersInfo function changes a system-wide setting or when policy settings have changed.
        /// <a href="https://docs.microsoft.com/en-us/windows/win32/winmsg/wm-settingchange">WM_SETTINGCHANGE message</a>
        /// </summary>
        WmSettingChange = WM_SETTINGCHANGE,

        /// <summary>
        /// Broadcast to every window following a theme change event. Examples of theme change events are the activation of a theme,
        /// the deactivation of a theme, or a transition from one theme to another.
        /// See <a href="https://docs.microsoft.com/en-us/windows/win32/winmsg/wm-themechanged">WM_THEMECHANGE message</a>
        /// </summary>
        WmThemeChanged = WM_THEMECHANGED,

        /// <summary>
        /// This message is only sent when using NOTIFYICON_VERSION_4, the Shell now sends the associated application an NIN_SELECT notification.
        /// Send when a notify icon is activated with mouse or ENTER key.
        /// Earlier versions send WM_RBUTTONDOWN and WM_RBUTTONUP messages.
        /// </summary>
        NinSelect = NIN_SELECT,

        /// <summary>
        /// This message is only sent when using NOTIFYICON_VERSION_4, the Shell now sends the associated application an NIN_SELECT notification.
        /// Send when a notify icon is activated with SPACEBAR or ENTER key.
        /// Earlier versions send WM_RBUTTONDOWN and WM_RBUTTONUP messages.
        /// </summary>
        NinKeySelect = NIN_KEYSELECT,

        /// <summary>
        /// Sent when the balloon is shown (balloons are queued).
        /// </summary>
        NinBalloonShow = NIN_BALLOONSHOW,

        /// <summary>
        /// Sent when the balloon disappears. For example, when the icon is deleted.
        /// This message is not sent if the balloon is dismissed because of a timeout or if the user clicks the mouse.
        ///
        /// As of Windows 7, NIN_BALLOONHIDE is also sent when a notification with the NIIF_RESPECT_QUIET_TIME flag set attempts to display during quiet time (a user's first hour on a new computer).
        /// In that case, the balloon is never displayed at all.
        /// </summary>
        NinBalloonHide = NIN_BALLOONHIDE,

        /// <summary>
        /// Sent when the balloon is dismissed because of a timeout.
        /// </summary>
        NinBalloonTimeout = NIN_BALLOONTIMEOUT,

        /// <summary>
        /// Sent when the balloon is dismissed because the user clicked the mouse.
        /// </summary>
        NinBalloonUserClick = NIN_BALLOONUSERCLICK,

        /// <summary>
        /// Sent when the user hovers the cursor over an icon to indicate that the richer pop-up UI should be used in place of a standard textual tooltip.
        /// </summary>
        NinPopupOpen = NIN_POPUPOPEN,

        /// <summary>
        /// Sent when a cursor no longer hovers over an icon to indicate that the rich pop-up UI should be closed.
        /// </summary>
        NinPopupClose = NIN_POPUPCLOSE,
    };

} // namespace Mercatec::WinUIEx::Messaging

//
// clang-format off
//
#define X WmMove           , WmClose            , WmSysCommand   , WmSetCursor        , WmNcMouseMove     ,\
          WmActivate       , WmActivateApp      , WmShowWindow   , WmWindowPosChanging, WmWindowPosChanged,\
          WmSetText        , WmGetText          , WmGetTextLength, WmNcActivate       , WmCaptureChanged  ,\
          WmNcMouseLeave   , WmMoving           , WmSize         , WmSizing           , WmGetMinMaxInfo   ,\
          WmEnable         , WmEnterSizeMove    , WmExitSizeMove , WmContextMenu      , WmMouseMove       ,\
          WmLButtonDown    , WmLButtonUp        , WmLButtonDblClk, WmRButtonDown      , WmRButtonUp       ,\
          WmRButtonDblClk  , WmMButtonDown      , WmMButtonUp    , WmMButtonDblClk    , WmUser            ,\
          WmGetIcon        , WmSetIcon          , WmDpiChanged   , WmDisplayChange    , WmSettingChange   ,\
          WmThemeChanged   , NinSelect          , NinKeySelect   , NinBalloonShow     , NinBalloonHide    ,\
          NinBalloonTimeout, NinBalloonUserClick, NinPopupOpen   , NinPopupClose

MAKE_ENUM_TRAITS(Mercatec::WinUIEx::Messaging, WindowsMessages)
#undef X
//
// clang-format on
//
