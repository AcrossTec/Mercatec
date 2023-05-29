#include "pch.h"
#include "Mercatec.WinUIEx.Icon.hpp"
#include "Mercatec.WinUIEx.Windows.Win32.hpp"

#include <memory>

#pragma warning(push)
//! Compiler Warning (level 4) C4458
//! declaration of 'identifier' hides class member
//! https://learn.microsoft.com/en-us/cpp/error-messages/compiler-warnings/compiler-warning-level-4-c4458?view=msvc-170
#pragma warning(disable : 4458)

namespace Mercatec::WinUIEx
{
    Icon::Icon(HICON Icon) noexcept
      : m_Handle{ Icon }
    {
    }

    Icon::~Icon() noexcept
    {
        ::DestroyIcon(m_Handle);
    }

    HICON Icon::GetHandle() const noexcept
    {
        return m_Handle;
    }

    Icon Icon::FromFile(const std::wstring_view FileName)
    {
        using enum Windows::Win32::UI::WindowsAndMessaging::GdiImageType;
        using enum Windows::Win32::UI::Controls::ImageFlags;

        using EnumType  = Enum<Windows::Win32::UI::WindowsAndMessaging::GdiImageType>;
        using EnumFlags = Enum<Windows::Win32::UI::Controls::ImageFlags>;

        HANDLE Handle = ::LoadImageW(nullptr, FileName.data(), EnumType::GetValue(ImageIcon), 16, 16, EnumFlags::GetValue(LrLoadFromFile));
        return Icon(HICON(Handle));
    }

    Icon Icon::FromByteArray(const winrt::array_view<std::byte> Rgba, const winrt::array_view<std::byte>::size_type Size)
    {
        std::unique_ptr<std::byte[]> AndMaskIcon{ new std::byte[Size * Size * 3U] };
        std::unique_ptr<std::byte[]> XOrMaskIcon{ new std::byte[Size * Size] };

        for ( winrt::array_view<std::byte>::size_type Index = 0; Index < Size * Size; ++Index )
        {
            AndMaskIcon[Index * 3]     = Rgba[Index * 4 + 3];
            AndMaskIcon[Index * 3 + 1] = Rgba[Index * 4 + 2];
            AndMaskIcon[Index * 3 + 2] = Rgba[Index * 4 + 1];
            XOrMaskIcon[Index]         = std::byte{ 0xAA }; // Rgba[Index * 4 + 3];
        }

        HMODULE HInstance = ::GetModuleHandleW(nullptr);
        HICON   Handle    = ::CreateIcon(HInstance, 32, 32, 24, 1, PBYTE(XOrMaskIcon.get()), PBYTE(AndMaskIcon.get()));

        ThrowIfInvalid(Handle);
        return Icon(Handle);
    }

    void Icon::ThrowIfInvalid(HICON Handle)
    {
        if ( Handle == NULL )
        {
            winrt::throw_last_error();
        }
    }

