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
    public:
        WindowsHelloControl();
        hstring UserName() const noexcept;
        void    UserName(const std::wstring_view Value) noexcept;

        Microsoft::UI::Xaml::Input::ICommand LoginWithWindowHelloCommand() const noexcept;
        void                                 LoginWithWindowHelloCommand(const Microsoft::UI::Xaml::Input::ICommand& Value) noexcept;

        static Microsoft::UI::Xaml::DependencyProperty UserNameProperty() noexcept;
        static Microsoft::UI::Xaml::DependencyProperty LoginWithWindowHelloCommandProperty() noexcept;

    private:
        static void OnUserNameChanged(const Microsoft::UI::Xaml::DependencyObject& Sender, const Microsoft::UI::Xaml::DependencyPropertyChangedEventArgs& Args);
    };
} // namespace winrt::Mercatec::Application::implementation

namespace winrt::Mercatec::Application::factory_implementation
{
    struct WindowsHelloControl : WindowsHelloControlT<WindowsHelloControl, implementation::WindowsHelloControl>
    {
    };
} // namespace winrt::Mercatec::Application::factory_implementation
