#include "pch.h"
#include "Mercatec.Helpers.ImagePickerResult.h"
#if __has_include("ImagePickerResult.g.cpp")
# include "ImagePickerResult.g.cpp"
#endif

namespace winrt::Mercatec::Helpers::implementation
{
    ImagePickerResult::ImagePickerResult() noexcept
      : m_FileName{ L"" }
      , m_ContentType{ L"" }
      , m_ImageBytes{}
      , m_ImageSource{ nullptr }
    {
    }

    hstring ImagePickerResult::FileName() const noexcept
    {
        return m_FileName;
    }

    void ImagePickerResult::FileName(const std::wstring_view Value) noexcept
    {
        m_FileName = Value;
    }

    hstring ImagePickerResult::ContentType() const noexcept
    {
        return m_ContentType;
    }

    void ImagePickerResult::ContentType(const std::wstring_view Value) noexcept
    {
        m_ContentType = Value;
    }

    com_array<byte> ImagePickerResult::ImageBytes() const noexcept
    {
        return com_array<byte>{ m_ImageBytes };
    }

    void ImagePickerResult::ImageBytes(const array_view<const byte>& Value) noexcept
    {
        m_ImageBytes = { Value.cbegin(), Value.cend() };
    }

    IInspectable ImagePickerResult::ImageSource() const noexcept
    {
        return m_ImageSource;
    }

    void ImagePickerResult::ImageSource(const IInspectable& Value) noexcept
    {
        m_ImageSource = Value;
    }
} // namespace winrt::Mercatec::Helpers::implementation
