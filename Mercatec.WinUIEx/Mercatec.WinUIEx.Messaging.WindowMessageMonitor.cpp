#include "pch.h"
#include "Mercatec.WinUIEx.Messaging.WindowMessageMonitor.hpp"
#include "Mercatec.WinUIEx.WindowExtensions.hpp"
#include <mutex>

using winrt::event;
using winrt::Mercatec::WinUIEx::Messaging::WindowMessageEventArgs;
using winrt::Windows::Foundation::EventHandler;

namespace Mercatec::WinUIEx::Messaging
{
    struct WindowMessageMonitor::WindowMessageMonitorImpl
    {
        HWND                                        Hwnd{ nullptr };
        SUBCLASSPROC                                Callback{ nullptr };
        LONG_PTR                                    UserData;
        std::mutex                                  LockObject;
        event<EventHandler<WindowMessageEventArgs>> NativeMessage;
    };

    /// <summary>
    ///     Initialize a new instance of the <see cref="WindowMessageMonitor"/> class.
    /// </summary>
    /// <param name="window">The window to listen to messages for.</param>
    WindowMessageMonitor::WindowMessageMonitor(const winrt::Microsoft::UI::Xaml::Window& Window)
      : WindowMessageMonitor(WindowExtensions::GetWindowHandle(Window))
    {
    }

    /// <summary>
    ///     Initialize a new instance of the <see cref="WindowMessageMonitor"/> class.
    /// </summary>
    /// <param name="hwnd">The window handle to listen to messages for.</param>
    WindowMessageMonitor::WindowMessageMonitor(HWND Hwnd)
      : Impl{ new WindowMessageMonitorImpl{ .Hwnd = Hwnd } }
    {
    }

    /// <summary>
    ///     Finalizer
    /// </summary>
    WindowMessageMonitor::~WindowMessageMonitor()
    {
        Unsubscribe();
    }

    /// <summary>
    ///     Event raised when a windows message is received.
    /// </summary>
    winrt::event_token WindowMessageMonitor::WindowMessageReceived(const EventHandler<WindowMessageEventArgs>& Handler)
    {
        if ( not Impl->NativeMessage )
        {
            Subscribe();
        }

        return Impl->NativeMessage.add(Handler);
    }

    void WindowMessageMonitor::WindowMessageReceived(const winrt::event_token& Token) noexcept
    {
        Impl->NativeMessage.remove(Token);

        if ( not Impl->NativeMessage )
        {
            Unsubscribe();
        }
    }

    void WindowMessageMonitor::Subscribe()
    {
        std::lock_guard Lock{ Impl->LockObject };

        if ( Impl->Callback == nullptr )
        {
            Impl->Callback = NewWindowProc;
            Impl->UserData = GetWindowLongPtrW(Impl->Hwnd, GWLP_USERDATA);

            [[maybe_unused]] BOOL IsOk = //
              ::SetWindowSubclass(Impl->Hwnd, Impl->Callback, 101, reinterpret_cast<DWORD_PTR>(this));
        }
    }

    void WindowMessageMonitor::Unsubscribe()
    {
        std::lock_guard Lock{ Impl->LockObject };

        if ( Impl->Callback != nullptr )
        {
            ::RemoveWindowSubclass(Impl->Hwnd, Impl->Callback, 101);
            Impl->Callback = nullptr;
        }
    }

    LRESULT WindowMessageMonitor::NewWindowProc(HWND Hwnd, UINT MessageId, WPARAM WParam, LPARAM LParam, [[maybe_unused]] UINT_PTR SubClassId, DWORD_PTR RefData)
    {
        auto Self = reinterpret_cast<WindowMessageMonitor*>(RefData);

        WindowMessageEventArgs EventArg(uint64_t(Hwnd), MessageId, WParam, LParam);
        Self->Impl->NativeMessage(*Self, EventArg);

        if ( EventArg.Handled() )
        {
            return EventArg.Result();
        }

        return ::DefSubclassProc(Hwnd, MessageId, WParam, LParam);
    }
} // namespace Mercatec::WinUIEx::Messaging
