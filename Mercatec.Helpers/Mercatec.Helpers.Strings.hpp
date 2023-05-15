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

namespace Mercatec::Helpers::inline Strings
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

    inline constexpr std::string_view StringViewOrDefault(const std::string_view text, const std::string_view _default = "")
    {
        if ( text.empty() )
        {
            return _default;
        }

        return text;
    }

    inline constexpr std::string_view StringViewOrDefault(const char* text, const std::string_view _default = "")
    {
        if ( text == nullptr || *text == '\0' )
        {
            return _default;
        }

        return text;
    }

    inline constexpr std::wstring_view StringViewOrDefault(const std::wstring_view text, const std::wstring_view _default = L"")
    {
        if ( text.empty() )
        {
            return _default;
        }

        return text;
    }

    inline constexpr std::wstring_view StringViewOrDefault(const wchar_t* text, const std::wstring_view _default = L"")
    {
        if ( text == nullptr || *text == L'\0' )
        {
            return _default;
        }

        return text;
    }

} // namespace Mercatec::Helpers::inline Strings
