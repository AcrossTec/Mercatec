#pragma once

#include <winrt/Windows.Security.Credentials.h>
#include <Mercatec.Helpers.ViewModels.Entity.hpp>
#include "Mercatec.Models.PassportDevice.hpp"
#include "PassportDevice.g.h"

namespace winrt::Mercatec::Models::implementation
{
    struct PassportDevice : PassportDeviceT<PassportDevice>, ::Mercatec::Helpers::ViewModels::Entity
    {
    public:
        using key_credential_attestation_result_t = Windows::Security::Credentials::KeyCredentialAttestationResult;

        PassportDevice() = default;

        void DeviceId(const std::wstring_view device_id) noexcept;

        hstring DeviceId() const noexcept;

        void PublicKey(const array_view<const uint8_t> public_key);

        com_array<uint8_t> PublicKey() const noexcept;

        void KeyAttestationResult(const key_credential_attestation_result_t& result) noexcept;

        key_credential_attestation_result_t KeyAttestationResult() const noexcept;

    public:
        ::Mercatec::Models::PassportDevice m_Model;

    private:
        key_credential_attestation_result_t m_KeyAttestationResult{ nullptr };
    };
} // namespace winrt::Mercatec::Models::implementation

namespace winrt::Mercatec::Models::factory_implementation
{
    struct PassportDevice : PassportDeviceT<PassportDevice, implementation::PassportDevice>
    {
    };
} // namespace winrt::Mercatec::Models::factory_implementation
