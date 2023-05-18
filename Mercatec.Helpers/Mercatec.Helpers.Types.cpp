#include "pch.h"
#include "Mercatec.Helpers.Types.hpp"

namespace winrt::Windows::UI::Xaml::Interop
{
    std::strong_ordering operator<=>(const TypeName& left, const TypeName& right) noexcept
    {
        if ( auto cmp_result = std::compare_strong_order_fallback(left.Name, right.Name); cmp_result != 0 )
        {
            return cmp_result;
        }

        return left.Kind <=> right.Kind;
    }
} // namespace winrt::Windows::UI::Xaml::Interop
