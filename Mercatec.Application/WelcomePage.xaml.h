// Copyright (c) Microsoft Corporation and Contributors.
// Licensed under the MIT License.

#pragma once

#include "WelcomePage.g.h"

#include <winrt/Mercatec.Services.Auths.Models.h>
#include <Mercatec.Helpers.Types.hpp>

namespace winrt::Mercatec::Application::implementation
{
    struct WelcomePage : WelcomePageT<WelcomePage>
    {
    public:
        using Account = ::winrt::Mercatec::Services::Auths::Models::UserAccount;

        WelcomePage();
        void OnNavigatedTo(const MUXN::NavigationEventArgs& args);
        void ButtonRestart_Click(const IInspectable& sender, const Microsoft::UI::Xaml::RoutedEventArgs& args);
        void ButtonForgetUser_Click(const IInspectable& sender, const Microsoft::UI::Xaml::RoutedEventArgs& args);

    private:
        std::optional<Account> m_ActiveAccount;
    };
} // namespace winrt::Mercatec::Application::implementation

namespace winrt::Mercatec::Application::factory_implementation
{
    struct WelcomePage : WelcomePageT<WelcomePage, implementation::WelcomePage>
    {
    };
} // namespace winrt::Mercatec::Application::factory_implementation
