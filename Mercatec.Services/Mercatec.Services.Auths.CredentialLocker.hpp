#pragma once

#include "Mercatec.Services.Exports.Api.hpp"

#include <winrt/Windows.Foundation.h>
#include <winrt/Windows.Security.Credentials.h>

namespace Mercatec::Services::Auths
{
    struct MERCATEC_SERVICES_API CredentialLockerService sealed abstract
    {
    public:
        CredentialLockerService();

    private:
        winrt::Windows::Security::Credentials::PasswordVault m_PasswordVault;
    };
} // namespace Mercatec::Services::Auths