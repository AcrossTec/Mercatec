#include "pch.h"
#include "Mercatec.Services.AuthService.hpp"

namespace Mercatec::Services
{
    AuthService::AuthService()
    {
    }

    AuthService& AuthService::Instance() noexcept
    {
        static AuthService auth_service;
        return auth_service;
    }

    Guid AuthService::GetUserId(const std::wstring_view user_name) const noexcept
    {
        return m_AccountStore.GetUserId(user_name);
    }

    AuthService::AccountStore_t::Account AuthService::GetUserAccount(const Guid& user_id) const noexcept
    {
        return m_AccountStore.GetUserAccount(user_id);
    }

    IObservableVector<AuthService::AccountStore_t::Account> AuthService::GetUserAccountsForDevice(const std::wstring_view device_id) const noexcept
    {
        return m_AccountStore.GetUserAccountsForDevice(device_id);
    }

    void AuthService::Register(const std::wstring_view user_name, const std::wstring_view password) noexcept
    {
        m_AccountStore.AddAccount(user_name, password);
    }

    bool AuthService::PassportRemoveUser(const Guid& user_id) noexcept
    {
        return m_AccountStore.RemoveAccount(user_id);
    }

    bool AuthService::PassportRemoveDevice(const Guid& user_id, const std::wstring_view device_id) noexcept
    {
        return m_AccountStore.RemoveDevice(user_id, device_id);
    }

    void AuthService::PassportUpdateDetails( //
      const Guid&                                                                  user_id,
      const std::wstring_view                                                      device_id,
      const array_view<Byte>                                                       public_key,
      const winrt::Windows::Security::Credentials::KeyCredentialAttestationResult& key_attestation_result
    ) noexcept
    {
        m_AccountStore.PassportUpdateDetails(user_id, device_id, public_key, key_attestation_result);
    }

    bool AuthService::ValidateCredentials(const std::wstring_view user_name, const std::wstring_view password)
    {
        if ( not user_name.empty() and not password.empty() )
        {
            // This would be used for existing accounts migrating to use Passport
            const Guid user_id = GetUserId(user_name);

            if ( user_id != GuidHelper::Empty() )
            {
                const AccountStore_t::Account account = GetUserAccount(user_id);

                if ( account != nullptr )
                {
                    if ( password == account.Password() )
                    {
                        return true;
                    }
                }
            }
        }

        return false;
    }

    bool AuthService::SendServerSignedChallenge(const Guid& user_id, const std::wstring_view device_id, [[maybe_unused]] const array_view<Byte> signed_challenge)
    {
        // Depending on your company polices and procedures this step will be different
        // It is at this point you will need to validate the SignedChallenge that is sent back from the client.
        // Validation is used to ensure the correct user is trying to access this account.
        // The validation process will use the SignedChallenge and the stored PublicKey
        // for the username and the specific device signin is called from.
        // Based on the validation result you will return a bool value to allow access to continue or to block the account.

        // For this sample validation will not happen as a best practice solution does not apply and will need to
        // be configured for each company.
        // Simply just return true.

        // You could get the User's Public Key with something similar to the following:
        [[maybe_unused]] auto user_public_key = m_AccountStore.GetPublicKey(user_id, device_id);
        return true;
    }

    winrt::Windows::Storage::Streams::IBuffer AuthService::PassportRequestChallenge()
    {
        return winrt::Windows::Security::Cryptography::CryptographicBuffer::ConvertStringToBinary( //
          L"ServerChallenge",
          winrt::Windows::Security::Cryptography::BinaryStringEncoding::Utf8
        );
    }
} // namespace Mercatec::Services
