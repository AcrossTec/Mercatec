// Copyright (c) Microsoft Corporation and Contributors.
// Licensed under the MIT License.

#pragma once

#include "winrt/Microsoft.UI.Xaml.h"
#include "winrt/Microsoft.UI.Xaml.Markup.h"
#include "winrt/Microsoft.UI.Xaml.Controls.Primitives.h"
#include "User.g.h"

#include "Mercatec.Models.UserAccount.hpp"

namespace winrt::Mercatec::ViewModels::implementation
{
    struct User : UserT<User>
    {
    public:
        User() = default;

        guid UserId() const noexcept;
        void UserId(const guid user_id) noexcept;

        hstring UserName() const noexcept;
        void    UserName(const hstring& user_name) noexcept;

        hstring Email() const noexcept;
        void    Email(const hstring& email) noexcept;

        hstring Phone() const noexcept;
        void    Phone(const hstring& phone) noexcept;

        hstring Address() const noexcept;
        void    Address(const hstring& address) noexcept;

        hstring Password() const noexcept;
        void    Password(const hstring& password) noexcept;

        uint64_t Model() const noexcept;

        event_token PropertyChanged(const Microsoft::UI::Xaml::Data::PropertyChangedEventHandler& handler);
        void        PropertyChanged(const event_token& token);

    private:
        ::Mercatec::Models::UserAccount                               m_User;
        event<Microsoft::UI::Xaml::Data::PropertyChangedEventHandler> m_PropertyChanged;
    };
} // namespace winrt::Mercatec::ViewModels::implementation

namespace winrt::Mercatec::ViewModels::factory_implementation
{
    struct User : UserT<User, implementation::User>
    {
    };
} // namespace winrt::Mercatec::ViewModels::factory_implementation
