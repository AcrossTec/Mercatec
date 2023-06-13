#include "pch.h"
#include "Mercatec.Helpers.ViewModels.ObservableObject.h"
#if __has_include("ViewModels.ObservableObject.g.cpp")
# include "ViewModels.ObservableObject.g.cpp"
#endif

#include <Mercatec.Helpers.Types.hpp>
#include <Mercatec.Helpers.Strings.hpp>
#include <Mercatec.Helpers.Models.hpp>

using namespace ::Mercatec::Types;

using ::Mercatec::Helpers::Empty;

namespace winrt::Mercatec::Helpers::ViewModels::implementation
{
    ObservableObject::ObservableObject() noexcept
      : m_IsEmpty{ false }
    {
    }

    bool ObservableObject::IsEmpty() const noexcept
    {
        return m_IsEmpty;
    }

    void ObservableObject::IsEmpty(const bool is_empty) noexcept
    {
        SET_PROPERTY(m_IsEmpty, is_empty);
    }

    void ObservableObject::Merge([[maybe_unused]] const ViewModels::ObservableObject& source)
    {
    }

    void ObservableObject::NotifyPropertyChanged(const std::wstring_view property_name)
    {
        m_PropertyChanged(*this, Microsoft::UI::Xaml::Data::PropertyChangedEventArgs(property_name));
    }

    void ObservableObject::NotifyChanges()
    {
        // Notify All Properties
        NotifyPropertyChanged(Empty<Char>);
    }

    winrt::event_token ObservableObject::PropertyChanged(const Microsoft::UI::Xaml::Data::PropertyChangedEventHandler& handler)
    {
        return m_PropertyChanged.add(handler);
    }

    void ObservableObject::PropertyChanged(const winrt::event_token& token)
    {
        m_PropertyChanged.remove(token);
    }
} // namespace winrt::Mercatec::Helpers::ViewModels::implementation
