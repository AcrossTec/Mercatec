#pragma once

#include <Windows.h>
#include <Unknwn.h>
#include <RestrictedErrorInfo.h>
#include <hstring.h>

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

#pragma comment(lib, "Shell32.lib")
#pragma comment(lib, "Shlwapi.lib")

#pragma warning(push)

//! Warning pragma
//! https://learn.microsoft.com/en-us/cpp/preprocessor/warning?view=msvc-170
//!
//! Compiler Warning C26495
//! Variable 'variable' is uninitialized. Always initialize a member variable (type.6).
//!
//! https://learn.microsoft.com/en-us/cpp/code-quality/c26495?view=msvc-170
//!
//! Remarks
//! A member variable isn't initialized by a constructor or by an initializer. Make sure all variables are initialized by the end of construction. For more information, see C++ Core Guidelines Type.6 and C.48.
//! Code analysis name : MEMBER_UNINIT

#pragma warning(disable : 26495)
#include <gtest/gtest.h>
#include <gmock/gmock.h>
#pragma warning(pop)

#pragma push_macro("GetCurrentTime")
#pragma push_macro("X64")

#undef GetCurrentTime
#undef X64

#include <winrt/Windows.Foundation.h>
#include <winrt/Windows.Foundation.Collections.h>
#include <winrt/Windows.Storage.h>
#include <winrt/Windows.Storage.Streams.h>
#include <winrt/Microsoft.UI.h>
#include <winrt/Microsoft.UI.Xaml.h>
#include <winrt/Microsoft.UI.Windowing.h>

#include <iostream>
#include <iomanip>
#include <map>
#include <vector>
#include <ctime>
#include <chrono>
#include <charconv>
#include <format>
#include <concepts>
#include <string>
#include <string_view>
#include <memory>
#include <chrono>
#include <tuple>
#include <ranges>
#include <filesystem>

namespace winrt
{
    using namespace Windows::Foundation;
    using namespace Windows::Foundation::Collections;
} // namespace winrt

using namespace std::string_literals;
using namespace std::string_view_literals;
using namespace std::chrono_literals;

#pragma pop_macro("GetCurrentTime")
#pragma pop_macro("X64")
