#include "pch.h"
#include "Mercatec.Services.SettingsService.h"
#if __has_include("SettingsService.g.cpp")
# include "SettingsService.g.cpp"
#endif

namespace winrt::Mercatec::Services::implementation
{
    SettingsService::SettingsService([[maybe_unused]] const Helpers::Services::IDialogService& dialog_service)
    {
    }

    hstring SettingsService::Version() const noexcept
    {
        return {};
    }

    hstring SettingsService::DbVersion() const noexcept
    {
        return {};
    }

    hstring SettingsService::UserName() const noexcept
    {
        return {};
    }

    void SettingsService::UserName([[maybe_unused]] const std::wstring_view value) noexcept
    {
    }

    Helpers::DataProviderType SettingsService::DataProvider() const noexcept
    {
        return Helpers::DataProviderType{ 0 };
    }

    void SettingsService::DataProvider([[maybe_unused]] const Helpers::DataProviderType value) noexcept
    {
    }

    hstring SettingsService::PatternConnectionString() const noexcept
    {
        return {};
    }

    hstring SettingsService::SQLServerConnectionString() const noexcept
    {
        return {};
    }

    void SettingsService::SQLServerConnectionString([[maybe_unused]] const std::wstring_view value) noexcept
    {
    }

    bool SettingsService::IsRandomErrorsEnabled() const noexcept
    {
        return false;
    }

    void SettingsService::IsRandomErrorsEnabled([[maybe_unused]] const bool value) noexcept
    {
    }

    Windows::Foundation::IAsyncOperation<Helpers::Result> SettingsService::ResetLocalDataProviderAsync()
    {
        co_return nullptr;
    }

    Windows::Foundation::IAsyncOperation<Helpers::Result> SettingsService::ValidateConnectionAsync([[maybe_unused]] const std::wstring_view connection_string)
    {
        co_return nullptr;
    }

    Windows::Foundation::IAsyncOperation<Helpers::Result> SettingsService::CreateDabaseAsync([[maybe_unused]] const std::wstring_view connection_string)
    {
        co_return nullptr;
    }
} // namespace winrt::Mercatec::Services::implementation
