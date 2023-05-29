#pragma once

#include "Mercatec.WinUIEx.Exports.Api.hpp"
#include <winrt/Windows.Foundation.Collections.h>

#include <Windows.h>
#include <string_view>

namespace Mercatec::WinUIEx
{
    class MERCATEC_WINUIEX_API Icon
    {
    public:
        Icon(HICON Icon) noexcept;
        ~Icon() noexcept;

        HICON GetHandle() const noexcept;
        __declspec(property(get = GetHandle)) HICON Handle;

        static Icon FromFile(const std::wstring_view FileName);
        static Icon FromByteArray(const winrt::array_view<std::byte> Rgba, const winrt::array_view<std::byte>::size_type Size);

        /// <summary>
        ///     For testing - Creates a simple Yang Icon.
        /// </summary>
        /// <returns>
        ///     Icon with a Yang Icon.
        /// </returns>
        static Icon Yang();

    private:
        static void ThrowIfInvalid(HICON Handle);
        HICON       m_Handle;
    };
} // namespace Mercatec::WinUIEx
