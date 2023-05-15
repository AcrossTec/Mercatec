#include "pch.h"
#include "Mercatec.Models.WinRT.UserAccount.h"
#if __has_include("UserAccount.g.cpp")
# include "UserAccount.g.cpp"
#endif

namespace winrt::Mercatec::Models::implementation
{
    UserAccount::UserAccount() noexcept
      : m_PassportDevices{ single_threaded_vector<Models::PassportDevice>() }
    {
    }

    void UserAccount::UserId(const winrt::guid& user_id) noexcept
    {
        SET_PROPERTY(m_Model.UserId, user_id);
    }

    winrt::guid UserAccount::UserId() const noexcept
    {
        return m_Model.UserId;
    }

    void UserAccount::UserName(const hstring& user_name) noexcept
    {
        SET_PROPERTY(m_Model.UserName, user_name);
    }

    hstring UserAccount::UserName() const noexcept
    {
        return m_Model.UserName;
    }

    void UserAccount::Email(const hstring& email) noexcept
    {
        SET_PROPERTY(m_Model.Email, email);
    }

    hstring UserAccount::Email() const noexcept
    {
        return m_Model.Email;
    }

    void UserAccount::Phone(const hstring& phone) noexcept
    {
        SET_PROPERTY(m_Model.Phone, phone);
    }

    hstring UserAccount::Phone() const noexcept
    {
        return m_Model.Phone;
    }

    void UserAccount::Address(const hstring& address) noexcept
    {
        SET_PROPERTY(m_Model.Address, address);
    }

    hstring UserAccount::Address() const noexcept
    {
        return m_Model.Address;
    }

    void UserAccount::Password(const hstring& password) noexcept
    {
        SET_PROPERTY(m_Model.Password, password);
    }

    hstring UserAccount::Password() const noexcept
    {
        return m_Model.Password;
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
} // namespace winrt::Mercatec::Models::implementation
