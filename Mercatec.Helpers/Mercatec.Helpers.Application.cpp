#include "pch.h"
#include "Mercatec.Helpers.Application.hpp"

using namespace winrt;

namespace Mercatec::Helpers::Applications
{
    winrt::IInspectable ResourceLookup(const std::wstring_view Key) noexcept
    {
        return Application::Current().Resources().Lookup(box_value(Key));
    }

    winrt::hstring ApplicationName() noexcept
    {
        return Lookup<winrt::hstring>(L"AppName");
    }

    winrt::hstring IconPath() noexcept
    {
        return Lookup<winrt::hstring>(L"IconPath");
    }
} // namespace Mercatec::Helpers::Applications