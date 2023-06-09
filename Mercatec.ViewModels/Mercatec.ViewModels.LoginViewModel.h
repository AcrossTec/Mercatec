#pragma once

#include "LoginViewModel.g.h"

#include <winrt/Microsoft.UI.Xaml.h>
#include <winrt/Microsoft.UI.Xaml.Input.h>
#include <winrt/Mercatec.Helpers.Services.h>

namespace winrt::Mercatec::ViewModels::implementation
{
    struct LoginViewModel : LoginViewModelT<LoginViewModel>
    {
    public:
        LoginViewModel( //!
          const Helpers::Services::ILoginService&    login_service,
          const Helpers::Services::ISettingsService& settings_service,
          const Helpers::Services::ICommonServices&  common_services
        );

        Helpers::Services::ILoginService    LoginService() const noexcept;
        Helpers::Services::ISettingsService SettingsService() const noexcept;

        Helpers::ViewModels::ShellArgs ViewModelArgs() const noexcept;
        void                           ViewModelArgs(const Helpers::ViewModels::ShellArgs& value) noexcept;

        bool IsBusy() const noexcept;
        void IsBusy(const bool value) noexcept;

        bool IsLoginWithPassword() const noexcept;
        void IsLoginWithPassword(const bool value) noexcept;

        bool IsLoginWithWindowsHello() const noexcept;
        void IsLoginWithWindowsHello(const bool value) noexcept;

        hstring UserName() const noexcept;
        void    UserName(const std::wstring_view value) noexcept;

        hstring Password() const noexcept;
        void    Password(const std::wstring_view value) noexcept;

        Microsoft::UI::Xaml::Input::ICommand ShowLoginWithPasswordCommand() const noexcept;
        Microsoft::UI::Xaml::Input::ICommand LoginWithPasswordCommand() const noexcept;
        Microsoft::UI::Xaml::Input::ICommand LoginWithWindowHelloCommand() const noexcept;

        Windows::Foundation::IAsyncAction LoadAsync(const Helpers::ViewModels::ShellArgs& args);
        void                              Login() noexcept;

    private:
        void            ShowLoginWithPassword() noexcept;
        fire_and_forget LoginWithPassword() noexcept;
        fire_and_forget LoginWithWindowHello() noexcept;
        void            EnterApplication() noexcept;
        Helpers::Result ValidateInput() noexcept;

    private:
        Helpers::Services::ILoginService     m_LoginService;
        Helpers::Services::ISettingsService  m_SettingsService;
        Helpers::ViewModels::ShellArgs       m_ViewModelArgs;
        bool                                 m_IsBusy;
        bool                                 m_IsLoginWithPassword;
        bool                                 m_IsLoginWithWindowsHello;
        hstring                              m_UserName;
        hstring                              m_Password;
        Microsoft::UI::Xaml::Input::ICommand m_ShowLoginWithPasswordCommand;
        Microsoft::UI::Xaml::Input::ICommand m_LoginWithPasswordCommand;
        Microsoft::UI::Xaml::Input::ICommand m_LoginWithWindowHelloCommand;
    };
} // namespace winrt::Mercatec::ViewModels::implementation

namespace winrt::Mercatec::ViewModels::factory_implementation
{
    struct LoginViewModel : LoginViewModelT<LoginViewModel, implementation::LoginViewModel>
    {
    };
} // namespace winrt::Mercatec::ViewModels::factory_implementation
