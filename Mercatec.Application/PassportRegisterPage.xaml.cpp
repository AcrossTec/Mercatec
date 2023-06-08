// Copyright (c) Microsoft Corporation and Contributors.
// Licensed under the MIT License.

#include "pch.h"
#include "PassportRegisterPage.xaml.h"
#if __has_include("PassportRegisterPage.g.cpp")
# include "PassportRegisterPage.g.cpp"
#endif

#include <Mercatec.Services.AuthService.hpp>
#include <Mercatec.Services.MicrosoftPassportService.hpp>

using namespace winrt;
using namespace winrt::Microsoft::UI::Xaml;

using ::Mercatec::Char;
using ::Mercatec::Guid;

using ::Mercatec::Helpers::Empty;
using ::Mercatec::Services::AuthService;
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

        // Validate entered credentials are acceptable
        if ( not UserNameTextBox().Text().empty() )
        {
            // Register an Account on the AuthService so that we can get back a userId
            AuthService::Instance().Register(UserNameTextBox().Text(), PasswordTextBox().Password());
            const Guid user_id = AuthService::Instance().GetUserId(UserNameTextBox().Text());

            if ( user_id != GuidHelper::Empty() )
            {
                // Now that the account exists on server try and create the necessary passport details and add them to the account
                bool is_successful = co_await MicrosoftPassportHelper::CreatePassportKeyAsync(user_id, UserNameTextBox().Text());

                if ( is_successful )
                {
                    // Navigate to the Welcome Screen.
                    Frame().Navigate(xaml_typename<Application::WelcomePage>(), AuthService::Instance().GetUserAccount(user_id));
                }
                else
                {
                    // The passport account creation failed.
                    // Remove the account from the server as passport details were not configured
                    AuthService::Instance().PassportRemoveUser(user_id);

                    ErrorMessage().Text(L"Account Creation Failed");
                }
            }
        }
        else
        {
            ErrorMessage().Text(L"Please enter a username");
        }
    }
} // namespace winrt::Mercatec::Application::implementation
