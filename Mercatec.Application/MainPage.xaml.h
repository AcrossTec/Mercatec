// Copyright (c) Microsoft Corporation and Contributors.
// Licensed under the MIT License.

#pragma once

#include "MainPage.g.h"

namespace winrt::Mercatec::Application::implementation
{
    struct MainPage : MainPageT<MainPage>
    {
        MainPage();
        fire_and_forget MainPage_Loaded(const IInspectable& sender, const MUX::RoutedEventArgs& args);
    };
} // namespace winrt::Mercatec::Application::implementation

namespace winrt::Mercatec::Application::factory_implementation
{
    struct MainPage : MainPageT<MainPage, implementation::MainPage>
    {
    };
} // namespace winrt::Mercatec::Application::factory_implementation
