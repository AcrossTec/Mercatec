#pragma once

#include "Mercatec.Helpers.Exports.Api.hpp"
#include <winrt/Windows.Foundation.h>

namespace Mercatec::Helpers
{
    struct MERCATEC_HELPERS_API AppDataPaths sealed abstract
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
} // namespace Mercatec::Helpers
