#pragma once

#include <Windows.h>

#define VIEWMODEL_DEFAULT_SET_PROPERTY(ObjectName, PropertyName, ParameterValue)                      \
 if ( m_##ObjectName.PropertyName != ParameterValue )                                                 \
 {                                                                                                    \
  m_##ObjectName.PropertyName = ParameterValue;                                                       \
  m_PropertyChanged(*this, Microsoft::UI::Xaml::Data::PropertyChangedEventArgs{ L## #PropertyName }); \
 }

#define SET_PROPERTY(field, value)                                                                             \
 if ( field != value )                                                                                         \
 {                                                                                                             \
  field = value;                                                                                               \
  constexpr std::wstring_view property_name{ __FUNCTIONW__ };                                                  \
  constexpr std::wstring_view property_changed{ property_name.substr(property_name.find_last_of(L"::") + 1) }; \
  NotifyPropertyChanged(property_changed);                                                                     \
 }

namespace Mercatec::Helpers::ViewModels
{
    template <typename Model, typename ViewModel>
    Model& ModelOf(ViewModel&& view_model) noexcept
    {
        return *reinterpret_cast<Model*>(view_model.Model());
    }
} // namespace Mercatec::Helpers::ViewModels
