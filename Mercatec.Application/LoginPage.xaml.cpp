// Copyright (c) Microsoft Corporation and Contributors.
// Licensed under the MIT License.

#include "pch.h"
#include "LoginPage.xaml.h"
#if __has_include("LoginPage.g.cpp")
# include "LoginPage.g.cpp"
#endif

#include <Mercatec.Helpers.Debug.hpp>
#include <Mercatec.Helpers.Types.hpp>
#include <Mercatec.Helpers.Strings.hpp>
#include <Mercatec.Helpers.MicrosoftPassportHelper.hpp>
#include <Mercatec.Models.AccountHelper.hpp>

using namespace winrt;
using namespace Microsoft::UI::Xaml;

namespace Helpers = ::Mercatec::Helpers;

// To learn more about WinUI, the WinUI project structure,
// and more about our project templates, see: http://aka.ms/winui-project-info.

namespace winrt::Mercatec::Application::implementation
{
    LoginPage::LoginPage()
    {
        InitializeComponent();
    }

    fire_and_forget LoginPage::OnNavigatedTo(const MUXN::NavigationEventArgs& args)
    {
        // Check Microsoft Passport is setup and available on this machine
        if ( co_await Helpers::MicrosoftPassportHelper::MicrosoftPassportAvailableCheckAsync() )
        {
        }
        else
        {
            // Microsoft Passport is not setup so inform the user
            PassportStatus().Background(MUXM::SolidColorBrush(MU::ColorHelper::FromArgb(255, 50, 170, 207)));
            PassportStatusText().Text(L"Microsoft Passport is not setup!\nPlease go to Windows Settings and set up a PIN to use it.");
            PassportSignInButton().IsEnabled(false);
        }
    }

    void LoginPage::PassportSignInButton_Click([[maybe_unused]] const IInspectable& sender, [[maybe_unused]] const MUX::RoutedEventArgs& args)
    {
        ErrorMessage().Text(Helpers::Empty<Helpers::Char>);
        SignInPassport();
    }

    void LoginPage::RegisterButtonTextBlock_OnPointerPressed([[maybe_unused]] const IInspectable& sender, [[maybe_unused]] const MUXI::PointerRoutedEventArgs& args)
    {
        ErrorMessage().Text(Helpers::Empty<Helpers::Char>);
    }

    IAsyncAction LoginPage::SignInPassport()
    {
        // apartment_context ui_thread; // Capture calling context.

        // co_await winrt::resume_background();
        // Do compute-bound work here.

        if ( Helpers::AccountHelper::ValidateAccountCredentials(UserNameTextBox().Text()) )
        {
            // Create and add a new local account
            m_Account = Helpers::AccountHelper::AddAccount(UserNameTextBox().Text());
            Helpers::OutputDebug(L"Successfully signed in with traditional credentials and created local account instance!");

            if ( co_await Helpers::MicrosoftPassportHelper::CreatePassportKeyAsync(UserNameTextBox().Text()) )
            {
                Helpers::OutputDebug(L"Successfully signed in with Microsoft Passport!");
            }
        }
        else
        {
            // co_await ui_thread; // Switch back to calling context.
            ErrorMessage().Text(L"Invalid Credentials");
        }
    }

} // namespace winrt::Mercatec::Application::implementation
