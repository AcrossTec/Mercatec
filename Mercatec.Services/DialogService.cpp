#include "pch.h"
#include "DialogService.h"
#if __has_include("DialogService.g.cpp")
# include "DialogService.g.cpp"
#endif

#include <winrt/Microsoft.UI.h>
#include <winrt/Microsoft.UI.Xaml.h>
#include <winrt/Microsoft.UI.Xaml.Controls.h>

#include <Mercatec.Helpers.Types.hpp>
#include <Mercatec.Helpers.Strings.hpp>

using namespace std::literals::chrono_literals;
using namespace ::Mercatec::Types;

using ::Mercatec::Helpers::Empty;

namespace winrt::Mercatec::Services::implementation
{
    DialogService::DialogService()
    {
    }

    IAsyncOperation<bool> DialogService::ShowAsync( //
      const Microsoft::UI::Xaml::XamlRoot& xaml_root,
      const std::wstring_view              title,
      const std::wstring_view              content
    )
    {
        return ShowAsync(xaml_root, title, content, L"Ok", Empty<Char>);
    }

    IAsyncOperation<bool> DialogService::ShowAsync( //
      const Microsoft::UI::Xaml::XamlRoot& xaml_root,
      const std::wstring_view              title,
      const std::wstring_view              content,
      const std::wstring_view              ok
    )
    {
        return ShowAsync(xaml_root, title, content, ok, Empty<Char>);
    }

    IAsyncOperation<bool> DialogService::ShowAsync( //
      const Microsoft::UI::Xaml::XamlRoot& xaml_root,
      const std::wstring_view              title,
      const std::wstring_view              content,
      const std::wstring_view              ok,
      const std::wstring_view              cancel
    )
    {
        MUXC::ContentDialog dialog;
        dialog.XamlRoot(xaml_root);
        dialog.Title(PropertyValue::CreateString(title));
        dialog.Content(PropertyValue::CreateString(content));
        dialog.PrimaryButtonText(ok);

        if ( not cancel.empty() )
        {
            dialog.SecondaryButtonText(cancel);
        }

        auto result = co_await dialog.ShowAsync();
        co_return result == MUXC::ContentDialogResult::Primary;
    }
} // namespace winrt::Mercatec::Services::implementation
