#pragma once

#include "Mercatec.WinUIEx.Exports.Api.hpp"
#include <winrt/Windows.Foundation.h>

namespace Mercatec::WinUIEx
{
    struct MERCATEC_WINUIEX_API UserDataPaths sealed abstract
    {
        [[nodiscard]] static winrt::hstring CameraRoll() noexcept;
        [[nodiscard]] static winrt::hstring Cookies() noexcept;
        [[nodiscard]] static winrt::hstring Desktop() noexcept;
        [[nodiscard]] static winrt::hstring Documents() noexcept;
        [[nodiscard]] static winrt::hstring Downloads() noexcept;
        [[nodiscard]] static winrt::hstring Favorites() noexcept;
        [[nodiscard]] static winrt::hstring History() noexcept;
        [[nodiscard]] static winrt::hstring InternetCache() noexcept;
        [[nodiscard]] static winrt::hstring LocalAppData() noexcept;
        [[nodiscard]] static winrt::hstring LocalAppDataLow() noexcept;
        [[nodiscard]] static winrt::hstring Music() noexcept;
        [[nodiscard]] static winrt::hstring Pictures() noexcept;
        [[nodiscard]] static winrt::hstring Profile() noexcept;
        [[nodiscard]] static winrt::hstring Recent() noexcept;
        [[nodiscard]] static winrt::hstring RoamingAppData() noexcept;
        [[nodiscard]] static winrt::hstring SavedPictures() noexcept;
        [[nodiscard]] static winrt::hstring Screenshots() noexcept;
        [[nodiscard]] static winrt::hstring Templates() noexcept;
        [[nodiscard]] static winrt::hstring Videos() noexcept;
    };
} // namespace Mercatec::WinUIEx
