// Copyright (c) Microsoft Corporation and Contributors.
// Licensed under the MIT License.

#include "pch.h"
#include "App.xaml.h"

#include <winrt/Mercatec.WinUIEx.h>
#include <winrt/Mercatec.WinUIEx.Messaging.h>

#include <Mercatec.Helpers.Debug.hpp>
#include <Mercatec.Helpers.Strings.hpp>

using namespace winrt::Windows::Foundation;

using namespace winrt::Mercatec::Application;
using namespace winrt::Mercatec::Application::implementation;

using namespace winrt::Microsoft::UI::Xaml;
using namespace winrt::Microsoft::UI::Xaml::Controls;
using namespace winrt::Microsoft::UI::Xaml::Navigation;

using namespace Mercatec::Helpers::Debug;
using namespace Mercatec::Helpers::Strings;

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

//! Enum-to-string helpers. This app only supports Launch and File activation.
//! Note that ExtendedActivationKind is a superset of ActivationKind, so
//! we could reduce these 2 methods to one, and cast appropriately from
//! ActivationKind to ExtendedActivationKind. However, this sample keeps
//! them separate to illustrate the difference between Xaml::LaunchActivatedEventArgs
//! and AppLifecycle::AppActivationArguments
inline constexpr std::wstring_view KindString(winrt::Windows::ApplicationModel::Activation::ActivationKind Kind)
{
    using namespace winrt::Windows::ApplicationModel::Activation;

    switch ( Kind )
    { // clang-format off
        case ActivationKind::Launch: return L"Launch";
        case ActivationKind::File:   return L"File";
        default:                     return L"Unknown";
    } // clang-format on
}

inline constexpr std::wstring_view KindString(winrt::Microsoft::Windows::AppLifecycle::ExtendedActivationKind ExtendedKind)
{
    using namespace winrt::Microsoft::Windows::AppLifecycle;

    switch ( ExtendedKind )
    { // clang-format off
        case ExtendedActivationKind::Launch: return L"Launch";
        case ExtendedActivationKind::File:   return L"File";
        default:                             return L"Unknown";
    } // clang-format on
}

/// <summary>
///     Invoked when the application is launched.
/// </summary>
/// <param name="e">
///     Details about the launch request and process.
/// </param>
void App::OnLaunched(const LaunchActivatedEventArgs& Args)
{
    //! https://github.com/microsoft/WindowsAppSDK-Samples/tree/main/Samples/AppLifecycle/Instancing/cpp-winui-packaged

    // NOTE: OnLaunched will always report that the ActivationKind == Launch,
    // even when it isn't.
    winrt::Windows::ApplicationModel::Activation::ActivationKind kind = Args.UWPLaunchActivatedEventArgs().Kind();
    OutputDebug(L"OnLaunched: Kind={}", KindString(kind));

    // NOTE: AppInstance is ambiguous between
    // Microsoft.Windows.AppLifecycle.AppInstance and
    // Windows.ApplicationModel.AppInstance
    auto CurrentInstance = winrt::Microsoft::Windows::AppLifecycle::AppInstance::GetCurrent();

    if ( CurrentInstance )
    {
        // AppInstance.GetActivatedEventArgs will report the correct ActivationKind, even in WinUI's OnLaunched.
        winrt::Microsoft::Windows::AppLifecycle::AppActivationArguments ActivationArgs = CurrentInstance.GetActivatedEventArgs();

        if ( ActivationArgs )
        {
            winrt::Microsoft::Windows::AppLifecycle::ExtendedActivationKind ExtendedKind = ActivationArgs.Kind();
            OutputDebug(L"ActivationArgs.Kind={}", KindString(ExtendedKind));
        }
    }

    // Go ahead and do standard window initialization regardless.
    m_Splash = Mercatec::Application::SplashScreen{};
    m_Splash.Completed([this, Strong = m_Splash](const auto&, const auto& Window) { m_Window = Window; });
}

// Rich activation ////////////////////////////////////////////////////////////
//
// Rich activation with the app lifecycle API
// https://learn.microsoft.com/en-us/windows/apps/windows-app-sdk/applifecycle/applifecycle-rich-activation
//

