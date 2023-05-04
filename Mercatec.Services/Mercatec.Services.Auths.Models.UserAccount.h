// Copyright (c) Microsoft Corporation and Contributors.
// Licensed under the MIT License.

#pragma once

#include "winrt/Microsoft.UI.Xaml.h"
#include "winrt/Microsoft.UI.Xaml.Markup.h"
#include "winrt/Microsoft.UI.Xaml.Controls.Primitives.h"
#include "Auths.Models.UserAccount.g.h"

#include "Mercatec.Services.Auths.Models.PassportDevice.h"

namespace winrt::Mercatec::Services::Auths::Models::implementation
{
    struct UserAccount : UserAccountT<UserAccount>
    {
    public:
        UserAccount() noexcept;

        void UserId(const winrt::guid& user_id) noexcept;

        winrt::guid UserId() const noexcept;

        void UserName(const hstring& user_name) noexcept;

        hstring UserName() const noexcept;

        void Password(const hstring& password) noexcept;

        hstring Password() const noexcept;

        void PassportDevices(const IVector<Models::PassportDevice>& devices) noexcept;

        IVector<Models::PassportDevice> PassportDevices() const noexcept;

    private:
        winrt::guid m_UserId;
        hstring     m_UserName;
        hstring     m_Password;

        IVector<Models::PassportDevice> m_PassportDevices;
    };
} // namespace winrt::Mercatec::Services::Auths::Models::implementation

namespace winrt::Mercatec::Services::Auths::Models::factory_implementation
{
    struct UserAccount : UserAccountT<UserAccount, implementation::UserAccount>
    {
    };
} // namespace winrt::Mercatec::Services::Auths::Models::factory_implementation
