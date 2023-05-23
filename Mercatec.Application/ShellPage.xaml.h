// Copyright (c) Microsoft Corporation and Contributors.
// Licensed under the MIT License.

#pragma once

#include "ShellPage.g.h"

namespace winrt::Mercatec::Application::implementation
{
    struct ShellPage : ShellPageT<ShellPage>
    {
        ShellPage();

        int32_t MyProperty();
        void    MyProperty(int32_t value);

        void MyButton_Click(const Windows::Foundation::IInspectable& sender, const Microsoft::UI::Xaml::RoutedEventArgs& args);
    };
} // namespace winrt::Mercatec::Application::implementation

namespace winrt::Mercatec::Application::factory_implementation
{
    struct ShellPage : ShellPageT<ShellPage, implementation::ShellPage>
    {
    };
} // namespace winrt::Mercatec::Application::factory_implementation
