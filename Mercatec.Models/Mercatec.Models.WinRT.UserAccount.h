#pragma once

#include <Mercatec.Helpers.ViewModels.Entity.hpp>
#include "Mercatec.Models.UserAccount.hpp"
#include "UserAccount.g.h"

namespace winrt::Mercatec::Models::implementation
{
    struct UserAccount : UserAccountT<UserAccount>, ::Mercatec::Helpers::ViewModels::Entity
    {
    public:
        UserAccount() noexcept;

        void        UserId(const winrt::guid& user_id) noexcept;
        winrt::guid UserId() const noexcept;

        void    UserName(const hstring& user_name) noexcept;
        hstring UserName() const noexcept;

        void    Email(const hstring& email) noexcept;
        hstring Email() const noexcept;

        void    Phone(const hstring& phone) noexcept;
        hstring Phone() const noexcept;

        void    Address(const hstring& address) noexcept;
        hstring Address() const noexcept;

        void    Password(const hstring& password) noexcept;
        hstring Password() const noexcept;

        void                            PassportDevices(const IVector<Models::PassportDevice>& devices) noexcept;
        IVector<Models::PassportDevice> PassportDevices() const noexcept;

    public:
        ::Mercatec::Models::UserAccount m_Model;

    private:
        IVector<Models::PassportDevice> m_PassportDevices;
    };
} // namespace winrt::Mercatec::Models::implementation

namespace winrt::Mercatec::Models::factory_implementation
{
    struct UserAccount : UserAccountT<UserAccount, implementation::UserAccount>
    {
    };
} // namespace winrt::Mercatec::Models::factory_implementation
