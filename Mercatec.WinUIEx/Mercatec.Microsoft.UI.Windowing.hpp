#pragma once

#include <winrt/Microsoft.UI.Windowing.h>
#include "Mercatec.WinUIEx.Enum.hpp"

//
// clang-format off
//

#define X Default, CompactOverlay, FullScreen, Overlapped
MAKE_ENUM_TRAITS(winrt::Microsoft::UI::Windowing, AppWindowPresenterKind)
#undef X

ENUM_BITMASK_OPS(winrt::Microsoft::UI::Windowing::AppWindowPresenterKind)

//
// clang-format on
//
