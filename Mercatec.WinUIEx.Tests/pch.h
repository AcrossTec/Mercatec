#pragma once

#include <Windows.h>
#include <Unknwn.h>
#include <RestrictedErrorInfo.h>
#include <hstring.h>

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
#pragma warning(pop)

#pragma push_macro("GetCurrentTime")
#pragma push_macro("X64")

#undef GetCurrentTime
#undef X64

#include <winrt/Windows.Foundation.h>
#include <winrt/Windows.Foundation.Collections.h>

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

namespace winrt
{
    using namespace Windows::Foundation;
    using namespace Windows::Foundation::Collections;
} // namespace winrt

#pragma pop_macro("GetCurrentTime")
#pragma pop_macro("X64")
