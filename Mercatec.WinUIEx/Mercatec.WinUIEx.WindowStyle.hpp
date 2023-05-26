#pragma once

#include <Windows.h>
#include "Mercatec.WinUIEx.Enum.hpp"

namespace Mercatec::WinUIEx
{
    /// <summary>
    /// Flags used for ToggleWindowStyle method
    /// </summary>
    enum struct WindowStyle : DWORD
    {
        /// <summary>The window has a thin-line border.</summary>
        WsBorder = WS_BORDER,

        /// <summary>The window has a title bar (includes the BORDER style).</summary>
        WsCaption = WS_CAPTION,

        /// <summary>The window is a child window. A window with this style cannot have a menu bar. This style cannot be used with the POPUP style.</summary>
        WsChild = WS_CHILD,

        /// <summary>Same as the <see cref="Child"/> style.</summary>
        WsChildWindow = WS_CHILDWINDOW,

        /// <summary>Excludes the area occupied by child windows when drawing occurs within the parent window. This style is used when creating the parent window.</summary>
        WsClipChildren = WS_CLIPCHILDREN,

        /// <summary>Clips child windows relative to each other; that is, when a particular child window receives a WM_PAINT message, the CLIPSIBLINGS style clips all other overlapping child windows out of the region of the child window to be updated. If CLIPSIBLINGS is not specified and child windows overlap, it is possible, when drawing within the client area of a child window, to draw within the client area of a neighboring child
        /// window.</summary>
        WsClipSiblings = WS_CLIPSIBLINGS,

        /// <summary>The window is initially disabled. A disabled window cannot receive input from the user. To change this after a window has been created, use the EnableWindow function.</summary>
        WsDisabled = WS_DISABLED,

        /// <summary>The window has a border of a style typically used with dialog boxes. A window with this style cannot have a title bar.</summary>
        WsDlgFrame = WS_DLGFRAME,

        /// <summary>The window is the first control of a group of controls. The group consists of this first control and all controls defined after it, up to the next control with the GROUP style. The first control in each group usually has the TABSTOP style so that the user can move from group to group. The user can subsequently change the keyboard focus from one control in the group to the next control in the group by using the direction keys.
        /// You can turn this style on and off to change dialog box navigation. To change this style after a window has been created, use the SetWindowLong function.</summary>
        WsGroup = WS_GROUP,

        /// <summary>The window has a horizontal scroll bar.</summary>
        WsHScroll = WS_HSCROLL,

        /// <summary>The window is initially minimized. Same as the MINIMIZE style.</summary>
        WsIconic = WS_ICONIC,

        /// <summary>The window is initially maximized.</summary>
        WsMaximize = WS_MAXIMIZE,

        /// <summary>The window has a maximize button. Cannot be combined with the EX_CONTEXTHELP style. The SYSMENU style must also be specified.</summary>
        WsMaximizeBox = WS_MAXIMIZEBOX,

        /// <summary>The window is initially minimized. Same as the ICONIC style.</summary>
        WsMinimize = WS_MINIMIZE,

        /// <summary>The window has a minimize button. Cannot be combined with the EX_CONTEXTHELP style. The SYSMENU style must also be specified.</summary>
        WsMinimizeBox = WS_MINIMIZEBOX,

        /// <summary>The window is an overlapped window. An overlapped window has a title bar and a border. Same as the TILED style.</summary>
        WsOverlapped = WS_OVERLAPPED,

        /// <summary>The window is an overlapped window. Same as the TILEDWINDOW style.</summary>
        WsOverlappedWindow = WS_OVERLAPPEDWINDOW,

        /// <summary>The window is a pop-up window. This style cannot be used with the CHILD style.</summary>
        WsPopup = WS_POPUP,

        /// <summary>The window is a pop-up window. The CAPTION and POPUPWINDOW styles must be combined to make the window menu visible.</summary>
        WsPopupWindow = WS_POPUPWINDOW,

        /// <summary>The window has a sizing border. Same as the THICKFRAME style.</summary>
        WsSizeBox = WS_SIZEBOX,

        /// <summary>The window has a window menu on its title bar. The CAPTION style must also be specified.</summary>
        WsSysMenu = WS_SYSMENU,

        /// <summary>The window is a control that can receive the keyboard focus when the user presses the TAB key. Pressing the TAB key changes the keyboard focus to the next control with the TABSTOP style.
        /// You can turn this style on and off to change dialog box navigation. To change this style after a window has been created, use the SetWindowLong function. For user-created windows and modeless dialogs to work with tab stops, alter the message loop to call the IsDialogMessage function.</summary>
        WsTabStop = WS_TABSTOP,

        /// <summary>The window has a sizing border. Same as the SIZEBOX style.</summary>
        WsThickFrame = WS_THICKFRAME,

        /// <summary>The window is an overlapped window. An overlapped window has a title bar and a border. Same as the OVERLAPPED style.</summary>
        WsTiled = WS_TILED,

        /// <summary>The window is an overlapped window. Same as the OVERLAPPEDWINDOW style.</summary>
        WsTiledWindow = WS_TILEDWINDOW,

        /// <summary>The window is initially visible.
        /// This style can be turned on and off by using the ShowWindow or SetWindowPos function.</summary>
        WsVisible = WS_VISIBLE,

        /// <summary>The window has a vertical scroll bar.</summary>
        WsVScroll = WS_VSCROLL
    };
} // namespace Mercatec::WinUIEx

//
// clang-format off
//
#define X WsBorder      , WsCaption         , WsChild      , WsChildWindow, WsClipChildren,\
          WsClipSiblings, WsDisabled        , WsDlgFrame   , WsGroup      , WsHScroll     ,\
          WsIconic      , WsMaximize        , WsMaximizeBox, WsMinimize   , WsMinimizeBox ,\
          WsOverlapped  , WsOverlappedWindow, WsPopup      , WsPopupWindow, WsSizeBox     ,\
          WsSysMenu     , WsTabStop         , WsThickFrame , WsTiled      , WsTiledWindow ,\
          WsVisible     , WsVScroll
MAKE_ENUM_TRAITS(Mercatec::WinUIEx, WindowStyle)
#undef X
//
// clang-format on
//

ENUM_BITMASK_OPS(Mercatec::WinUIEx::WindowStyle)
