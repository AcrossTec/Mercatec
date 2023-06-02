// Copyright (c) Microsoft Corporation and Contributors.
// Licensed under the MIT License.

#pragma once

#include "App.xaml.g.h"

namespace winrt::Mercatec::Application::implementation
{
    struct App : AppT<App>
    {
    public:
        App();
        void OnLaunched(const Microsoft::UI::Xaml::LaunchActivatedEventArgs&);

    private:
        Mercatec::Application::SplashScreen m_Splash{ nullptr };
        Microsoft::UI::Xaml::Window         m_Window{ nullptr };
    };
} // namespace winrt::Mercatec::Application::implementation
