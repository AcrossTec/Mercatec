#include "pch.h"
#include <winrt/Mercatec.WinUIEx.h>
#include <winrt/Mercatec.WinUIEx.Messaging.h>
#include <Mercatec.WinUIEx.AppDataPaths.hpp>
#include <Mercatec.WinUIEx.UserDataPaths.hpp>
#include <Mercatec.WinUIEx.WindowsShell.hpp>
#include <Mercatec.WinUIEx.Application.hpp>

//!
//! https://google.github.io/googletest/primer.html
//!

using namespace winrt;
using namespace winrt::Mercatec::WinUIEx;
using namespace ::Mercatec::WinUIEx;

class LocalSettingsTest : public ::testing::TestWithParam<std::tuple<std::filesystem::path, bool>>
{
protected:
    // LocalSettingsTest() noexcept
    // {
    //    // You can do set-up work for each test here.
    // }
    //
    // ~LocalSettingsTest() noexcept
    // {
    //    // You can do clean-up work that doesn't throw exceptions here.
    // }

    // If the constructor and destructor are not enough for setting up
    // and cleaning up each test, you can define the following methods:

    void SetUp() override
    {
        // Code here will be called immediately after the constructor (right before each test).
        wchar_t CurrentPathExe[MAX_PATH] = { L'\0' };
        ::GetModuleFileNameW(NULL, CurrentPathExe, MAX_PATH);
        std::filesystem::path ModuleFilePath{ CurrentPathExe };
        std::filesystem::current_path(ModuleFilePath.parent_path());
        Settings.AppDataPath((std::filesystem::current_path() / MercatecTestPath()).c_str());
    }

    void TearDown() override
    {
        // Code here will be called immediately after each test (right before the destructor).
        ClearSettings();
    }

    const std::filesystem::path& MercatecTestPath()
    {
        return std::get<std::filesystem::path>(GetParam());
    }

    bool& DestroyFile()
    {
        return const_cast<bool&>(std::get<bool>(GetParam()));
    }

    void ClearSettings() noexcept
    {
        if ( DestroyFile() )
        {
            std::filesystem::remove(Settings.SettingFile().c_str());
            ::RemoveDirectoryW(Settings.AppDataPath().c_str());
            ::RemoveDirectoryW(MercatecTestPath().c_str());
        }
    }

    // Class members declared here can be used by all tests in the test suite
    LocalSettings Settings;
};

winrt::hstring GetFolderPath(const int32_t CSIDL)
{
    return ::Mercatec::WinUIEx::GetSpecialFolderPath(CSIDL) //
      .value_or(winrt::impl::empty_value<winrt::hstring>());
}

TEST_P(LocalSettingsTest, CreateSettingFile)
{
    EXPECT_NO_THROW(ClearSettings(););
    EXPECT_TRUE(std::filesystem::create_directories(Settings.AppDataPath().c_str()));
    EXPECT_TRUE(::RemoveDirectoryW(Settings.AppDataPath().c_str()));
    EXPECT_FALSE(std::filesystem::exists(Settings.SettingFile().c_str()));

    // Open the existing file, or if the file does not exist, create a new file.
    EXPECT_TRUE(std::filesystem::create_directories(Settings.AppDataPath().c_str()));

    HANDLE FileData = CreateFileW(
      Settings.SettingFile().c_str(), // Open Two.txt
      FILE_APPEND_DATA,               // Open for writing
      FILE_SHARE_READ,                // Allow multiple readers
      NULL,                           // No security
      OPEN_ALWAYS,                    // Open or Create
      FILE_ATTRIBUTE_NORMAL,          // Normal file
      NULL
    ); // no attr. template

    EXPECT_NE(FileData, INVALID_HANDLE_VALUE);

    if ( FileData != INVALID_HANDLE_VALUE )
    {
        CloseHandle(FileData);
    }

    EXPECT_TRUE(std::filesystem::exists(Settings.SettingFile().c_str()));
    EXPECT_TRUE(std::filesystem::remove(Settings.SettingFile().c_str()));
    EXPECT_FALSE(std::filesystem::exists(Settings.SettingFile().c_str()));
}

