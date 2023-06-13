#pragma once

#include "Converters.BoolNegationConverter.g.h"

namespace winrt::Mercatec::Helpers::Converters::implementation
{
    struct BoolNegationConverter : BoolNegationConverterT<BoolNegationConverter>
    {
        using TypeName = Windows::UI::Xaml::Interop::TypeName;

        BoolNegationConverter() noexcept;
        IInspectable Convert(const IInspectable& Value, const TypeName& TargetType, const IInspectable& Parameter, const hstring& Language) const noexcept;
        IInspectable ConvertBack(const IInspectable& Value, const TypeName& TargetType, const IInspectable& Parameter, const hstring& Language) const noexcept;
    };
} // namespace winrt::Mercatec::Helpers::Converters::implementation

namespace winrt::Mercatec::Helpers::Converters::factory_implementation
{
    struct BoolNegationConverter : BoolNegationConverterT<BoolNegationConverter, implementation::BoolNegationConverter>
    {
    };
} // namespace winrt::Mercatec::Helpers::Converters::factory_implementation
