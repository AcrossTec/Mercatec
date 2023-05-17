// Copyright (c) Microsoft Corporation and Contributors.
// Licensed under the MIT License.

#pragma once

#include "LoginPage.g.h"

#include <winrt/Mercatec.Services.h>
#include <Mercatec.Models.WinRT.hpp>

namespace winrt::Mercatec::Application::implementation
{
    struct LoginPage : LoginPageT<LoginPage>
    {
    public:
        using Account = winrt::Mercatec::Models::UserAccount;

        LoginPage();
        fire_and_forget OnNavigatedTo(const MUXN::NavigationEventArgs& args);
        fire_and_forget PassportSignInButton_Click(const IInspectable& sender, const MUX::RoutedEventArgs& args);
        fire_and_forget RegisterButtonTextBlock_OnPointerPressed(const IInspectable& sender, const MUXI::PointerRoutedEventArgs& args);
        IAsyncAction    SignInPassportAsync();

    private:
        Account                 m_Account;
        bool                    m_IsExistingAccount;
        Services::DialogService m_DialogService;
    };
} // namespace winrt::Mercatec::Application::implementation

namespace winrt::Mercatec::Application::factory_implementation
{
    struct LoginPage : LoginPageT<LoginPage, implementation::LoginPage>
    {
    };
} // namespace winrt::Mercatec::Application::factory_implementation
