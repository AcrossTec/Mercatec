// Copyright (c) Microsoft Corporation and Contributors.
// Licensed under the MIT License.

#include "pch.h"
#include "MainPage.xaml.h"
#if __has_include("MainPage.g.cpp")
# include "MainPage.g.cpp"
#endif

#include <winrt/Mercatec.Helpers.h>
#include <winrt/Mercatec.Helpers.ViewModels.h>

#include "Mercatec.Application.ActivationService.hpp"

using namespace winrt;
using namespace winrt::Microsoft::UI::Xaml;
using namespace winrt::Windows::Security::Credentials;
using namespace winrt::Mercatec::Helpers;
using namespace winrt::Mercatec::Helpers::ViewModels;

using ::Mercatec::Application::ActivationInfo;
using ::Mercatec::Application::ActivationService;

// To learn more about WinUI, the WinUI project structure,
// and more about our project templates, see: http://aka.ms/winui-project-info.

namespace winrt::Mercatec::Application::implementation
{
    MainPage::MainPage()
    {
        InitializeComponent();
    }

    UserInfo TryGetUserInfo()
    {
        PasswordVault      Vault;
        PasswordCredential Credential;

        UserInfo User;
        User.AccountName(Credential.UserName());
        User.PictureSource(box_value(Credential.Resource()));

        return User;
    }

    void MainPage::MainPage_Loaded(const IInspectable&, const MUX::RoutedEventArgs&)
    {
        auto AppInstance{ winrt::Microsoft::Windows::AppLifecycle::AppInstance::GetCurrent() };

        // AppInstance.GetActivatedEventArgs will report the correct ActivationKind, even in WinUI's OnLaunched.
        auto ActivationArgs{ AppInstance.GetActivatedEventArgs() };

        auto ActivationInfo{ ActivationService::GetActivationInfo(ActivationArgs) };

        // TODO: Verificar si el usuario tiene las credenciales guardadas

        ShellArgs Args;
        Args.ViewModel(ActivationInfo->EntryViewModel);
        Args.Parameter(ActivationInfo->EntryArgs);
        Args.UserInfo(TryGetUserInfo());

        Frame().Navigate(xaml_typename<Mercatec::Application::LoginPage>(), Args);
    }

} // namespace winrt::Mercatec::Application::implementation
