#pragma once
#pragma once

#include "Mercatec.Helpers.Exports.Api.hpp"
#include <string_view>
#include <memory>

#pragma warning(push)
//! Compiler Warning (level 1) C4251
//! 'type' : class 'type1' needs to have dll-interface to be used by clients of class 'type2'
//! https://learn.microsoft.com/en-us/cpp/error-messages/compiler-warnings/compiler-warning-level-1-c4251?view=msvc-170
#pragma warning(disable : 4251)

#pragma push_macro("GetUserName")
#pragma push_macro("GetComputerName")
#pragma push_macro("GetSystemDirectory")
#pragma push_macro("GetWindowsDirectory")

#undef GetUserName
#undef GetComputerName
#undef GetSystemDirectory
#undef GetWindowsDirectory

namespace Mercatec::Helpers
{
    class MERCATEC_HELPERS_API AppSettings
    {
    public:
        AppSettings() noexcept;
        static AppSettings& Current() noexcept;

        AppSettings(const AppSettings&)            = delete;
        AppSettings(AppSettings&&)                 = delete;
        AppSettings& operator=(const AppSettings&) = delete;
        AppSettings& operator=(AppSettings&&)      = delete;
        ~AppSettings() noexcept                    = default;

        const std::wstring_view SQLiteConnectionString;
        const std::wstring_view AppLogConnectionString;

        std::wstring GetUserName() const noexcept;
        void         SetUserName(const std::wstring_view Value) noexcept;
        __declspec(property(get = GetUserName, put = SetUserName)) std::wstring UserName;

        std::wstring GetWindowsHelloPublicKeyHint() const noexcept;
        void         SetWindowsHelloPublicKeyHint(const std::wstring_view Value) noexcept;
        __declspec(property(get = GetWindowsHelloPublicKeyHint, put = SetWindowsHelloPublicKeyHint)) std::wstring WindowsHelloPublicKeyHint;

        std::wstring GetVersion() const;
        __declspec(property(get = GetVersion)) std::wstring Version;

        std::wstring GetComputerName() const;
        __declspec(property(get = GetComputerName)) std::wstring ComputerName;

        std::wstring GetSystemDirectory() const;
        __declspec(property(get = GetSystemDirectory)) std::wstring SystemDirectory;

        std::wstring GetWindowsDirectory() const;
        __declspec(property(get = GetWindowsDirectory)) std::wstring WindowsDirectory;

        std::wstring GetAccountName() const;
        __declspec(property(get = GetAccountName)) std::wstring AccountName;

    private:
        struct AppSettingsImpl;
        std::unique_ptr<AppSettingsImpl> Impl;
    };
} // namespace Mercatec::Helpers

#pragma pop_macro("GetUserName")
#pragma pop_macro("GetComputerName")
#pragma pop_macro("GetSystemDirectory")
#pragma pop_macro("GetWindowsDirectory")
#pragma warning(pop)
