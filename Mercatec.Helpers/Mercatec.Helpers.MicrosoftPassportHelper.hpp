#pragma once

#include <winrt/Windows.Foundation.h>
#include "Mercatec.Helpers.Exports.Api.hpp"

namespace Mercatec::Helpers
{
    struct MERCATEC_HELPERS_API MicrosoftPassportHelper sealed abstract
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
        /// Creates a Passport key on the machine using the "LoginPage.m_Account" id passed.
        /// </summary>
        /// <param name="accountId">The "LoginPage.m_Account" id associated with the "LoginPage.m_Account" that we are enrolling into Passport</param>
        /// <returns>Boolean representing if creating the Passport key succeeded</returns>
        static winrt::Windows::Foundation::IAsyncOperation<bool> CreatePassportKeyAsync(const std::wstring_view account_id);
    };
} // namespace Mercatec::Helpers
