#pragma once

#include "WindowEx.g.h"

namespace winrt::Mercatec::WinUIEx::implementation
{
    struct WindowEx : WindowExT<WindowEx>
    {
    public:
        WindowEx();

        Windows::Foundation::IInspectable WindowContent() const noexcept;

        void WindowContent(const Windows::Foundation::IInspectable& content) noexcept;

        bool BringToFront();

    private:
        Microsoft::UI::Xaml::Controls::ContentControl m_WindowArea;
    };
} // namespace winrt::Mercatec::WinUIEx::implementation

namespace winrt::Mercatec::WinUIEx::factory_implementation
{
    struct WindowEx : WindowExT<WindowEx, implementation::WindowEx>
    {
    };
} // namespace winrt::Mercatec::WinUIEx::factory_implementation
