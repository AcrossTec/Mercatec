#pragma once

#include <winrt/Windows.Foundation.h>
#include <winrt/Windows.Foundation.Collections.h>

namespace Mercatec::Helpers
{
    using Boolean = bool;

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

    using DateTime = winrt::Windows::Foundation::DateTime;
    using TimeSpan = winrt::Windows::Foundation::TimeSpan;

    template <typename T>
    using Nullable = std::optional<T>;
} // namespace Mercatec::Helpers
