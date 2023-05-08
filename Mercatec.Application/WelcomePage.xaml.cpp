// Copyright (c) Microsoft Corporation and Contributors.
// Licensed under the MIT License.

#include "pch.h"
#include "WelcomePage.xaml.h"
#if __has_include("WelcomePage.g.cpp")
# include "WelcomePage.g.cpp"
#endif

#include <Mercatec.Helpers.Debug.hpp>
#include <Mercatec.Services.Auths.AccountHelper.hpp>
#include <Mercatec.Services.Auths.MicrosoftPassportHelper.hpp>

using namespace winrt;
using namespace Microsoft::UI::Xaml;

namespace Helpers = ::Mercatec::Helpers;
namespace Auths   = ::Mercatec::Services::Auths;

// To learn more about WinUI, the WinUI project structure,
// and more about our project templates, see: http://aka.ms/winui-project-info.

namespace winrt::Mercatec::Application::implementation
{
    WelcomePage::WelcomePage()
    {
        InitializeComponent();
    }

    void WelcomePage::OnNavigatedTo(const MUXN::NavigationEventArgs& args)
    {
        m_ActiveAccount = args.Parameter().try_as<Account>();

        if ( m_ActiveAccount )
        {
            UserNameText().Text(m_ActiveAccount.UserName());
        }
    }

    void WelcomePage::ButtonRestart_Click([[maybe_unused]] const IInspectable& sender, [[maybe_unused]] const MUX::RoutedEventArgs& args)
    {
        Frame().Navigate(xaml_typename<Mercatec::Application::UserSelectionPage>());
    }

    void WelcomePage::ButtonForgetUser_Click([[maybe_unused]] const IInspectable& sender, [[maybe_unused]] const MUX::RoutedEventArgs& args)
    {
        // Remove it from Microsoft Passport
        ::Auths::MicrosoftPassportHelper::RemovePassportAccountAsync(m_ActiveAccount);

        // Remove it from the local accounts list and resave the updated list
        ::Auths::AccountHelper::RemoveAccount(m_ActiveAccount);

        ::Helpers::OutputDebug(L"User {} deleted.", m_ActiveAccount.UserName());

        // Navigate back to UserSelection page.
        Frame().Navigate(xaml_typename<Mercatec::Application::UserSelectionPage>());
    }
} // namespace winrt::Mercatec::Application::implementation
