#pragma once

#include "Mercatec.Helpers.FunctionTraits.hpp"
#include "Mercatec.Helpers.Platform.hpp"
#include "Mercatec.Helpers.Utility.hpp"
#include <optional>

namespace Cxx
{
    template <typename Type>
    struct Optional : public std::optional<Type>
    {
        using base_type = std::optional<Type>;
        using std::optional<Type>::optional;
        using std::optional<Type>::operator=;

        template <typename Self, std::integral... Index>
        constexpr decltype(auto) operator[](this Self&& self, const Index... indices)
        requires requires { self->operator[](indices...); }
        {
            return self->operator[](indices...);
        }

        template <typename Self>
        constexpr decltype(auto) operator*(this Self&& self)
        {
            if ( not self.has_value() )
                throw std::bad_optional_access{};

            return Cxx::Utilities::deep_smart_pointer_dereference(self.base_type::operator->());
        }

        template <typename Self>
        constexpr decltype(auto) operator->(this Self&& self)
        {
            using Cxx::Utilities::deep_raw_pointer_dereference;

            if ( not self.has_value() )
                throw std::bad_optional_access{};

            if constexpr ( requires { deep_raw_pointer_dereference(self.base_type::operator->()).operator->(); } )
            {
                return deep_raw_pointer_dereference(self.base_type::operator->());
            }
            else
            {
                return &deep_raw_pointer_dereference(self.base_type::operator->());
            }
        }
    };
} // namespace Cxx
