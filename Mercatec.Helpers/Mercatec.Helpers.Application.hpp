#pragma once

#include "Mercatec.Helpers.Exports.Api.hpp"

#include <winrt/Windows.Foundation.h>

namespace Mercatec::Helpers::Applications
{
    MERCATEC_HELPERS_API winrt::hstring ApplicationName() noexcept;
} // namespace Mercatec::Helpers::Applications
