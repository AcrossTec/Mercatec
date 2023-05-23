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
        MERCATEC_APPLICATION_API NavigationService();

        MERCATEC_APPLICATION_API static void Register(TypeName ViewModelType, TypeName ViewType);

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

        MERCATEC_APPLICATION_API static TypeName GetView(TypeName ViewModel);
        MERCATEC_APPLICATION_API static TypeName GetViewModel(TypeName View);

        MERCATEC_APPLICATION_API winrt::Microsoft::UI::Xaml::Controls::Frame Frame() const noexcept;
        MERCATEC_APPLICATION_API bool                                        CanGoBack() const noexcept;

        MERCATEC_APPLICATION_API void GoBack();
        MERCATEC_APPLICATION_API void Initialize(winrt::Microsoft::UI::Xaml::Controls::Frame Frame);

        template <typename TViewModel>
        bool Navigate(IInspectable Parameter = nullptr)
        {
            return Navigate(xaml_typename<TViewModel>(), Parameter);
        }

        MERCATEC_APPLICATION_API bool Navigate(TypeName ViewModelType);
        MERCATEC_APPLICATION_API bool Navigate(TypeName ViewModelType, IInspectable Parameter);

        template <typename TViewModel>
        void CreateNewView(IInspectable Parameter = nullptr)
        {
            return CreateNewView(xaml_typename<TViewModel>(), Parameter);
        }

        MERCATEC_APPLICATION_API void CreateNewView(TypeName ViewModelType);
        MERCATEC_APPLICATION_API void CreateNewView(TypeName ViewModelType, IInspectable Parameter);

    private:
        winrt::Microsoft::UI::Xaml::Controls::Frame m_Frame;
        static IMap<TypeName, TypeName>             m_ViewModelMap;
    };
} // namespace Mercatec::Application
