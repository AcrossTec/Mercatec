#include "pch.h"
#include "Mercatec.WinUIEx.Icon.h"
#if __has_include("Icon.g.cpp")
# include "Icon.g.cpp"
#endif

namespace winrt::Mercatec::WinUIEx::implementation
{
    Icon::Icon(std::unique_ptr<::Mercatec::WinUIEx::Internal::Icon>&& NativeIcon)
      : m_Icon{ std::move(NativeIcon) }
    {
    }

    uint64_t Icon::Handle() const noexcept
    {
        return reinterpret_cast<uint64_t>(m_Icon->Handle);
    }

    uint64_t Icon::NativeIcon() const noexcept
    {
        return reinterpret_cast<uint64_t>(m_Icon.get());
    }

    WinUIEx::Icon Icon::FromFile(const hstring& FileName)
    {
        return make<Icon>(::Mercatec::WinUIEx::Internal::Icon::MakeFromFile(FileName));
    }

    WinUIEx::Icon Icon::FromByteArray(const array_view<const uint8_t> Rgba, const uint32_t Size)
    {
        return make<Icon>(::Mercatec::WinUIEx::Internal::Icon::MakeFromByteArray( //
          { reinterpret_cast<const std::byte*>(Rgba.data()), Rgba.size() },
          Size
        ));
    }

    /// <summary>
    ///     For testing - Creates a simple Yang Icon.
    /// </summary>
    /// <returns>
    ///     Icon with a Yang Icon.
    /// </returns>
    WinUIEx::Icon Icon::Yang()
    {
        return make<Icon>(::Mercatec::WinUIEx::Internal::Icon::MakeYang());
    }
} // namespace winrt::Mercatec::WinUIEx::implementation
