//!
//! Managing Application State
//! https://learn.microsoft.com/en-us/windows/win32/learnwin32/managing-application-state-
//!

#include "pch.h"
#include "Mercatec.WinUIEx.Windowing.WindowMessageSink.hpp"
#include "Mercatec.WinUIEx.Messaging.WindowsMessages.hpp"
#include "Mercatec.WinUIEx.Debug.hpp"

namespace Mercatec::WinUIEx
{
    struct WindowMessageSink::WindowMessageSinkImpl
    {
#pragma region    Properties
        /// <summary>
        ///     Window class ID.
        /// </summary>
        std::optional<winrt::hstring> WindowId;

        /// <summary>
        ///     Handle for the message window.
        /// </summary>
        HWND MessageWindowHandle{ nullptr };
#pragma endregion Properties

#pragma region Members

        /// <summary>
        ///     The ID of the message that is being received if the taskbar is (re)started.
        /// </summary>
        uint32_t TaskbarRestartMessageId{ 0 };

        /// <summary>
        ///     Used to track whether a mouse-up event is just
        ///     the aftermath of a double-click and therefore needs to be suppressed.
        /// </summary>
        bool IsDoubleClick{ false };
#pragma endregion Members

#pragma region    Events
        /// <summary>
        ///     The custom tooltip should be closed or hidden.
        /// </summary>
        winrt::event<winrt::Windows::Foundation::EventHandler<bool>> ChangeToolTipStateRequest;

        /// <summary>
        ///     Fired in case the user clicked or moved within the taskbar icon area.
        /// </summary>
        winrt::event<winrt::Windows::Foundation::EventHandler<MouseEvent>> MouseEventReceived;

        /// <summary>
        ///     Fired if a balloon ToolTip was either displayed or closed (indicated by the boolean flag).
        /// </summary>
        winrt::event<winrt::Windows::Foundation::EventHandler<bool>> BalloonToolTipChanged;

        /// <summary>
        ///     Fired if the taskbar was created or restarted. Requires the taskbar icon to be reset.
        /// </summary>
        winrt::event<winrt::Windows::Foundation::EventHandler<winrt::Windows::Foundation::IInspectable>> TaskbarCreated;
#pragma endregion Events
    };

    /// <summary>
    ///     Creates a new message sink that receives message from a given taskbar icon.
    /// </summary>
    WindowMessageSink::WindowMessageSink() noexcept
      : WindowMessageSink{ false }
    {
    }

    WindowMessageSink::WindowMessageSink(const bool AsEmpty) noexcept
      : Impl{ std::make_unique<WindowMessageSinkImpl>() }
    {
        if ( not AsEmpty )
        {
            CreateMessageWindow();
        }
    }

    WindowMessageSink::~WindowMessageSink() noexcept
    {
        ::DestroyWindow(Impl->MessageWindowHandle);
    }

    /// <summary>
    ///     Creates a dummy instance that provides an empty pointer rather than a real window handler.<br/>
    ///     Used at design time.
    /// </summary>
    /// <returns>WindowMessageSink</returns>
    winrt::com_ptr<WindowMessageSink> WindowMessageSink::CreateEmpty() noexcept
    {
        return winrt::make_self<WindowMessageSink>(true);
    }

    /// <summary>
    ///     Window class ID.
    /// </summary>
    std::optional<winrt::hstring> WindowMessageSink::GetWindowId() const noexcept
    {
        return Impl->WindowId;
    }

    /// <summary>
    ///     Handle for the message window.
    /// </summary>
    HWND WindowMessageSink::GetMessageWindowHandle() const noexcept
    {
        return Impl->MessageWindowHandle;
    }

    /// <summary>
    ///     The custom tooltip should be closed or hidden.
    /// </summary>
    winrt::event_token WindowMessageSink::ChangeToolTipStateRequest(const winrt::Windows::Foundation::EventHandler<bool>& Handler)
    {
        return Impl->ChangeToolTipStateRequest.add(Handler);
    }

    void WindowMessageSink::ChangeToolTipStateRequest(const winrt::event_token& Token) noexcept
    {
        Impl->ChangeToolTipStateRequest.remove(Token);
    }

