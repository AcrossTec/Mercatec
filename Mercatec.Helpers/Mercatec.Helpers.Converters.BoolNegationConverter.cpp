#include "pch.h"
#include "Mercatec.Helpers.Converters.BoolNegationConverter.h"
#if __has_include("Converters.BoolNegationConverter.g.cpp")
# include "Converters.BoolNegationConverter.g.cpp"
#endif

namespace winrt::Mercatec::Helpers::Converters::implementation
{
    BoolNegationConverter::BoolNegationConverter() noexcept
    {
    }

    IInspectable BoolNegationConverter::Convert( //
      const IInspectable&                  Value,
      [[maybe_unused]] const TypeName&     TargetType,
      [[maybe_unused]] const IInspectable& Parameter,
      [[maybe_unused]] const hstring&      Language
    ) const noexcept
    {
        return box_value(not unbox_value_or<bool>(Value, false));
    }

    IInspectable BoolNegationConverter::ConvertBack( //
      const IInspectable&                  Value,
      [[maybe_unused]] const TypeName&     TargetType,
      [[maybe_unused]] const IInspectable& Parameter,
      [[maybe_unused]] const hstring&      Language
    ) const noexcept
    {
        return box_value(not unbox_value_or<bool>(Value, false));
    }
} // namespace winrt::Mercatec::Helpers::Converters::implementation
