#pragma once

#include "Mercatec.Application.Exports.Api.hpp"
#include <Mercatec.Helpers.Types.hpp>

#include <winrt/Mercatec.Services.h>
#include <winrt/Mercatec.Helpers.Services.h>

namespace Mercatec::Application
{
    struct NavigationService : winrt::implements<NavigationService, winrt::Mercatec::Helpers::Services::INavigationService>
    {
    public:
        NavigationService();

        static UInt64 MainViewId() noexcept;
        static void   Register(TypeName ViewModelType, TypeName ViewType);

        template <typename TViewModel, typename TView>
        inline static void Register()
        {
            Register(xaml_typename<TViewModel>(), xaml_typename<TView>());
        }

        template <typename TViewModel>
        inline static TypeName GetView()
        {
            return GetView(xaml_typename<TViewModel>());
        }

        static TypeName GetView(TypeName ViewModel);
        static TypeName GetViewModel(TypeName View);

        winrt::Microsoft::UI::Xaml::Controls::Frame Frame() const noexcept;

        bool IsMainView() const noexcept;
        bool CanGoBack() const noexcept;

        void GoBack();
        void Initialize(winrt::Microsoft::UI::Xaml::Controls::Frame Frame);

        template <typename TViewModel>
        bool Navigate(IInspectable Parameter = nullptr)
        {
            return Navigate(xaml_typename<TViewModel>(), Parameter);
        }

        bool Navigate(TypeName ViewModelType);
        bool Navigate(TypeName ViewModelType, IInspectable Parameter);

        template <typename TViewModel>
        IAsyncOperation<Int32> CreateNewViewAsync(IInspectable Parameter = nullptr)
        {
            return CreateNewViewAsync(xaml_typename<TViewModel>(), Parameter);
        }

        IAsyncOperation<Int32> CreateNewViewAsync(TypeName ViewModelType);
        IAsyncOperation<Int32> CreateNewViewAsync(TypeName ViewModelType, IInspectable Parameter);
        IAsyncAction           CloseViewAsync();

    private:
        winrt::Microsoft::UI::Xaml::Controls::Frame m_Frame;
        static IMap<TypeName, TypeName>             m_ViewModelMap;
    };
} // namespace Mercatec::Application
