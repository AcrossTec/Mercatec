#pragma once

#include "Customer.g.h"

namespace winrt::Mercatec::ViewModels::implementation
{
    struct Customer : CustomerT<Customer>
    {
        Customer();
    };
} // namespace winrt::Mercatec::ViewModels::implementation

namespace winrt::Mercatec::ViewModels::factory_implementation
{
    struct Customer : CustomerT<Customer, implementation::Customer>
    {
    };
} // namespace winrt::Mercatec::ViewModels::factory_implementation
