// Copyright (c) Microsoft Corporation and Contributors.
// Licensed under the MIT License.

#pragma once

#include "winrt/Microsoft.UI.Xaml.h"
#include "winrt/Microsoft.UI.Xaml.Markup.h"
#include "winrt/Microsoft.UI.Xaml.Controls.Primitives.h"
#include "winrt/Windows.Security.Credentials.h"
#include "Auths.Models.PassportDevice.g.h"

namespace winrt::Mercatec::Services::Auths::Models::implementation
{
    struct PassportDevice : PassportDeviceT<PassportDevice>
    {
    public:
        using key_credential_attestation_result_t = Windows::Security::Credentials::KeyCredentialAttestationResult;

        PassportDevice() = default;

        void DeviceId(const winrt::guid& device_id) noexcept;

        winrt::guid DeviceId() const noexcept;

        void PublicKey(const array_view<const uint8_t> public_key);

        com_array<uint8_t> PublicKey() const noexcept;

        void KeyAttestationResult(const key_credential_attestation_result_t& result) noexcept;

        key_credential_attestation_result_t KeyAttestationResult() const noexcept;

    private:
        std::vector<uint8_t>                m_PublicKey;
        winrt::guid                         m_DeviceId{ GuidHelper::Empty() };
        key_credential_attestation_result_t m_KeyAttestationResult{ nullptr };
    };
} // namespace winrt::Mercatec::Services::Auths::Models::implementation

namespace winrt::Mercatec::Services::Auths::Models::factory_implementation
{
    struct PassportDevice : PassportDeviceT<PassportDevice, implementation::PassportDevice>
    {
    };
} // namespace winrt::Mercatec::Services::Auths::Models::factory_implementation
