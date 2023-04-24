#pragma once

#include <cinttypes>
#include <winrt/Windows.Foundation.h>

namespace Mercatec::Models
{
    struct User
    {
        uint64_t       UserId;
        winrt::hstring UserName;
        winrt::hstring Email;
        winrt::hstring Phone;
        winrt::hstring Address;
        winrt::hstring Password;
    };
}
