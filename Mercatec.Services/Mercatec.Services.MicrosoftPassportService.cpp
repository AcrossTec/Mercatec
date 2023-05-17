#include "pch.h"
#include "Mercatec.Services.MicrosoftPassportService.hpp"
#include "Mercatec.Services.AuthService.hpp"

#include <Mercatec.Helpers.Auth.hpp>

using Mercatec::Helpers::OutputDebug;

namespace Mercatec::Services
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
    winrt::IAsyncOperation<bool> MicrosoftPassportHelper::CreatePassportKeyAsync(const std::wstring_view user_name)
    {
        WSC::KeyCredentialRetrievalResult key_creation_result = co_await WSC::KeyCredentialManager::RequestCreateAsync(user_name, WSC::KeyCredentialCreationOption::ReplaceExisting);

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

    /// <summary>
    ///     Creates a Passport key on the machine using the "LoginPage.m_Account" id passed.
    /// </summary>
    winrt::IAsyncOperation<bool> MicrosoftPassportHelper::CreatePassportKeyAsync(const winrt::guid& user_id, const std::wstring_view user_name)
    {
        WSC::KeyCredentialRetrievalResult key_creation_result = co_await WSC::KeyCredentialManager::RequestCreateAsync(user_name, WSC::KeyCredentialCreationOption::ReplaceExisting);

        switch ( key_creation_result.Status() )
        {
            case WSC::KeyCredentialStatus::Success:
            {
                OutputDebug(L"Successfully made key");
                co_await GetKeyAttestationAsync(user_id, key_creation_result);
                co_return true;
            }
            case WSC::KeyCredentialStatus::UserCanceled:
            {
                OutputDebug(L"User cancelled sign-in process.");
                break;
            }
            case WSC::KeyCredentialStatus::NotFound:
            {
                // User needs to setup Windows Hello
                OutputDebug(L"Windows Hello is not setup!\nPlease go to Windows Settings and set up a PIN to use it.");
                break;
            }
            default:
            {
                break;
            }
        }

        co_return false;
    }

    /// <summary>
    ///     This method will demonstrate how to obtain all the necessary information that can be
    ///     provided by Windows Hello for each account on a specific device.
    /// </summary>
    winrt::IAsyncAction MicrosoftPassportHelper::GetKeyAttestationAsync(const winrt::guid& user_id, const WSC::KeyCredentialRetrievalResult& key_creation_result)
    {
        WSC::KeyCredential                  user_key                               = key_creation_result.Credential();
        WSS::IBuffer                        public_key                             = user_key.RetrievePublicKey();
        WSC::KeyCredentialAttestationResult key_attestation_result                 = co_await user_key.GetAttestationAsync();
        WSS::IBuffer                        key_attestation                        = nullptr;
        WSS::IBuffer                        certificate_chain                      = nullptr;
        bool                                key_attestation_included               = false;
        bool                                key_attestation_can_be_retrieved_later = false;
        WSC::KeyCredentialAttestationStatus key_attestation_retry_type             = WSC::KeyCredentialAttestationStatus::Success;

        if ( key_attestation_result.Status() == WSC::KeyCredentialAttestationStatus::Success )
        {
            key_attestation_included = true;
            key_attestation          = key_attestation_result.AttestationBuffer();
            certificate_chain        = key_attestation_result.CertificateChainBuffer();
            OutputDebug(L"Successfully made key and attestation");
        }
        else if ( key_attestation_result.Status() == WSC::KeyCredentialAttestationStatus::TemporaryFailure )
        {
            key_attestation_retry_type             = WSC::KeyCredentialAttestationStatus::TemporaryFailure;
            key_attestation_can_be_retrieved_later = true;
            OutputDebug(L"Successfully made key but not attestation");
        }
        else if ( key_attestation_result.Status() == WSC::KeyCredentialAttestationStatus::NotSupported )
        {
            key_attestation_retry_type             = WSC::KeyCredentialAttestationStatus::NotSupported;
            key_attestation_can_be_retrieved_later = false;
            OutputDebug(L"Key created, but key attestation not supported");
        }

        const String device_id = Helpers::GetDeviceId();

        // Update the Pasport details with the information we have just gotten above.
        UpdatePassportDetails(user_id, device_id, { public_key.data(), public_key.Length() }, key_attestation_result);
    }

    bool MicrosoftPassportHelper::UpdatePassportDetails(const winrt::guid& user_id, const std::wstring_view device_id, const winrt::array_view<uint8_t> public_key, const WSC::KeyCredentialAttestationResult& key_attestation_result)
    {
        // In the real world you would use an API to add Passport signing info to server for the signed in _account.
        // For this tutorial we do not implement a WebAPI for our server and simply mock the server locally
        // The CreatePassportKey method handles adding the Windows Hello account locally to the device using the KeyCredential Manager

        // Using the userId the existing account should be found and updated.
        AuthService::Instance().PassportUpdateDetails(user_id, device_id, public_key, key_attestation_result);
        return true;
    }

    winrt::IAsyncOperation<bool> MicrosoftPassportHelper::RequestSignAsync(const winrt::guid& user_id, const WSC::KeyCredentialRetrievalResult& open_key_result)
    {
        // Calling user_key.RequestSignAsync() prompts the uses to enter the PIN or use Biometrics (Windows Hello).
        // The app would use the private key from the user account to sign the sign-in request (challenge)
        // The client would then send it back to the server and await the servers response.

        WSS::IBuffer                      challenge_message = AuthService::Instance().PassportRequestChallenge();
        WSC::KeyCredential                user_key          = open_key_result.Credential();
        WSC::KeyCredentialOperationResult sign_result       = co_await user_key.RequestSignAsync(challenge_message);

        if ( sign_result.Status() == WSC::KeyCredentialStatus::Success )
        {
            // If the challenge from the server is signed successfully
            // send the signed challenge back to the server and await the servers response
            co_return AuthService::Instance().SendServerSignedChallenge(user_id, Helpers::GetDeviceId(), { sign_result.Result().data(), sign_result.Result().Length() });
        }
        else if ( sign_result.Status() == WSC::KeyCredentialStatus::UserCanceled )
        {
            // User cancelled the Windows Hello PIN entry.
        }
        else if ( sign_result.Status() == WSC::KeyCredentialStatus::NotFound )
        {
            // Must recreate Windows Hello key
        }
        else if ( sign_result.Status() == WSC::KeyCredentialStatus::SecurityDeviceLocked )
        {
            // Can't use Windows Hello right now, remember that hardware failed and suggest restart
        }
        else if ( sign_result.Status() == WSC::KeyCredentialStatus::UnknownError )
        {
            // Can't use Windows Hello right now, try again later
        }

        co_return false;
    }

    /// <summary>
    ///     Function to be called when user requests deleting their account.
    ///     Checks the KeyCredentialManager to see if there is a Passport for the current user
    ///     Then deletes the local key associated with the Passport.
    /// </summary>
    winrt::fire_and_forget MicrosoftPassportHelper::RemovePassportAccountAsync(const Account& account)
    {
        // Open the account with Passport
        WSC::KeyCredentialRetrievalResult key_open_result = co_await WSC::KeyCredentialManager::OpenAsync(account.UserName());

        if ( key_open_result.Status() == WSC::KeyCredentialStatus::Success )
        {
            // In the real world you would send key information to server to unregister
            // for example, RemovePassportAccountOnServer(account);
            AuthService::Instance().PassportRemoveUser(account.UserId());
        }

        // Then delete the account from the machines list of Passport Accounts
        co_await WSC::KeyCredentialManager::DeleteAsync(account.UserName());
    }

    /// <summary>
    ///     Function to be called when user requests deleting their account.
    /// </summary>
    void MicrosoftPassportHelper::RemovePassportDevice(const Account& account, const std::wstring_view device_id)
    {
        AuthService::Instance().PassportRemoveDevice(account.UserId(), device_id);
    }

    /// <summary>
    ///     Attempts to sign a message using the Passport key on the system for the accountId passed.
    /// </summary>
    /// <returns>Boolean representing if creating the Passport authentication message succeeded</returns>
    winrt::Windows::Foundation::IAsyncOperation<bool> MicrosoftPassportHelper::GetPassportAuthenticationMessageAsync(const Account& insecure_account)
    {
        //! https://learn.microsoft.com/en-us/cpp/code-quality/c26811?view=msvc-170
        //! https://learn.microsoft.com/en-us/windows/uwp/cpp-and-winrt-apis/concurrency#parameter-passing
        //! Warning C26811 Lifetime of the memory referenced by parameter ''args'' might end by the time the coroutine is resumed(lifetime .1)

        const Account account = insecure_account;

        WSC::KeyCredentialRetrievalResult open_key_result = co_await WSC::KeyCredentialManager::OpenAsync(account.UserName());

        // Calling OpenAsync will allow the user access to what is available in the app and will not require user credentials again.
        // If you wanted to force the user to sign in again you can use the following:
        // var consentResult = await Windows.Security.Credentials.UI.UserConsentVerifier.RequestVerificationAsync(account.Username);
        // This will ask for the either the password of the currently signed in Microsoft Account or the PIN used for Microsoft Passport.

        if ( open_key_result.Status() == WSC::KeyCredentialStatus::Success )
        {
            // If OpenAsync has succeeded, the next thing to think about is whether the client application requires access to backend services.
            // If it does here you would Request a challenge from the Server. The client would sign this challenge and the server
            // would check the signed challenge. If it is correct it would allow the user access to the backend.
            // You would likely make a new method called RequestSignAsync to handle all this
            // for example, RequestSignAsync(openKeyResult);
            // Refer to the second Microsoft Passport sample for information on how to do this.

            // For this sample there is not concept of a server implemented so just return true.
            co_return co_await RequestSignAsync(account.UserId(), open_key_result);
        }
        else if ( open_key_result.Status() == WSC::KeyCredentialStatus::NotFound )
        {
            // If the _account is not found at this stage. It could be one of two errors.
            // 1. Microsoft Passport has been disabled
            // 2. Microsoft Passport has been disabled and re-enabled cause the Microsoft Passport Key to change.
            // Calling CreatePassportKey and passing through the account will attempt to replace the existing Microsoft Passport Key for that account.
            // If the error really is that Microsoft Passport is disabled then the CreatePassportKey method will output that error.

            __pragma(warning(push));
            __pragma(warning(disable : 26811));
            if ( co_await CreatePassportKeyAsync(account.UserId(), account.UserName()) )
            {
                // If the Passport Key was again successfully created, Microsoft Passport has just been reset.
                // Now that the Passport Key has been reset for the _account retry sign in.
                co_return co_await GetPassportAuthenticationMessageAsync(account);
            }
            __pragma(warning(pop));
        }

        // Can't use Passport right now, try again later
        co_return false;
    }
} // namespace Mercatec::Services
