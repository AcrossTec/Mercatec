// Copyright (c) Microsoft Corporation and Contributors.
// Licensed under the MIT License.

#include "pch.h"
#include "UserSelectionPage.xaml.h"
#if __has_include("UserSelectionPage.g.cpp")
# include "UserSelectionPage.g.cpp"
#endif

#include <Mercatec.Helpers.Auth.hpp>
#include <Mercatec.Helpers.Debug.hpp>
#include <Mercatec.Services.AuthService.hpp>

using namespace winrt;
using namespace Microsoft::UI::Xaml;
using namespace ::Mercatec::Services;

using ::Mercatec::Helpers::GetDeviceId;
using ::Mercatec::Helpers::OutputDebug;

// To learn more about WinUI, the WinUI project structure,
// and more about our project templates, see: http://aka.ms/winui-project-info.

namespace winrt::Mercatec::Application::implementation
{
    UserSelectionPage::UserSelectionPage()
    {
        InitializeComponent();
        Loaded({ this, &UserSelectionPage::UserSelectionLoaded });
    }

    void UserSelectionPage::UserSelectionLoaded([[maybe_unused]] const IInspectable& sender, [[maybe_unused]] const RoutedEventArgs& args)
    {
        auto accounts = AuthService::Instance().GetUserAccountsForDevice(GetDeviceId());

        if ( accounts.Size() != 0 )
        {
            UserListView().ItemsSource(accounts);
            UserListView().SelectionChanged({ this, &UserSelectionPage::UserSelectionChanged });
        }
        else
        {
            // If there are no accounts navigate to the LoginPage
            Frame().Navigate(xaml_typename<Mercatec::Application::LoginPage>());
        }
    }

    /// <summary>
    ///     Function called when an account is selected in the list of accounts
    ///     Navigates to the Login page and passes the chosen account
    /// </summary>
    void UserSelectionPage::UserSelectionChanged([[maybe_unused]] const IInspectable& sender, [[maybe_unused]] const MUXC::SelectionChangedEventArgs& args)
    {
        if ( sender.as<ListView>().SelectedValue() )
        {
            auto account = sender.as<ListView>().SelectedValue().try_as<Mercatec::Models::UserAccount>();

            if ( account != nullptr )
            {
                OutputDebug(L"Account {} Selected!", account.UserName());
            }

            Frame().Navigate(xaml_typename<winrt::Mercatec::Application::LoginPage>(), account);
        }
    }

    /// <summary>
    ///     Function called when the "+" button is clicked to add a new user.
    ///     Navigates to the Login page with nothing filled out
    /// </summary>
    void UserSelectionPage::AddUserButton_Click([[maybe_unused]] const IInspectable& sender, [[maybe_unused]] const RoutedEventArgs& args)
    {
        Frame().Navigate(xaml_typename<winrt::Mercatec::Application::LoginPage>());
    }
} // namespace winrt::Mercatec::Application::implementation
