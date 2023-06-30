#pragma once

#include "Mercatec.WinUIEx.Exports.Api.hpp"
#include <winrt/Windows.Foundation.h>

//! CSIDL
//! https://learn.microsoft.com/en-us/windows/win32/shell/csidl
//!
//! CSIDL (constant special item ID list) values provide a unique system-independent way to identify special folders used
//! frequently by applications, but which may not have the same name or location on any given system.
//!
//! For example, the system folder may be "C:\Windows" on one system and "C:\Winnt" on another.
//! These constants are defined in Shlobj.h.
//!
//! SHGetSpecialFolderPathW function (shlobj_core.h)
//! https://learn.microsoft.com/en-us/windows/win32/api/shlobj_core/nf-shlobj_core-shgetspecialfolderpathw
//!
//! KNOWNFOLDERID
//! https://learn.microsoft.com/en-us/windows/win32/shell/knownfolderid

#include <Shlobj.h>
#include <ShlObj_core.h>
#include <Shlwapi.h>
#include <KnownFolders.h>
#include <optional>

#pragma comment(lib, "Shell32.lib")
#pragma comment(lib, "Shlwapi.lib")

namespace Mercatec::WinUIEx
{
    MERCATEC_WINUIEX_API std::optional<winrt::hstring> GetKnownFolderPath(REFKNOWNFOLDERID FolderId, const DWORD Flags = KF_FLAG_DEFAULT, HANDLE Token = nullptr) noexcept;
    MERCATEC_WINUIEX_API std::optional<winrt::hstring> GetSpecialFolderPath(const int32_t CSIDL, const bool Create = false) noexcept;
} // namespace Mercatec::WinUIEx
