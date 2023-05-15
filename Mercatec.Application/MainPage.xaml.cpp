// Copyright (c) Microsoft Corporation and Contributors.
// Licensed under the MIT License.

#include "pch.h"
#include "MainPage.xaml.h"
#if __has_include("MainPage.g.cpp")
# include "MainPage.g.cpp"
#endif

#include "LoginPage.xaml.h"

#include <Mercatec.Services.AccountService.hpp>

using namespace winrt;
using namespace Microsoft::UI::Xaml;

using AccountHelper = ::Mercatec::Services::AccountHelper;

// To learn more about WinUI, the WinUI project structure,
// and more about our project templates, see: http://aka.ms/winui-project-info.

namespace winrt::Mercatec::Application::implementation
{
    MainPage::MainPage()
    {
        InitializeComponent();
    }

    fire_and_forget MainPage::MainPage_Loaded([[maybe_unused]] const IInspectable& sender, [[maybe_unused]] const MUX::RoutedEventArgs& args)
    {
        // Load the local Accounts List before navigating to the UserSelection page
        co_await AccountHelper::LoadAccountListAsync();

        Frame().Navigate(xaml_typename<Mercatec::Application::UserSelectionPage>());
    }
} // namespace winrt::Mercatec::Application::implementation
