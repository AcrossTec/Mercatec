// Copyright (c) Microsoft Corporation and Contributors.
// Licensed under the MIT License.

#pragma once
#include <Windows.h>
#include <Unknwn.h>

#ifdef PUSH_MACRO_GetCurrentTime
# pragma push_macro("GetCurrentTime")
#endif

#undef GetCurrentTime

#include <winrt/Windows.Foundation.h>
#include <winrt/Windows.Foundation.Collections.h>
#include <winrt/Windows.Globalization.h>
#include <winrt/Windows.Security.Credentials.h>
#include <winrt/Windows.UI.Xaml.Data.h>
#include <winrt/Windows.Graphics.Effects.h>

#include <winrt/Microsoft.UI.Composition.h>
#include <winrt/Microsoft.UI.Xaml.h>
#include <winrt/Microsoft.UI.Xaml.Controls.h>
#include <winrt/Microsoft.UI.Xaml.Controls.Primitives.h>
#include <winrt/Microsoft.UI.Xaml.Data.h>
#include <winrt/Microsoft.UI.Xaml.Hosting.h>
#include <winrt/Microsoft.UI.Xaml.Markup.h>
#include <winrt/Microsoft.UI.Xaml.Navigation.h>
#include <winrt/Microsoft.UI.Dispatching.h>
#include <wil/cppwinrt_helpers.h>

#include <array>
#include <iostream>
#include <iomanip>
#include <vector>
#include <string>
#include <string_view>
#include <chrono>
#include <format>
#include <filesystem>
#include <sstream>
#include <fstream>
#include <atomic>
#include <memory>
#include <mutex>

using namespace std::string_literals;
using namespace std::string_view_literals;

namespace winrt
{
    using namespace Microsoft::UI;
    using namespace Microsoft::UI::Xaml;
    using namespace Microsoft::UI::Xaml::Controls;
    using namespace Microsoft::UI::Xaml::Navigation;
    using namespace Microsoft::UI::Windowing;
    using namespace Windows::Graphics;
    using namespace Windows::Foundation;
    using namespace Windows::Foundation::Collections;
} // namespace winrt

namespace MUW  = winrt::Microsoft::UI::Windowing;
namespace MUX  = winrt::Microsoft::UI::Xaml;
namespace MUXC = winrt::Microsoft::UI::Xaml::Controls;
namespace MUXN = winrt::Microsoft::UI::Xaml::Navigation;
namespace MUXI = winrt::Microsoft::UI::Xaml::Input;
namespace WSC  = winrt::Windows::Security::Credentials;

#ifdef PUSH_MACRO_GetCurrentTime
# pragma pop_macro("GetCurrentTime")
#endif
