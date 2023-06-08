#include "pch.h"
#include "Mercatec.Application.ActivationService.hpp"

namespace Mercatec::Application
{
    winrt::com_ptr<ActivationInfo> ActivationInfo::CreateDefault()
    {
        return Create<winrt::Mercatec::ViewModels::DashboardViewModel>();
    }
} // namespace Mercatec::Application