TEST_P(LocalSettingsTest, KnownDirectories)
{
    // clang-format off
    EXPECT_EQ(AppDataPaths::Cookies()       , GetFolderPath(CSIDL_COOKIES)       );
    EXPECT_EQ(AppDataPaths::Desktop()       , GetFolderPath(CSIDL_DESKTOP)       );
    EXPECT_EQ(AppDataPaths::Documents()     , GetFolderPath(CSIDL_MYDOCUMENTS)   );
    EXPECT_EQ(AppDataPaths::Documents()     , GetFolderPath(CSIDL_PERSONAL)      );
    EXPECT_EQ(AppDataPaths::Favorites()     , GetFolderPath(CSIDL_FAVORITES)     );
    EXPECT_EQ(AppDataPaths::History()       , GetFolderPath(CSIDL_HISTORY)       );
    EXPECT_EQ(AppDataPaths::InternetCache() , GetFolderPath(CSIDL_INTERNET_CACHE));
    EXPECT_EQ(AppDataPaths::LocalAppData()  , GetFolderPath(CSIDL_LOCAL_APPDATA) );
    EXPECT_EQ(AppDataPaths::RoamingAppData(), GetFolderPath(CSIDL_APPDATA)       );
    // clang-format on
}

TEST_P(LocalSettingsTest, SaveProperties)
{
    auto AddSettings = [&]
    {
        Settings.Add(L"Key.Char", u'C');
        Settings.Add(L"Key.Int16", int16_t(10));
        Settings.Add(L"Key.Int32", int32_t(20));
        Settings.Add(L"Key.Int64", int64_t(30));
        Settings.Add(L"Key.UInt8", uint8_t(40));
        Settings.Add(L"Key.UInt16", uint16_t(50));
        Settings.Add(L"Key.UInt32", uint32_t(60));
        Settings.Add(L"Key.UInt64", uint64_t(70));
        Settings.Add(L"Key.Single", float_t(80.80));
        Settings.Add(L"Key.Double", double_t(90.90));
        Settings.Add(L"Key.Boolean", true);

        Settings.Add(L"Key.String", L"String"sv);
        Settings.Add(L"Key.UInt8[]", com_array<uint8_t>({ 1, 2, 3, 4, 5, 6, 7, 8, 9, 10 }));
        Settings.Add(L"Key.Guid", guid(L"b3bd0870-f4e5-4a37-b5fe-0d38b4c39bd2"));

        Settings.Add(L"Key.DateTime", Windows::Foundation::DateTime(static_cast<std::chrono::local_days>(std::chrono::year_month_day(std::chrono::year(2023), std::chrono::December, std::chrono::day(31))).time_since_epoch()));
        Settings.Add(L"Key.TimeSpan", Windows::Foundation::TimeSpan(std::chrono::milliseconds(std::chrono::hours(1))));

        Windows::Storage::Streams::Buffer Buffer(sizeof(wchar_t) * 10 /*Denis West*/);
        Buffer.Length(sizeof(wchar_t) * 5);
        memcpy_s(Buffer.data(), Buffer.Length() * sizeof(wchar_t), L"Denis", sizeof(wchar_t) * 5);
        Settings.Add(L"Key.IBuffer.1", Buffer);

        Buffer.Length(sizeof(wchar_t) * 10);
        memcpy_s(Buffer.data() + sizeof(wchar_t) * 6, sizeof(wchar_t) * 4, L"West", sizeof(wchar_t) * 4);
        Settings.Add(L"Key.IBuffer.2", Buffer, sizeof(wchar_t) * 6, sizeof(wchar_t) * 4);
    };

    EXPECT_NO_THROW(AddSettings(););
    EXPECT_NO_THROW(Settings.SaveAsync().get(););
    EXPECT_TRUE(std::filesystem::exists(Settings.SettingFile().c_str()));
    EXPECT_GT(std::filesystem::file_size(Settings.SettingFile().c_str()), 0);
    DestroyFile() = false;
}

