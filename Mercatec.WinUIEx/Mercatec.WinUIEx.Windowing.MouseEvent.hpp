#pragma once

#include "Mercatec.WinUIEx.Enum.hpp"
#include <winrt/Mercatec.WinUIEx.h>

namespace Mercatec::WinUIEx
{
    using winrt::Mercatec::WinUIEx::MouseEvent;
}

//
// clang-format off
//
#define X MouseMove        , IconRightMouseDown, IconLeftMouseDown     ,\
          IconRightMouseUp , IconLeftMouseUp   , IconMiddleMouseDown   ,\
          IconMiddleMouseUp, IconDoubleClick   , BalloonToolTipClicked
MAKE_ENUM_TRAITS(winrt::Mercatec::WinUIEx, MouseEvent)
ENUM_BITMASK_OPS(winrt::Mercatec::WinUIEx::MouseEvent)
#undef X
//
// clang-format on
//
