#include "pch.h"
#include "Mercatec.Application.ActivationService.hpp"

namespace Mercatec::Application
{
    winrt::com_ptr<ActivationInfo> ActivationInfo::CreateDefault()
    {
        return Create<winrt::Mercatec::ViewModels::DashboardViewModel>();
    }

    winrt::com_ptr<ActivationInfo> ActivationService::GetActivationInfo(const winrt::Microsoft::Windows::AppLifecycle::AppActivationArguments& Args)
    {
        switch ( Args.Kind() )
        { // clang-format off
                case winrt::Microsoft::Windows::AppLifecycle::ExtendedActivationKind::Launch:
                default: return ActivationInfo::CreateDefault();
        } // clang-format on
    }
} // namespace Mercatec::Application
