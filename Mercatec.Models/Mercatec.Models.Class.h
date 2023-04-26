// Copyright (c) Microsoft Corporation and Contributors.
// Licensed under the MIT License.

#pragma once

#include "winrt/Microsoft.UI.Xaml.h"
#include "winrt/Microsoft.UI.Xaml.Markup.h"
#include "winrt/Microsoft.UI.Xaml.Controls.Primitives.h"
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
