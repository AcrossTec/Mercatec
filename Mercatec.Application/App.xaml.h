// Copyright (c) Microsoft Corporation and Contributors.
// Licensed under the MIT License.

#pragma once

#include "App.xaml.g.h"
#include <winrt/Mercatec.Helpers.h>

namespace winrt::Mercatec::Application::implementation
{
    struct App : AppT<App, Helpers::IApplication>
    {
    public:
        App();
        void OnLaunched(const Microsoft::UI::Xaml::LaunchActivatedEventArgs&);

        Microsoft::UI::Xaml::Window MainWindow() const noexcept;

    private:
        Mercatec::Application::SplashScreen m_Splash{ nullptr };
        Microsoft::UI::Xaml::Window         m_Window{ nullptr };
    };
} // namespace winrt::Mercatec::Application::implementation