    /// <summary>
    ///     Fired in case the user clicked or moved within the taskbar icon area.
    /// </summary>
    winrt::event_token WindowMessageSink::MouseEventReceived(const winrt::Windows::Foundation::EventHandler<MouseEvent>& Handler)
    {
        return Impl->MouseEventReceived.add(Handler);
    }

    void WindowMessageSink::MouseEventReceived(const winrt::event_token& Token) noexcept
    {
        Impl->MouseEventReceived.remove(Token);
    }

    /// <summary>
    ///     Fired if a balloon ToolTip was either displayed or closed (indicated by the boolean flag).
    /// </summary>
    winrt::event_token WindowMessageSink::BalloonToolTipChanged(const winrt::Windows::Foundation::EventHandler<bool>& Handler)
    {
        return Impl->BalloonToolTipChanged.add(Handler);
    }

    void WindowMessageSink::BalloonToolTipChanged(const winrt::event_token& Token) noexcept
    {
        Impl->BalloonToolTipChanged.remove(Token);
    }

    /// <summary>
    ///     Fired if the taskbar was created or restarted. Requires the taskbar icon to be reset.
    /// </summary>
    winrt::event_token WindowMessageSink::TaskbarCreated(const winrt::Windows::Foundation::EventHandler<winrt::Windows::Foundation::IInspectable>& Handler)
    {
        return Impl->TaskbarCreated.add(Handler);
    }

    void WindowMessageSink::TaskbarCreated(const winrt::event_token& Token) noexcept
    {
        Impl->TaskbarCreated.remove(Token);
    }

    /// <summary>
    ///     Creates the helper message window that is used to receive messages from the taskbar icon.
    /// </summary>
    void WindowMessageSink::CreateMessageWindow()
    {
        // Generate a unique ID for the window
        Impl->WindowId = L"TaskbarIcon_" + winrt::to_hstring(winrt::GuidHelper::CreateNewGuid());

        // Register window message handler
        // Create a simple window class which is reference through
        WNDCLASSEXW Wc{};
        Wc.cbSize        = sizeof(WNDCLASSEXW);
        Wc.style         = 0;
        Wc.lpfnWndProc   = OnWindowMessageReceived;
        Wc.cbClsExtra    = 0;
        Wc.cbWndExtra    = 0;
        Wc.hInstance     = nullptr;
        Wc.hIcon         = nullptr;
        Wc.hIconSm       = nullptr;
        Wc.hCursor       = nullptr;
        Wc.hbrBackground = nullptr;
        Wc.lpszMenuName  = L"";
        Wc.lpszClassName = Impl->WindowId->c_str();

        // Register the window class
        ::RegisterClassExW(&Wc);

        // Get the message used to indicate the taskbar has been restarted
        // This is used to re-add icons when the taskbar restarts
        Impl->TaskbarRestartMessageId = ::RegisterWindowMessageW(L"TaskbarCreated");

        HWND HwndParent{ nullptr /*::GetActiveWindow()*/ };

        // Create the message window
        Impl->MessageWindowHandle = CreateWindowExW(0, WindowId->c_str(), L"", 0, 0, 0, 1, 1, HwndParent, nullptr, nullptr, this);

        if ( Impl->MessageWindowHandle == nullptr )
        {
            throw winrt::hresult_error(winrt::impl::error_fail, L"Message window handle was not a valid pointer");
        }
    }

    /// <summary>
    ///     Callback method that receives messages from the taskbar area.
    /// </summary>
    LRESULT WindowMessageSink::OnWindowMessageReceived(HWND Hwnd, const UINT MessageId, const WPARAM WParam, const LPARAM LParam)
    {
        WindowMessageSink* Self = nullptr;

        if ( MessageId == WM_NCCREATE )
        {
            auto pCreate = reinterpret_cast<LPCREATESTRUCTW>(LParam);
            auto pThis   = reinterpret_cast<WindowMessageSink*>(pCreate->lpCreateParams);
            SetWindowLongPtrW(Hwnd, GWLP_USERDATA, (LONG_PTR)pThis);

            Self = pThis;
        }
        else
        {
            Self = reinterpret_cast<WindowMessageSink*>(GetWindowLongPtrW(Hwnd, GWLP_USERDATA));
        }

        if ( MessageId == Self->Impl->TaskbarRestartMessageId )
        {
            // Recreate the icon if the taskbar was restarted (e.g. due to Win Explorer shutdown)
            Self->Impl->TaskbarCreated(*Self, nullptr);
        }

        // Forward message
        Self->ProcessWindowMessage(MessageId, WParam, LParam);
        return DefWindowProcW(Hwnd, MessageId, WParam, LParam);
    }

