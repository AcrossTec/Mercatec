#pragma once

#include <Windows.h>

#define VIEWMODEL_DEFAULT_SET_PROPERTY(ObjectName, PropertyName, ParameterValue)                      \
 if ( m_##ObjectName.PropertyName != ParameterValue )                                                 \
 {                                                                                                    \
  m_##ObjectName.PropertyName = ParameterValue;                                                       \
  m_PropertyChanged(*this, Microsoft::UI::Xaml::Data::PropertyChangedEventArgs{ L## #PropertyName }); \
 }

namespace Mercatec::Helpers::ViewModels
{
    template <typename Model, typename ViewModel>
    Model& ModelOf(ViewModel&& view_model) noexcept
    {
        return *reinterpret_cast<Model*>(view_model.Model());
    }
} // namespace Mercatec::Helpers::ViewModels
