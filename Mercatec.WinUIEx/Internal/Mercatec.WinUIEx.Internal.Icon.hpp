#pragma once

#include "Mercatec.WinUIEx.Exports.Api.hpp"
#include <winrt/Windows.Foundation.Collections.h>

#include <Windows.h>

#include <memory>
#include <string_view>

namespace Mercatec::WinUIEx::Internal
{
    class MERCATEC_WINUIEX_API Icon
    {
    public:
        Icon(HICON Icon) noexcept;
        ~Icon() noexcept;

        Icon(Icon&&)                 = default;
        Icon(const Icon&)            = delete;
        Icon& operator=(Icon&&)      = default;
        Icon& operator=(const Icon&) = delete;

        HICON GetHandle() const noexcept;
        __declspec(property(get = GetHandle)) HICON Handle;

        static std::unique_ptr<Icon> MakeYang() noexcept;
        static std::unique_ptr<Icon> MakeFromFile(const std::wstring_view FileName);
        static std::unique_ptr<Icon> MakeFromByteArray(const winrt::array_view<const std::byte> Rgba, const winrt::array_view<const std::byte>::size_type Size);

        static Icon FromFile(const std::wstring_view FileName);
        static Icon FromByteArray(const winrt::array_view<const std::byte> Rgba, const winrt::array_view<const std::byte>::size_type Size);

        /// <summary>
        ///     For testing - Creates a simple Yang Icon.
        /// </summary>
        /// <returns>
        ///     Icon with a Yang Icon.
        /// </returns>
        static Icon Yang() noexcept;
        static void ThrowIfInvalid(HICON Handle);

    private:
        HICON m_Handle;
    };
} // namespace Mercatec::WinUIEx::Internal
