#include "pch.h"
#include "Mercatec.Services.MicrosoftPassportService.hpp"
#include "Mercatec.Helpers.Debug.hpp"

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

            Helpers::OutputDebug(L"Microsoft Passport is not setup!\nPlease go to Windows Settings and set up a PIN to use it.");
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
                Helpers::OutputDebug(L"Successfully made key");

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
                Helpers::OutputDebug(L"User cancelled sign-in process.");
                break;
            }
            case winrt::Windows::Security::Credentials::KeyCredentialStatus::NotFound:
            {
                // User needs to setup Microsoft Passport
                Helpers::OutputDebug(L"Microsoft Passport is not setup!\nPlease go to Windows Settings and set up a PIN to use it.");
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
        }

        // Then delete the account from the machines list of Passport Accounts
        co_await WSC::KeyCredentialManager::DeleteAsync(account.UserName());
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
            co_return true;
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
            if ( co_await CreatePassportKeyAsync(account.UserName()) )
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
