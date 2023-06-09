#pragma once

#include "ImagePickerResult.g.h"

namespace winrt::Mercatec::Helpers::implementation
{
    struct ImagePickerResult : ImagePickerResultT<ImagePickerResult>
    {
    public:
        ImagePickerResult() noexcept;

        hstring FileName() const noexcept;
        void    FileName(const std::wstring_view Value) noexcept;

        hstring ContentType() const noexcept;
        void    ContentType(const std::wstring_view Value) noexcept;

        com_array<byte> ImageBytes() const noexcept;
        void            ImageBytes(const array_view<const byte>& Value) noexcept;

        IInspectable ImageSource() const noexcept;
        void         ImageSource(const IInspectable& Value) noexcept;

    private:
        hstring           m_FileName;
        hstring           m_ContentType;
        std::vector<byte> m_ImageBytes;
        IInspectable      m_ImageSource;
    };
} // namespace winrt::Mercatec::Helpers::implementation

namespace winrt::Mercatec::Helpers::factory_implementation
{
    struct ImagePickerResult : ImagePickerResultT<ImagePickerResult, implementation::ImagePickerResult>
    {
    };
} // namespace winrt::Mercatec::Helpers::factory_implementation