    /// <summary>
    ///     For testing - Creates a simple Yang Icon.
    /// </summary>
    /// <returns>
    ///     Icon with a Yang Icon.
    /// </returns>
    Icon Icon::Yang()
    {
        BYTE AndMaskIcon[] =        //
          { 0xFF, 0xFF, 0xFF, 0xFF, // line 1
            0xFF, 0xFF, 0xC3, 0xFF, // line 2
            0xFF, 0xFF, 0x00, 0xFF, // line 3
            0xFF, 0xFE, 0x00, 0x7F, // line 4

            0xFF, 0xFC, 0x00, 0x1F, // line 5
            0xFF, 0xF8, 0x00, 0x0F, // line 6
            0xFF, 0xF8, 0x00, 0x0F, // line 7
            0xFF, 0xF0, 0x00, 0x07, // line 8

            0xFF, 0xF0, 0x00, 0x03, // line 9
            0xFF, 0xE0, 0x00, 0x03, // line 10
            0xFF, 0xE0, 0x00, 0x01, // line 11
            0xFF, 0xE0, 0x00, 0x01, // line 12

            0xFF, 0xF0, 0x00, 0x01, // line 13
            0xFF, 0xF0, 0x00, 0x00, // line 14
            0xFF, 0xF8, 0x00, 0x00, // line 15
            0xFF, 0xFC, 0x00, 0x00, // line 16

            0xFF, 0xFF, 0x00, 0x00, // line 17
            0xFF, 0xFF, 0x80, 0x00, // line 18
            0xFF, 0xFF, 0xE0, 0x00, // line 19
            0xFF, 0xFF, 0xE0, 0x01, // line 20

            0xFF, 0xFF, 0xF0, 0x01, // line 21
            0xFF, 0xFF, 0xF0, 0x01, // line 22
            0xFF, 0xFF, 0xF0, 0x03, // line 23
            0xFF, 0xFF, 0xE0, 0x03, // line 24

            0xFF, 0xFF, 0xE0, 0x07, // line 25
            0xFF, 0xFF, 0xC0, 0x0F, // line 26
            0xFF, 0xFF, 0xC0, 0x0F, // line 27
            0xFF, 0xFF, 0x80, 0x1F, // line 28

            0xFF, 0xFF, 0x00, 0x7F,   // line 29
            0xFF, 0xFC, 0x00, 0xFF,   // line 30
            0xFF, 0xF8, 0x03, 0xFF,   // line 31
            0xFF, 0xFC, 0x3F, 0xFF }; // line 32

        BYTE XOrMaskIcon[] =        //
          { 0x00, 0x00, 0x00, 0x00, // line 1
            0x00, 0x00, 0x00, 0x00, // line 2
            0x00, 0x00, 0x00, 0x00, // line 3
            0x00, 0x00, 0x00, 0x00, // line 4

            0x00, 0x00, 0x00, 0x00, // line 5
            0x00, 0x00, 0x00, 0x00, // line 6
            0x00, 0x00, 0x00, 0x00, // line 7
            0x00, 0x00, 0x38, 0x00, // line 8

            0x00, 0x00, 0x7C, 0x00, // line 9
            0x00, 0x00, 0x7C, 0x00, // line 10
            0x00, 0x00, 0x7C, 0x00, // line 11
            0x00, 0x00, 0x38, 0x00, // line 12

            0x00, 0x00, 0x00, 0x00, // line 13
            0x00, 0x00, 0x00, 0x00, // line 14
            0x00, 0x00, 0x00, 0x00, // line 15
            0x00, 0x00, 0x00, 0x00, // line 16

            0x00, 0x00, 0x00, 0x00, // line 17
            0x00, 0x00, 0x00, 0x00, // line 18
            0x00, 0x00, 0x00, 0x00, // line 19
            0x00, 0x00, 0x00, 0x00, // line 20

            0x00, 0x00, 0x00, 0x00, // line 21
            0x00, 0x00, 0x00, 0x00, // line 22
            0x00, 0x00, 0x00, 0x00, // line 23
            0x00, 0x00, 0x00, 0x00, // line 24

            0x00, 0x00, 0x00, 0x00, // line 25
            0x00, 0x00, 0x00, 0x00, // line 26
            0x00, 0x00, 0x00, 0x00, // line 27
            0x00, 0x00, 0x00, 0x00, // line 28

            0x00, 0x00, 0x00, 0x00,   // line 29
            0x00, 0x00, 0x00, 0x00,   // line 30
            0x00, 0x00, 0x00, 0x00,   // line 31
            0x00, 0x00, 0x00, 0x00 }; // line 32

        HMODULE HInstance = ::GetModuleHandleW(nullptr);
        HICON   Handle    = ::CreateIcon(HInstance, 32, 32, 1, 1, AndMaskIcon, XOrMaskIcon);

        return Icon(Handle);
    }
} // namespace Mercatec::WinUIEx

#pragma warning(pop)