void GetActivationInfo()
{
    winrt::Microsoft::Windows::AppLifecycle::AppActivationArguments Args = winrt::Microsoft::Windows::AppLifecycle::AppInstance::GetCurrent().GetActivatedEventArgs();
    winrt::Microsoft::Windows::AppLifecycle::ExtendedActivationKind Kind = Args.Kind();

    if ( Kind == winrt::Microsoft::Windows::AppLifecycle::ExtendedActivationKind::Launch )
    {
        auto LaunchArgs = Args.Data().as<winrt::Windows::ApplicationModel::Activation::ILaunchActivatedEventArgs>();

        if ( LaunchArgs )
        {
            auto                      ArgString  = LaunchArgs.Arguments();
            std::vector<std::wstring> ArgStrings = SplitStrings(ArgString);
            OutputDebug(ArgStrings, L"Launch Activation");
        }
    }
    else if ( Kind == winrt::Microsoft::Windows::AppLifecycle::ExtendedActivationKind::File )
    {
        auto FileArgs = Args.Data().as<winrt::Windows::ApplicationModel::Activation::IFileActivatedEventArgs>();

        if ( FileArgs )
        {
            winrt::Windows::Storage::IStorageItem File = FileArgs.Files().GetAt(0);
            OutputDebug(L"File activation for '{}'", File.Name());
        }
    }
}

void ReportLaunchArgs(const std::wstring_view CallLocation, const winrt::Microsoft::Windows::AppLifecycle::AppActivationArguments& Args)
{
    winrt::Windows::ApplicationModel::Activation::ILaunchActivatedEventArgs LaunchArgs = Args.Data().as<winrt::Windows::ApplicationModel::Activation::ILaunchActivatedEventArgs>();

    if ( LaunchArgs )
    {
        winrt::hstring            ArgString  = LaunchArgs.Arguments();
        std::vector<std::wstring> ArgStrings = SplitStrings(ArgString);
        OutputDebug(ArgStrings, std::format(L"Launch activation ({})", CallLocation));
    }
}

void ReportFileArgs(const std::wstring_view CallLocation, const winrt::Microsoft::Windows::AppLifecycle::AppActivationArguments& Args)
{
    winrt::Windows::ApplicationModel::Activation::IFileActivatedEventArgs FileArgs = Args.Data().as<winrt::Windows::ApplicationModel::Activation::IFileActivatedEventArgs>();

    if ( FileArgs )
    {
        winrt::Windows::Storage::IStorageItem File = FileArgs.Files().GetAt(0);
        OutputDebug(L"File activation ({}) for '{}'", CallLocation, File.Name());
    }
}

void OnActivated(const winrt::IInspectable&, const winrt::Microsoft::Windows::AppLifecycle::AppActivationArguments& Args)
{
    static int32_t                                                  ActivationCount      = 0;
    constexpr int32_t                                               ArraySize            = 4'096;
    WCHAR                                                           ArrayTemp[ArraySize] = { L'\0' };
    size_t                                                          SizeBytes            = ArraySize * sizeof(WCHAR);
    winrt::Microsoft::Windows::AppLifecycle::ExtendedActivationKind kind                 = Args.Kind();

    if ( kind == winrt::Microsoft::Windows::AppLifecycle::ExtendedActivationKind::File )
    {
        if ( StringCbPrintfW(ArrayTemp, SizeBytes, L"OnActivated, Count=%d", ++ActivationCount) == 0 )
        {
            ReportFileArgs(ArrayTemp, Args);
        }
        else
        {
            ReportFileArgs(L"OnActivated", Args);
        }
    }
}

// wil requires the Microsoft.Windows.ImplementationLibrary nuget.
// https://github.com/Microsoft/wil

wil::unique_event RedirectEventHandle;

winrt::fire_and_forget Redirect(const winrt::Microsoft::Windows::AppLifecycle::AppInstance& KeyInstance, const winrt::Microsoft::Windows::AppLifecycle::AppActivationArguments& Args)
{
    // Using this type of event ensures that it gets signaled when it
    // goes out of scope, even if the RedirectActivationToAsync fails.
    [[maybe_unused]] wil::event_set_scope_exit ensure_signaled = wil::SetEvent_scope_exit(RedirectEventHandle.get());
    co_await KeyInstance.RedirectActivationToAsync(Args);
}

