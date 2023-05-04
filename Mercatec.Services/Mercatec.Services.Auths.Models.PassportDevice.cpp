// Copyright (c) Microsoft Corporation and Contributors.
// Licensed under the MIT License.

#include "pch.h"
#include "Mercatec.Services.Auths.Models.PassportDevice.h"
#if __has_include("Auths.Models.PassportDevice.g.cpp")
# include "Auths.Models.PassportDevice.g.cpp"
#endif

using namespace winrt;
using namespace Microsoft::UI::Xaml;

// To learn more about WinUI, the WinUI project structure,
// and more about our project templates, see: http://aka.ms/winui-project-info.

namespace winrt::Mercatec::Services::Auths::Models::implementation
{
    void PassportDevice::DeviceId(const winrt::guid& device_id) noexcept
    {
        m_DeviceId = device_id;
    }

    winrt::guid PassportDevice::DeviceId() const noexcept
    {
        return m_DeviceId;
    }

    void PassportDevice::PublicKey(const array_view<const uint8_t> public_key)
    {
        m_PublicKey.assign(public_key.cbegin(), public_key.cend());
    }

    com_array<uint8_t> PassportDevice::PublicKey() const noexcept
    {
        return com_array<uint8_t>(m_PublicKey);
    }

    void PassportDevice::KeyAttestationResult(const key_credential_attestation_result_t& key_credential_result) noexcept
    {
        m_KeyAttestationResult = key_credential_result;
    }

    PassportDevice::key_credential_attestation_result_t PassportDevice::KeyAttestationResult() const noexcept
    {
        return m_KeyAttestationResult;
    }
} // namespace winrt::Mercatec::Services::Auths::Models::implementation
