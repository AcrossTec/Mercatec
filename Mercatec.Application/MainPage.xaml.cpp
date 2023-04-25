// Copyright (c) Microsoft Corporation and Contributors.
// Licensed under the MIT License.

#include "pch.h"
#include "MainPage.xaml.h"
#if __has_include("MainPage.g.cpp")
# include "MainPage.g.cpp"
#endif

#include "LoginPage.xaml.h"

using namespace winrt;
using namespace Microsoft::UI::Xaml;

// To learn more about WinUI, the WinUI project structure,
// and more about our project templates, see: http://aka.ms/winui-project-info.

namespace winrt::Mercatec::Application::implementation
{
    MainPage::MainPage()
    {
        InitializeComponent();
    }

    void MainPage::MainPage_Loaded([[maybe_unused]] const IInspectable& sender, [[maybe_unused]] const MUX::RoutedEventArgs& args)
    {
        Frame().Navigate(xaml_typename<Mercatec::Application::LoginPage>());
    }
} // namespace winrt::Mercatec::Application::implementation
