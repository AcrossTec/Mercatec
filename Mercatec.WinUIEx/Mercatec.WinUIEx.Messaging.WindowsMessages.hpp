#pragma once

#include <Windows.h>
#include "Mercatec.WinUIEx.Enum.hpp"
#include <winrt/Mercatec.WinUIEx.Messaging.h>

namespace Mercatec::WinUIEx::Messaging
{
    // Good list of message numbers: https://wiki.winehq.org/List_Of_Windows_Messages

    /// <summary>
    /// This enum defines the windows messages we respond to.
    /// See more on Windows messages <a href="https://docs.microsoft.com/en-us/windows/win32/learnwin32/window-messages">here</a>
    /// </summary>
    using winrt::Mercatec::WinUIEx::Messaging::WindowsMessages;
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
MAKE_ENUM_TRAITS(winrt::Mercatec::WinUIEx::Messaging, WindowsMessages)
ENUM_BITMASK_OPS(winrt::Mercatec::WinUIEx::Messaging::WindowsMessages)
#undef X
//
// clang-format on
//
