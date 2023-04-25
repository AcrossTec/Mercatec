// Copyright (c) Microsoft Corporation and Contributors.
// Licensed under the MIT License.

#pragma once

#include "WelcomePage.g.h"

namespace winrt::Mercatec::Application::implementation
{
    struct WelcomePage : WelcomePageT<WelcomePage>
    {
        WelcomePage();
    };
}

namespace winrt::Mercatec::Application::factory_implementation
{
    struct WelcomePage : WelcomePageT<WelcomePage, implementation::WelcomePage>
    {
    };
}
