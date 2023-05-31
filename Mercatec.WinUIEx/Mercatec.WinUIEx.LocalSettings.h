#pragma once

#include "LocalSettings.g.h"

namespace winrt::Mercatec::WinUIEx::implementation
{
    struct LocalSettings : LocalSettingsT<LocalSettings>
    {
    public:
        LocalSettings();

        void Load();
        void Save();

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

        guid     GetGuid(const std::wstring_view Key);
        char16_t GetChar(const std::wstring_view Key);
        int16_t  GetInt16(const std::wstring_view Key);
        int32_t  GetInt32(const std::wstring_view Key);
        int64_t  GetInt64(const std::wstring_view Key);
        uint8_t  GetUInt8(const std::wstring_view Key);
        uint16_t GetUInt16(const std::wstring_view Key);
        uint32_t GetUInt32(const std::wstring_view Key);
        uint64_t GetUInt64(const std::wstring_view Key);
        float_t  GetSingle(const std::wstring_view Key);
        double_t GetDouble(const std::wstring_view Key);
        hstring  GetString(const std::wstring_view Key);
        bool     GetBoolean(const std::wstring_view Key);

        com_array<uint8_t> GetArray(const std::wstring_view Key);

    private:
    };
} // namespace winrt::Mercatec::WinUIEx::implementation

namespace winrt::Mercatec::WinUIEx::factory_implementation
{
    struct LocalSettings : LocalSettingsT<LocalSettings, implementation::LocalSettings>
    {
    };
} // namespace winrt::Mercatec::WinUIEx::factory_implementation
