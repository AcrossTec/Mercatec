#include "pch.h"
#include <winrt/Mercatec.WinUIEx.h>
#include <winrt/Mercatec.WinUIEx.Messaging.h>
#include <Mercatec.WinUIEx.AppDataPaths.hpp>
#include <Mercatec.WinUIEx.UserDataPaths.hpp>
#include <Mercatec.WinUIEx.WindowsShell.hpp>

using namespace winrt;
using namespace winrt::Mercatec::WinUIEx;
using namespace ::Mercatec::WinUIEx;

winrt::hstring GetFolderPath(const int32_t CSIDL)
{
    return ::Mercatec::WinUIEx::GetSpecialFolderPath(CSIDL) //
      .value_or(winrt::impl::empty_value<winrt::hstring>());
}

TEST(Mercatec_WinUIEx_LocalSettings, KnownDirectories)
{
    EXPECT_EQ(AppDataPaths::LocalAppData(), GetFolderPath(CSIDL_LOCAL_APPDATA));
    EXPECT_EQ(AppDataPaths::RoamingAppData(), GetFolderPath(CSIDL_APPDATA));
    EXPECT_EQ(AppDataPaths::Desktop(), GetFolderPath(CSIDL_DESKTOP));
}

TEST(Mercatec_WinUIEx_LocalSettings, Properties)
{
    LocalSettings Settings;
    wprintf_s(L"File Name:     %s\n", Settings.FileName().c_str());
    wprintf_s(L"App Data Path: %s\n", Settings.AppDataPath().c_str());
    wprintf_s(L"Setting File:  %s\n", Settings.SettingFile().c_str());

    Settings.Add(L"Windows.Left", 500);
    Settings.Add(L"Windows.Top", 150);
    Settings.SaveAsync().get();
}
