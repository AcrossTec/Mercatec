// Copyright (c) Microsoft Corporation and Contributors.
// Licensed under the MIT License.

#pragma once

#include "Class.g.h"

namespace winrt::Mercatec::Helpers::implementation
{
    struct Class : ClassT<Class>
    {
        Class();
    };
} // namespace winrt::Mercatec::Helpers::implementation

namespace winrt::Mercatec::Helpers::factory_implementation
{
    struct Class : ClassT<Class, implementation::Class>
    {
    };
} // namespace winrt::Mercatec::Helpers::factory_implementation
