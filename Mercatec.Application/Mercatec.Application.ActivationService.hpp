#pragma once

#include "Mercatec.Application.Exports.Api.hpp"

#include <winrt/Mercatec.ViewModels.h>
#include <winrt/Mercatec.Helpers.ViewModels.h>
#include <winrt/Microsoft.Windows.AppLifecycle.h>
#include <winrt/Windows.UI.Xaml.Interop.h>

namespace Mercatec::Application
{
    struct ActivationInfo : winrt::implements<ActivationInfo, winrt::IInspectable>
    {
        MERCATEC_APPLICATION_API static winrt::com_ptr<ActivationInfo> CreateDefault();

        template <typename TViewModel>
        requires /* std::is_base_of_v<winrt::Mercatec::Helpers::ViewModels::ViewModelBase, TViewModel> and */ requires { winrt::xaml_typename<TViewModel>(); }
        static winrt::com_ptr<ActivationInfo> Create(const IInspectable& entry_args = nullptr)
        {
            winrt::com_ptr<ActivationInfo> Info{ winrt::make_self<ActivationInfo>() };
            Info->EntryViewModel = winrt::xaml_typename<TViewModel>();
            Info->EntryArgs      = entry_args;
            return Info;
        }

        winrt::Windows::UI::Xaml::Interop::TypeName EntryViewModel;
        winrt::IInspectable                         EntryArgs;
    };

    struct ActivationService sealed abstract
    {
    public:
        MERCATEC_APPLICATION_API static winrt::com_ptr<ActivationInfo> GetActivationInfo(const winrt::Microsoft::Windows::AppLifecycle::AppActivationArguments& Args);
    };
} // namespace Mercatec::Application
