// Copyright (c) Microsoft Corporation and Contributors.
// Licensed under the MIT License.

#include "pch.h"
#include "UserSelectionPage.xaml.h"
#if __has_include("UserSelectionPage.g.cpp")
# include "UserSelectionPage.g.cpp"
#endif

#include <Mercatec.Helpers.Debug.hpp>
#include <Mercatec.Services.Auths.AccountHelper.hpp>

using namespace winrt;
using namespace Microsoft::UI::Xaml;
using namespace ::Mercatec::Services::Auths;

using ::Mercatec::Helpers::OutputDebug;

// To learn more about WinUI, the WinUI project structure,
// and more about our project templates, see: http://aka.ms/winui-project-info.

namespace winrt::Mercatec::Application::implementation
{
    UserSelectionPage::UserSelectionPage()
    {
        InitializeComponent();
        // Loaded(std::bind_front(&UserSelectionPage::UserSelectionLoaded, this));
        Loaded({ this, &UserSelectionPage::UserSelectionLoaded });
    }

    void UserSelectionPage::UserSelectionLoaded([[maybe_unused]] const IInspectable& sender, [[maybe_unused]] const RoutedEventArgs& args)
    {
        if ( AccountHelper::AccountList.Size() == 0 )
        {
            // If there are no accounts navigate to the LoginPage
            Frame().Navigate(xaml_typename<Mercatec::Application::LoginPage>());
        }

        OutputDebug(AccountHelper::AccountList, L"AccountHelper::AccountList");
        UserListView().ItemsSource(AccountHelper::AccountList);

        // UserListView().SelectionChanged(std::bind_front(&UserSelectionPage::UserSelectionChanged, this));
        UserListView().SelectionChanged({ this, &UserSelectionPage::UserSelectionChanged });
    }

    /// <summary>
    ///     Function called when an account is selected in the list of accounts
    ///     Navigates to the Login page and passes the chosen account
    /// </summary>
    void UserSelectionPage::UserSelectionChanged([[maybe_unused]] const IInspectable& sender, [[maybe_unused]] const MUXC::SelectionChangedEventArgs& args)
    {
        if ( sender.as<ListView>().SelectedValue() )
        {
            auto account = sender.as<ListView>().SelectedValue().as<winrt::Mercatec::Services::Auths::Models::UserAccount>();

            if ( account )
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
