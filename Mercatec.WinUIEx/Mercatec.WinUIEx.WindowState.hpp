#pragma once

#include "Mercatec.WinUIEx.Enum.hpp"
#include <winrt/Mercatec.WinUIEx.h>

namespace Mercatec::WinUIEx
{
    using winrt::Mercatec::WinUIEx::WindowState;
} // namespace Mercatec::WinUIEx

//
// clang-format off
//
#define X Normal, Minimized, Maximized
MAKE_ENUM_TRAITS(winrt::Mercatec::WinUIEx, WindowState)
ENUM_BITMASK_OPS(winrt::Mercatec::WinUIEx::WindowState)

#undef X
//
// clang-format on
//
