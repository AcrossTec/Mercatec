#include "pch.h"
#include "Mercatec.WinUIEx.UserDataPaths.hpp"
#include "Mercatec.WinUIEx.WindowsShell.hpp"

namespace Mercatec::WinUIEx
{
    winrt::hstring UserDataPaths::CameraRoll() noexcept
    {
        return GetKnownFolderPath(FOLDERID_CameraRoll).value_or(winrt::impl::empty_value<winrt::hstring>());
    }

    winrt::hstring UserDataPaths::Cookies() noexcept
    {
        return GetKnownFolderPath(FOLDERID_Cookies).value_or(winrt::impl::empty_value<winrt::hstring>());
    }

    winrt::hstring UserDataPaths::Desktop() noexcept
    {
        return GetKnownFolderPath(FOLDERID_Desktop).value_or(winrt::impl::empty_value<winrt::hstring>());
    }

    winrt::hstring UserDataPaths::Documents() noexcept
    {
        return GetKnownFolderPath(FOLDERID_Documents).value_or(winrt::impl::empty_value<winrt::hstring>());
    }

    winrt::hstring UserDataPaths::Downloads() noexcept
    {
        return GetKnownFolderPath(FOLDERID_Downloads).value_or(winrt::impl::empty_value<winrt::hstring>());
    }

    winrt::hstring UserDataPaths::Favorites() noexcept
    {
        return GetKnownFolderPath(FOLDERID_Favorites).value_or(winrt::impl::empty_value<winrt::hstring>());
    }

    winrt::hstring UserDataPaths::History() noexcept
    {
        return GetKnownFolderPath(FOLDERID_History).value_or(winrt::impl::empty_value<winrt::hstring>());
    }

    winrt::hstring UserDataPaths::InternetCache() noexcept
    {
        return GetKnownFolderPath(FOLDERID_InternetCache).value_or(winrt::impl::empty_value<winrt::hstring>());
    }

    winrt::hstring UserDataPaths::LocalAppData() noexcept
    {
        return GetKnownFolderPath(FOLDERID_LocalAppData).value_or(winrt::impl::empty_value<winrt::hstring>());
    }

    winrt::hstring UserDataPaths::LocalAppDataLow() noexcept
    {
        return GetKnownFolderPath(FOLDERID_LocalAppDataLow).value_or(winrt::impl::empty_value<winrt::hstring>());
    }

    winrt::hstring UserDataPaths::Music() noexcept
    {
        return GetKnownFolderPath(FOLDERID_Music).value_or(winrt::impl::empty_value<winrt::hstring>());
    }

    winrt::hstring UserDataPaths::Pictures() noexcept
    {
        return GetKnownFolderPath(FOLDERID_Pictures).value_or(winrt::impl::empty_value<winrt::hstring>());
    }

    winrt::hstring UserDataPaths::Profile() noexcept
    {
        return GetKnownFolderPath(FOLDERID_Profile).value_or(winrt::impl::empty_value<winrt::hstring>());
    }

    winrt::hstring UserDataPaths::Recent() noexcept
    {
        return GetKnownFolderPath(FOLDERID_Recent).value_or(winrt::impl::empty_value<winrt::hstring>());
    }

    winrt::hstring UserDataPaths::RoamingAppData() noexcept
    {
        return GetKnownFolderPath(FOLDERID_RoamingAppData).value_or(winrt::impl::empty_value<winrt::hstring>());
    }

    winrt::hstring UserDataPaths::SavedPictures() noexcept
    {
        return GetKnownFolderPath(FOLDERID_SavedPictures).value_or(winrt::impl::empty_value<winrt::hstring>());
    }

    winrt::hstring UserDataPaths::Screenshots() noexcept
    {
        return GetKnownFolderPath(FOLDERID_Screenshots).value_or(winrt::impl::empty_value<winrt::hstring>());
    }

    winrt::hstring UserDataPaths::Templates() noexcept
    {
        return GetKnownFolderPath(FOLDERID_Templates).value_or(winrt::impl::empty_value<winrt::hstring>());
    }

    winrt::hstring UserDataPaths::Videos() noexcept
    {
        return GetKnownFolderPath(FOLDERID_Videos).value_or(winrt::impl::empty_value<winrt::hstring>());
    }
} // namespace Mercatec::WinUIEx
