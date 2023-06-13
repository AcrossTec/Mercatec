// Copyright (c) Microsoft Corporation and Contributors.
// Licensed under the MIT License.

#include "pch.h"
#include "WindowsHelloControl.xaml.h"
#if __has_include("WindowsHelloControl.g.cpp")
# include "WindowsHelloControl.g.cpp"
#endif

using namespace winrt;
using namespace winrt::Microsoft::UI::Xaml;
using namespace winrt::Microsoft::UI::Xaml::Input;

// To learn more about WinUI, the WinUI project structure,
// and more about our project templates, see: http://aka.ms/winui-project-info.

//!
//! Implement Custom Control Class
//! https://learn.microsoft.com/en-us/windows/uwp/cpp-and-winrt-apis/xaml-cust-ctrl
//!

namespace winrt::Mercatec::Application::implementation
{
    WindowsHelloControl::WindowsHelloControl()
    {
        InitializeComponent();
    }

    hstring WindowsHelloControl::UserName() const noexcept
    {
        return unbox_value<hstring>(GetValue(UserNameProperty()));
    }

    void WindowsHelloControl::UserName(const std::wstring_view Value) noexcept
    {
        SetValue(UserNameProperty(), box_value(Value));
    }

    ICommand WindowsHelloControl::LoginWithWindowHelloCommand() const noexcept
    {
        return unbox_value<ICommand>(GetValue(LoginWithWindowHelloCommandProperty()));
    }

    void WindowsHelloControl::LoginWithWindowHelloCommand(const ICommand& Value) noexcept
    {
        SetValue(LoginWithWindowHelloCommandProperty(), box_value(Value));
    }

    DependencyProperty WindowsHelloControl::UserNameProperty() noexcept
    {
        static DependencyProperty Property = DependencyProperty::Register( //
          L"UserName",
          xaml_typename<hstring>(),
          xaml_typename<Application::WindowsHelloControl>(),
          PropertyMetadata::Create(box_value(L"Windows Hello"), PropertyChangedCallback{ &WindowsHelloControl::OnUserNameChanged })
        );

        return Property;
    }

    DependencyProperty WindowsHelloControl::LoginWithWindowHelloCommandProperty() noexcept
    {
        static DependencyProperty Property = DependencyProperty::Register( //
          L"LoginWithWindowHelloCommand",
          xaml_typename<ICommand>(),
          xaml_typename<Application::WindowsHelloControl>(),
          PropertyMetadata::Create(ICommand{ nullptr })
        );

        return Property;
    }

    void WindowsHelloControl::OnUserNameChanged(const Microsoft::UI::Xaml::DependencyObject& Sender, [[maybe_unused]] const Microsoft::UI::Xaml::DependencyPropertyChangedEventArgs& Args)
    {
        if ( Application::WindowsHelloControl Control{ Sender.try_as<Application::WindowsHelloControl>() } )
        {
            // Call members of the projected type via Control.

            WindowsHelloControl* ControlPointer{ get_self<WindowsHelloControl>(Control) };
            // Call members of the implementation type via ptr.

            winrt::com_ptr<WindowsHelloControl> Impl;
            Impl.copy_from(ControlPointer);
            // com_ptr::copy_from ensures that AddRef is called.
        }
    }
} // namespace winrt::Mercatec::Application::implementation
