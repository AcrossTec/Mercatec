// Copyright (c) Microsoft Corporation and Contributors.
// Licensed under the MIT License.

#include "pch.h"
#include "PassportRegisterPage.xaml.h"
#if __has_include("PassportRegisterPage.g.cpp")
# include "PassportRegisterPage.g.cpp"
#endif

#include <Mercatec.Helpers.Types.hpp>
#include <Mercatec.Helpers.Strings.hpp>

#include <Mercatec.Services.AccountService.hpp>
#include <Mercatec.Services.MicrosoftPassportService.hpp>

using namespace winrt;
using namespace Microsoft::UI::Xaml;

using ::Mercatec::Char;

using ::Mercatec::Helpers::Empty;
using ::Mercatec::Services::AccountHelper;
using ::Mercatec::Services::MicrosoftPassportHelper;

// To learn more about WinUI, the WinUI project structure,
// and more about our project templates, see: http://aka.ms/winui-project-info.

namespace winrt::Mercatec::Application::implementation
{
    PassportRegisterPage::PassportRegisterPage()
    {
        InitializeComponent();
    }

    fire_and_forget PassportRegisterPage::RegisterButtonClickAsync(const IInspectable&, const RoutedEventArgs&)
    {
        ErrorMessage().Text(Empty<Char>);

        // In the real world you would normally validate the entered credentials and information before
        // allowing a user to register a new account.
        // For this sample though we will skip that step and just register an account if username is not null.

        if ( not UserNameTextBox().Text().empty() )
        {
            // Register a new account
            m_Account = AccountHelper::AddAccount(UserNameTextBox().Text());

            // Register new account with Microsoft Passport
            co_await MicrosoftPassportHelper::CreatePassportKeyAsync(m_Account.UserName());

            // Navigate to the Welcome Screen.
            Frame().Navigate(xaml_typename<Mercatec::Application::WelcomePage>(), m_Account);
        }
        else
        {
            ErrorMessage().Text(L"Please enter a username");
        }
    }
} // namespace winrt::Mercatec::Application::implementation
