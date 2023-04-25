#include "pch.h"
#include "Mercatec.Models.AccountHelper.hpp"

#include "Mercatec.Helpers.Debug.hpp"

#include <winrt/Windows.Foundation.Diagnostics.h>
#include <winrt/Windows.Storage.h>
#include <winrt/Windows.System.h>

#include <tinyxml2.h>
#include <algorithm>

namespace Mercatec::Helpers
{
    WFC::IVector<AccountHelper::Account> AccountHelper::AccountList{ winrt::single_threaded_vector<AccountHelper::Account>() };

    /// <summary>
    ///     Create and save a useraccount list file. (Updating the old one)
    /// </summary>
    winrt::Windows::Foundation::IAsyncAction AccountHelper::SaveAccountListAsync()
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
            auto accounts_file = co_await ApplicationData::Current().LocalFolder().CreateFileAsync(USER_ACCOUNT_LIST_FILE_NAME);
            co_await FileIO::WriteTextAsync(accounts_file, accounts_xml);
        }
    }

    /// <summary>
    ///     Gets the useraccount list file and deserializes it from XML to a list of useraccount objects.
    /// </summary>
    /// <returns>List of useraccount objects</returns>
    winrt::Windows::Foundation::IAsyncOperation<WFC::IVector<AccountHelper::Account>> AccountHelper::LoadAccountListAsync()
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

        XMLNode* root = document.NewElement("Accounts");
        document.InsertFirstChild(root);

        for ( const auto& user : AccountList )
        {
            XMLNode* account = document.NewElement("Account");

            XMLNode* user_id       = document.NewElement("UserId");
            XMLNode* user_name     = document.NewElement("UserName");
            XMLNode* user_email    = document.NewElement("Email");
            XMLNode* user_phone    = document.NewElement("Phone");
            XMLNode* user_address  = document.NewElement("Address");
            XMLNode* user_password = document.NewElement("Password");

            user_id->SetValue("0");
            user_name->SetValue(winrt::to_string(user.UserName).c_str());
            user_email->SetValue("");
            user_phone->SetValue("");
            user_address->SetValue("");
            user_password->SetValue("");

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
    /// Takes an XML formatted string representing a list of accounts and returns a list object of accounts
    /// </summary>
    /// <param name="listAsXml">XML formatted list of accounts</param>
    /// <returns>List object of accounts</returns>
    WFC::IVector<AccountHelper::Account>& AccountHelper::DeserializeXmlToAccountList(const std::wstring_view list_as_xml)
    {
        using namespace tinyxml2;

        tinyxml2::XMLDocument document;

        if ( document.Parse(winrt::to_string(list_as_xml).c_str()) == XML_SUCCESS )
        {
            AccountList.Clear();

            auto root = document.FirstChildElement("Accounts");

            XMLElement* child = root->FirstChildElement("Account");

            while ( child != nullptr )
            {
                Account account;
                account.UserId   = child->Int64Text();
                account.UserName = winrt::to_hstring(child->Value());

                AccountList.Append(account);
                child = child->NextSibling()->ToElement();
            }
        }

        return AccountList;
    }

    AccountHelper::Account AccountHelper::AddAccount(const std::wstring_view user_name)
    {
        // Create a new account with the username
        Account account;
        account.UserName = user_name;

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
               [&](const Account& value) { return account.UserName == value.UserName; }
             );
             found != AccountList.end() )
        {
            AccountList.RemoveAt(static_cast<uint32_t>(std::distance(AccountList.begin(), found)));
        }

        // Re save the updated list
        SaveAccountListAsync();
    }

    bool AccountHelper::ValidateAccountCredentials(const std::wstring_view user_name)
    {
        // In the real world, this method would call the server to authenticate that the account exists and is valid.
        // For this tutorial however we will just have a existing sample user that is just "SampleUsername"
        // If the username is null or does not match "sampleUsername" it will fail validation.
        // In which case the user should register a new passport user

        if ( user_name.empty() )
        {
            return false;
        }

        if ( user_name != L"SampleUsername" )
        {
            return false;
        }

        return true;
    }
} // namespace Mercatec::Helpers
