#include "pch.h"
#include "Mercatec.Application.NavigationService.hpp"

#include <winrt/Mercatec.Helpers.h>
#include <winrt/Mercatec.Helpers.ViewModels.h>

using namespace winrt::Microsoft::UI::Xaml;
using namespace winrt::Microsoft::UI::Xaml::Controls;

using namespace winrt::Windows::UI::Core;
using namespace winrt::Windows::UI::ViewManagement;
using namespace winrt::Windows::ApplicationModel::Core;

using namespace winrt::Mercatec::Helpers::ViewModels;

namespace Mercatec::Application
{
    Mercatec::IMap<TypeName, TypeName> NavigationService::m_ViewModelMap{ multi_threaded_map<TypeName, TypeName, std::ranges::less>() };

    NavigationService::NavigationService()
      : m_Frame{ nullptr }
    {
    }

    UInt64 NavigationService::MainViewId() noexcept
    {
        static const UInt64 ViewId = ApplicationView::GetForCurrentView().Id();
        return ViewId;
    }

    void NavigationService::Register(TypeName ViewModelType, TypeName ViewType)
    {
        if ( not m_ViewModelMap.Insert(ViewModelType, ViewType) )
        {
            throw winrt::hresult_invalid_argument(std::format(L"ViewModel already registered '{}'", ViewModelType.Name));
        }
    }

    TypeName NavigationService::GetView(TypeName ViewModel)
    {
        if ( auto Value = m_ViewModelMap.TryLookup(ViewModel); Value.has_value() )
        {
            return *Value;
        }

        throw winrt::hresult_invalid_argument(std::format(L"View not registered for ViewModel '{}'", ViewModel.Name));
    }

    TypeName NavigationService::GetViewModel(TypeName View)
    {
        using IKeyValuePair = winrt::IKeyValuePair<TypeName, TypeName>;

        // clang-format off
        auto ViewTypes = m_ViewModelMap
            | std::views::filter([&](const IKeyValuePair& Pair) { return Pair.Key() == View; })
            | std::views::transform([](const IKeyValuePair& Pair) { return Pair.Key(); });
        // clang-format on

        if ( std::begin(ViewTypes) == std::end(ViewTypes) )
        {
            throw winrt::hresult_invalid_argument(std::format(L"View not registered for ViewModel '{}'", View.Name));
        }

        return *ViewTypes.begin();
    }

    winrt::Microsoft::UI::Xaml::Controls::Frame NavigationService::Frame() const noexcept
    {
        return m_Frame;
    }

    bool NavigationService::IsMainView() const noexcept
    {
        return winrt::Windows::ApplicationModel::Core::CoreApplication::GetCurrentView().IsMain();
    }

    bool NavigationService::CanGoBack() const noexcept
    {
        return m_Frame.CanGoBack();
    }

    void NavigationService::GoBack()
    {
        m_Frame.GoBack();
    }

    void NavigationService::Initialize(winrt::Microsoft::UI::Xaml::Controls::Frame Frame)
    {
        m_Frame = Frame;
    }

    bool NavigationService::Navigate(TypeName ViewModelType)
    {
        return Navigate(ViewModelType, nullptr);
    }

    bool NavigationService::Navigate(TypeName ViewModelType, IInspectable Parameter)
    {
        if ( m_Frame == nullptr )
        {
            throw winrt::hresult_invalid_argument(L"Navigation frame not initialized.");
        }

        return m_Frame.Navigate(GetView(ViewModelType), Parameter);
    }

    IAsyncOperation<Int32> NavigationService::CreateNewViewAsync(TypeName ViewModelType)
    {
        return CreateNewViewAsync(ViewModelType, nullptr);
    }

    IAsyncOperation<Int32> NavigationService::CreateNewViewAsync(TypeName ViewModelType, IInspectable Parameter)
    {
        Int32 ViewId = 0;

        auto NewView = CoreApplication::CreateNewView();

        co_await NewView.Dispatcher().RunAsync(
          CoreDispatcherPriority::Normal,
          [&]
          {
              ViewId = ApplicationView::GetForCurrentView().Id();

              winrt::Microsoft::UI::Xaml::Controls::Frame Frame;
              ShellArgs                                   Args;

              Args.ViewModel(ViewModelType);
              Args.Parameter(Parameter);

              // Frame.Navigate(xaml_typename<ShellView>, Args);

              Window::Current().Content(Frame);
              Window::Current().Activate();
          }
        );

        if ( co_await ApplicationViewSwitcher::TryShowAsStandaloneAsync(ViewId) )
        {
            co_return ViewId;
        }

        co_return 0;
    }

    IAsyncAction NavigationService::CloseViewAsync()
    {
        Int32 CurrentId = ApplicationView::GetForCurrentView().Id();
        co_await ApplicationViewSwitcher::SwitchAsync((Int32)MainViewId(), CurrentId, ApplicationViewSwitchingOptions::ConsolidateViews);
    }
} // namespace Mercatec::Application
