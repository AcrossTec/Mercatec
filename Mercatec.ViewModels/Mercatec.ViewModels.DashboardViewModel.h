#pragma once

#include "DashboardViewModel.g.h"

namespace winrt::Mercatec::ViewModels::implementation
{
    struct DashboardViewModel : DashboardViewModelT<DashboardViewModel>
    {
        DashboardViewModel();
    };
} // namespace winrt::Mercatec::ViewModels::implementation

namespace winrt::Mercatec::ViewModels::factory_implementation
{
    struct DashboardViewModel : DashboardViewModelT<DashboardViewModel, implementation::DashboardViewModel>
    {
    };
} // namespace winrt::Mercatec::ViewModels::factory_implementation
