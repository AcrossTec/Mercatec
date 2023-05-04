// Copyright (c) Microsoft Corporation and Contributors.
// Licensed under the MIT License.

#include "pch.h"
#include "WelcomePage.xaml.h"
#if __has_include("WelcomePage.g.cpp")
# include "WelcomePage.g.cpp"
#endif

#include <Mercatec.Helpers.Debug.hpp>
#include <Mercatec.Services.Auths.AccountHelper.hpp>

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
        m_ActiveAccount = unbox_value<Windows::Foundation::IReference<Account>>(args.Parameter());

        if ( m_ActiveAccount.has_value() )
        {
            UserNameText().Text(m_ActiveAccount->UserName());
        }
    }

    void WelcomePage::ButtonRestart_Click([[maybe_unused]] const IInspectable& sender, [[maybe_unused]] const MUX::RoutedEventArgs& args)
    {
    }

    void WelcomePage::ButtonForgetUser_Click([[maybe_unused]] const IInspectable& sender, [[maybe_unused]] const MUX::RoutedEventArgs& args)
    {
        // Remove it from Microsoft Passport
        // MicrosoftPassportHelper.RemovePassportAccountAsync(_activeAccount);

        // Remove it from the local accounts list and resave the updated list
        ::Auths::AccountHelper::RemoveAccount(*m_ActiveAccount);

        ::Helpers::OutputDebug(L"User {} deleted.", m_ActiveAccount->UserName());
    }
} // namespace winrt::Mercatec::Application::implementation