///////////////////////////////////////////////////////////////////////////////

int32_t WINAPI wWinMain([[maybe_unused]] _In_ HINSTANCE hInstance, [[maybe_unused]] _In_opt_ HINSTANCE hPrevInstance, [[maybe_unused]] _In_ LPWSTR lpCmdLine, [[maybe_unused]] _In_ int32_t nShowCmd)
{
    {
        void(WINAPI * PfnXamlCheckProcessRequirements)();
        auto Module = ::LoadLibraryW(L"Microsoft.ui.xaml.dll");

        if ( Module )
        {
            PfnXamlCheckProcessRequirements = reinterpret_cast<decltype(PfnXamlCheckProcessRequirements)>(GetProcAddress(Module, "XamlCheckProcessRequirements"));
            if ( PfnXamlCheckProcessRequirements )
            {
                (*PfnXamlCheckProcessRequirements)();
            }

            ::FreeLibrary(Module);
        }
    }

    winrt::init_apartment(winrt::apartment_type::single_threaded);

    bool IsRedirect = false;

    // Find out what kind of activation this is.
    winrt::Microsoft::Windows::AppLifecycle::AppActivationArguments Args = winrt::Microsoft::Windows::AppLifecycle::AppInstance::GetCurrent().GetActivatedEventArgs();
    winrt::Microsoft::Windows::AppLifecycle::ExtendedActivationKind Kind = Args.Kind();

    if ( Kind == winrt::Microsoft::Windows::AppLifecycle::ExtendedActivationKind::Launch )
    {
        // This is a launch activation.
        ReportLaunchArgs(L"Main", Args);
    }
    else if ( Kind == winrt::Microsoft::Windows::AppLifecycle::ExtendedActivationKind::File )
    {
        ReportFileArgs(L"Main", Args);

        try
        {
            // This is a file activation: here we'll get the file information,
            // and register the file name as our instance key.
            winrt::Windows::ApplicationModel::Activation::IFileActivatedEventArgs FileArgs = Args.Data().as<winrt::Windows::ApplicationModel::Activation::IFileActivatedEventArgs>();

            if ( FileArgs )
            {
                winrt::Windows::Storage::IStorageItem                File        = FileArgs.Files().GetAt(0);
                winrt::Microsoft::Windows::AppLifecycle::AppInstance KeyInstance = winrt::Microsoft::Windows::AppLifecycle::AppInstance::FindOrRegisterForKey(File.Name());
                OutputDebug(L"Registered key = {}", KeyInstance.Key());

                // If we successfully registered the file name, we must be the
                // only instance running that was activated for this file.
                if ( KeyInstance.IsCurrent() )
                {
                    // Report successful file name key registration.
                    OutputDebug(L"IsCurrent=true; registered this instance for {}", File.Name());

                    [[maybe_unused]] winrt::event_token ActivationToken =                                                               //
                      KeyInstance.Activated(                                                                                            //
                        [&KeyInstance](const auto& Sender, const winrt::Microsoft::Windows::AppLifecycle::AppActivationArguments& Args) //
                        {                                                                                                               //
                            OnActivated(Sender, Args);
                        }
                      );

                    OutputDebug(L"Connected Activated event");
                }
                else
                {
                    // We're in an STA so we must not block the thread by
                    // waiting on the async call. Instead, we'll move the call
                    // to a separate thread, and use an event to synchronize.
                    IsRedirect = true;
                    RedirectEventHandle.create();
                    Redirect(KeyInstance, Args);

                    DWORD  HandleIndex = 0;
                    HANDLE RawHandle   = RedirectEventHandle.get();

                    if ( CoWaitForMultipleObjects(CWMO_DEFAULT, INFINITE, 1, &RawHandle, &HandleIndex) != 0 )
                    {
                        OutputDebug(L"Error waiting on event");
                    }
                }
            }
        }
        catch ( ... )
        {
            OutputDebug(L"Error getting instance information");
        }
    }

    if ( not IsRedirect )
    {
        ::winrt::Microsoft::UI::Xaml::Application::Start( //
          [](auto&&)                                      //
          {                                               //
              ::winrt::make<::winrt::Mercatec::Application::implementation::App>();
          }
        );
    }

    return 0;
}
