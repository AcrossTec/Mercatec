#pragma once

#include <winrt/Windows.Foundation.h>
#include <winrt/Windows.Foundation.Collections.h>

#include "Mercatec.Models.User.hpp"

#include <string_view>
#include <filesystem>

namespace Mercatec::Helpers
{
    class AccountHelper sealed abstract
    {
    private:
        using Account = Models::User;

        // In the real world this would not be needed as there would be a server implemented that would host a user account database.
        // For this tutorial we will just be storing accounts locally.
        inline static constexpr std::wstring_view USER_ACCOUNT_LIST_FILE_NAME = L"AccountList.xml";

        inline static const std::filesystem::path AccountListPath = std::filesystem::current_path() / USER_ACCOUNT_LIST_FILE_NAME;

        /// <summary>
        ///     Create and save a useraccount list file. (Updating the old one)
        /// </summary>

        static winrt::Windows::Foundation::IAsyncAction SaveAccountListAsync();

    public:
        /// <summary>
        ///     Gets the useraccount list file and deserializes it from XML to a list of useraccount objects.
        /// </summary>
        /// <returns>List of useraccount objects</returns>
        static winrt::Windows::Foundation::IAsyncOperation<winrt::Windows::Foundation::Collections::IVector<typename Account>> LoadAccountListAsync();

        /// <summary>
        /// Uses the local list of accounts and returns an XML formatted string representing the list
        /// </summary>
        /// <returns>XML formatted list of accounts</returns>
        static winrt::hstring SerializeAccountListToXml();

        /// <summary>
        /// Takes an XML formatted string representing a list of accounts and returns a list object of accounts
        /// </summary>
        /// <param name="listAsXml">XML formatted list of accounts</param>
        /// <returns>List object of accounts</returns>
        static winrt::Windows::Foundation::Collections::IVector<Account>& DeserializeXmlToAccountList(const std::wstring_view list_as_xml);

        static Account AddAccount(const std::wstring_view user_name);

        static void RemoveAccount(const Account& account);

        static bool ValidateAccountCredentials(const std::wstring_view user_name);

    public:
        static winrt::Windows::Foundation::Collections::IVector<Account> AccountList;
    };
} // namespace Mercatec::Helpers
