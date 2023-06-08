#pragma once

#include "Mercatec.Helpers.Exports.Api.hpp"

#include <winrt/Windows.Foundation.h>

namespace Mercatec::Helpers::Applications
{
    MERCATEC_HELPERS_API winrt::IInspectable ResourceLookup(const std::wstring_view Key) noexcept;

    template <typename TResource>
    TResource Lookup(const std::wstring_view Key) noexcept
    {
        return winrt::unbox_value<TResource>(ResourceLookup(Key));
    }

    MERCATEC_HELPERS_API winrt::hstring ApplicationName() noexcept;
    MERCATEC_HELPERS_API winrt::hstring IconPath() noexcept;
} // namespace Mercatec::Helpers::Applications
