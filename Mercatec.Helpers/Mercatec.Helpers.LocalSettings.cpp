#include "pch.h"
#include "Mercatec.Helpers.LocalSettings.h"
#if __has_include("LocalSettings.g.cpp")
# include "LocalSettings.g.cpp"
#endif

#include "Mercatec.Helpers.Visitor.hpp"
#include "Mercatec.Helpers.Application.hpp"
#include "Mercatec.Helpers.AppDataPaths.hpp"
#include "Mercatec.Helpers.WindowsShell.hpp"

#include <winrt/Windows.Foundation.h>
#include <winrt/Windows.UI.Xaml.Controls.h>

using namespace winrt;
using namespace winrt::Windows::Storage;
using namespace winrt::Windows::Storage::Streams;
using namespace winrt::Windows::UI::Xaml::Controls;

using namespace ::Mercatec::Helpers;
using namespace ::Mercatec::Helpers::Applications;
using namespace ::Mercatec::Helpers::DesignPatterns;

using MercatecDataPaths = ::Mercatec::Helpers::AppDataPaths;

//!
//! DataReader Class
//! https://learn.microsoft.com/en-us/uwp/api/windows.storage.streams.datareader?view=winrt-22621
//!
//! PathCombineW function (shlwapi.h)
//! https://learn.microsoft.com/en-us/windows/win32/api/shlwapi/nf-shlwapi-pathcombinew
//!
//! PathCchCombine function (pathcch.h)
//! https://learn.microsoft.com/en-us/windows/win32/api/pathcch/nf-pathcch-pathcchcombine
//!
//! Appending One File to Another File
//! https://learn.microsoft.com/en-us/windows/win32/fileio/appending-one-file-to-another-file
//!

#pragma push_macro("PathAppend")
#pragma push_macro("PathCombine")
#pragma push_macro("PathAddExtension")

#undef PathAppend
#undef PathCombine
#undef PathAddExtension

namespace winrt::Mercatec::Helpers::implementation
{
    LocalSettings::LocalSettings()
      : m_FileName{ *PathAddExtension({ ApplicationName() }, L".bin") }
    {
        AppDataPath(MercatecDataPaths::RoamingAppData());
    }

    hstring LocalSettings::AppDataPath() const noexcept
    {
        return m_AppDataPath;
    }

    void LocalSettings::AppDataPath(const std::wstring_view Value) noexcept
    {
        // clang-format off
        m_AppDataPath = *PathAppend({ Value.data(), ApplicationName() })
            .or_else([] { return PathAppend({ MercatecDataPaths::RoamingAppData(), ApplicationName() }); });
        // clang-format on
    }

    hstring LocalSettings::FileName() const noexcept
    {
        return m_FileName;
    }

    void LocalSettings::FileName(const std::wstring_view Value) noexcept
    {
        m_FileName = Value;
    }

    hstring LocalSettings::SettingFile() const noexcept
    {
        return *PathAppend({ AppDataPath(), FileName() });
    }

