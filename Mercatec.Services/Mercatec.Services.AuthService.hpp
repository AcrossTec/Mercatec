#pragma once

#include "Mercatec.Services.Exports.Api.hpp"
#include <Mercatec.Stores.UserAccountStore.hpp>

//! https://learn.microsoft.com/en-us/cpp/cpp/property-cpp?view=msvc-170

namespace Mercatec::Services
{
    class MERCATEC_SERVICES_API AuthService
    {
    public:
        using AccountStore_t = Repositories::UserAccountStore;

        AuthService();

        static AuthService& GetInstance() noexcept;
        __declspec(property(get = GetInstance)) AuthService& Instance;

        Guid                                       GetUserId(const std::wstring_view user_name) const noexcept;
        AccountStore_t::Account                    GetUserAccount(const Guid& user_id) const noexcept;
        IObservableVector<AccountStore_t::Account> GetUserAccountsForDevice(const Guid& device_id) const noexcept;

        void Register(const std::wstring_view user_name) noexcept;
        bool PassportRemoveUser(const Guid& user_id) noexcept;
        bool PassportRemoveDevice(const Guid& user_id, Guid device_id) noexcept;
        void PassportUpdateDetails( //
          const Guid&                                                                  user_id,
          const Guid&                                                                  device_id,
          const array_view<Byte>                                                       public_key,
          const winrt::Windows::Security::Credentials::KeyCredentialAttestationResult& key_attestation_result
        ) noexcept;

        bool ValidateCredentials(const std::wstring_view user_name, const std::wstring_view password);
        bool SendServerSignedChallenge(const Guid& user_id, const Guid& device_id, const array_view<Byte> signed_challenge);

        winrt::Windows::Storage::Streams::IBuffer PassportRequestChallenge();

    private:
        AccountStore_t m_AccountStore;
    };
} // namespace Mercatec::Services
