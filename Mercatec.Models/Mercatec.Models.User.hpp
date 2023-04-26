#pragma once

#include <winrt/Windows.Foundation.h>

namespace Mercatec::Models
{
    struct User
    {
        uint64_t       UserId{ 0 };
        winrt::hstring UserName;
        winrt::hstring Email;
        winrt::hstring Phone;
        winrt::hstring Address;
        winrt::hstring Password;
    };
} // namespace Mercatec::Models
