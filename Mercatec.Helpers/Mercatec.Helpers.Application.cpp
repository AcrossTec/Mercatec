#include "pch.h"
#include "Mercatec.Helpers.Application.hpp"
#include <winrt/Mercatec.Helpers.h>

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

    winrt::Microsoft::UI::Xaml::XamlRoot XamlRoot() noexcept
    {
        const auto Current    = Microsoft::UI::Xaml::Application::Current();
        const auto App        = Current.as<winrt::Mercatec::Helpers::IApplication>();
        const auto MainWindow = App.MainWindow();
        const auto XamlRoot   = MainWindow.Content().XamlRoot();

        return XamlRoot;
    }
} // namespace Mercatec::Helpers::Applications