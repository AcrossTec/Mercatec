#include "pch.h"
#include "Mercatec.WinUIEx.WindowEx.h"
#if __has_include("WindowEx.g.cpp")
# include "WindowEx.g.cpp"
#endif

namespace winrt::Mercatec::WinUIEx::implementation
{
    WindowEx::WindowEx()
    {
    }

    Windows::Foundation::IInspectable WindowEx::WindowContent() const noexcept
    {
        return m_WindowArea.Content();
    }

    void WindowEx::WindowContent(const Windows::Foundation::IInspectable& content) noexcept
    {
        m_WindowArea.Content(content);
    }

    bool WindowEx::BringToFront()
    {
        return false;
    }
} // namespace winrt::Mercatec::WinUIEx::implementation
