// Copyright (c) Microsoft Corporation and Contributors.
// Licensed under the MIT License.

#pragma once

#include "PassportRegisterPage.g.h"

#include <Mercatec.Services.Auths.Models.hpp>

namespace winrt::Mercatec::Application::implementation
{
    struct PassportRegisterPage : PassportRegisterPageT<PassportRegisterPage>
    {
    public:
        PassportRegisterPage();
        fire_and_forget RegisterButtonClickAsync(const Windows::Foundation::IInspectable& sender, const Microsoft::UI::Xaml::RoutedEventArgs& args);

    private:
        Mercatec::Services::Auths::Models::UserAccount m_Account;
    };
} // namespace winrt::Mercatec::Application::implementation

namespace winrt::Mercatec::Application::factory_implementation
{
    struct PassportRegisterPage : PassportRegisterPageT<PassportRegisterPage, implementation::PassportRegisterPage>
    {
    };
} // namespace winrt::Mercatec::Application::factory_implementation
