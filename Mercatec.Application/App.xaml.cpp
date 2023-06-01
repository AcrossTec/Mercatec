// Copyright (c) Microsoft Corporation and Contributors.
// Licensed under the MIT License.

#include "pch.h"

#include "App.xaml.h"
#include "MainWindow.xaml.h"

#include <microsoft.ui.xaml.window.h>

#include "Mercatec.Application.Startup.hpp"

using namespace winrt;
using namespace winrt::Mercatec::Application;
using namespace winrt::Mercatec::Application::implementation;

using namespace Windows::Foundation;
using namespace Microsoft::UI::Xaml;
using namespace Microsoft::UI::Xaml::Controls;
using namespace Microsoft::UI::Xaml::Navigation;

// To learn more about WinUI, the WinUI project structure,
// and more about our project templates, see: http://aka.ms/winui-project-info.

/// <summary>
/// Initializes the singleton application object.  This is the first line of authored code
/// executed, and as such is the logical equivalent of main() or WinMain().
/// </summary>
App::App()
{
    InitializeComponent();

#if defined _DEBUG && !defined DISABLE_XAML_GENERATED_BREAK_ON_UNHANDLED_EXCEPTION
    UnhandledException(
      [this](const IInspectable&, const UnhandledExceptionEventArgs& event)
      {
          if ( IsDebuggerPresent() )
          {
              auto error_message = event.Message();
              __debugbreak();
          }
      }
    );
#endif
}

/// <summary>
///     Invoked when the application is launched.
/// </summary>
/// <param name="e">
///     Details about the launch request and process.
/// </param>
fire_and_forget App::OnLaunched(const LaunchActivatedEventArgs&)
{
    //! https://learn.microsoft.com/en-us/windows/apps/develop/ui-input/retrieve-hwnd
    //! https://learn.microsoft.com/en-us/windows/apps/windows-app-sdk/windowing/windowing-overview
    //! https://stackoverflow.com/questions/71546846/open-app-always-in-the-center-of-the-display-windows-11-winui-3
    //! https://learn.microsoft.com/en-us/windows/windows-app-sdk/api/win32/microsoft.ui.xaml.window/nf-microsoft-ui-xaml-window-iwindownative-get_windowhandle

    m_Window = make<MainWindow>();
    co_await ::Mercatec::Application::Configurations::Startup::ConfigureAsync();
    m_Window.Activate();
}
