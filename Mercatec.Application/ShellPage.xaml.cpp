// Copyright (c) Microsoft Corporation and Contributors.
// Licensed under the MIT License.

#include "pch.h"
#include "ShellPage.xaml.h"
#if __has_include("ShellPage.g.cpp")
# include "ShellPage.g.cpp"
#endif

using namespace winrt;
using namespace winrt::Microsoft::UI::Xaml;

// To learn more about WinUI, the WinUI project structure,
// and more about our project templates, see: http://aka.ms/winui-project-info.

namespace winrt::Mercatec::Application::implementation
{
    ShellPage::ShellPage()
    {
        InitializeComponent();
    }

    int32_t ShellPage::MyProperty()
    {
        throw hresult_not_implemented();
    }

    void ShellPage::MyProperty(int32_t /* value */)
    {
        throw hresult_not_implemented();
    }

    void ShellPage::MyButton_Click(const IInspectable&, const RoutedEventArgs&)
    {
        MyButton().Content(box_value(L"Clicked"));
    }
} // namespace winrt::Mercatec::Application::implementation
