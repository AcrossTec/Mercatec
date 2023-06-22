#pragma once

#include "LoginService.g.h"
#include "Mercatec.Services.hpp"

#include <winrt/Windows.Storage.Streams.h>

namespace winrt::Mercatec::Services::implementation
{
    struct LoginService : LoginServiceT<LoginService>
    {
    public:
        using IBuffer = Windows::Storage::Streams::IBuffer;

        LoginService(const Helpers::Services::IMessageService& MessageService, const Helpers::Services::IDialogService& DialogService);

        Helpers::Services::IMessageService MessageService() const noexcept;
        Helpers::Services::IDialogService  DialogService() const noexcept;

        bool IsAuthenticated() const noexcept;
        void IsAuthenticated(const bool Value) noexcept;

        void Logoff();
        bool IsWindowsHelloEnabled(const std::wstring_view UserName);

        Windows::Foundation::IAsyncAction TrySetupWindowsHelloAsync(const std::wstring_view UserName);

        Windows::Foundation::IAsyncOperation<bool>            SignInWithPasswordAsync(const std::wstring_view UserName, const std::wstring_view Password);
        Windows::Foundation::IAsyncOperation<Helpers::Result> SignInWithWindowsHelloAsync();

    private:
        void                                                 UpdateAuthenticationStatus(const bool IsAuthenticated);
        Windows::Foundation::IAsyncAction                    SetupWindowsHelloAsync(const std::wstring_view UserName);
        Windows::Foundation::IAsyncOperation<bool>           TryDeleteCredentialAccountAsync(const std::wstring_view UserName);
        Windows::Foundation::IAsyncOperation<IBuffer>        CreatePassportKeyCredentialAsync(const std::wstring_view UserName);
        static Windows::Foundation::IAsyncOperation<bool>    RegisterPassportCredentialWithServerAsync(const IBuffer& PublicKey);
        winrt::com_ptr<::Mercatec::Services::MessageService> MsgService() const noexcept;

    private:
        bool                               m_IsAuthenticated;
        Helpers::Services::IMessageService m_MessageService;
        Helpers::Services::IDialogService  m_DialogService;
    };
} // namespace winrt::Mercatec::Services::implementation

namespace winrt::Mercatec::Services::factory_implementation
{
    struct LoginService : LoginServiceT<LoginService, implementation::LoginService>
    {
    };
} // namespace winrt::Mercatec::Services::factory_implementation