    Windows::Foundation::IAsyncAction LocalSettings::LoadAsync()
    {
        StorageFolder       Folder = co_await StorageFolder::GetFolderFromPathAsync(AppDataPath());
        StorageFile         File   = co_await Folder.GetFileAsync(FileName());
        IRandomAccessStream Stream = co_await File.OpenAsync(FileAccessMode::Read);

        // Create the input stream at position 0 so that the stream can be read from the beginning.
        DataReader Reader(Stream.GetInputStreamAt(0));

        // The encoding and byte order need to match the settings of the writer we previously used.
        Reader.UnicodeEncoding(UnicodeEncoding::Utf8);
        Reader.ByteOrder(ByteOrder::LittleEndian);

        // Once we have written the contents successfully we load the stream.
        co_await Reader.LoadAsync(static_cast<uint32_t>(Stream.Size()));

        // Keep reading until we consume the complete stream.
        while ( Reader.UnconsumedBufferLength() > 0 )
        {
            uint32_t     BytesToRead{ 0 };
            IBuffer      ValueBuffer{ nullptr };
            std::wstring MapKey;
            std::wstring ValueType;
            std::wstring ValueString;

            // Note that the call to readString requires a length of "code units" to read.
            // This is the reason each string is preceded by its length when "on the wire".
            BytesToRead = Reader.ReadUInt32();
            MapKey      = std::wstring(std::from_range, Reader.ReadString(BytesToRead));

            BytesToRead = Reader.ReadUInt16();
            ValueType   = std::wstring(std::from_range, Reader.ReadString(BytesToRead));

            if ( ValueType == L"G" )
            {
                Add(MapKey, Reader.ReadGuid());
            }
            else if ( ValueType == L"C16" )
            {
                Add(MapKey, static_cast<char16_t>(Reader.ReadUInt16()));
            }
            else if ( ValueType == L"I16" )
            {
                Add(MapKey, Reader.ReadInt16());
            }
            else if ( ValueType == L"I32" )
            {
                Add(MapKey, Reader.ReadInt32());
            }
            else if ( ValueType == L"I64" )
            {
                Add(MapKey, Reader.ReadInt64());
            }
            else if ( ValueType == L"UI8" )
            {
                Add(MapKey, Reader.ReadByte());
            }
            else if ( ValueType == L"UI16" )
            {
                Add(MapKey, Reader.ReadUInt16());
            }
            else if ( ValueType == L"UI32" )
            {
                Add(MapKey, Reader.ReadUInt32());
            }
            else if ( ValueType == L"UI64" )
            {
                Add(MapKey, Reader.ReadUInt64());
            }
            else if ( ValueType == L"F" )
            {
                Add(MapKey, Reader.ReadSingle());
            }
            else if ( ValueType == L"D" )
            {
                Add(MapKey, Reader.ReadDouble());
            }
            else if ( ValueType == L"S" )
            {
                BytesToRead = Reader.ReadUInt32();
                ValueString = std::wstring(std::from_range, Reader.ReadString(BytesToRead));
                Add(MapKey, ValueString);
            }
            else if ( ValueType == L"B" )
            {
                Add(MapKey, Reader.ReadBoolean());
            }
            else if ( ValueType == L"V" )
            {
                BytesToRead = Reader.ReadUInt32();
                ValueBuffer = Reader.ReadBuffer(BytesToRead);
                Add(MapKey, ValueBuffer);
            }
            else if ( ValueType == L"Date" )
            {
                Add(MapKey, Reader.ReadDateTime());
            }
            else if ( ValueType == L"Time" )
            {
                Add(MapKey, Reader.ReadTimeSpan());
            }
        }
    }

