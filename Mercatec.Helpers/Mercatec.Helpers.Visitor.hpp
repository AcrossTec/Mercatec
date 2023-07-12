#pragma once

#include <variant>
#include <any>

//!
//! std::visit
//! https://en.cppreference.com/w/cpp/utility/variant/visit
//!
//! std::type_index
//! https://en.cppreference.com/w/cpp/types/type_index
//!
//! The Amazing std::visit
//! https://www.cppstories.com/2018/09/visit-variants/
//!

namespace Mercatec::Helpers::DesignPatterns
{
    // Helper constant for the visitor
    template <class>
    inline constexpr bool always_false_v = false;

    // Helper type for the visitor
    template <class... Ts>
    struct overloaded : Ts...
    {
        using Ts::operator()...;
    };

    // explicit deduction guide (not needed as of C++20)
    template <class... Ts>
    overloaded(Ts...) -> overloaded<Ts...>;

    template <class... Ts, class Callable, class... Args>
    void visit(Callable&& callable, const std::any& any, Args&&... args)
    {
        (
          [&]
          {
              if ( any.type() == typeid(Ts) )
              {
                  std::forward<Callable>(callable)(std::any_cast<const Ts&>(any), std::forward<Args>(args)...);
              }
          }(),
          ...
        );
    }
} // namespace Mercatec::Helpers::DesignPatterns
