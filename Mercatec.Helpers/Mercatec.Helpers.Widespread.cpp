#include "pch.h"
#include "Mercatec.Helpers.Widespread.hpp"

namespace Mercatec::Helpers::Widespread
{
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
} // namespace Mercatec::Helpers::Widespread