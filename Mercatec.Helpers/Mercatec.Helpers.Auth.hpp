#pragma once

#include "Mercatec.Helpers.Exports.Api.hpp"
#include <winrt/Windows.Foundation.h>

namespace Mercatec::Helpers::inline Auth
{
    MERCATEC_HELPERS_API winrt::hstring GetDeviceId();
}
