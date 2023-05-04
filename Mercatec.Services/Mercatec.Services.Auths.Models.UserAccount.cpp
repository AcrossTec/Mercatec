// Copyright (c) Microsoft Corporation and Contributors.
// Licensed under the MIT License.

#include "pch.h"
#include "Mercatec.Services.Auths.Models.UserAccount.h"
#if __has_include("Auths.Models.UserAccount.g.cpp")
# include "Auths.Models.UserAccount.g.cpp"
#endif

using namespace winrt;
using namespace Microsoft::UI::Xaml;

// To learn more about WinUI, the WinUI project structure,
// and more about our project templates, see: http://aka.ms/winui-project-info.

namespace winrt::Mercatec::Services::Auths::Models::implementation
{
    UserAccount::UserAccount() noexcept
      : m_UserId{ GuidHelper::Empty() }
      , m_PassportDevices{ single_threaded_vector<Mercatec::Services::Auths::Models::PassportDevice>() }
    {
    }

    void UserAccount::UserId(const winrt::guid& user_id) noexcept
    {
        m_UserId = user_id;
    }

    winrt::guid UserAccount::UserId() const noexcept
    {
        return m_UserId;
    }

    void UserAccount::UserName(const hstring& user_name) noexcept
    {
        m_UserName = user_name;
    }

    hstring UserAccount::UserName() const noexcept
    {
        return m_UserName;
    }

    void UserAccount::Password(const hstring& password) noexcept
    {
        m_Password = password;
    }

    hstring UserAccount::Password() const noexcept
    {
        return m_Password;
    }

    void UserAccount::PassportDevices(const IVector<Models::PassportDevice>& passport_devices) noexcept
    {
        // Remark: Crea una copia del argumento.
        // TODO: Crear prueba unitaria para IVector<>.

        std::vector<Models::PassportDevice> temporal{ passport_devices.Size() };
        passport_devices.GetMany(0, temporal);
        m_PassportDevices = single_threaded_vector(std::move(temporal));
    }

    IVector<Models::PassportDevice> UserAccount::PassportDevices() const noexcept
    {
        return m_PassportDevices;
    }
} // namespace winrt::Mercatec::Services::Auths::Models::implementation