    Windows::Foundation::IAsyncAction LocalSettings::SaveAsync()
    {
        std::filesystem::create_directories(AppDataPath().c_str());

        StorageFolder       Folder = co_await StorageFolder::GetFolderFromPathAsync(AppDataPath());
        StorageFile         File   = co_await Folder.CreateFileAsync(FileName(), CreationCollisionOption::ReplaceExisting);
        IRandomAccessStream Stream = co_await File.OpenAsync(FileAccessMode::ReadWrite);

        // Create the data writer object backed by the in-memory stream.
        DataWriter Writer(Stream);
        Writer.UnicodeEncoding(UnicodeEncoding::Utf8);
        Writer.ByteOrder(ByteOrder::LittleEndian);

        auto WriteType(
          [&](const std::wstring_view Type)
          {
              Writer.WriteUInt16(static_cast<uint16_t>(Type.size()));
              Writer.WriteString(Type);
          }
        );

        for ( const auto& [Key, Value] : m_Data )
        {
            const uint32_t KeyInputSize = Writer.MeasureString(Key);
            Writer.WriteUInt32(KeyInputSize);
            Writer.WriteString(Key);

            visit<guid, char16_t, int16_t, int32_t, int64_t, uint8_t, uint16_t, uint32_t, uint64_t, float_t, double_t, std::wstring, bool, std::vector<uint8_t>, date_time_t, time_span_t, buffer_t>(
              overloaded //
              { [&](const guid Value)
                {
                    WriteType(L"G");
                    Writer.WriteGuid(Value);
                },
                [&](const char16_t Value)
                {
                    WriteType(L"C16");
                    Writer.WriteUInt16(static_cast<uint16_t>(Value));
                },
                [&](const int16_t Value)
                {
                    WriteType(L"I16");
                    Writer.WriteInt16(Value);
                },
                [&](const int32_t Value)
                {
                    WriteType(L"I32");
                    Writer.WriteInt32(Value);
                },
                [&](const int64_t Value)
                {
                    WriteType(L"I64");
                    Writer.WriteInt64(Value);
                },
                [&](const uint8_t Value)
                {
                    WriteType(L"UI8");
                    Writer.WriteByte(Value);
                },
                [&](const uint16_t Value)
                {
                    WriteType(L"UI16");
                    Writer.WriteUInt16(Value);
                },
                [&](const uint32_t Value)
                {
                    WriteType(L"UI32");
                    Writer.WriteUInt32(Value);
                },
                [&](const uint64_t Value)
                {
                    WriteType(L"UI64");
                    Writer.WriteUInt64(Value);
                },
                [&](const float_t Value)
                {
                    WriteType(L"F");
                    Writer.WriteSingle(static_cast<float>(Value));
                },
                [&](const double_t Value)
                {
                    WriteType(L"D");
                    Writer.WriteDouble(static_cast<double>(Value));
                },
                [&](const std::wstring_view Value)
                {
                    WriteType(L"S");
                    Writer.WriteUInt32(Writer.MeasureString(Value));
                    Writer.WriteString(Value);
                },
                [&](const bool Value)
                {
                    WriteType(L"B");
                    Writer.WriteBoolean(Value);
                },
                [&](const std::vector<uint8_t>& Value)
                {
                    WriteType(L"V");
                    Writer.WriteUInt32(static_cast<uint32_t>(Value.size()));
                    Writer.WriteBytes(Value);
                },
                [&](const date_time_t Value)
                {
                    WriteType(L"Date");
                    Writer.WriteDateTime(Value);
                },
                [&](const time_span_t Value)
                {
                    WriteType(L"Time");
                    Writer.WriteTimeSpan(Value);
                },
                [&](const buffer_t Value)
                {
                    WriteType(L"V");
                    Writer.WriteUInt32(Value.Length());
                    Writer.WriteBuffer(Value);
                } },
              Value
            );
        }

        // Send the contents of the writer to the backing stream.
        co_await Writer.StoreAsync();

        // For the in-memory stream implementation we are using, the FlushAsync call
        // is superfluous, but other types of streams may require it.
        co_await Writer.FlushAsync();

        // In order to prolong the lifetime of the stream, detach it from the
        // DataWriter so that it will not be closed when Dispose() is called on
        // dataWriter. Were we to fail to detach the stream, the call to
        // dataWriter.Dispose() would close the underlying stream, preventing
        // its subsequent use by the DataReader below.
        Writer.DetachStream();
    }

    void LocalSettings::Add(const std::wstring_view Key, const guid Value)
    {
        m_Data[std::wstring(Key)] = std::make_any<guid>(Value);
    }

    void LocalSettings::Add(const std::wstring_view Key, const char16_t Value)
    {
        m_Data[std::wstring(Key)] = std::make_any<char16_t>(Value);
    }

    void LocalSettings::Add(const std::wstring_view Key, const int16_t Value)
    {
        m_Data[std::wstring(Key)] = std::make_any<int16_t>(Value);
    }

    void LocalSettings::Add(const std::wstring_view Key, const int32_t Value)
    {
        m_Data[std::wstring(Key)] = std::make_any<int32_t>(Value);
    }

    void LocalSettings::Add(const std::wstring_view Key, const int64_t Value)
    {
        m_Data[std::wstring(Key)] = std::make_any<int64_t>(Value);
    }

    void LocalSettings::Add(const std::wstring_view Key, const uint8_t Value)
    {
        m_Data[std::wstring(Key)] = std::make_any<uint8_t>(Value);
    }

    void LocalSettings::Add(const std::wstring_view Key, const uint16_t Value)
    {
        m_Data[std::wstring(Key)] = std::make_any<uint16_t>(Value);
    }

    void LocalSettings::Add(const std::wstring_view Key, const uint32_t Value)
    {
        m_Data[std::wstring(Key)] = std::make_any<uint32_t>(Value);
    }

    void LocalSettings::Add(const std::wstring_view Key, const uint64_t Value)
    {
        m_Data[std::wstring(Key)] = std::make_any<uint64_t>(Value);
    }

    void LocalSettings::Add(const std::wstring_view Key, const float_t Value)
    {
        m_Data[std::wstring(Key)] = std::make_any<float_t>(Value);
    }

    void LocalSettings::Add(const std::wstring_view Key, const double_t Value)
    {
        m_Data[std::wstring(Key)] = std::make_any<double_t>(Value);
    }

    void LocalSettings::Add(const std::wstring_view Key, const std::wstring_view Value)
    {
        m_Data[std::wstring(Key)] = std::make_any<std::wstring>(Value);
    }

