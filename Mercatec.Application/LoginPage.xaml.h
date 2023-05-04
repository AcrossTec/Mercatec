// Copyright (c) Microsoft Corporation and Contributors.
// Licensed under the MIT License.

#pragma once

#include "LoginPage.g.h"

#include <winrt/Mercatec.Services.Auths.Models.h>

namespace winrt::Mercatec::Application::implementation
{
    struct LoginPage : LoginPageT<LoginPage>
    {
    public:
        using Account = winrt::Mercatec::Services::Auths::Models::UserAccount;

        LoginPage();
        fire_and_forget OnNavigatedTo(const MUXN::NavigationEventArgs& args);

        void PassportSignInButton_Click(const IInspectable& sender, const MUX::RoutedEventArgs& args);
        void RegisterButtonTextBlock_OnPointerPressed(const IInspectable& sender, const MUXI::PointerRoutedEventArgs& args);

    private:
        IAsyncAction        SignInPassport();
        IReference<Account> m_Account;
    };
} // namespace winrt::Mercatec::Application::implementation

namespace winrt::Mercatec::Application::factory_implementation
{
    struct LoginPage : LoginPageT<LoginPage, implementation::LoginPage>
    {
    };
} // namespace winrt::Mercatec::Application::factory_implementation
