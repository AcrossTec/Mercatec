#pragma once

#include <Mercatec.Helpers.Exports.Api.hpp>

#include <winrt/Windows.Foundation.h>
#include <winrt/Windows.Foundation.Collections.h>
#include <winrt/Windows.UI.Xaml.Interop.h>

#include <concepts>
#include <compare>

#include <array>
#include <vector>
#include <deque>
#include <list>

#include <map>
#include <set>

#include <unordered_map>
#include <unordered_set>

namespace Mercatec::inline Types
{
    using Boolean = bool;
    using Guid    = winrt::guid;
    using Byte    = uint8_t;
    using Int8    = int_fast8_t;
    using UInt8   = uint_fast8_t;
    using Int16   = int_fast16_t;
    using UInt16  = uint_fast16_t;
    using Int32   = int_fast32_t;
    using UInt32  = uint_fast32_t;
    using Int64   = int_fast64_t;
    using UInt64  = uint_fast64_t;
    using Single  = float_t;
    using Double  = double_t;
    using Char    = wchar_t;
    using String  = winrt::hstring;

    template <typename T>
    using Nullable = std::optional<T>;

    using winrt::Windows::Foundation::DateTime;
    using winrt::Windows::Foundation::GuidHelper;
    using winrt::Windows::Foundation::IInspectable;
    using winrt::Windows::Foundation::IReference;
    using winrt::Windows::Foundation::TimeSpan;
    using winrt::Windows::Foundation::Collections::IMap;
    using winrt::Windows::Foundation::Collections::IObservableMap;
    using winrt::Windows::Foundation::Collections::IObservableVector;
    using winrt::Windows::Foundation::Collections::IVector;

    using winrt::Windows::Foundation::IAsyncAction;
    using winrt::Windows::Foundation::IAsyncActionWithProgress;
    using winrt::Windows::Foundation::IAsyncOperation;
    using winrt::Windows::Foundation::IAsyncOperationWithProgress;

    using winrt::array_view;
    using winrt::com_array;
    using winrt::com_ptr;
    using winrt::fire_and_forget;
    using winrt::weak_ref;

    using winrt::multi_threaded_map;
    using winrt::multi_threaded_observable_map;
    using winrt::multi_threaded_observable_vector;
    using winrt::multi_threaded_vector;
    using winrt::single_threaded_map;
    using winrt::single_threaded_observable_map;
    using winrt::single_threaded_observable_vector;
    using winrt::single_threaded_vector;

    using winrt::make;
    using winrt::make_agile;
    using winrt::make_self;
    using winrt::xaml_typename;

    using winrt::Windows::UI::Xaml::Interop::TypeName;
} // namespace Mercatec::inline Types

template <typename T>
inline constexpr bool std::ranges::enable_borrowed_range<Mercatec::IVector<T>> = true;

template <typename T>
inline constexpr bool std::ranges::enable_borrowed_range<Mercatec::IObservableVector<T>> = true;

namespace winrt::Windows::UI::Xaml::Interop
{
    MERCATEC_HELPERS_API std::strong_ordering operator<=>(const TypeName& left, const TypeName& right) noexcept;
}