    void LocalSettings::Add(const std::wstring_view Key, const bool Value)
    {
        m_Data[std::wstring(Key)] = std::make_any<bool>(Value);
    }

    void LocalSettings::Add(const std::wstring_view Key, const array_view<const uint8_t> Value)
    {
        m_Data[std::wstring(Key)] = std::make_any<std::vector<uint8_t>>(Value.cbegin(), Value.cend());
    }

    void LocalSettings::Add(const std::wstring_view Key, const date_time_t& Value)
    {
        m_Data[std::wstring(Key)] = std::make_any<Windows::Foundation::DateTime>(Value);
    }

    void LocalSettings::Add(const std::wstring_view Key, const time_span_t& Value)
    {
        m_Data[std::wstring(Key)] = std::make_any<Windows::Foundation::TimeSpan>(Value);
    }

    void LocalSettings::Add(const std::wstring_view Key, const buffer_t& Buffer)
    {
        m_Data[std::wstring(Key)] = std::make_any<std::vector<uint8_t>>(Buffer.data(), Buffer.data() + Buffer.Length());
    }

    void LocalSettings::Add(const std::wstring_view Key, const buffer_t& Buffer, const uint32_t Start, const uint32_t Count)
    {
        m_Data[std::wstring(Key)] = std::make_any<std::vector<uint8_t>>(Buffer.data() + Start, Buffer.data() + Start + Count);
    }

    void LocalSettings::Get(const std::wstring_view Key, guid& Value)
    {
        Value = std::any_cast<const guid&>(m_Data.at(std::wstring(Key)));
    }

    void LocalSettings::Get(const std::wstring_view Key, char16_t& Value)
    {
        Value = std::any_cast<const char16_t&>(m_Data.at(std::wstring(Key)));
    }

    void LocalSettings::Get(const std::wstring_view Key, int16_t& Value)
    {
        Value = std::any_cast<const int16_t&>(m_Data.at(std::wstring(Key)));
    }

    void LocalSettings::Get(const std::wstring_view Key, int32_t& Value)
    {
        Value = std::any_cast<const int32_t&>(m_Data.at(std::wstring(Key)));
    }

    void LocalSettings::Get(const std::wstring_view Key, int64_t& Value)
    {
        Value = std::any_cast<const int64_t&>(m_Data.at(std::wstring(Key)));
    }

    void LocalSettings::Get(const std::wstring_view Key, uint8_t& Value)
    {
        Value = std::any_cast<const uint8_t&>(m_Data.at(std::wstring(Key)));
    }

    void LocalSettings::Get(const std::wstring_view Key, uint16_t& Value)
    {
        Value = std::any_cast<const uint16_t&>(m_Data.at(std::wstring(Key)));
    }

    void LocalSettings::Get(const std::wstring_view Key, uint32_t& Value)
    {
        Value = std::any_cast<const uint32_t&>(m_Data.at(std::wstring(Key)));
    }

    void LocalSettings::Get(const std::wstring_view Key, uint64_t& Value)
    {
        Value = std::any_cast<const uint64_t&>(m_Data.at(std::wstring(Key)));
    }

    void LocalSettings::Get(const std::wstring_view Key, float_t& Value)
    {
        Value = std::any_cast<const float_t&>(m_Data.at(std::wstring(Key)));
    }

    void LocalSettings::Get(const std::wstring_view Key, double_t& Value)
    {
        Value = std::any_cast<const double_t&>(m_Data.at(std::wstring(Key)));
    }

    void LocalSettings::Get(const std::wstring_view Key, hstring& Value)
    {
        Value = std::any_cast<const std::wstring&>(m_Data.at(std::wstring(Key)));
    }

    void LocalSettings::Get(const std::wstring_view Key, bool& Value)
    {
        Value = std::any_cast<const bool&>(m_Data.at(std::wstring(Key)));
    }

    void LocalSettings::Get(const std::wstring_view Key, com_array<uint8_t>& Value)
    {
        Value = com_array<uint8_t>{ std::any_cast<const std::vector<uint8_t>&>(m_Data.at(std::wstring(Key))) };
    }

    void LocalSettings::Get(const std::wstring_view Key, date_time_t& Value)
    {
        Value = std::any_cast<const Windows::Foundation::DateTime&>(m_Data.at(std::wstring(Key)));
    }

