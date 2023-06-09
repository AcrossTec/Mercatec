// Copyright (c) Microsoft Corporation and Contributors.
// Licensed under the MIT License.

#include "pch.h"
#include "LoginPage.xaml.h"
#if __has_include("LoginPage.g.cpp")
# include "LoginPage.g.cpp"
#endif

#include <Mercatec.Helpers.Debug.hpp>
#include <Mercatec.Helpers.Types.hpp>
#include <Mercatec.Helpers.Strings.hpp>
#include <Mercatec.Services.AuthService.hpp>
#include <Mercatec.Services.MicrosoftPassportService.hpp>

#pragma warning(push)

//! https://learn.microsoft.com/en-us/cpp/code-quality/c26811?view=msvc-170
//! https://learn.microsoft.com/en-us/windows/uwp/cpp-and-winrt-apis/concurrency#parameter-passing
//! Warning C26811 Lifetime of the memory referenced by parameter ''args'' might end by the time the coroutine is resumed(lifetime .1)
#pragma warning(disable : 26811)

using namespace winrt;
using namespace winrt::Microsoft::UI::Xaml;
using namespace ::Mercatec::Types;

using ::Mercatec::Helpers::Empty;
using ::Mercatec::Helpers::OutputDebug;
using ::Mercatec::Services::AuthService;
using ::Mercatec::Services::MicrosoftPassportHelper;

// To learn more about WinUI, the WinUI project structure,
// and more about our project templates, see: http://aka.ms/winui-project-info.

namespace winrt::Mercatec::Application::implementation
{
    LoginPage::LoginPage()
    {
        InitializeComponent();
    }

} // namespace winrt::Mercatec::Application::implementation

#pragma warning(pop)