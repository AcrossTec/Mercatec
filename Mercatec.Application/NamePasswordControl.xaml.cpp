// Copyright (c) Microsoft Corporation and Contributors.
// Licensed under the MIT License.

#include "pch.h"
#include "NamePasswordControl.xaml.h"
#if __has_include("NamePasswordControl.g.cpp")
# include "NamePasswordControl.g.cpp"
#endif

using namespace winrt;
using namespace winrt::Microsoft::UI::Xaml;
using namespace winrt::Microsoft::UI::Xaml::Input;

// To learn more about WinUI, the WinUI project structure,
// and more about our project templates, see: http://aka.ms/winui-project-info.

namespace winrt::Mercatec::Application::implementation
{
    NamePasswordControl::NamePasswordControl()
    {
        InitializeComponent();
    }

    void NamePasswordControl::Focus() noexcept
    {
        UserNameTextBox().Focus(FocusState::Programmatic);
    }

    hstring NamePasswordControl::UserName() const noexcept
    {
        return unbox_value<hstring>(GetValue(UserNameProperty()));
    }

    void NamePasswordControl::UserName(const std::wstring_view Value) noexcept
    {
        SetValue(UserNameProperty(), box_value(Value));
    }

    hstring NamePasswordControl::Password() const noexcept
    {
        return unbox_value<hstring>(GetValue(PasswordProperty()));
    }

    void NamePasswordControl::Password(const std::wstring_view Value) noexcept
    {
        SetValue(PasswordProperty(), box_value(Value));
    }

    ICommand NamePasswordControl::LoginWithPasswordCommand() const noexcept
    {
        return unbox_value<ICommand>(GetValue(LoginWithPasswordCommandProperty()));
    }

    void NamePasswordControl::LoginWithPasswordCommand(const ICommand& Value) const noexcept
    {
        SetValue(LoginWithPasswordCommandProperty(), box_value(Value));
    }

    DependencyProperty NamePasswordControl::UserNameProperty() noexcept
    {
        static DependencyProperty Property = DependencyProperty::Register( //
          L"UserName",
          xaml_typename<hstring>(),
          xaml_typename<Application::NamePasswordControl>(),
          PropertyMetadata::Create(box_value(L""))
        );

        return Property;
    }

    DependencyProperty NamePasswordControl::PasswordProperty() noexcept
    {
        static DependencyProperty Property = DependencyProperty::Register( //
          L"Password",
          xaml_typename<hstring>(),
          xaml_typename<Application::NamePasswordControl>(),
          PropertyMetadata::Create(box_value(L""))
        );

        return Property;
    }

    DependencyProperty NamePasswordControl::LoginWithPasswordCommandProperty() noexcept
    {
        static DependencyProperty Property = DependencyProperty::Register( //
          L"LoginWithPasswordCommand",
          xaml_typename<ICommand>(),
          xaml_typename<Application::NamePasswordControl>(),
          PropertyMetadata::Create(ICommand{ nullptr })
        );

        return Property;
    }
} // namespace winrt::Mercatec::Application::implementation
