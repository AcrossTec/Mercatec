#pragma once

#include <string_view>

#define SET_PROPERTY(field, value)                                                                             \
 if ( field != value )                                                                                         \
 {                                                                                                             \
  field = value;                                                                                               \
  constexpr std::wstring_view property_name{ __FUNCTIONW__ };                                                  \
  constexpr std::wstring_view property_changed{ property_name.substr(property_name.find_last_of(L"::") + 1) }; \
  NotifyPropertyChanged(property_changed);                                                                     \
 }

namespace Mercatec::Helpers::Models
{
    template <typename Model, typename ViewModel>
    Model& ModelOf(ViewModel&& view_model) noexcept
    {
        return *reinterpret_cast<Model*>(view_model.Model());
    }
} // namespace Mercatec::Helpers::Models