    void LocalSettings::Get(const std::wstring_view Key, time_span_t& Value)
    {
        Value = std::any_cast<const Windows::Foundation::TimeSpan&>(m_Data.at(std::wstring(Key)));
    }

    void LocalSettings::Get(const std::wstring_view Key, buffer_t& Buffer)
    {
        const auto& Value = std::any_cast<const std::vector<uint8_t>&>(m_Data.at(std::wstring(Key)));

        Buffer = Windows::Storage::Streams::Buffer(static_cast<uint32_t>(Value.size()));
        Buffer.Length(static_cast<uint32_t>(Value.size()));

        std::ranges::copy(Value, Buffer.data());
    }

    guid LocalSettings::GetGuid(const std::wstring_view Key)
    {
        return std::any_cast<const guid&>(m_Data.at(std::wstring(Key)));
    }

    char16_t LocalSettings::GetChar(const std::wstring_view Key)
    {
        return std::any_cast<const char16_t&>(m_Data.at(std::wstring(Key)));
    }

    int16_t LocalSettings::GetInt16(const std::wstring_view Key)
    {
        return std::any_cast<const int16_t&>(m_Data.at(std::wstring(Key)));
    }

    int32_t LocalSettings::GetInt32(const std::wstring_view Key)
    {
        return std::any_cast<const int32_t&>(m_Data.at(std::wstring(Key)));
    }

    int64_t LocalSettings::GetInt64(const std::wstring_view Key)
    {
        return std::any_cast<const int64_t&>(m_Data.at(std::wstring(Key)));
    }

    uint8_t LocalSettings::GetUInt8(const std::wstring_view Key)
    {
        return std::any_cast<const uint8_t&>(m_Data.at(std::wstring(Key)));
    }

    uint16_t LocalSettings::GetUInt16(const std::wstring_view Key)
    {
        return std::any_cast<const uint16_t&>(m_Data.at(std::wstring(Key)));
    }

    uint32_t LocalSettings::GetUInt32(const std::wstring_view Key)
    {
        return std::any_cast<const uint32_t&>(m_Data.at(std::wstring(Key)));
    }

    uint64_t LocalSettings::GetUInt64(const std::wstring_view Key)
    {
        return std::any_cast<const uint64_t&>(m_Data.at(std::wstring(Key)));
    }

    float_t LocalSettings::GetSingle(const std::wstring_view Key)
    {
        return std::any_cast<const float_t&>(m_Data.at(std::wstring(Key)));
    }

    double_t LocalSettings::GetDouble(const std::wstring_view Key)
    {
        return std::any_cast<const double_t&>(m_Data.at(std::wstring(Key)));
    }

    hstring LocalSettings::GetString(const std::wstring_view Key)
    {
        return hstring{ std::any_cast<const std::wstring&>(m_Data.at(std::wstring(Key))) };
    }

    bool LocalSettings::GetBoolean(const std::wstring_view Key)
    {
        return std::any_cast<const bool&>(m_Data.at(std::wstring(Key)));
    }

    com_array<uint8_t> LocalSettings::GetArray(const std::wstring_view Key)
    {
        return com_array<uint8_t>{ std::any_cast<const std::vector<uint8_t>&>(m_Data.at(std::wstring(Key))) };
    }

    LocalSettings::date_time_t LocalSettings::GetDateTime(const std::wstring_view Key)
    {
        return std::any_cast<const Windows::Foundation::DateTime&>(m_Data.at(std::wstring(Key)));
    }

    LocalSettings::time_span_t LocalSettings::GetTimeSpan(const std::wstring_view Key)
    {
        return std::any_cast<const Windows::Foundation::TimeSpan&>(m_Data.at(std::wstring(Key)));
    }

    LocalSettings::buffer_t LocalSettings::GetBuffer(const std::wstring_view Key)
    {
        const std::vector<uint8_t>& Value(std::any_cast<const std::vector<uint8_t>&>(m_Data.at(std::wstring(Key))));

        Windows::Storage::Streams::Buffer Buffer(static_cast<uint32_t>(Value.size()));
        Buffer.Length(static_cast<uint32_t>(Value.size()));

        std::ranges::copy(Value, Buffer.data());
        return Buffer;
    }
} // namespace winrt::Mercatec::Helpers::implementation

#pragma pop_macro("PathAppend")
#pragma pop_macro("PathCombine")
#pragma pop_macro("PathAddExtension")
