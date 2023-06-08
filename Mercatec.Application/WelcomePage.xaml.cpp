// Copyright (c) Microsoft Corporation and Contributors.
// Licensed under the MIT License.

#include "pch.h"
#include "WelcomePage.xaml.h"
#if __has_include("WelcomePage.g.cpp")
# include "WelcomePage.g.cpp"
#endif

#include <Mercatec.Helpers.Debug.hpp>
#include <Mercatec.Services.AuthService.hpp>
#include <Mercatec.Services.MicrosoftPassportService.hpp>

using namespace winrt;
using namespace winrt::Microsoft::UI::Xaml;

using ::Mercatec::Helpers::OutputDebug;
using ::Mercatec::Services::AuthService;
using ::Mercatec::Services::MicrosoftPassportHelper;

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

        if ( m_ActiveAccount != nullptr )
        {
            const Account account = AuthService::Instance().GetUserAccount(m_ActiveAccount.UserId());

            if ( account != nullptr )
            {
                UserListView().ItemsSource(account.PassportDevices());
                UserNameText().Text(account.UserName());
            }
        }
    }

    void WelcomePage::ButtonRestart_Click([[maybe_unused]] const IInspectable& sender, [[maybe_unused]] const MUX::RoutedEventArgs& args)
    {
        Frame().Navigate(xaml_typename<Mercatec::Application::UserSelectionPage>());
    }

    void WelcomePage::ButtonForgetUser_Click([[maybe_unused]] const IInspectable& sender, [[maybe_unused]] const MUX::RoutedEventArgs& args)
    {
        // Remove it from Microsoft Passport
        MicrosoftPassportHelper::RemovePassportAccountAsync(m_ActiveAccount);

        OutputDebug(L"User {} deleted.", m_ActiveAccount.UserName());

        // Navigate back to UserSelection page.
        Frame().Navigate(xaml_typename<Mercatec::Application::UserSelectionPage>());
    }

    void WelcomePage::ButtonForgetDevice_Click([[maybe_unused]] const IInspectable& sender, [[maybe_unused]] const MUX::RoutedEventArgs& args)
    {
        PassportDevice selected_device = UserListView().SelectedItem().try_as<PassportDevice>();

        if ( selected_device != nullptr )
        {
            // Remove it from Windows Hello
            MicrosoftPassportHelper::RemovePassportDevice(m_ActiveAccount, selected_device.DeviceId());

            OutputDebug(L"User {} deleted.", m_ActiveAccount.UserName());

            if ( UserListView().Items().Size() == 0 )
            {
                // Navigate back to UserSelection page.
                Frame().Navigate(xaml_typename<Mercatec::Application::UserSelectionPage>());
            }
        }
        else
        {
            ForgetDeviceErrorTextBlock().Visibility(MUX::Visibility::Visible);
        }
    }
} // namespace winrt::Mercatec::Application::implementation
