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

#pragma push_macro("PathAppend")
#pragma push_macro("PathCombine")
#pragma push_macro("PathAddExtension")

#undef PathAppend
#undef PathCombine
#undef PathAddExtension

namespace Mercatec::WinUIEx
{
    MERCATEC_WINUIEX_API std::optional<winrt::hstring> PathAdd(const winrt::param::async_iterable<winrt::hstring>& Paths);
    MERCATEC_WINUIEX_API std::optional<winrt::hstring> PathAppend(const winrt::param::async_iterable<winrt::hstring>& Paths) noexcept;
    MERCATEC_WINUIEX_API std::optional<winrt::hstring> PathCombine(const winrt::param::async_iterable<winrt::hstring>& Paths) noexcept;
    MERCATEC_WINUIEX_API std::optional<winrt::hstring> PathAddExtension(const winrt::param::async_iterable<winrt::hstring>& Paths, const winrt::hstring& Extension) noexcept;
    MERCATEC_WINUIEX_API std::optional<winrt::hstring> GetKnownFolderPath(REFKNOWNFOLDERID FolderId, const DWORD Flags = KF_FLAG_DEFAULT, HANDLE Token = nullptr) noexcept;
    MERCATEC_WINUIEX_API std::optional<winrt::hstring> GetSpecialFolderPath(const int32_t CSIDL, const bool Create = false) noexcept;
} // namespace Mercatec::WinUIEx

#pragma pop_macro("PathAppend")
#pragma pop_macro("PathCombine")
#pragma pop_macro("PathAddExtension")