TEST_P(LocalSettingsTest, LoadPropertiesGetXXX)
{
    EXPECT_TRUE(std::filesystem::exists(Settings.SettingFile().c_str()));
    EXPECT_NO_THROW(Settings.LoadAsync().get(););

    EXPECT_EQ(Settings.GetChar(L"Key.Char"), u'C');
    EXPECT_EQ(Settings.GetInt16(L"Key.Int16"), int16_t(10));
    EXPECT_EQ(Settings.GetInt32(L"Key.Int32"), int32_t(20));
    EXPECT_EQ(Settings.GetInt64(L"Key.Int64"), int64_t(30));
    EXPECT_EQ(Settings.GetUInt8(L"Key.UInt8"), uint8_t(40));
    EXPECT_EQ(Settings.GetUInt16(L"Key.UInt16"), uint16_t(50));
    EXPECT_EQ(Settings.GetUInt32(L"Key.UInt32"), uint32_t(60));
    EXPECT_EQ(Settings.GetUInt64(L"Key.UInt64"), uint64_t(70));
    EXPECT_EQ(Settings.GetSingle(L"Key.Single"), float_t(80.80));
    EXPECT_EQ(Settings.GetDouble(L"Key.Double"), double_t(90.90));
    EXPECT_EQ(Settings.GetString(L"Key.String"), hstring(L"String"));
    EXPECT_EQ(Settings.GetBoolean(L"Key.Boolean"), true);

    EXPECT_EQ(Settings.GetGuid(L"Key.Guid"), guid(L"b3bd0870-f4e5-4a37-b5fe-0d38b4c39bd2"));
    EXPECT_EQ(Settings.GetArray(L"Key.UInt8[]"), com_array<uint8_t>({ 1, 2, 3, 4, 5, 6, 7, 8, 9, 10 }));

    EXPECT_EQ(Settings.GetDateTime(L"Key.DateTime"), Windows::Foundation::DateTime(static_cast<std::chrono::local_days>(std::chrono::year_month_day(2023y, std::chrono::December, 31d)).time_since_epoch()));
    EXPECT_EQ(Settings.GetTimeSpan(L"Key.TimeSpan"), Windows::Foundation::TimeSpan(3'600'000ms));

    auto ExpectBufferEq = [](auto&& Buffer, auto&& Value)
    {
        const wchar_t* TextBuffer = reinterpret_cast<const wchar_t*>(Buffer.data());
        EXPECT_TRUE(std::ranges::equal(TextBuffer, TextBuffer + Buffer.Length() / sizeof(wchar_t), Value.begin(), Value.end()));
    };

    ExpectBufferEq(Settings.GetBuffer(L"Key.IBuffer.1"), L"Denis"sv);
    ExpectBufferEq(Settings.GetBuffer(L"Key.IBuffer.2"), L"West"sv);
    DestroyFile() = false;
}

TEST_P(LocalSettingsTest, LoadPropertiesGetMethod)
{
    EXPECT_TRUE(std::filesystem::exists(Settings.SettingFile().c_str()));
    EXPECT_NO_THROW(Settings.LoadAsync().get(););

    auto ExpectEq = [&]<typename TValue>(const std::wstring_view Key, TValue&& CompareValue)
    {
        std::remove_cvref_t<TValue> Value{};
        Settings.Get(Key, Value);
        EXPECT_EQ(Value, CompareValue);
    };

    ExpectEq(L"Key.Char", u'C');
    ExpectEq(L"Key.Int16", int16_t(10));
    ExpectEq(L"Key.Int32", int32_t(20));
    ExpectEq(L"Key.Int64", int64_t(30));
    ExpectEq(L"Key.UInt8", uint8_t(40));
    ExpectEq(L"Key.UInt16", uint16_t(50));
    ExpectEq(L"Key.UInt32", uint32_t(60));
    ExpectEq(L"Key.UInt64", uint64_t(70));
    ExpectEq(L"Key.Single", float_t(80.80));
    ExpectEq(L"Key.Double", double_t(90.90));
    ExpectEq(L"Key.String", hstring(L"String"));
    ExpectEq(L"Key.Boolean", true);
    ExpectEq(L"Key.Guid", guid(L"b3bd0870-f4e5-4a37-b5fe-0d38b4c39bd2"));
    ExpectEq(L"Key.UInt8[]", com_array<uint8_t>({ 1, 2, 3, 4, 5, 6, 7, 8, 9, 10 }));
    ExpectEq(L"Key.DateTime", Windows::Foundation::DateTime(static_cast<std::chrono::local_days>(std::chrono::year_month_day(2023y, std::chrono::December, 31d)).time_since_epoch()));
    ExpectEq(L"Key.TimeSpan", Windows::Foundation::TimeSpan(3'600'000ms));

    auto ExpectBufferEq = [&](const std::wstring_view Key, const std::wstring_view Value)
    {
        Windows::Storage::Streams::IBuffer Buffer;
        Settings.Get(Key, Buffer);
        const wchar_t* TextBuffer = reinterpret_cast<const wchar_t*>(Buffer.data());
        EXPECT_TRUE(std::ranges::equal(TextBuffer, TextBuffer + Buffer.Length() / sizeof(wchar_t), Value.begin(), Value.end()));
    };

    ExpectBufferEq(L"Key.IBuffer.1", L"Denis");
    ExpectBufferEq(L"Key.IBuffer.2", L"West");
}

INSTANTIATE_TEST_SUITE_P( //
  MercatecWinUIEx,
  LocalSettingsTest,
  ::testing::Values(std::make_tuple(std::filesystem::path(L"LocalSettingsTest"), true))
);
