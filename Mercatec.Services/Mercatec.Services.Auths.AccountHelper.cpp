#include "pch.h"
#include "Mercatec.Services.Auths.AccountHelper.hpp"
#include "Mercatec.Helpers.Debug.hpp"
#include "Mercatec.Helpers.Strings.hpp"
#include "Mercatec.Helpers.Widespread.hpp"
#include <winrt/Windows.Storage.h>
#include <tinyxml2.h>
#include <algorithm>
#include <fstream>
#include <ios>

namespace Mercatec::Services::Auths
{
    winrt::IObservableVector<AccountHelper::Account> AccountHelper::AccountList{ winrt::single_threaded_observable_vector<AccountHelper::Account>() };

    /// <summary>
    ///     Create and save a useraccount list file. (Updating the old one)
    /// </summary>
    /// <remarks>
    ///     https://learn.microsoft.com/en-us/windows/uwp/files/
    ///     https://learn.microsoft.com/en-us/windows/uwp/files/quickstart-reading-and-writing-files
    ///     https://learn.microsoft.com/en-us/windows/uwp/files/best-practices-for-writing-to-files
    ///     https://en.cppreference.com/w/cpp/io/basic_filebuf/open
    /// </remarks>
    winrt::fire_and_forget AccountHelper::SaveAccountListAsync()
    {
        using namespace winrt::Windows::Storage;

        const winrt::hstring accounts_xml = SerializeAccountListToXml();

        if ( std::filesystem::exists(AccountListPath) )
        {
            auto accounts_file = co_await StorageFile::GetFileFromPathAsync(AccountListPath.c_str());
            co_await FileIO::WriteTextAsync(accounts_file, accounts_xml);
        }
        else
        {
#ifdef WINDOWS_APPLICATION_PACKAGING_PROJECT_ENABLED
            auto accounts_file = co_await ApplicationData::Current().LocalFolder().CreateFileAsync(USER_ACCOUNT_LIST_FILE_NAME);
            co_await FileIO::WriteTextAsync(accounts_file, accounts_xml);
#else
            std::wofstream accounts_file{ USER_ACCOUNT_LIST_FILE_NAME.data(), std::ios::out | std::ios::binary };
            accounts_file.write(accounts_xml.c_str(), accounts_xml.size() * sizeof(winrt::hstring::value_type));
#endif
        }
    }

    /// <summary>
    ///     Gets the useraccount list file and deserializes it from XML to a list of useraccount objects.
    /// </summary>
    /// <returns>List of useraccount objects</returns>
    winrt::IAsyncOperation<winrt::IObservableVector<AccountHelper::Account>> AccountHelper::LoadAccountListAsync()
    {
        using namespace winrt::Windows::Storage;

        if ( std::filesystem::exists(AccountListPath) )
        {
            auto accounts_file = co_await StorageFile::GetFileFromPathAsync(AccountListPath.c_str());

            winrt::hstring accounts_xml = co_await FileIO::ReadTextAsync(accounts_file);
            DeserializeXmlToAccountList(accounts_xml);
        }

        co_return AccountList;
    }

    /// <summary>
    /// Uses the local list of accounts and returns an XML formatted string representing the list
    /// </summary>
    /// <returns>XML formatted list of accounts</returns>
    winrt::hstring AccountHelper::SerializeAccountListToXml()
    {
        using namespace tinyxml2;

        tinyxml2::XMLDocument document;

        XMLElement* root = document.NewElement("Accounts");
        document.InsertFirstChild(root);

        for ( const auto& user : AccountList )
        {
            XMLElement* account = document.NewElement("Account");

            XMLElement* user_id       = document.NewElement("UserId");
            XMLElement* user_name     = document.NewElement("UserName");
            // XMLElement* user_email    = document.NewElement("Email");
            // XMLElement* user_phone    = document.NewElement("Phone");
            // XMLElement* user_address  = document.NewElement("Address");
            XMLElement* user_password = document.NewElement("Password");

            user_id->SetText(Helpers::GuidToString(user.UserId()).c_str());
            user_name->SetText(winrt::to_string(user.UserName()).c_str());
            // user_email->SetText("");
            // user_phone->SetText("");
            // user_address->SetText("");
            user_password->SetText(winrt::to_string(user.Password()).c_str());

            account->InsertEndChild(user_id);
            account->InsertEndChild(user_name);
            // account->InsertEndChild(user_email);
            // account->InsertEndChild(user_phone);
            // account->InsertEndChild(user_address);
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
    winrt::IObservableVector<AccountHelper::Account> AccountHelper::DeserializeXmlToAccountList(const std::wstring_view list_as_xml)
    {
        using namespace tinyxml2;

        tinyxml2::XMLDocument document;

        if ( document.Parse(winrt::to_string(list_as_xml).c_str()) == XML_SUCCESS )
        {
            AccountList.Clear();

            auto root = document.FirstChildElement("Accounts");

            XMLNode* account_element = root->FirstChildElement("Account");

            while ( account_element != nullptr )
            {
                XMLElement* user_id_element       = account_element->FirstChildElement("UserId");
                XMLElement* user_name_element     = account_element->FirstChildElement("UserName");
                XMLElement* user_password_element = account_element->FirstChildElement("Password");

                Account account;

                try
                {

                    account.UserId(winrt::guid{ Helpers::StringViewOrDefault(user_id_element->GetText()) });
                }
                catch ( const std::invalid_argument& )
                {
                    account.UserId(winrt::Windows::Foundation::GuidHelper::Empty());
                }

                account.UserName(winrt::to_hstring(Helpers::StringViewOrDefault(user_name_element->GetText())));
                account.Password(winrt::to_hstring(Helpers::StringViewOrDefault(user_password_element->GetText())));

                AccountList.Append(account);
                account_element = account_element->NextSibling();
            }
        }

        return AccountList;
    }

    AccountHelper::Account AccountHelper::AddAccount(const std::wstring_view user_name)
    {
        // Create a new account with the username
        Account account;
        account.UserId(winrt::GuidHelper::CreateNewGuid());
        account.UserName(user_name);

        // Add it to the local list of accounts
        AccountList.Append(account);

        // SaveAccountList and return the account
        SaveAccountListAsync();
        return account;
    }

    void AccountHelper::RemoveAccount(const Account& account)
    {
        // Remove the account from the accounts list
        if ( auto found = //
             std::find_if(
               AccountList.begin(),
               AccountList.end(), //
               [&](const Account& value) { return account.UserName() == value.UserName(); }
             );
             found != AccountList.end() )
        {
            const ptrdiff_t account_index = std::distance(AccountList.begin(), found);
            AccountList.RemoveAt(static_cast<uint32_t>(account_index));
        }

        // Re save the updated list
        SaveAccountListAsync();
    }

    bool AccountHelper::ValidateAccountCredentials(const std::wstring_view user_name)
    {
        // In the real world, this method would call the server to authenticate that the account exists and is valid.
        // For this tutorial however we will just have a existing sample user that is just "SampleUserName"
        // If the username is null or does not match "SampleUserName" it will fail validation.
        // In which case the user should register a new passport user

        if ( user_name.empty() )
        {
            return false;
        }

        if ( user_name != L"SampleUserName" )
        {
            return false;
        }

        return true;
    }
} // namespace Mercatec::Services::Auths
