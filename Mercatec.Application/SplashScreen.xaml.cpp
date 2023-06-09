// Copyright (c) Microsoft Corporation and Contributors.
// Licensed under the MIT License.

#include "pch.h"
#include "SplashScreen.xaml.h"
#if __has_include("SplashScreen.g.cpp")
# include "SplashScreen.g.cpp"
#endif

#include "Mercatec.Application.Startup.hpp"
#include <Mercatec.Helpers.Application.hpp>

using namespace winrt;
using namespace winrt::Microsoft::UI::Xaml;

using namespace ::Mercatec::Helpers::Applications;

// To learn more about WinUI, the WinUI project structure,
// and more about our project templates, see: http://aka.ms/winui-project-info.

//!
//! Threading functionality migration
//! https://learn.microsoft.com/en-us/windows/apps/windows-app-sdk/migrate-to-windows-app-sdk/guides/threading
//!

namespace winrt::Mercatec::Application::implementation
{
    SplashScreen::SplashScreen() // clang-format off
      : SplashScreenT<SplashScreen>{ [] { return Application::MainWindow(); } } // clang-format on
    {
        InitializeComponent();
        BackdropType(WinUIEx::BackdropType::DesktopAcrylic);
        WindowExtensions::SetIcon(*this, IconPath());
    }

    Windows::Foundation::IAsyncAction SplashScreen::OnLoading()
    {
        using namespace std::chrono_literals;

        auto StartupTask{ ::Mercatec::Application::Configurations::Startup::ConfigureAsync() };

        StartupTask.Progress(
          [this](const auto&, const double_t Value) -> winrt::fire_and_forget
          {
              co_await wil::resume_foreground(DispatcherQueue());
              Status().Text(std::format(L"Cargando {}%...", Value));
              Progress().Value(Value);
          }
        );

        co_await StartupTask;
    }
} // namespace winrt::Mercatec::Application::implementation
