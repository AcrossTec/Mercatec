#include "pch.h"
#include "Mercatec.Stores.UserAccountStore.hpp"

#include <Mercatec.Helpers.Debug.hpp>
#include <Mercatec.Helpers.Strings.hpp>
#include <Mercatec.Helpers.Widespread.hpp>

#include <tinyxml2.h>

using namespace Mercatec::Types;
using namespace Mercatec::Helpers::Debug;
using namespace Mercatec::Helpers::Strings;
using namespace Mercatec::Helpers::Widespread;

using winrt::Windows::Security::Credentials::KeyCredentialAttestationResult;

namespace Mercatec::Repositories
{
    UserAccountStore::UserAccountStore()
      : m_UserAccountListPath{ std::filesystem::current_path() / USER_ACCOUNT_LIST_FILE_NAME }
      , m_UserAccountsList{ winrt::single_threaded_observable_vector<UserAccountStore::Account>() }
    {
        LoadAccountListAsync();
    }

    Guid UserAccountStore::GetUserId(const std::wstring_view user_name) const noexcept
    {
        if ( m_UserAccountsList.Size() != 0 )
        {
            auto iter_result = std::find_if( //
              m_UserAccountsList.begin(),
              m_UserAccountsList.end(),
              [&](const Account& user) { return user.UserName() == user_name; }
            );

            if ( iter_result != m_UserAccountsList.end() )
            {
                return (*iter_result).UserId();
            }
        }

        return GuidHelper::Empty();
    }

    UserAccountStore::Account UserAccountStore::GetUserAccount(const Guid& user_id) const noexcept
    {
        auto iter_result = std::find_if( //
          m_UserAccountsList.begin(),
          m_UserAccountsList.end(),
          [&](const Account& user) { return user.UserId() == user_id; }
        );

        if ( iter_result != m_UserAccountsList.end() )
        {
            return *iter_result;
        }

        return nullptr;
    }

    IObservableVector<UserAccountStore::Account> UserAccountStore::GetUserAccountsForDevice(const Guid& device_id) const noexcept
    {
        std::vector<Account> users_for_device;

        for ( const Account& account : m_UserAccountsList )
        {
            if ( std::any_of( //
                   account.PassportDevices().begin(),
                   account.PassportDevices().end(),
                   [&](const PassportDevice& device) { return device.DeviceId() == device_id; }
                 ) )
            {
                users_for_device.emplace_back(account);
            }
        }

        return single_threaded_observable_vector(std::move(users_for_device));
    }

    winrt::com_array<Byte> UserAccountStore::GetPublicKey(const Guid& user_id, const Guid& device_id) const noexcept
    {
        auto iter_result = std::find_if( //
          m_UserAccountsList.begin(),
          m_UserAccountsList.end(),
          [&](const Account& user) { return user.UserId() == user_id; }
        );

        if ( iter_result != m_UserAccountsList.end() )
        {
            const Account account = *iter_result;

            if ( account.PassportDevices().Size() != 0 )
            {
                auto iter_result = std::find_if( //
                  account.PassportDevices().begin(),
                  account.PassportDevices().end(),
                  [&](const PassportDevice& device) { return device.DeviceId() == device_id; }
                );

                if ( iter_result != account.PassportDevices().end() )
                {
                    return (*iter_result).PublicKey();
                }
            }
        }

        return winrt::com_array<Byte>();
    }

    UserAccountStore::Account UserAccountStore::AddAccount(const std::wstring_view user_name) noexcept
    {
        try
        {
            UserAccount new_account;
            new_account.UserId(GuidHelper::CreateNewGuid());
            new_account.UserName(user_name);

            m_UserAccountsList.Append(new_account);
            SaveAccountListAsync();
        }
        catch ( [[maybe_unused]] const std::exception& ex )
        {
            throw;
        }

        return nullptr;
    }

    Boolean UserAccountStore::RemoveAccount(const Guid& user_id) noexcept
    {
        UserAccount user_account = GetUserAccount(user_id);

        if ( user_account != nullptr )
        {
            if ( UInt32 index{ 0 }; m_UserAccountsList.IndexOf(user_account, index) )
            {
                m_UserAccountsList.RemoveAt(index);
            }

            SaveAccountListAsync();
            return true;
        }

        return false;
    }

