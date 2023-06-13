// Copyright (c) Microsoft Corporation and Contributors.
// Licensed under the MIT License.

#pragma once

#include "winrt/Microsoft.UI.Xaml.h"
#include "winrt/Microsoft.UI.Xaml.Markup.h"
#include "winrt/Microsoft.UI.Xaml.Controls.Primitives.h"
#include "NamePasswordControl.g.h"

namespace winrt::Mercatec::Application::implementation
{
    struct NamePasswordControl : NamePasswordControlT<NamePasswordControl>
    {
    public:
        NamePasswordControl();

        void Focus() noexcept;

        hstring UserName() const noexcept;
        void    UserName(const std::wstring_view Value) noexcept;

        hstring Password() const noexcept;
        void    Password(const std::wstring_view Value) noexcept;

        Microsoft::UI::Xaml::Input::ICommand LoginWithPasswordCommand() const noexcept;
        void                                 LoginWithPasswordCommand(const Microsoft::UI::Xaml::Input::ICommand& Value) const noexcept;

        static Microsoft::UI::Xaml::DependencyProperty UserNameProperty() noexcept;
        static Microsoft::UI::Xaml::DependencyProperty PasswordProperty() noexcept;
        static Microsoft::UI::Xaml::DependencyProperty LoginWithPasswordCommandProperty() noexcept;
    };
} // namespace winrt::Mercatec::Application::implementation

namespace winrt::Mercatec::Application::factory_implementation
{
    struct NamePasswordControl : NamePasswordControlT<NamePasswordControl, implementation::NamePasswordControl>
    {
    };
} // namespace winrt::Mercatec::Application::factory_implementation
