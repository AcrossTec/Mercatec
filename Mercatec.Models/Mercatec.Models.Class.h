#pragma once

#include "Class.g.h"

namespace winrt::Mercatec::Models::implementation
{
    struct Class : ClassT<Class>
    {
        Class();
    };
} // namespace winrt::Mercatec::Models::implementation

namespace winrt::Mercatec::Models::factory_implementation
{
    struct Class : ClassT<Class, implementation::Class>
    {
    };
} // namespace winrt::Mercatec::Models::factory_implementation
