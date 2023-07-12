#pragma once

#include "Mercatec.WinUIEx.Exports.Api.hpp"
#include <winrt/Windows.Foundation.h>

namespace Mercatec::WinUIEx::inline Applications
{
    MERCATEC_WINUIEX_API winrt::Windows::Foundation::IInspectable ResourceLookup(const std::wstring_view Key) noexcept;

    template <typename TResource>
    TResource Lookup(const std::wstring_view Key) noexcept
    {
        return winrt::unbox_value<TResource>(ResourceLookup(Key));
    }

    MERCATEC_WINUIEX_API winrt::hstring ApplicationName() noexcept;
    MERCATEC_WINUIEX_API winrt::hstring IconPath() noexcept;
} // namespace Mercatec::WinUIEx::inline Applications
