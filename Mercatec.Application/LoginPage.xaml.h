// Copyright (c) Microsoft Corporation and Contributors.
// Licensed under the MIT License.

#pragma once

#include "LoginPage.g.h"
#include <winrt/Mercatec.ViewModels.h>

namespace winrt::Mercatec::Application::implementation
{
    struct LoginPage : LoginPageT<LoginPage>
    {
    public:
        LoginPage() noexcept;
        ViewModels::LoginViewModel            ViewModel() const noexcept;

        fire_and_forget OnNavigatedTo(const Microsoft::UI::Xaml::Navigation::NavigationEventArgs& Args);
        fire_and_forget OnKeyDown(const Microsoft::UI::Xaml::Input::KeyRoutedEventArgs& Args);
        fire_and_forget OnShowLoginWithPassword(const IInspectable& Sender, const RoutedEventArgs& Args);
        void            OnBackgroundFocus(const IInspectable& Sender, const RoutedEventArgs& Args);
        void            OnForegroundFocus(const IInspectable& Sender, const RoutedEventArgs& Args);

    private:
        void DoEffectIn(const double_t MilliSeconds = 1'000);
        void DoEffectOut(const double_t MilliSeconds = 1'000);

    protected:
        void InitializeContext();
        void InitializeNavigation();

    private:
        ViewModels::LoginViewModel m_ViewModel;
        EffectMode                 m_EffectMode;
    };
} // namespace winrt::Mercatec::Application::implementation

namespace winrt::Mercatec::Application::factory_implementation
{
    struct LoginPage : LoginPageT<LoginPage, implementation::LoginPage>
    {
    };
} // namespace winrt::Mercatec::Application::factory_implementation
