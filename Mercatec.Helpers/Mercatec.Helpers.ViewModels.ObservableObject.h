#pragma once

#include "ViewModels.ObservableObject.g.h"

namespace winrt::Mercatec::Helpers::ViewModels::implementation
{
    struct ObservableObject : ObservableObjectT<ObservableObject>
    {
    public:
        ObservableObject();

        bool IsEmpty() const noexcept;
        void IsEmpty(const bool empty) noexcept;

        void Merge(const ViewModels::ObservableObject& source);
        void NotifyPropertyChanged(const std::wstring_view property_name);
        void NotifyChanges();

        winrt::event_token PropertyChanged(const Microsoft::UI::Xaml::Data::PropertyChangedEventHandler& handler);
        void               PropertyChanged(const winrt::event_token& token);

    private:
        bool                                                                 m_IsEmpty;
        winrt::event<Microsoft::UI::Xaml::Data::PropertyChangedEventHandler> m_PropertyChanged;
    };
} // namespace winrt::Mercatec::ViewModels::implementation

namespace winrt::Mercatec::Helpers::ViewModels::factory_implementation
{
    struct ObservableObject : ObservableObjectT<ObservableObject, implementation::ObservableObject>
    {
    };
} // namespace winrt::Mercatec::ViewModels::factory_implementation
