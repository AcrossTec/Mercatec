#pragma once

#include <winrt/Windows.Foundation.h>
#include <winrt/Windows.Foundation.Collections.h>

#include <concepts>

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
    using Guid = winrt::guid;

    using Boolean = bool;

    using Byte = uint8_t;

    using Int8  = int_fast8_t;
    using UInt8 = uint_fast8_t;

    using Int16  = int_fast16_t;
    using UInt16 = uint_fast16_t;

    using Int32  = int_fast32_t;
    using UInt32 = uint_fast32_t;

    using Int64  = int_fast64_t;
    using UInt64 = uint_fast64_t;

    using Single = float_t;
    using Double = double_t;

    using Char   = wchar_t;
    using String = winrt::hstring;

    using Object   = winrt::Windows::Foundation::IInspectable;
    using DateTime = winrt::Windows::Foundation::DateTime;
    using TimeSpan = winrt::Windows::Foundation::TimeSpan;

    template <typename T>
    using Nullable = std::optional<T>;

    template <typename T>
    using IReference = winrt::Windows::Foundation::IReference<T>;

    template <typename T>
    using IVector = winrt::Windows::Foundation::Collections::IVector<T>;

    template <typename T>
    using IObservableVector = winrt::Windows::Foundation::Collections::IObservableVector<T>;

    template <typename Key, typename Value>
    using IMap = winrt::Windows::Foundation::Collections::IMap<Key, Value>;

    template <typename Key, typename Value>
    using IObservableMap = winrt::Windows::Foundation::Collections::IObservableMap<Key, Value>;

    template <typename T>
    using array_view = winrt::array_view<T>;

    template <typename T>
    using com_array = winrt::com_array<T>;

    using winrt::Windows::Foundation::GuidHelper;

    using winrt::multi_threaded_map;
    using winrt::multi_threaded_observable_map;
    using winrt::multi_threaded_observable_vector;
    using winrt::multi_threaded_vector;
    using winrt::single_threaded_map;
    using winrt::single_threaded_observable_map;
    using winrt::single_threaded_observable_vector;
    using winrt::single_threaded_vector;
} // namespace Mercatec::inline Types

template <typename T>
inline constexpr bool std::ranges::enable_borrowed_range<Mercatec::IVector<T>> = true;

template <typename T>
inline constexpr bool std::ranges::enable_borrowed_range<Mercatec::IObservableVector<T>> = true;
