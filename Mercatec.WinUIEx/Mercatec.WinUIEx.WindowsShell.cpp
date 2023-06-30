#include "pch.h"
#include "Mercatec.WinUIEx.WindowsShell.hpp"

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

namespace Mercatec::WinUIEx
{
    std::optional<winrt::hstring> GetKnownFolderPath(REFKNOWNFOLDERID FolderId, const DWORD Flags, HANDLE Token) noexcept
    {
        PWSTR   szPath  = NULL;
        HRESULT HResult = ::SHGetKnownFolderPath(FolderId, Flags, Token, &szPath);

        if ( SUCCEEDED(HResult) )
        {
            winrt::hstring FolderPath = szPath;
            CoTaskMemFree(szPath);
            return FolderPath;
        }

        return std::nullopt;
    }

    std::optional<winrt::hstring> GetSpecialFolderPath(const int32_t CSIDL, const bool Create) noexcept
    {
        if ( TCHAR szPath[MAX_PATH] = { L'\0' }; SUCCEEDED(::SHGetSpecialFolderPathW(NULL, szPath, CSIDL, Create)) )
        {
            return szPath;
        }

        return std::nullopt;
    }
} // namespace Mercatec::WinUIEx