    Boolean UserAccountStore::RemoveDevice(const Guid& user_id, const Guid& device_id) noexcept
    {
        UserAccount    user_account     = GetUserAccount(user_id);
        PassportDevice device_to_remove = nullptr;

        int32_t index{ 0 };

        if ( user_account != nullptr )
        {
            for ( PassportDevice device : user_account.PassportDevices() )
            {
                if ( device.DeviceId() == device_id )
                {
                    device_to_remove = device;
                    break;
                }

                ++index;
            }
        }

        if ( device_to_remove != nullptr )
        {
            // Remove the PassportDevice
            user_account.PassportDevices().RemoveAt(index);
            SaveAccountListAsync();
        }

        return true;
    }

    void UserAccountStore::PassportUpdateDetails( //
      const Guid&                           user_id,
      const Guid&                           device_id,
      const array_view<Byte>                public_key,
      const KeyCredentialAttestationResult& key_attestation_result
    )
    {
        UserAccount existing_user_account = GetUserAccount(user_id);

        if ( existing_user_account != nullptr )
        {

            if ( not std::any_of( //
                   existing_user_account.PassportDevices().begin(),
                   existing_user_account.PassportDevices().end(),
                   [&](const PassportDevice& device) { return device.DeviceId() == device_id; }
                 ) )
            {
                PassportDevice passport_device;
                passport_device.DeviceId(device_id);
                passport_device.PublicKey(public_key);
                passport_device.KeyAttestationResult(key_attestation_result);

                existing_user_account.PassportDevices().Append(passport_device);
            }
        }
        SaveAccountListAsync();
    }

#pragma region Save and Load Helpers

    void UserAccountStore::InitializeSampleUserAccounts()
    {
        // Create a sample Traditional User Account that only has a Username and Password
        // This will be used initially to demonstrate how to migrate to use Windows Hello

        Account user_account;
        user_account.UserId(GuidHelper::CreateNewGuid());
        user_account.UserName(L"SampleUserName");
        user_account.Password(L"SamplePassword");

        // Add the sampleUserAccount to the _mockDatabase
        m_UserAccountsList.Append(user_account);
        SaveAccountListAsync();
    }

    /// <summary>
    ///     Create and save a useraccount list file. (Replacing the old one)
    /// </summary>
    winrt::fire_and_forget UserAccountStore::SaveAccountListAsync()
    {
        using namespace winrt::Windows::Storage;

        const winrt::hstring accounts_xml = SerializeAccountListToXml();

        if ( std::filesystem::exists(m_UserAccountListPath) )
        {
            auto accounts_file = co_await StorageFile::GetFileFromPathAsync(m_UserAccountListPath.c_str());
            co_await FileIO::WriteTextAsync(accounts_file, accounts_xml);
        }
        else
        {
            std::wofstream accounts_file{ USER_ACCOUNT_LIST_FILE_NAME.data(), std::ios::out | std::ios::binary };
            accounts_file.write(accounts_xml.c_str(), accounts_xml.size() * sizeof(winrt::hstring::value_type));
        }
    }

    /// <summary>
    ///     Gets the useraccount list file and deserializes it from XML to a list of useraccount objects.
    /// </summary>
    /// <returns>List of useraccount objects</returns>
    winrt::fire_and_forget UserAccountStore::LoadAccountListAsync()
    {
        using namespace winrt::Windows::Storage;

        if ( std::filesystem::exists(m_UserAccountListPath) )
        {
            StorageFile accounts_file = co_await StorageFile::GetFileFromPathAsync(m_UserAccountListPath.c_str());

            winrt::hstring accounts_xml = co_await FileIO::ReadTextAsync(accounts_file);
            DeserializeXmlToAccountList(accounts_xml);
        }

        // If the UserAccountList does not contain the sampleUser Initialize the sample users
        // This is only needed as it in a Hand on Lab to demonstrate a user migrating
        // In the real world user accounts would just be in a database
        if ( not std::any_of( //
               m_UserAccountsList.begin(),
               m_UserAccountsList.end(),
               [](const Account& user) { return user.UserName() == L"SampleUserName"; }
             ) )
        {
            // If the list is empty InitializeSampleAccounts and return the list
            InitializeSampleUserAccounts();
        }
    }

