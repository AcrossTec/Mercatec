// Copyright (c) Microsoft Corporation and Contributors.
// Licensed under the MIT License.

#pragma once

#include "SplashScreen.g.h"

namespace winrt::Mercatec::Application::implementation
{
    struct SplashScreen : SplashScreenT<SplashScreen>
    {
        SplashScreen();
        Windows::Foundation::IAsyncAction OnLoading();
    };
} // namespace winrt::Mercatec::Application::implementation

namespace winrt::Mercatec::Application::factory_implementation
{
    struct SplashScreen : SplashScreenT<SplashScreen, implementation::SplashScreen>
    {
    };
} // namespace winrt::Mercatec::Application::factory_implementation
