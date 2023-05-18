#include "pch.h"
#include "Mercatec.Helpers.Application.hpp"

using namespace winrt;

namespace Mercatec::Helpers::Applications
{
    winrt::hstring ApplicationName() noexcept
    {
        IInspectable app_name = Application::Current().Resources().Lookup(box_value(L"AppName"));
        return unbox_value<hstring>(app_name);
    }
} // namespace Mercatec::Helpers::Applications