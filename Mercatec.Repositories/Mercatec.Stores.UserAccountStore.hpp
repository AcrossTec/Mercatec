#pragma once

#include <Mercatec.Repositories.Exports.Api.hpp>

#include <winrt/Windows.Foundation.h>
#include <winrt/Windows.Foundation.Collections.h>
#include <winrt/Windows.Security.Credentials.h>
#include <winrt/Mercatec.Models.h>

#include <Mercatec.Helpers.Types.hpp>
#include <string_view>
#include <filesystem>

#pragma warning(push)

// https://learn.microsoft.com/en-us/cpp/error-messages/compiler-warnings/compiler-warning-level-1-c4251?view=msvc-170
// Description: 'type' : class 'type1' needs to have dll-interface to be used by clients of class 'type2'
#pragma warning(disable : 4251)

namespace Mercatec::Repositories
{
    class MERCATEC_REPOSITORIES_API UserAccountStore
    {
    public:
        using Account        = winrt::Mercatec::Models::UserAccount;
        using UserAccount    = winrt::Mercatec::Models::UserAccount;
        using PassportDevice = winrt::Mercatec::Models::PassportDevice;

    public:
        UserAccountStore();

        Guid                       GetUserId(const std::wstring_view user_name) const noexcept;
        UserAccount                GetUserAccount(const Guid& user_id) const noexcept;
        IObservableVector<Account> GetUserAccountsForDevice(const std::wstring_view device_id) const noexcept;
        winrt::com_array<Byte>     GetPublicKey(const Guid& user_id, const std::wstring_view device_id) const noexcept;

        Account AddAccount(const std::wstring_view user_name, const std::wstring_view password) noexcept;
        Boolean RemoveAccount(const Guid& user_id) noexcept;
        Boolean RemoveDevice(const Guid& user_id, const std::wstring_view device_id) noexcept;

        void PassportUpdateDetails( //
          const Guid&                                                                  user_id,
          const std::wstring_view                                                      device_id,
          const array_view<Byte>                                                       public_key,
          const winrt::Windows::Security::Credentials::KeyCredentialAttestationResult& key_attestation_result
        );

    private:
#pragma region Save and Load Helpers
        void InitializeSampleUserAccounts();

        /// <summary>
        ///     Create and save a useraccount list file. (Replacing the old one)
        /// </summary>
        winrt::fire_and_forget SaveAccountListAsync();

        /// <summary>
        ///     Gets the useraccount list file and deserializes it from XML to a list of useraccount objects.
        /// </summary>
        /// <returns>
        ///     List of useraccount objects
        /// </returns>
        winrt::fire_and_forget LoadAccountListAsync();

        /// <summary>
        ///     Uses the local list of accounts and returns an XML formatted string representing the list
        /// </summary>
        /// <returns>
        ///     XML formatted list of accounts
        /// </returns>
        winrt::hstring SerializeAccountListToXml();

        /// <summary>
        ///     Takes an XML formatted string representing a list of accounts and returns a list object of accounts
        /// </summary>
        /// <param name="listAsXml">
        ///     XML formatted list of accounts
        /// </param>
        /// <returns>
        ///     List object of accounts
        /// </returns>
        IObservableVector<Account> DeserializeXmlToAccountList(const std::wstring_view list_as_xml);
#pragma endregion

#pragma region Private Fields
        inline static constexpr std::wstring_view USER_ACCOUNT_LIST_FILE_NAME = L"AccountList.xml";

        std::filesystem::path      m_UserAccountListPath;
        IObservableVector<Account> m_UserAccountsList;
#pragma endregion
    };
} // namespace Mercatec::Repositories

#pragma warning(pop)
