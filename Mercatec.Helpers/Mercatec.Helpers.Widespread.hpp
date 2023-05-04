#pragma once

#include <winrt/Windows.Foundation.h>
#include <winrt/Windows.Foundation.Collections.h>

// TODO:
//  On awaiting a task with a timeout in C++/WinRT
//  https://devblogs.microsoft.com/oldnewthing/20220506-00/?p=106602

// References:
//  IReference<T>: https://devblogs.microsoft.com/oldnewthing/20221214-00/?p=107589
//  Guid: https://stackoverflow.com/questions/1327157/whats-the-c-version-of-guid-newguid

namespace Mercatec::Helpers
{
    /// <summary>
    ///     https://devblogs.microsoft.com/oldnewthing/20220504-00/?p=106569
    /// </summary>
    template <typename T>
    constexpr T winrt_empty_value() noexcept
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

    winrt::hstring GuidToHString(const winrt::guid& guid) noexcept
    {
        wchar_t guid_string[37];

        swprintf( //
          guid_string,
          sizeof(guid_string) / sizeof(guid_string[0]),
          L"%08x-%04x-%04x-%02x%02x-%02x%02x%02x%02x%02x%02x",
          guid.Data1,
          guid.Data2,
          guid.Data3,
          guid.Data4[0],
          guid.Data4[1],
          guid.Data4[2],
          guid.Data4[3],
          guid.Data4[4],
          guid.Data4[5],
          guid.Data4[6],
          guid.Data4[7]
        );

        // remove when VC++7.1 is no longer supported
        guid_string[sizeof(guid_string) / sizeof(guid_string[0]) - 1] = L'\0';
        return guid_string;
    }

    std::string GuidToString(const winrt::guid& guid) noexcept
    {
        return winrt::to_string(GuidToHString(guid));
    }
} // namespace Mercatec::Helpers
