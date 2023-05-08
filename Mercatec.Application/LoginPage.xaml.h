// Copyright (c) Microsoft Corporation and Contributors.
// Licensed under the MIT License.

#pragma once

#include "LoginPage.g.h"

#include <Mercatec.Services.Auths.Models.hpp>

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
        fire_and_forget SignInPassport();

        Account m_Account;
        bool    m_IsExistingAccount;
    };
} // namespace winrt::Mercatec::Application::implementation

namespace winrt::Mercatec::Application::factory_implementation
{
    struct LoginPage : LoginPageT<LoginPage, implementation::LoginPage>
    {
    };
} // namespace winrt::Mercatec::Application::factory_implementation
