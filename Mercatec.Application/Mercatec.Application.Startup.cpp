#include "pch.h"
#include "Mercatec.Application.Startup.hpp"
#include "Mercatec.Application.NavigationService.hpp"

#include <Mercatec.Helpers.Types.hpp>
#include <Mercatec.Helpers.ServiceLocator.hpp>
#include <Mercatec.Services.hpp>

#include <winrt/Mercatec.Application.h>
#include <winrt/Mercatec.Helpers.ViewModels.h>
#include <winrt/Mercatec.ViewModels.h>

//!
//! Example: Creating a C++ Windows Runtime Component and Consuming it from C#
//! https://learn.microsoft.com/en-us/cpp/parallel/concrt/creating-asynchronous-operations-in-cpp-for-windows-store-apps?view=msvc-170
//! https://learn.microsoft.com/en-us/cpp/parallel/concrt/creating-asynchronous-operations-in-cpp-for-windows-store-apps?view=msvc-170#example-component
//!
//! Advanced concurrency and asynchrony with C++/WinRT: Reporting progress
//! https://learn.microsoft.com/en-us/windows/uwp/cpp-and-winrt-apis/concurrency-2#reporting-progress
//!

using namespace winrt;

using namespace Cxx::DesignPatterns;

namespace ViewModels
{
    using namespace winrt::Mercatec::Helpers::ViewModels;
    using namespace winrt::Mercatec::ViewModels;
} // namespace ViewModels

namespace Interfaces
{
    using namespace winrt::Mercatec::Helpers::Services;
}

namespace Services
{
    using namespace ::Mercatec::Services;
    using namespace winrt::Mercatec::Services;
    using ::Mercatec::Application::NavigationService;
} // namespace Services

namespace Pages
{
    using namespace winrt::Mercatec::Application;
}

extern void LoadExternalDLLFiles();

namespace Mercatec::Application::Configurations
{
    IAsyncActionWithProgress<double_t> Startup::ConfigureAsync()
    {
        auto Progress{ co_await winrt::get_progress_token() };

        ConfigureServiceLocator();
        ConfigureNavigation();
        LoadExternalDLLFiles();

        for ( uint32_t Index = 0; Index <= 100; Index += 5 )
        {
            Progress(Index);
            co_await 50ms;
        }

        co_await 1s;
    }

    void Startup::ConfigureServiceLocator()
    {
        ServiceLocator::Default().Register<Interfaces::IMessageService>(winrt::make<::Services::MessageService>());
        ServiceLocator::Default().Register<Interfaces::INavigationService>(winrt::make<::Services::NavigationService>());
        ServiceLocator::Default().Register<Interfaces::IDialogService>(::Services::DialogService());
        ServiceLocator::Default().Register<Interfaces::IContextService>(::Services::ContextService());
        ServiceLocator::Default().Register<Interfaces::ISettingsService>(
          []
          {
              const auto& DialogService = ServiceLocator::Default().GetService<Interfaces::IDialogService>();
              return ::Services::SettingsService(DialogService);
          }
        );
        ServiceLocator::Default().Register<Interfaces::ILogService>(
          []
          {
              const auto& MessageService = ServiceLocator::Default().GetService<Interfaces::IMessageService>();
              return ::Services::LogService(MessageService);
          }
        );
        ServiceLocator::Default().Register<Interfaces::ICommonServices>(
          []
          {
              const auto& ContextService    = ServiceLocator::Default().GetService<Interfaces::IContextService>();
              const auto& NavigationService = ServiceLocator::Default().GetService<Interfaces::INavigationService>();
              const auto& MessageService    = ServiceLocator::Default().GetService<Interfaces::IMessageService>();
              const auto& DialogService     = ServiceLocator::Default().GetService<Interfaces::IDialogService>();
              const auto& LogService        = ServiceLocator::Default().GetService<Interfaces::ILogService>();
              return ::Services::CommonServices(ContextService, NavigationService, MessageService, DialogService, LogService);
          }
        );
        ServiceLocator::Default().Register<Interfaces::ILoginService>(
          []
          {
              const auto& MessageService = ServiceLocator::Default().GetService<Interfaces::IMessageService>();
              const auto& DialogService  = ServiceLocator::Default().GetService<Interfaces::IDialogService>();
              return ::Services::LoginService(MessageService, DialogService);
          }
        );
        ServiceLocator::Default().Register<ViewModels::LoginViewModel>(
          []
          {
              const auto& LoginService    = ServiceLocator::Default().GetService<Interfaces::ILoginService>();
              const auto& SettingsService = ServiceLocator::Default().GetService<Interfaces::ISettingsService>();
              const auto& CommonServices  = ServiceLocator::Default().GetService<Interfaces::ICommonServices>();
              return ViewModels::LoginViewModel(LoginService, SettingsService, CommonServices);
          }
        );
        ServiceLocator::Default().Register<ViewModels::ShellViewModel>(
          []
          {
              const auto& LoginService   = ServiceLocator::Default().GetService<Interfaces::ILoginService>();
              const auto& CommonServices = ServiceLocator::Default().GetService<Interfaces::ICommonServices>();
              return ViewModels::ShellViewModel(LoginService, CommonServices);
          }
        );
        ServiceLocator::Default().Register<ViewModels::MainShellViewModel>(
          []
          {
              const auto& LoginService   = ServiceLocator::Default().GetService<Interfaces::ILoginService>();
              const auto& CommonServices = ServiceLocator::Default().GetService<Interfaces::ICommonServices>();
              return ViewModels::MainShellViewModel(LoginService, CommonServices);
          }
        );
        ServiceLocator::Default().Register<ViewModels::DashboardViewModel>(
          []
          {
              [[maybe_unused]] const auto& CommonServices = ServiceLocator::Default().GetService<Interfaces::ICommonServices>();
              return ViewModels::DashboardViewModel();
          }
        );
    }

    void Startup::ConfigureNavigation()
    {
        using ::Services::NavigationService;

        NavigationService::Register<ViewModels::LoginViewModel, Pages::LoginPage>();
        NavigationService::Register<ViewModels::ShellViewModel, Pages::ShellPage>();
    }
} // namespace Mercatec::Application::Configurations
