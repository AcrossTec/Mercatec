// Copyright (c) Microsoft Corporation and Contributors.
// Licensed under the MIT License.

#include "pch.h"
#include "Mercatec.ViewModels.User.h"
#if __has_include("User.g.cpp")
# include "User.g.cpp"
#endif

#include <Mercatec.Helpers.Strings.hpp>
#include <Mercatec.Helpers.ViewModels.hpp>

using namespace winrt;
using namespace Microsoft::UI::Xaml;

// To learn more about WinUI, the WinUI project structure,
// and more about our project templates, see: http://aka.ms/winui-project-info.

namespace winrt::Mercatec::ViewModels::implementation
{
    uint64_t User::UserId() const noexcept
    {
        return m_User.UserId;
    }

    void User::UserId(const uint64_t user_id) noexcept
    {
        VIEWMODEL_DEFAULT_SET_PROPERTY(User, UserId, user_id);
    }

    hstring User::UserName() const noexcept
    {
        return m_User.UserName;
    }

    void User::UserName(const hstring& user_name) noexcept
    {
        VIEWMODEL_DEFAULT_SET_PROPERTY(User, UserName, user_name);
    }

    hstring User::Email() const noexcept
    {
        return m_User.Email;
    }

    void User::Email(const hstring& email) noexcept
    {
        VIEWMODEL_DEFAULT_SET_PROPERTY(User, Email, email);
    }

    hstring User::Phone() const noexcept
    {
        return m_User.Phone;
    }

    void User::Phone(const hstring& phone) noexcept
    {
        VIEWMODEL_DEFAULT_SET_PROPERTY(User, Phone, phone);
    }

    hstring User::Address() const noexcept
    {
        return m_User.Address;
    }

    void User::Address(const hstring& address) noexcept
    {
        VIEWMODEL_DEFAULT_SET_PROPERTY(User, Address, address);
    }

    hstring User::Password() const noexcept
    {
        return m_User.Password;
    }

    void User::Password(const hstring& password) noexcept
    {
        VIEWMODEL_DEFAULT_SET_PROPERTY(User, Password, password);
    }

    uint64_t User::Model() const noexcept
    {
        return reinterpret_cast<uint64_t>(std::addressof(m_User));
    }

    event_token User::PropertyChanged(const Microsoft::UI::Xaml::Data::PropertyChangedEventHandler& handler)
    {
        return m_PropertyChanged.add(handler);
    }

    void User::PropertyChanged(const event_token& token)
    {
        m_PropertyChanged.remove(token);
    }
} // namespace winrt::Mercatec::ViewModels::implementation
