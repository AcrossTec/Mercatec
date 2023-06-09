// Copyright (c) Microsoft Corporation and Contributors.
// Licensed under the MIT License.

#pragma once

#include "winrt/Microsoft.UI.Xaml.h"
#include "winrt/Microsoft.UI.Xaml.Markup.h"
#include "winrt/Microsoft.UI.Xaml.Controls.Primitives.h"
#include "WindowsHelloControl.g.h"

namespace winrt::Mercatec::Application::implementation
{
    struct WindowsHelloControl : WindowsHelloControlT<WindowsHelloControl>
    {
        WindowsHelloControl();

        int32_t MyProperty();
        void    MyProperty(int32_t value);

        void myButton_Click(const Windows::Foundation::IInspectable& sender, const Microsoft::UI::Xaml::RoutedEventArgs& args);
    };
} // namespace winrt::Mercatec::Application::implementation

namespace winrt::Mercatec::Application::factory_implementation
{
    struct WindowsHelloControl : WindowsHelloControlT<WindowsHelloControl, implementation::WindowsHelloControl>
    {
    };
} // namespace winrt::Mercatec::Application::factory_implementation
