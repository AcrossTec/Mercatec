#include "pch.h"
#include "Mercatec.Helpers.AppSettings.hpp"

#pragma warning(push)
#pragma push_macro("GetUserName")
#pragma push_macro("GetComputerName")
#pragma push_macro("GetSystemDirectory")
#pragma push_macro("GetWindowsDirectory")

#undef GetUserName
#undef GetComputerName
#undef GetSystemDirectory
#undef GetWindowsDirectory

#define INFO_BUFFER_SIZE 32767

namespace Mercatec::Helpers
{
    //!
    //! VERSIONINFO resource
    //! https://learn.microsoft.com/en-us/windows/win32/menurc/versioninfo-resource
    //!
    //! Getting System Information
    //! https://learn.microsoft.com/en-us/windows/win32/sysinfo/getting-system-information
    //!

    struct ThreadSafeAppSettings
    {
        static AppSettings& Current()
        {
            std::call_once(CreateFlag, [] { Instance = std::make_unique<AppSettings>(); });
            return *Instance;
        }

        static std::unique_ptr<AppSettings> Instance;
        static std::once_flag               CreateFlag;
    };

    std::unique_ptr<AppSettings> ThreadSafeAppSettings::Instance;
    std::once_flag               ThreadSafeAppSettings::CreateFlag;

    struct AppSettings::AppSettingsImpl
    {
    };

    AppSettings::AppSettings() noexcept
      : Impl{ std::make_unique<AppSettingsImpl>() }
      , SQLiteConnectionString{ L"" }
      , AppLogConnectionString{ L"" }
    {
    }

    AppSettings& AppSettings::Current() noexcept
    {
        return ThreadSafeAppSettings::Current();
    }

    std::wstring AppSettings::GetUserName() const noexcept
    {
        return L"";
    }

    void AppSettings::SetUserName([[maybe_unused]] const std::wstring_view Value) noexcept
    {
    }

    std::wstring AppSettings::GetWindowsHelloPublicKeyHint() const noexcept
    {
        return L"";
    }

    void AppSettings::SetWindowsHelloPublicKeyHint([[maybe_unused]] const std::wstring_view Value) noexcept
    {
    }

    std::wstring AppSettings::GetVersion() const
    {
        // TODO: Crear Implementación para obtener toda la información desde el ensamblado.
        return L"1.0.0.0";
    }

    std::wstring AppSettings::GetComputerName() const
    {
        std::wstring InfoBuf(INFO_BUFFER_SIZE, L'\0');
        DWORD        BufCharCount{ INFO_BUFFER_SIZE };

        // Get and display the name of the computer.
        if ( not ::GetComputerNameW(InfoBuf.data(), &BufCharCount) )
        {
            winrt::throw_last_error();
        }

        return InfoBuf;
    }

    std::wstring AppSettings::GetAccountName() const
    {
        std::wstring InfoBuf(INFO_BUFFER_SIZE, L'\0');
        DWORD        BufCharCount{ INFO_BUFFER_SIZE };

        // Get and display the user name.
        if ( not ::GetUserNameW(InfoBuf.data(), &BufCharCount) )
        {
            winrt::throw_last_error();
        }

        return InfoBuf;
    }

    std::wstring AppSettings::GetSystemDirectory() const
    {
        std::wstring InfoBuf(INFO_BUFFER_SIZE, L'\0');

        // Get and display the system directory.
        if ( not ::GetSystemDirectoryW(InfoBuf.data(), INFO_BUFFER_SIZE) )
        {
            winrt::throw_last_error();
        }

        return InfoBuf;
    }

    std::wstring AppSettings::GetWindowsDirectory() const
    {
        std::wstring InfoBuf(INFO_BUFFER_SIZE, L'\0');

        // Get and display the Windows directory.
        if ( not ::GetWindowsDirectoryW(InfoBuf.data(), INFO_BUFFER_SIZE) )
        {
            winrt::throw_last_error();
        }

        return InfoBuf;
    }

} // namespace Mercatec::Helpers

#pragma pop_macro("GetUserName")
#pragma pop_macro("GetComputerName")
#pragma pop_macro("GetSystemDirectory")
#pragma pop_macro("GetWindowsDirectory")
#pragma warning(pop)
