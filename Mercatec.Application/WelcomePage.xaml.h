// Copyright (c) Microsoft Corporation and Contributors.
// Licensed under the MIT License.

#pragma once

#include "WelcomePage.g.h"

#include <Mercatec.Models.WinRT.hpp>

namespace winrt::Mercatec::Application::implementation
{
    struct WelcomePage : WelcomePageT<WelcomePage>
    {
    public:
        using Account        = ::winrt::Mercatec::Models::UserAccount;
        using PassportDevice = ::winrt::Mercatec::Models::PassportDevice;

        WelcomePage();
        void OnNavigatedTo(const Microsoft::UI::Xaml::Navigation::NavigationEventArgs& args);
        void ButtonRestart_Click(const IInspectable& sender, const Microsoft::UI::Xaml::RoutedEventArgs& args);
        void ButtonForgetUser_Click(const IInspectable& sender, const Microsoft::UI::Xaml::RoutedEventArgs& args);
        void ButtonForgetDevice_Click(const IInspectable& sender, const Microsoft::UI::Xaml::RoutedEventArgs& args);

    private:
        Account m_ActiveAccount;
    };
} // namespace winrt::Mercatec::Application::implementation

namespace winrt::Mercatec::Application::factory_implementation
{
    struct WelcomePage : WelcomePageT<WelcomePage, implementation::WelcomePage>
    {
    };
} // namespace winrt::Mercatec::Application::factory_implementation
