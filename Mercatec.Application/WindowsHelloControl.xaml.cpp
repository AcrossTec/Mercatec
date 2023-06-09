// Copyright (c) Microsoft Corporation and Contributors.
// Licensed under the MIT License.

#include "pch.h"
#include "WindowsHelloControl.xaml.h"
#if __has_include("WindowsHelloControl.g.cpp")
# include "WindowsHelloControl.g.cpp"
#endif

using namespace winrt;
using namespace winrt::Microsoft::UI::Xaml;

// To learn more about WinUI, the WinUI project structure,
// and more about our project templates, see: http://aka.ms/winui-project-info.

namespace winrt::Mercatec::Application::implementation
{
    WindowsHelloControl::WindowsHelloControl()
    {
        InitializeComponent();
    }

    int32_t WindowsHelloControl::MyProperty()
    {
        throw hresult_not_implemented();
    }

    void WindowsHelloControl::MyProperty(int32_t /* value */)
    {
        throw hresult_not_implemented();
    }

    void WindowsHelloControl::myButton_Click(const IInspectable&, const RoutedEventArgs&)
    {
        myButton().Content(box_value(L"Clicked"));
    }
} // namespace winrt::Mercatec::Application::implementation
