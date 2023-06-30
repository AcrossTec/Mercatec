#pragma once

#include "Mercatec.WinUIEx.Exports.Api.hpp"
#include <winrt/Windows.Foundation.h>

namespace Mercatec::WinUIEx
{
    struct MERCATEC_WINUIEX_API AppDataPaths sealed abstract
    {
        [[nodiscard]] static winrt::hstring Cookies() noexcept;
        [[nodiscard]] static winrt::hstring Desktop() noexcept;
        [[nodiscard]] static winrt::hstring Documents() noexcept;
        [[nodiscard]] static winrt::hstring Favorites() noexcept;
        [[nodiscard]] static winrt::hstring History() noexcept;
        [[nodiscard]] static winrt::hstring InternetCache() noexcept;
        [[nodiscard]] static winrt::hstring LocalAppData() noexcept;
        [[nodiscard]] static winrt::hstring ProgramData() noexcept;
        [[nodiscard]] static winrt::hstring RoamingAppData() noexcept;
    };
} // namespace Mercatec::WinUIEx
