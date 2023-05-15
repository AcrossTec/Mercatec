#pragma once

#include <Mercatec.Helpers.Widespread.hpp>
#include <winrt/Mercatec.Models.h>

//! References:
//!     https://fmt.dev/latest/api.html
//!     https://fmt.dev/latest/api.html#format-api
//!     https://wgml.pl/blog/formatting-user-defined-types-fmt.html
//!     https://www.cppstories.com/2022/custom-stdformat-cpp20/
//!     https://www.cppstories.com/2020/02/extra-format-cpp20.html/#user-defined-types
//!     https://www.modernescpp.com/index.php/extend-std-format-in-c-20-for-user-defined-types
//!     https://quuxplusone.github.io/blog/2023/04/21/format-part-1/
//!     https://quuxplusone.github.io/blog/2023/04/22/format-part-2/
//!     https://quuxplusone.github.io/blog/2023/04/23/format-part-3/

template <>
struct std::formatter<winrt::Mercatec::Models::UserAccount, wchar_t>
{
    constexpr auto parse(std::wformat_parse_context& context)
    {
        return context.begin();
    }

    template <typename FormatContext>
    auto format(const winrt::Mercatec::Models::UserAccount& user_account, FormatContext& format_context)
    {
        return std::format_to( //
          format_context.out(),
          L"{{ UserId: {}, UserName: {}, Password: {} }}",
          ::Mercatec::Helpers::GuidToHString(user_account.UserId()),
          user_account.UserName(),
          user_account.Password()
        );
    }
};

namespace winrt
{
    inline hstring to_hstring(const winrt::Mercatec::Models::UserAccount& user_account)
    {
        return hstring{ std::format(L"{}", user_account) };
    }
} // namespace winrt

#ifndef WINRT_LEAN_AND_MEAN
inline std::wostream& operator<<(std::wostream& stream, const winrt::Mercatec::Models::UserAccount& user_account)
{
    return stream << std::format(L"{}", user_account);
}
#endif
