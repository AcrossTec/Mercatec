#pragma once

#include "LocalSettings.g.h"

#include <concurrent_unordered_map.h>
#include <concurrent_vector.h>
#include <variant>
#include <vector>
#include <any>

namespace winrt::Mercatec::Helpers::implementation
{
    struct LocalSettings : LocalSettingsT<LocalSettings>
    {
    public:
        using data_t      = concurrency::concurrent_unordered_map<std::wstring, std::any>;
        using date_time_t = Windows::Foundation::DateTime;
        using time_span_t = Windows::Foundation::TimeSpan;
        using buffer_t    = Windows::Storage::Streams::IBuffer;

        LocalSettings();

        hstring AppDataPath() const noexcept;
        void    AppDataPath(const std::wstring_view Value) noexcept;

        hstring FileName() const noexcept;
        void    FileName(const std::wstring_view Value) noexcept;

        hstring SettingFile() const noexcept;

        Windows::Foundation::IAsyncAction LoadAsync();
        Windows::Foundation::IAsyncAction SaveAsync();

        void Add(const std::wstring_view Key, const guid Value);
        void Add(const std::wstring_view Key, const char16_t Value);
        void Add(const std::wstring_view Key, const int16_t Value);
        void Add(const std::wstring_view Key, const int32_t Value);
        void Add(const std::wstring_view Key, const int64_t Value);
        void Add(const std::wstring_view Key, const uint8_t Value);
        void Add(const std::wstring_view Key, const uint16_t Value);
        void Add(const std::wstring_view Key, const uint32_t Value);
        void Add(const std::wstring_view Key, const uint64_t Value);
        void Add(const std::wstring_view Key, const float_t Value);
        void Add(const std::wstring_view Key, const double_t Value);
        void Add(const std::wstring_view Key, const std::wstring_view Value);
        void Add(const std::wstring_view Key, const bool Value);
        void Add(const std::wstring_view Key, const array_view<const uint8_t> Value);
        void Add(const std::wstring_view Key, const date_time_t& Value);
        void Add(const std::wstring_view Key, const time_span_t& Value);
        void Add(const std::wstring_view Key, const buffer_t& Buffer);
        void Add(const std::wstring_view Key, const buffer_t& Buffer, const uint32_t Start, const uint32_t Count);

        void Get(const std::wstring_view Key, guid& Value);
        void Get(const std::wstring_view Key, char16_t& Value);
        void Get(const std::wstring_view Key, int16_t& Value);
        void Get(const std::wstring_view Key, int32_t& Value);
        void Get(const std::wstring_view Key, int64_t& Value);
        void Get(const std::wstring_view Key, uint8_t& Value);
        void Get(const std::wstring_view Key, uint16_t& Value);
        void Get(const std::wstring_view Key, uint32_t& Value);
        void Get(const std::wstring_view Key, uint64_t& Value);
        void Get(const std::wstring_view Key, float_t& Value);
        void Get(const std::wstring_view Key, double_t& Value);
        void Get(const std::wstring_view Key, hstring& Value);
        void Get(const std::wstring_view Key, bool& Value);
        void Get(const std::wstring_view Key, com_array<uint8_t>& Value);
        void Get(const std::wstring_view Key, date_time_t& Value);
        void Get(const std::wstring_view Key, time_span_t& Value);
        void Get(const std::wstring_view Key, buffer_t& Buffer);

        guid               GetGuid(const std::wstring_view Key);
        char16_t           GetChar(const std::wstring_view Key);
        int16_t            GetInt16(const std::wstring_view Key);
        int32_t            GetInt32(const std::wstring_view Key);
        int64_t            GetInt64(const std::wstring_view Key);
        uint8_t            GetUInt8(const std::wstring_view Key);
        uint16_t           GetUInt16(const std::wstring_view Key);
        uint32_t           GetUInt32(const std::wstring_view Key);
        uint64_t           GetUInt64(const std::wstring_view Key);
        float_t            GetSingle(const std::wstring_view Key);
        double_t           GetDouble(const std::wstring_view Key);
        hstring            GetString(const std::wstring_view Key);
        bool               GetBoolean(const std::wstring_view Key);
        com_array<uint8_t> GetArray(const std::wstring_view Key);
        date_time_t        GetDateTime(const std::wstring_view Key);
        time_span_t        GetTimeSpan(const std::wstring_view Key);
        buffer_t           GetBuffer(const std::wstring_view Key);

    private:
        hstring m_AppDataPath;
        hstring m_FileName;
        data_t  m_Data;
    };
} // namespace winrt::Mercatec::Helpers::implementation

namespace winrt::Mercatec::Helpers::factory_implementation
{
    struct LocalSettings : LocalSettingsT<LocalSettings, implementation::LocalSettings>
    {
    };
} // namespace winrt::Mercatec::Helpers::factory_implementation
