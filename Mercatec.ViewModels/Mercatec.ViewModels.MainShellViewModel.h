#pragma once

#include "MainShellViewModel.g.h"
#include "Mercatec.ViewModels.ShellViewModel.h"

namespace winrt::Mercatec::ViewModels::implementation
{
    struct MainShellViewModel : MainShellViewModelT<MainShellViewModel, ShellViewModel>
    {
        MainShellViewModel( //!
          const Helpers::Services::ILoginService&   login_service,
          const Helpers::Services::ICommonServices& common_services
        );
    };
} // namespace winrt::Mercatec::ViewModels::implementation

namespace winrt::Mercatec::ViewModels::factory_implementation
{
    struct MainShellViewModel : MainShellViewModelT<MainShellViewModel, implementation::MainShellViewModel>
    {
    };
} // namespace winrt::Mercatec::ViewModels::factory_implementation
