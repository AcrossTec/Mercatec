#pragma once

#include <winrt/Windows.Foundation.h>
#include <winrt/Windows.Foundation.Collections.h>

#include "Mercatec.Helpers.Exports.Api.hpp"

// TODO:
//  On awaiting a task with a timeout in C++/WinRT
//  https://devblogs.microsoft.com/oldnewthing/20220506-00/?p=106602

// References:
//  IReference<T>: https://devblogs.microsoft.com/oldnewthing/20221214-00/?p=107589
//  Guid: https://stackoverflow.com/questions/1327157/whats-the-c-version-of-guid-newguid

namespace Mercatec::Helpers::inline Widespread
{
    /// <summary>
    ///     https://devblogs.microsoft.com/oldnewthing/20220504-00/?p=106569
    /// </summary>
    template <typename T>
    inline constexpr T winrt_empty_value() noexcept
    {
        if constexpr ( std::is_base_of_v<winrt::Windows::Foundation::IUnknown, T> )
        {
            return nullptr;
        }
        else
        {
            return {};
        }
    }

    MERCATEC_HELPERS_API winrt::hstring GuidToHString(const winrt::guid& guid) noexcept;
    MERCATEC_HELPERS_API std::string GuidToString(const winrt::guid& guid) noexcept;
} // namespace Mercatec::Helpers::inline Widespread