    /// <summary>
    ///     Processes incoming system messages.
    /// </summary>
    /// <param name="msg">Callback ID.</param>
    /// <param name="wParam">
    ///     If the version is Vista or higher, this parameter can be used to resolve mouse coordinates.
    ///     Currently not in use.
    /// </param>
    /// <param name="lParam">Provides information about the event.</param>
    void WindowMessageSink::ProcessWindowMessage(const UINT MessageId, [[maybe_unused]] const WPARAM WParam, const LPARAM LParam)
    {
        using enum Messaging::WindowsMessages;
        using Enum = Enum<Messaging::WindowsMessages>;

        if ( MessageId != CallbackMessageId )
        {
            return;
        }

        OutputDebug(L"Got message {}", Enum::GetName(LParam));

        switch ( Enum::GetValue(LParam) )
        {
            case WmContextMenu:
            {
                // TODO: Handle WM_CONTEXTMENU, see https://docs.microsoft.com/en-us/windows/win32/api/shellapi/nf-shellapi-shell_notifyiconw
                OutputDebug(L"Unhandled WM_CONTEXTMENU");
                break;
            }

            case WmMouseMove:
            {
                Impl->MouseEventReceived(*this, MouseEvent::MouseMove);
                break;
            }

            case WmLButtonDown:
            {
                Impl->MouseEventReceived(*this, MouseEvent::IconLeftMouseDown);
                break;
            }

            case WmLButtonUp:
            {
                if ( not Impl->IsDoubleClick )
                {
                    Impl->MouseEventReceived(*this, MouseEvent::IconLeftMouseUp);
                }

                Impl->IsDoubleClick = false;
                break;
            }

            case WmLButtonDblClk:
            {
                Impl->IsDoubleClick = true;
                Impl->MouseEventReceived(*this, MouseEvent::IconDoubleClick);
                break;
            }

            case WmRButtonDown:
            {
                Impl->MouseEventReceived(*this, MouseEvent::IconRightMouseDown);
                break;
            }

            case WmRButtonUp:
            {
                Impl->MouseEventReceived(*this, MouseEvent::IconRightMouseUp);
                break;
            }

            case WmRButtonDblClk:
            {
                // Double click with right mouse button - do not trigger event
                break;
            }

            case WmMButtonDown:
            {
                Impl->MouseEventReceived(*this, MouseEvent::IconMiddleMouseDown);
                break;
            }

            case WmMButtonUp:
            {
                Impl->MouseEventReceived(*this, MouseEvent::IconMiddleMouseUp);
                break;
            }

            case WmMButtonDblClk:
            {
                // double click with middle mouse button - do not trigger event
                break;
            }

            case NinBalloonShow:
            {
                Impl->BalloonToolTipChanged(*this, true);
                break;
            }

            case NinBalloonHide:
            case NinBalloonTimeout:
            {
                Impl->BalloonToolTipChanged(*this, false);
                break;
            }

            case NinBalloonUserClick:
            {
                Impl->MouseEventReceived(*this, MouseEvent::BalloonToolTipClicked);
                break;
            }

            case NinPopupOpen:
            {
                Impl->ChangeToolTipStateRequest(*this, true);
                break;
            }

            case NinPopupClose:
            {
                Impl->ChangeToolTipStateRequest(*this, false);
                break;
            }

            case NinSelect:
            {
                // TODO: Handle NIN_SELECT see https://docs.microsoft.com/en-us/windows/win32/api/shellapi/nf-shellapi-shell_notifyiconw
                OutputDebug(L"Unhandled NIN_SELECT");
                break;
            }

            case NinKeySelect:
            {
                // TODO: Handle NIN_KEYSELECT see https://docs.microsoft.com/en-us/windows/win32/api/shellapi/nf-shellapi-shell_notifyiconw
                OutputDebug(L"Unhandled NIN_KEYSELECT");
                break;
            }

            default:
            {
                OutputDebug(L"Unhandled NotifyIcon Message ID: '{}' {}", LParam, Enum::GetName(LParam));
                break;
            }
        }
    }
} // namespace Mercatec::WinUIEx
