#pragma once

#include "Mercatec.WinUIEx.Exports.Api.hpp"
#include <winrt/Mercatec.WinUIEx.Messaging.h>
#include <winrt/Windows.Foundation.h>
#include <winrt/Microsoft.UI.Xaml.h>

#include <Windows.h>
#include <memory>

#pragma warning(push)
//! Compiler Warning (level 1) C4251
//! 'type' : class 'type1' needs to have dll-interface to be used by clients of class 'type2'
//! https://learn.microsoft.com/en-us/cpp/error-messages/compiler-warnings/compiler-warning-level-1-c4251?view=msvc-170
#pragma warning(disable : 4251)

namespace Mercatec::WinUIEx::Messaging
{
    /// <summary>
    ///     The message monitor allows you to monitor all WM_MESSAGE events for a given window.
    /// </summary>
    struct WindowMessageMonitor : winrt::implements<WindowMessageMonitor, winrt::IInspectable>
    {
    public:
        /// <summary>
        ///     Initialize a new instance of the <see cref="WindowMessageMonitor"/> class.
        /// </summary>
        /// <param name="window">The window to listen to messages for.</param>
        MERCATEC_WINUIEX_API WindowMessageMonitor(const winrt::Microsoft::UI::Xaml::Window& Window);

        /// <summary>
        ///     Initialize a new instance of the <see cref="WindowMessageMonitor"/> class.
        /// </summary>
        /// <param name="hwnd">The window handle to listen to messages for.</param>
        MERCATEC_WINUIEX_API WindowMessageMonitor(HWND Hwnd);

        /// <summary>
        ///     Finalizer
        /// </summary>
        MERCATEC_WINUIEX_API ~WindowMessageMonitor();

        WindowMessageMonitor(const WindowMessageMonitor&)            = default;
        WindowMessageMonitor(WindowMessageMonitor&&)                 = default;
        WindowMessageMonitor& operator=(const WindowMessageMonitor&) = default;
        WindowMessageMonitor& operator=(WindowMessageMonitor&&)      = default;

        /// <summary>
        ///     Event raised when a windows message is received.
        /// </summary>
        MERCATEC_WINUIEX_API winrt::event_token WindowMessageReceived(const winrt::Windows::Foundation::EventHandler<winrt::Mercatec::WinUIEx::Messaging::WindowMessageEventArgs>& Handler);
        MERCATEC_WINUIEX_API void               WindowMessageReceived(const winrt::event_token& Token) noexcept;

    private:
        MERCATEC_WINUIEX_API void Subscribe();
        MERCATEC_WINUIEX_API void Unsubscribe();

        MERCATEC_WINUIEX_API static LRESULT NewWindowProc(HWND Hwnd, UINT MessageId, WPARAM WParam, LPARAM LParam, UINT_PTR SubClassId, DWORD_PTR RefData);

        struct WindowMessageMonitorImpl;
        std::unique_ptr<WindowMessageMonitorImpl> Impl;
    };
} // namespace Mercatec::WinUIEx::Messaging

#pragma warning(pop)
