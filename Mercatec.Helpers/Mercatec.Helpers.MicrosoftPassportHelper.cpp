#include "pch.h"
#include "Mercatec.Helpers.MicrosoftPassportHelper.hpp"
#include "Mercatec.Helpers.Debug.hpp"

namespace Mercatec::Helpers
{
    /// <summary>
    /// Checks to see if Passport is ready to be used.
    ///
    /// Passport has dependencies on:
    ///     1. Having a connected Microsoft Account
    ///     2. Having a Windows PIN set up for that _account on the local machine
    /// </summary>
    winrt::IAsyncOperation<bool> MicrosoftPassportHelper::MicrosoftPassportAvailableCheckAsync() noexcept
    {
        const bool key_credential_available = co_await winrt::Windows::Security::Credentials::KeyCredentialManager::IsSupportedAsync();

        if ( key_credential_available == false )
        {
            // Key credential is not enabled yet as user
            // needs to connect to a Microsoft Account and select a PIN in the connecting flow.

            OutputDebug(L"Microsoft Passport is not setup!\nPlease go to Windows Settings and set up a PIN to use it.");
            co_return false;
        }

        co_return true;
    }

    /// <summary>
    /// Creates a Passport key on the machine using the _account id passed.
    /// </summary>
    /// <param name="accountId">The _account id associated with the _account that we are enrolling into Passport</param>
    /// <returns>Boolean representing if creating the Passport key succeeded</returns>
    winrt::IAsyncOperation<bool> MicrosoftPassportHelper::CreatePassportKeyAsync(const std::wstring_view account_id)
    {
        winrt::Windows::Security::Credentials::KeyCredentialRetrievalResult key_creation_result =   //
          co_await winrt::Windows::Security::Credentials::KeyCredentialManager::RequestCreateAsync( //
            account_id,
            winrt::Windows::Security::Credentials::KeyCredentialCreationOption::ReplaceExisting
          );

        switch ( key_creation_result.Status() )
        {
            case winrt::Windows::Security::Credentials::KeyCredentialStatus::Success:
            {
                OutputDebug(L"Successfully made key");

                // In the real world authentication would take place on a server.
                // So every time a user migrates or creates a new Microsoft Passport account Passport details should be pushed to the server.
                // The details that would be pushed to the server include:
                // The public key, keyAttesation if available,
                // certificate chain for attestation endorsement key if available,
                // status code of key attestation result: keyAttestationIncluded or
                // keyAttestationCanBeRetrievedLater and keyAttestationRetryType
                // As this sample has no concept of a server it will be skipped for now
                // for information on how to do this refer to the second Passport sample

                // For this sample just return true
                co_return true;
            }
            case winrt::Windows::Security::Credentials::KeyCredentialStatus::UserCanceled:
            {
                OutputDebug(L"User cancelled sign-in process.");
                break;
            }
            case winrt::Windows::Security::Credentials::KeyCredentialStatus::NotFound:
            {
                // User needs to setup Microsoft Passport
                OutputDebug(L"Microsoft Passport is not setup!\nPlease go to Windows Settings and set up a PIN to use it.");
                break;
            }
            default:
            {
                break;
            }
        }

        co_return false;
    }
} // namespace Mercatec::Helpers