    /// <summary>
    ///     Uses the local list of accounts and returns an XML formatted string representing the list
    /// </summary>
    /// <returns>XML formatted list of accounts</returns>
    winrt::hstring UserAccountStore::SerializeAccountListToXml()
    {
        using namespace tinyxml2;

        tinyxml2::XMLDocument document;

        auto root = document.NewElement("Accounts");

        for ( const auto& user : m_UserAccountsList )
        {
            XMLElement* account = document.NewElement("Account");

            XMLElement* user_id       = document.NewElement("UserId");
            XMLElement* user_name     = document.NewElement("UserName");
            XMLElement* user_email    = document.NewElement("Email");
            XMLElement* user_phone    = document.NewElement("Phone");
            XMLElement* user_address  = document.NewElement("Address");
            XMLElement* user_password = document.NewElement("Password");

            user_id->SetText(GuidToString(user.UserId()).c_str());
            user_name->SetText(winrt::to_string(user.UserName()).c_str());
            user_email->SetText(winrt::to_string(user.Email()).c_str());
            user_phone->SetText(winrt::to_string(user.Phone()).c_str());
            user_address->SetText(winrt::to_string(user.Address()).c_str());
            user_password->SetText(winrt::to_string(user.Password()).c_str());

            account->InsertEndChild(user_id);
            account->InsertEndChild(user_name);
            account->InsertEndChild(user_email);
            account->InsertEndChild(user_phone);
            account->InsertEndChild(user_address);
            account->InsertEndChild(user_password);

            root->InsertEndChild(account);
        }

        XMLPrinter printer;
        document.Print(&printer);
        return winrt::to_hstring(printer.CStr());
    }

    /// <summary>
    ///     Takes an XML formatted string representing a list of accounts and returns a list object of accounts
    /// </summary>
    /// <param name="listAsXml">XML formatted list of accounts</param>
    /// <returns>List object of accounts</returns>
    IObservableVector<UserAccountStore::Account> UserAccountStore::DeserializeXmlToAccountList(const std::wstring_view list_as_xml)
    {
        using namespace tinyxml2;

        tinyxml2::XMLDocument document;

        if ( document.Parse(winrt::to_string(list_as_xml).c_str()) == XML_SUCCESS )
        {
            m_UserAccountsList.Clear();

            auto root = document.FirstChildElement("Accounts");

            XMLNode* account_element = root->FirstChildElement("Account");

            while ( account_element != nullptr )
            {
                XMLElement* user_id_element       = account_element->FirstChildElement("UserId");
                XMLElement* user_name_element     = account_element->FirstChildElement("UserName");
                XMLElement* user_email            = account_element->FirstChildElement("Email");
                XMLElement* user_phone            = account_element->FirstChildElement("Phone");
                XMLElement* user_address          = account_element->FirstChildElement("Address");
                XMLElement* user_password_element = account_element->FirstChildElement("Password");

                Account account;

                try
                {

                    account.UserId(winrt::guid{ Helpers::StringViewOrDefault(user_id_element->GetText()) });
                }
                catch ( const std::invalid_argument& )
                {
                    account.UserId(GuidHelper::Empty());
                }

                account.UserName(winrt::to_hstring(Helpers::StringViewOrDefault(user_name_element->GetText())));
                account.Email(winrt::to_hstring(Helpers::StringViewOrDefault(user_email->GetText())));
                account.Phone(winrt::to_hstring(Helpers::StringViewOrDefault(user_phone->GetText())));
                account.Address(winrt::to_hstring(Helpers::StringViewOrDefault(user_address->GetText())));
                account.Password(winrt::to_hstring(Helpers::StringViewOrDefault(user_password_element->GetText())));

                m_UserAccountsList.Append(account);
                account_element = account_element->NextSibling();
            }
        }

        return m_UserAccountsList;
    }

#pragma endregion
} // namespace Mercatec::Repositories
