#include "pch.h"
#include "Mercatec.Helpers.AppDataPaths.hpp"
#include "Mercatec.Helpers.WindowsShell.hpp"

//!
//! CSIDL
//! https://learn.microsoft.com/en-us/windows/win32/shell/csidl
//!
//! SHGetSpecialFolderPathW
//! https://learn.microsoft.com/en-us/windows/win32/api/shlobj_core/nf-shlobj_core-shgetspecialfolderpathw
//!
//! SHGetKnownFolderPath
//! https://learn.microsoft.com/en-us/windows/win32/api/shlobj_core/nf-shlobj_core-shgetknownfolderpath
//!
//! Known Folders Sample
//! https://learn.microsoft.com/en-us/windows/win32/shell/samples-knownfolders
//!
//! Known Folders
//! https://learn.microsoft.com/en-us/windows/win32/shell/known-folders
//!

namespace Mercatec::Helpers
{
    winrt::hstring AppDataPaths::Cookies() noexcept
    {
        return GetKnownFolderPath(FOLDERID_Cookies).value_or(winrt::impl::empty_value<winrt::hstring>());
    }

    winrt::hstring AppDataPaths::Desktop() noexcept
    {
        return GetKnownFolderPath(FOLDERID_Desktop).value_or(winrt::impl::empty_value<winrt::hstring>());
    }

    winrt::hstring AppDataPaths::Documents() noexcept
    {
        return GetKnownFolderPath(FOLDERID_Documents).value_or(winrt::impl::empty_value<winrt::hstring>());
    }

    winrt::hstring AppDataPaths::Favorites() noexcept
    {
        return GetKnownFolderPath(FOLDERID_Favorites).value_or(winrt::impl::empty_value<winrt::hstring>());
    }

    winrt::hstring AppDataPaths::History() noexcept
    {
        return GetKnownFolderPath(FOLDERID_History).value_or(winrt::impl::empty_value<winrt::hstring>());
    }

    winrt::hstring AppDataPaths::InternetCache() noexcept
    {
        return GetKnownFolderPath(FOLDERID_InternetCache).value_or(winrt::impl::empty_value<winrt::hstring>());
    }

    winrt::hstring AppDataPaths::LocalAppData() noexcept
    {
        return GetKnownFolderPath(FOLDERID_LocalAppData).value_or(winrt::impl::empty_value<winrt::hstring>());
    }

    winrt::hstring AppDataPaths::ProgramData() noexcept
    {
        return GetKnownFolderPath(FOLDERID_ProgramData).value_or(winrt::impl::empty_value<winrt::hstring>());
    }

    winrt::hstring AppDataPaths::RoamingAppData() noexcept
    {
        return GetKnownFolderPath(FOLDERID_RoamingAppData).value_or(winrt::impl::empty_value<winrt::hstring>());
    }
} // namespace Mercatec::Helpers
