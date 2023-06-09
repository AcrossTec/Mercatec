#include "pch.h"
#include "Mercatec.ViewModels.LoginViewModel.h"
#if __has_include("LoginViewModel.g.cpp")
# include "LoginViewModel.g.cpp"
#endif

#include <Mercatec.Helpers.Application.hpp>
#include <Mercatec.Helpers.Models.hpp>
#include <Mercatec.Helpers.RelayCommand.hpp>

using Mercatec::Helpers::DelegateCommand;
namespace App = Mercatec::Helpers::Applications;

namespace winrt::Mercatec::ViewModels::implementation
{
    LoginViewModel::LoginViewModel( //!
      const Helpers::Services::ILoginService&    login_service,
      const Helpers::Services::ISettingsService& settings_service,
      const Helpers::Services::ICommonServices&  common_services
    )
      : LoginViewModelT<LoginViewModel>(common_services)
      , m_LoginService{ login_service }
      , m_SettingsService{ settings_service }
      , m_ViewModelArgs{ nullptr }
      , m_IsBusy{ false }
      , m_IsLoginWithPassword{ false }
      , m_IsLoginWithWindowsHello{ false }
      , m_UserName{}
      , m_Password{}
      , m_ShowLoginWithPasswordCommand{ make<DelegateCommand>(std::bind_front(&LoginViewModel::ShowLoginWithPassword, this)) }
      , m_LoginWithWindowHelloCommand{ make<DelegateCommand>(std::bind_front(&LoginViewModel::LoginWithWindowHello, this)) }
      , m_LoginWithPasswordCommand{ make<DelegateCommand>(std::bind_front(&LoginViewModel::LoginWithPassword, this)) }
    {
    }

    Helpers::Services::ILoginService LoginViewModel::LoginService() const noexcept
    {
        return m_LoginService;
    }

    Helpers::Services::ISettingsService LoginViewModel::SettingsService() const noexcept
    {
        return m_SettingsService;
    }

    Helpers::ViewModels::ShellArgs LoginViewModel::ViewModelArgs() const noexcept
    {
        return m_ViewModelArgs;
    }

    void LoginViewModel::ViewModelArgs(const Helpers::ViewModels::ShellArgs& value) noexcept
    {
        m_ViewModelArgs = value;
    }

    bool LoginViewModel::IsBusy() const noexcept
    {
        return m_IsBusy;
    }

    void LoginViewModel::IsBusy(const bool value) noexcept
    {
        SET_PROPERTY(m_IsBusy, value);
    }

    bool LoginViewModel::IsLoginWithPassword() const noexcept
    {
        return m_IsLoginWithPassword;
    }

    void LoginViewModel::IsLoginWithPassword(const bool value) noexcept
    {
        SET_PROPERTY(m_IsLoginWithPassword, value);
    }

    bool LoginViewModel::IsLoginWithWindowsHello() const noexcept
    {
        return m_IsLoginWithWindowsHello;
    }

    void LoginViewModel::IsLoginWithWindowsHello(const bool value) noexcept
    {
        SET_PROPERTY(m_IsLoginWithWindowsHello, value);
    }

    hstring LoginViewModel::UserName() const noexcept
    {
        return m_UserName;
    }

    void LoginViewModel::UserName(const std::wstring_view value) noexcept
    {
        SET_PROPERTY(m_UserName, value);
    }

    hstring LoginViewModel::Password() const noexcept
    {
        return m_Password;
    }

    void LoginViewModel::Password(const std::wstring_view value) noexcept
    {
        SET_PROPERTY(m_Password, value);
    }

    Microsoft::UI::Xaml::Input::ICommand LoginViewModel::ShowLoginWithPasswordCommand() const noexcept
    {
        return m_ShowLoginWithPasswordCommand;
    }

    Microsoft::UI::Xaml::Input::ICommand LoginViewModel::LoginWithPasswordCommand() const noexcept
    {
        return m_LoginWithPasswordCommand;
    }

    Microsoft::UI::Xaml::Input::ICommand LoginViewModel::LoginWithWindowHelloCommand() const noexcept
    {
        return m_LoginWithWindowHelloCommand;
    }

    Windows::Foundation::IAsyncAction LoginViewModel::LoadAsync([[maybe_unused]] const Helpers::ViewModels::ShellArgs& args)
    {
        ViewModelArgs(args);
        UserName(m_SettingsService.UserName().empty() ? args.UserInfo().AccountName() : m_SettingsService.UserName());
        IsLoginWithWindowsHello(m_LoginService.IsWindowsHelloEnabled(m_UserName));
        IsLoginWithPassword(not IsLoginWithWindowsHello());
        IsBusy(false);
        co_return;
    }

    void LoginViewModel::Login() noexcept
    {
        if ( IsLoginWithPassword() )
        {
            LoginWithPassword();
        }
        else
        {
            LoginWithWindowHello();
        }
    }

    void LoginViewModel::ShowLoginWithPassword() noexcept
    {
        IsLoginWithWindowsHello(false);
        IsLoginWithPassword(true);
    }

    fire_and_forget LoginViewModel::LoginWithPassword() noexcept
    {
        IsBusy(true);
        auto Result = ValidateInput();

        if ( Result.IsOk() )
        {
            if ( co_await m_LoginService.SignInWithPasswordAsync(m_UserName, m_Password) )
            {
                if ( not m_LoginService.IsWindowsHelloEnabled(m_UserName) )
                {
                    co_await m_LoginService.TrySetupWindowsHelloAsync(m_UserName);
                }

                m_SettingsService.UserName(m_UserName);
                EnterApplication();
                co_return;
            }
        }

        co_await DialogService().ShowAsync(App::XamlRoot(), Result.Message(), Result.Description());
        IsBusy(false);
    }

    fire_and_forget LoginViewModel::LoginWithWindowHello() noexcept
    {
        IsBusy(true);
        auto Result = co_await m_LoginService.SignInWithWindowsHelloAsync();

        if ( Result.IsOk() )
        {
            EnterApplication();
            co_return;
        }

        co_await DialogService().ShowAsync(App::XamlRoot(), Result.Message(), Result.Description());
        IsBusy(false);
    }

    void LoginViewModel::EnterApplication() noexcept
    {
        if ( m_ViewModelArgs.UserInfo().AccountName() != m_UserName )
        {
            Helpers::UserInfo UserInfo;
            UserInfo.AccountName(m_UserName);
            UserInfo.FirstName(m_UserName);
            UserInfo.PictureSource(nullptr);

            m_ViewModelArgs.UserInfo(UserInfo);
        }

        NavigationService().Navigate(xaml_typename<MainShellViewModel>(), m_ViewModelArgs);
    }

    Helpers::Result LoginViewModel::ValidateInput() noexcept
    {
        if ( m_UserName.empty() )
        {
            return Helpers::Result::Error(L"Login Error", L"Please, Enter A Valid User Name.");
        }

        if ( m_Password.empty() )
        {
            return Helpers::Result::Error(L"Login Error", L"Please, Enter A Valid Password.");
        }

        return Helpers::Result::Ok();
    }

} // namespace winrt::Mercatec::ViewModels::implementation
