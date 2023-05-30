#pragma once

#include "Mercatec.WinUIEx.Enum.hpp"
#include <winrt/Mercatec.WinUIEx.h>

namespace Mercatec::WinUIEx
{
    using winrt::Mercatec::WinUIEx::BackdropType;
} // namespace Mercatec::WinUIEx

//
// clang-format off
//
#define X Mica, MicaAlt, DesktopAcrylic, DefaultColor
MAKE_ENUM_TRAITS(winrt::Mercatec::WinUIEx, BackdropType)
ENUM_BITMASK_OPS(winrt::Mercatec::WinUIEx::BackdropType)

#undef X
//
// clang-format on
//
