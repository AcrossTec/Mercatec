#include "pch.h"
#include "Mercatec.Helpers.UserInfo.h"
#if __has_include("UserInfo.g.cpp")
# include "UserInfo.g.cpp"
#endif

namespace winrt::Mercatec::Helpers::implementation
{
    UserInfo::UserInfo() noexcept
    {
    }

    void UserInfo::AccountName(const std::wstring_view account_name) noexcept
    {
        m_AccountName = account_name;
    }

    hstring UserInfo::AccountName() const noexcept
    {
        return m_AccountName;
    }

    void UserInfo::FirstName(const std::wstring_view first_name) noexcept
    {
        m_FirstName = first_name;
    }

    hstring UserInfo::FirstName() const noexcept
    {
        return m_FirstName;
    }

    void UserInfo::LastName(const std::wstring_view last_name) noexcept
    {
        m_LastName = last_name;
    }

    hstring UserInfo::LastName() const noexcept
    {
        return m_LastName;
    }

    void UserInfo::PictureSource(const IInspectable& picture_source) noexcept
    {
        m_PictureSource = picture_source;
    }

    IInspectable UserInfo::PictureSource() const noexcept
    {
        return m_PictureSource;
    }

    hstring UserInfo::ToString() const noexcept
    {
        return DisplayName();
    }

    hstring UserInfo::DisplayName() const noexcept
    {
        return hstring(std::format(L"{} {}", m_FirstName, m_LastName));
    }

    bool UserInfo::IsEmpty() const noexcept
    {
        return m_FirstName.empty() and m_LastName.empty();
    }
} // namespace winrt::Mercatec::Helpers::implementation
