#include "pch.h"
#include "Mercatec.Models.WinRT.PassportDevice.h"
#if __has_include("PassportDevice.g.cpp")
# include "PassportDevice.g.cpp"
#endif

#include <Mercatec.Helpers.Models.hpp>

namespace winrt::Mercatec::Models::implementation
{
    void PassportDevice::DeviceId(const winrt::guid& device_id) noexcept
    {
        SET_PROPERTY(m_Model.DeviceId, device_id);
    }

    winrt::guid PassportDevice::DeviceId() const noexcept
    {
        return m_Model.DeviceId;
    }

    void PassportDevice::PublicKey(const array_view<const uint8_t> public_key)
    {
        if ( not std::equal(m_Model.PublicKey.cbegin(), m_Model.PublicKey.cend(), public_key.cbegin(), public_key.cend()) )
        {
            m_Model.PublicKey.assign(public_key.cbegin(), public_key.cend());
            NotifyPropertyChanged(L"PublicKey");
        }
    }

    com_array<uint8_t> PassportDevice::PublicKey() const noexcept
    {
        return com_array<uint8_t>(m_Model.PublicKey);
    }

    void PassportDevice::KeyAttestationResult(const key_credential_attestation_result_t& key_credential_result) noexcept
    {
        SET_PROPERTY(m_KeyAttestationResult, key_credential_result);
    }

    PassportDevice::key_credential_attestation_result_t PassportDevice::KeyAttestationResult() const noexcept
    {
        return m_KeyAttestationResult;
    }
} // namespace winrt::Mercatec::Models::implementation
