#pragma once

#include "Mercatec.Helpers.TypeTraits.hpp"
#include "Mercatec.Helpers.Utility.hpp"

namespace Cxx
{
    template <typename Type>
    class Reference : public std::reference_wrapper<Type>
    {
    public:
        using base_type = std::reference_wrapper<Type>;
        using std::reference_wrapper<Type>::reference_wrapper;

        template <typename Self>
        constexpr decltype(auto) operator->(this Self&& self) noexcept
        {
            if constexpr ( requires { Utilities::deep_raw_pointer_dereference(self.get()).operator->(); } )
            {
                return Utilities::deep_raw_pointer_dereference(self.get());
            }
            else
            {
                return &Utilities::deep_raw_pointer_dereference(self.get());
            }
        }

        template <typename Self>
        constexpr decltype(auto) operator*(this Self&& self) noexcept
        {
            return Utilities::deep_smart_pointer_dereference(self.get());
        }
    };
} // namespace Cxx
