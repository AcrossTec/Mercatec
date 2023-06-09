#include "pch.h"
#include "Mercatec.Services.LoginService.h"
#if __has_include("LoginService.g.cpp")
# include "LoginService.g.cpp"
#endif

namespace winrt::Mercatec::Services::implementation
{
    LoginService::LoginService( //!
      const Helpers::Services::IMessageService& MessageService,
      const Helpers::Services::IDialogService&  DialogService
    )
      : m_MessageService{ MessageService }
      , m_DialogService{ DialogService }
      , m_IsAuthenticated{ false }
    {
    }

    Helpers::Services::IMessageService LoginService::MessageService() const noexcept
    {
        return m_MessageService;
    }

    Helpers::Services::IDialogService LoginService::DialogService() const noexcept
    {
        return m_DialogService;
    }

    bool LoginService::IsAuthenticated() const noexcept
    {
        return m_IsAuthenticated;
    }

    void LoginService::IsAuthenticated(const bool Value) noexcept
    {
        m_IsAuthenticated = Value;
    }

    void LoginService::Logoff()
    {
    }

    bool LoginService::IsWindowsHelloEnabled([[maybe_unused]] const std::wstring_view UserName)
    {
        return false;
    }

    Windows::Foundation::IAsyncAction LoginService::TrySetupWindowsHelloAsync([[maybe_unused]] const std::wstring_view UserName)
    {
        co_return;
    }

    Windows::Foundation::IAsyncOperation<bool> LoginService::SignInWithPasswordAsync([[maybe_unused]] const std::wstring_view UserName, [[maybe_unused]] const std::wstring_view Password)
    {
        co_return false;
    }

    Windows::Foundation::IAsyncOperation<Helpers::Result> LoginService::SignInWithWindowsHelloAsync()
    {
        co_return nullptr;
    }
} // namespace winrt::Mercatec::Services::implementation
