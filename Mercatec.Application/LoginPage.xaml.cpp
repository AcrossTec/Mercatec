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
#include <Mercatec.Services.Auths.AccountHelper.hpp>
#include <Mercatec.Services.Auths.MicrosoftPassportHelper.hpp>

#pragma warning(push)

//! https://learn.microsoft.com/en-us/cpp/code-quality/c26811?view=msvc-170
//! https://learn.microsoft.com/en-us/windows/uwp/cpp-and-winrt-apis/concurrency#parameter-passing
//! Warning C26811 Lifetime of the memory referenced by parameter ''args'' might end by the time the coroutine is resumed(lifetime .1)
#pragma warning(disable : 26811)

using namespace ::winrt;
using namespace ::Microsoft::UI::Xaml;
using namespace ::Mercatec::Types;

namespace Helpers = ::Mercatec::Helpers;
namespace Auths   = ::Mercatec::Services::Auths;

// To learn more about WinUI, the WinUI project structure,
// and more about our project templates, see: http://aka.ms/winui-project-info.

namespace winrt::Mercatec::Application::implementation
{
    LoginPage::LoginPage()
      : m_IsExistingAccount{ false }
      , m_Account{ nullptr }
    {
        InitializeComponent();
    }

    /// <summary>
    ///     Function called when this frame is navigated to.
    ///     Checks to see if Microsoft Passport is available and if an account was passed in.
    ///     If an account was passed in set the "m_IsExistingAccount" flag to true and set the _account
    /// </summary>
    /// <remarks>
    ///     https://learn.microsoft.com/en-us/windows/uwp/cpp-and-winrt-apis/weak-references
    ///     https://learn.microsoft.com/en-us/windows/uwp/cpp-and-winrt-apis/concurrency#parameter-passing
    /// </remarks>
    fire_and_forget LoginPage::OnNavigatedTo(const MUXN::NavigationEventArgs& insecure_args)
    {
        const MUXN::NavigationEventArgs args = insecure_args;

        // Check Microsoft Passport is setup and available on this machine
        if ( co_await Auths::MicrosoftPassportHelper::MicrosoftPassportAvailableCheckAsync() )
        {
            if ( args.Parameter() )
            {
                m_IsExistingAccount = true;

                // Set the account to the existing account being passed in
                m_Account = args.Parameter().as<Account>();

                UserNameTextBox().Text(m_Account.UserName());
                SignInPassport();
            }
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
        ErrorMessage().Text(Helpers::Empty<Char>);
        SignInPassport();
    }

    fire_and_forget LoginPage::RegisterButtonTextBlock_OnPointerPressed([[maybe_unused]] const IInspectable& sender, [[maybe_unused]] const MUXI::PointerRoutedEventArgs& args)
    {
        ErrorMessage().Text(Helpers::Empty<Char>);
        co_await m_DialogService.ShowAsync(XamlRoot(), L"PassportRegisterPage", L"Registrar nuevo usuario");
        Frame().Navigate(xaml_typename<PassportRegisterPage>());
    }

    fire_and_forget LoginPage::SignInPassport()
    {
        if ( m_IsExistingAccount )
        {
            if ( co_await Auths::MicrosoftPassportHelper::GetPassportAuthenticationMessageAsync(m_Account) )
            {
                Frame().Navigate(xaml_typename<Mercatec::Application::WelcomePage>(), m_Account);
            }
        }
        else if ( Auths::AccountHelper::ValidateAccountCredentials(UserNameTextBox().Text()) )
        {
            // Create and add a new local account
            m_Account = Auths::AccountHelper::AddAccount(UserNameTextBox().Text());
            Helpers::OutputDebug(L"Successfully signed in with traditional credentials and created local account instance!");

            if ( co_await Auths::MicrosoftPassportHelper::CreatePassportKeyAsync(UserNameTextBox().Text()) )
            {
                Helpers::OutputDebug(L"Successfully signed in with Microsoft Passport!");
                Frame().Navigate(xaml_typename<Mercatec::Application::WelcomePage>(), m_Account);
            }
        }
        else
        {
            // co_await ui_thread; // Switch back to calling context.
            ErrorMessage().Text(L"Invalid Credentials");
        }
    }

} // namespace winrt::Mercatec::Application::implementation

#pragma warning(pop)