#pragma once

#include "SettingsService.g.h"
#include "Mercatec.Services.hpp"
#include <winrt/Mercatec.Helpers.h>

namespace winrt::Mercatec::Services::implementation
{
    struct SettingsService : SettingsServiceT<SettingsService>
    {
    public:
        SettingsService(const Helpers::Services::IDialogService& dialog_service);

        hstring Version() const noexcept;
        hstring DbVersion() const noexcept;

        hstring UserName() const noexcept;
        void    UserName(const std::wstring_view value) noexcept;

        Helpers::DataProviderType DataProvider() const noexcept;
        void                      DataProvider(const Helpers::DataProviderType value) noexcept;

        hstring PatternConnectionString() const noexcept;

        hstring SQLServerConnectionString() const noexcept;
        void    SQLServerConnectionString(const std::wstring_view value) noexcept;

        bool IsRandomErrorsEnabled() const noexcept;
        void IsRandomErrorsEnabled(const bool value) noexcept;

        Windows::Foundation::IAsyncOperation<Helpers::Result> ResetLocalDataProviderAsync();
        Windows::Foundation::IAsyncOperation<Helpers::Result> ValidateConnectionAsync(const std::wstring_view connection_string);
        Windows::Foundation::IAsyncOperation<Helpers::Result> CreateDabaseAsync(const std::wstring_view connection_string);

    private:
    };
} // namespace winrt::Mercatec::Services::implementation

namespace winrt::Mercatec::Services::factory_implementation
{
    struct SettingsService : SettingsServiceT<SettingsService, implementation::SettingsService>
    {
    };
} // namespace winrt::Mercatec::Services::factory_implementation
