#pragma once

#include "UserInfo.g.h"

namespace winrt::Mercatec::Helpers::implementation
{
    struct UserInfo : UserInfoT<UserInfo>
    {
    public:
        UserInfo() noexcept;
        void    AccountName(const std::wstring_view account_name) noexcept;
        hstring AccountName() const noexcept;

        void    FirstName(const std::wstring_view first_name) noexcept;
        hstring FirstName() const noexcept;

        void    LastName(const std::wstring_view last_name) noexcept;
        hstring LastName() const noexcept;

        void         PictureSource(const IInspectable& picture_source) noexcept;
        IInspectable PictureSource() const noexcept;

        hstring ToString() const noexcept;
        hstring DisplayName() const noexcept;
        bool    IsEmpty() const noexcept;

    private:
        hstring      m_AccountName;
        hstring      m_FirstName;
        hstring      m_LastName;
        IInspectable m_PictureSource;
    };
} // namespace winrt::Mercatec::Helpers::implementation

namespace winrt::Mercatec::Helpers::factory_implementation
{
    struct UserInfo : UserInfoT<UserInfo, implementation::UserInfo>
    {
    };
} // namespace winrt::Mercatec::Helpers::factory_implementation
