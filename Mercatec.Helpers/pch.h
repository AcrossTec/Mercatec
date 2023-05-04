// Copyright (c) Microsoft Corporation and Contributors.
// Licensed under the MIT License.

#pragma once
#include <unknwn.h>

#pragma push_macro("GetCurrentTime")
#undef GetCurrentTime

#include <winrt/Windows.Security.Credentials.h>

#include <winrt/Windows.Foundation.h>
#include <winrt/Windows.Foundation.Collections.h>
#include <winrt/Microsoft.UI.Composition.h>
#include <winrt/Microsoft.UI.Xaml.h>
#include <winrt/Microsoft.UI.Xaml.Controls.h>
#include <winrt/Microsoft.UI.Xaml.Controls.Primitives.h>
#include <winrt/Microsoft.UI.Xaml.Data.h>
#include <winrt/Microsoft.UI.Xaml.Markup.h>
#include <winrt/Microsoft.UI.Xaml.Navigation.h>
#include <winrt/Microsoft.UI.Dispatching.h>
#include <wil/cppwinrt_helpers.h>

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

#pragma pop_macro("GetCurrentTime")