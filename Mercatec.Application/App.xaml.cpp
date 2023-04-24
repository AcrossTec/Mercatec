// Copyright (c) Microsoft Corporation and Contributors.
// Licensed under the MIT License.

#include "pch.h"

#include "App.xaml.h"
#include "MainWindow.xaml.h"

using namespace winrt;
using namespace Windows::Foundation;
using namespace Microsoft::UI::Xaml;
using namespace Microsoft::UI::Xaml::Controls;
using namespace Microsoft::UI::Xaml::Navigation;
using namespace Mercatec::Application;
using namespace Mercatec::Application::implementation;

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
void App::OnLaunched(const LaunchActivatedEventArgs&)
{
    //! https://learn.microsoft.com/en-us/windows/apps/develop/ui-input/retrieve-hwnd
    //! https://learn.microsoft.com/en-us/windows/apps/windows-app-sdk/windowing/windowing-overview
    //! https://stackoverflow.com/questions/71546846/open-app-always-in-the-center-of-the-display-windows-11-winui-3

    m_Window = make<MainWindow>();

    // Get access to IWindowNative
    auto window_native{ m_Window.try_as<IWindowNative>() };
    winrt::check_bool(window_native);

    // Get the HWND for the XAML Window
    HWND hwnd{ nullptr };
    window_native->get_WindowHandle(&hwnd);

    // Get the WindowId for our window
    winrt::WindowId window_id = winrt::GetWindowIdFromWindow(hwnd);

    // Get the AppWindow for the WindowId
    auto app_window = AppWindow::GetFromWindowId(window_id);

    if ( app_window )
    {
        auto display_area = DisplayArea::GetFromWindowId(window_id, DisplayAreaFallback::Nearest);

        if ( display_area )
        {
            PointInt32 centered_position{ // clang-format off
                .X = (display_area.WorkArea().Width - app_window.Size().Width) / 2,
                .Y = (display_area.WorkArea().Height - app_window.Size().Height) / 2
            }; // clang-format on

            app_window.Move(centered_position);
        }
    }

    m_Window.Activate();
}
