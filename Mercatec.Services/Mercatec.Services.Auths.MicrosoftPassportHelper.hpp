#pragma once

#include <winrt/Windows.Foundation.h>
#include "Mercatec.Services.Exports.Api.hpp"
#include "winrt/Mercatec.Services.Auths.Models.h"

namespace Mercatec::Services::Auths
{
    struct MERCATEC_SERVICES_API MicrosoftPassportHelper sealed abstract
    {
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
        /// <param name="accountId">The "LoginPage.m_Account" id associated with the "LoginPage.m_Account" that we are enrolling into Passport</param>
        /// <returns>Boolean representing if creating the Passport key succeeded</returns>
        static winrt::Windows::Foundation::IAsyncOperation<bool> CreatePassportKeyAsync(const std::wstring_view account_id);

        /// <summary>
        ///     Function to be called when user requests deleting their account.
        ///     Checks the KeyCredentialManager to see if there is a Passport for the current user
        ///     Then deletes the local key associated with the Passport.
        /// </summary>
        static winrt::fire_and_forget RemovePassportAccountAsync(const winrt::Mercatec::Services::Auths::Models::UserAccount& account);

        /// <summary>
        ///     Attempts to sign a message using the Passport key on the system for the accountId passed.
        /// </summary>
        /// <returns>Boolean representing if creating the Passport authentication message succeeded</returns>
        static winrt::Windows::Foundation::IAsyncOperation<bool> GetPassportAuthenticationMessageAsync(const winrt::Mercatec::Services::Auths::Models::UserAccount& account);
    };
} // namespace Mercatec::Services::Auths
