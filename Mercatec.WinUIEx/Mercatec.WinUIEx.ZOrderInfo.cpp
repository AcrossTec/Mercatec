#include "pch.h"
#include "Mercatec.WinUIEx.ZOrderInfo.h"
#if __has_include("ZOrderInfo.g.cpp")
# include "ZOrderInfo.g.cpp"
#endif

namespace winrt::Mercatec::WinUIEx::implementation
{
    ZOrderInfo::ZOrderInfo() noexcept
      : m_IsZOrderAtTop{ false }
      , m_IsZOrderAtBottom{ false }
      , m_ZOrderBelowWindowId{ 0 }
    {
    }

    bool ZOrderInfo::IsZOrderAtTop() const noexcept
    {
        return m_IsZOrderAtTop;
    }

    void ZOrderInfo::IsZOrderAtTop(const bool is_zorder_at_top) noexcept
    {
        m_IsZOrderAtTop = is_zorder_at_top;
    }

    bool ZOrderInfo::IsZOrderAtBottom() const noexcept
    {
        return m_IsZOrderAtBottom;
    }

    void ZOrderInfo::IsZOrderAtBottom(const bool is_zorder_at_bottom) noexcept
    {
        m_IsZOrderAtBottom = is_zorder_at_bottom;
    }

    Microsoft::UI::WindowId ZOrderInfo::ZOrderBelowWindowId() const noexcept
    {
        return m_ZOrderBelowWindowId;
    }

    void ZOrderInfo::ZOrderBelowWindowId(const Microsoft::UI::WindowId& window_id) noexcept
    {
        m_ZOrderBelowWindowId = window_id;
    }
} // namespace winrt::Mercatec::WinUIEx::implementation
