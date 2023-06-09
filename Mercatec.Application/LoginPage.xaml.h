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
        LoginPage();

    private:
        Services::DialogService m_DialogService;
    };
} // namespace winrt::Mercatec::Application::implementation

namespace winrt::Mercatec::Application::factory_implementation
{
    struct LoginPage : LoginPageT<LoginPage, implementation::LoginPage>
    {
    };
} // namespace winrt::Mercatec::Application::factory_implementation
