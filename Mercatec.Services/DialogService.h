#pragma once

#include "DialogService.g.h"

namespace winrt::Mercatec::Services::implementation
{
    struct DialogService : DialogServiceT<DialogService>
    {
        DialogService();
        IAsyncOperation<bool> ShowAsync(const Microsoft::UI::Xaml::XamlRoot& xaml_root, const std::wstring_view title, const std::wstring_view content);
        IAsyncOperation<bool> ShowAsync(const Microsoft::UI::Xaml::XamlRoot& xaml_root, const std::wstring_view title, const std::wstring_view content, const std::wstring_view ok);
        IAsyncOperation<bool> ShowAsync(const Microsoft::UI::Xaml::XamlRoot& xaml_root, const std::wstring_view title, const std::wstring_view content, const std::wstring_view ok, const std::wstring_view cancel);
    };
} // namespace winrt::Mercatec::Services::implementation

namespace winrt::Mercatec::Services::factory_implementation
{
    struct DialogService : DialogServiceT<DialogService, implementation::DialogService>
    {
    };
} // namespace winrt::Mercatec::Services::factory_implementation
