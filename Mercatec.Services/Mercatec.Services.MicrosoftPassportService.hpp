#pragma once

#include "Mercatec.Services.Exports.Api.hpp"

#include <winrt/Windows.Foundation.h>
#include <winrt/Windows.Security.Credentials.h>

#include <winrt/Mercatec.Models.h>

namespace Mercatec::Services
{
    //! https://learn.microsoft.com/en-us/windows/uwp/security/microsoft-passport-login
    //! https://learn.microsoft.com/en-us/windows/uwp/security/microsoft-passport-login-auth-service
    struct MERCATEC_SERVICES_API MicrosoftPassportHelper sealed abstract
    {
        using Account = winrt::Mercatec::Models::UserAccount;

        /// <summary>
        /// Checks to see if Passport is ready to be used.
        ///
        /// Passport has dependencies on:
        ///     1. Having a connected Microsoft Account
        ///     2. Having a Windows PIN set up for that "LoginPage.m_Account" on the local machine
        /// </summary>
        static winrt::Windows::Foundation::IAsyncOperation<bool> MicrosoftPassportAvailableCheckAsync() noexcept;

        /// <summary>
        ///     Creates a Passport key on the machine using the "LoginPage.m_Account" id passed.
        /// </summary>
        /// <param name="user_name">The "LoginPage.m_Account" id associated with the "LoginPage.m_Account" that we are enrolling into Passport</param>
        /// <returns>Boolean representing if creating the Passport key succeeded</returns>
        static winrt::Windows::Foundation::IAsyncOperation<bool> CreatePassportKeyAsync(const std::wstring_view user_name);

        /// <summary>
        ///     Creates a Passport key on the machine using the "LoginPage.m_Account" id passed.
        /// </summary>
        static winrt::Windows::Foundation::IAsyncOperation<bool> CreatePassportKeyAsync(const winrt::guid& user_id, const std::wstring_view user_name);

        /// <summary>
        ///     Function to be called when user requests deleting their account.
        ///     Checks the KeyCredentialManager to see if there is a Passport for the current user
        ///     Then deletes the local key associated with the Passport.
        /// </summary>
        static winrt::fire_and_forget RemovePassportAccountAsync(const Account& account);

        /// <summary>
        ///     Function to be called when user requests deleting their account.
        /// </summary>
        static void RemovePassportDevice(const Account& account, const std::wstring_view device_id);

        /// <summary>
        ///     Attempts to sign a message using the Passport key on the system for the accountId passed.
        /// </summary>
        /// <returns>Boolean representing if creating the Passport authentication message succeeded</returns>
        static winrt::Windows::Foundation::IAsyncOperation<bool> GetPassportAuthenticationMessageAsync(const Account& account);

        /// <summary>
        ///     This method will demonstrate how to obtain all the necessary information that can be
        ///     provided by Windows Hello for each account on a specific device.
        /// </summary>
        static winrt::Windows::Foundation::IAsyncAction GetKeyAttestationAsync( //
          const winrt::guid&                                                         user_id,
          const winrt::Windows::Security::Credentials::KeyCredentialRetrievalResult& key_creation_result
        );

        /// <summary>
        ///     You may have noticed in the GetKeyAttestationAsync method that you just added the last line was commented out.
        ///     This last line will be a new method you create that will send all the Windows Hello information to the AuthService.
        ///     In the real world you would need to send this to an actual server with a Web API.
        /// </summary>
        static bool UpdatePassportDetails( //
          const winrt::guid&                                                           user_id,
          const std::wstring_view                                                      device_id,
          const winrt::array_view<uint8_t>                                             public_key,
          const winrt::Windows::Security::Credentials::KeyCredentialAttestationResult& key_attestation_result
        );

        /// <summary>
        ///     This will request a challenge from the AuthService, locally sign that challenge
        ///     using a Passport API and send the signed challenge to the AuthService.
        ///     In this hands on lab the AuthService will receive the signed challenge and return true.
        ///     In an actual implementation you would need to implement a verification mechanism to determine is the challenge
        ///     was signed by the correct user on the correct device.
        /// </summary>
        static winrt::Windows::Foundation::IAsyncOperation<bool> RequestSignAsync( //
          const winrt::guid&                                                         user_id,
          const winrt::Windows::Security::Credentials::KeyCredentialRetrievalResult& open_key_result
        );
    };
} // namespace Mercatec::Services
