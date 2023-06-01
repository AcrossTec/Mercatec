#pragma once

#include "Icon.g.h"
#include "Internal/Mercatec.WinUIEx.Internal.Icon.hpp"
#include <memory>

namespace winrt::Mercatec::WinUIEx::implementation
{
    struct Icon : IconT<Icon>
    {
    public:
        Icon(std::unique_ptr<::Mercatec::WinUIEx::Internal::Icon>&& NativeIcon);
        uint64_t Handle() const noexcept;
        uint64_t NativeIcon() const noexcept;

        static WinUIEx::Icon FromFile(const hstring& FileName);
        static WinUIEx::Icon FromByteArray(const array_view<const uint8_t> Rgba, const uint32_t Size);

        /// <summary>
        ///     For testing - Creates a simple Yang Icon.
        /// </summary>
        /// <returns>
        ///     Icon with a Yang Icon.
        /// </returns>
        static WinUIEx::Icon Yang();

    private:
        std::unique_ptr<::Mercatec::WinUIEx::Internal::Icon> m_Icon;
    };
} // namespace winrt::Mercatec::WinUIEx::implementation

namespace winrt::Mercatec::WinUIEx::factory_implementation
{
    struct Icon : IconT<Icon, implementation::Icon>
    {
    };
} // namespace winrt::Mercatec::WinUIEx::factory_implementation
