// Copyright (c) Microsoft Corporation and Contributors.
// Licensed under the MIT License.

#pragma once

#include "winrt/Microsoft.UI.Xaml.h"
#include "winrt/Microsoft.UI.Xaml.Markup.h"
#include "winrt/Microsoft.UI.Xaml.Controls.Primitives.h"
#include "User.g.h"

namespace winrt::Mercatec::ViewModels::implementation
{
    struct User : UserT<User>
    {
        User();
        int32_t MyProperty();
        void MyProperty( int32_t value );
    };
}

namespace winrt::Mercatec::ViewModels::factory_implementation
{
    struct User : UserT<User, implementation::User>
    {
    };
}
