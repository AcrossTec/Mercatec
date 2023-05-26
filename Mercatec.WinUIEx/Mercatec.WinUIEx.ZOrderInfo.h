#pragma once

#include "ZOrderInfo.g.h"

namespace winrt::Mercatec::WinUIEx::implementation
{
    /// <summary>
    /// Information about the ZOrder of the window
    /// </summary>
    /// <seealso cref="WindowEx.ZOrderChanged"/>
    /// <seealso cref="WindowEx.OnZOrderChanged"/>
    struct ZOrderInfo : ZOrderInfoT<ZOrderInfo>
    {
    public:
        ZOrderInfo() noexcept;

        /// <summary>
        /// Gets a value indicating whether the window's Z Order is at the top.
        /// </summary>
        /// <seealso cref="Microsoft.UI.Windowing.AppWindowChangedEventArgs.IsZOrderAtTop"/>
        bool IsZOrderAtTop() const noexcept;
        void IsZOrderAtTop(const bool is_zorder_at_top) noexcept;

        /// <summary>
        /// Gets a value indicating whether the window's Z Order is at the bottom.
        /// </summary>
        /// <seealso cref="Microsoft.UI.Windowing.AppWindowChangedEventArgs.IsZOrderAtBottom"/>
        bool IsZOrderAtBottom() const noexcept;
        void IsZOrderAtBottom(const bool is_zorder_at_bottom) noexcept;

        /// <summary>
        /// Gets the id of the window this window is below.
        /// </summary>
        /// <seealso cref="Microsoft.UI.Windowing.AppWindowChangedEventArgs.ZOrderBelowWindowId"/>
        Microsoft::UI::WindowId ZOrderBelowWindowId() const noexcept;
        void                    ZOrderBelowWindowId(const Microsoft::UI::WindowId& window_id) noexcept;

    private:
        bool                    m_IsZOrderAtTop;
        bool                    m_IsZOrderAtBottom;
        Microsoft::UI::WindowId m_ZOrderBelowWindowId;
    };
} // namespace winrt::Mercatec::WinUIEx::implementation

namespace winrt::Mercatec::WinUIEx::factory_implementation
{
    struct ZOrderInfo : ZOrderInfoT<ZOrderInfo, implementation::ZOrderInfo>
    {
    };
} // namespace winrt::Mercatec::WinUIEx::factory_implementation
