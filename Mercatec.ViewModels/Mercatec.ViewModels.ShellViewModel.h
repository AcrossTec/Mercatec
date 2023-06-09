#pragma once

#include "ShellViewModel.g.h"

namespace winrt::Mercatec::ViewModels::implementation
{
    struct ShellViewModel : ShellViewModelT<ShellViewModel>
    {
        ShellViewModel( //!
          const Helpers::Services::ILoginService&   login_service,
          const Helpers::Services::ICommonServices& common_services
        );
    };
} // namespace winrt::Mercatec::ViewModels::implementation

namespace winrt::Mercatec::ViewModels::factory_implementation
{
    struct ShellViewModel : ShellViewModelT<ShellViewModel, implementation::ShellViewModel>
    {
    };
} // namespace winrt::Mercatec::ViewModels::factory_implementation
