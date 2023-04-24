#pragma once

#include <string>
#include <string_view>
#include <sstream>
#include <span>
#include <spanstream>
#include <format>
#include <array>
#include <cstring>
#include <cuchar>
#include <cwchar>

namespace Mercatec::Helpers
{
    template <typename ValueType>
    inline constexpr const ValueType Empty = std::declval<ValueType>();

    // clang-format off
    template<> inline constexpr const     char* Empty<char>     = "";
    template<> inline constexpr const  wchar_t* Empty<wchar_t>  = L"";
    template<> inline constexpr const  char8_t* Empty<char8_t>  = u8"";
    template<> inline constexpr const char16_t* Empty<char16_t> = u"";
    template<> inline constexpr const char32_t* Empty<char32_t> = U"";
    // clang-format on

} // namespace Mercatec::Helpers
