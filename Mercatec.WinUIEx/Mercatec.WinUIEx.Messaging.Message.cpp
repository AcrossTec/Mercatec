#include "pch.h"
#include "Mercatec.WinUIEx.Messaging.Message.hpp"
#include "Mercatec.WinUIEx.Messaging.WindowsMessages.hpp"

#include <format>

namespace Mercatec::WinUIEx::Messaging
{
    struct Message::MessageImpl
    {
        HWND   Hwnd;
        UINT   MessageId;
        WPARAM WParam;
        LPARAM LParam;
    };

    Message::Message() noexcept
      : Impl(new MessageImpl{ .Hwnd = nullptr, .MessageId = 0, .WParam = 0, .LParam = 0 })
    {
    }

    Message::Message(HWND Hwnd, const UINT MessageId, const WPARAM WParam, const LPARAM LParam) noexcept
      : Impl(new MessageImpl{ .Hwnd = Hwnd, .MessageId = MessageId, .WParam = WParam, .LParam = LParam })
    {
    }

    Message::~Message() noexcept
    {
    }

    HWND Message::GetHwnd() const noexcept
    {
        return Impl->Hwnd;
    }

    Message& Message::SetHwnd(HWND Hwnd) noexcept
    {
        Impl->Hwnd = Hwnd;
        return *this;
    }

    UINT Message::GetMessageId() const noexcept
    {
        return Impl->MessageId;
    }

    Message& Message::SetMessageId(const UINT MessageId) noexcept
    {
        Impl->MessageId = MessageId;
        return *this;
    }

    WPARAM Message::GetWParam() const noexcept
    {
        return Impl->WParam;
    }

    Message& Message::SetWParam(const WPARAM WParam) noexcept
    {
        Impl->WParam = WParam;
        return *this;
    }

    LPARAM Message::GetLParam() const noexcept
    {
        return Impl->LParam;
    }

    Message& Message::SetLParam(const LPARAM LParam) noexcept
    {
        Impl->LParam = LParam;
        return *this;
    }

    WORD Message::GetLowOrder() const noexcept
    {
        return LOWORD(Impl->LParam);
    }

    WORD Message::GetHighOrder() const noexcept
    {
        return HIWORD(Impl->LParam);
    }

    std::wstring Message::ToString() const noexcept
    {
        switch ( Enum<WindowsMessages>::GetValue(Impl->MessageId) )
        {
            case WindowsMessages::WmSizing:
            {
                std::wstring Side = std::to_wstring(Impl->WParam);

                // clang-format off
                switch(Impl->WParam) 
                {
                    case 1: Side = L"Left"        ; break;
                    case 2: Side = L"Right"       ; break;
                    case 3: Side = L"Top"         ; break;
                    case 4: Side = L"Top-Left"    ; break;
                    case 5: Side = L"Top-Right"   ; break;
                    case 6: Side = L"Bottom"      ; break;
                    case 7: Side = L"Bottom-Left" ; break;
                    case 8: Side = L"Bottom-Right"; break;
                };
                // clang-format on

                auto Rect = reinterpret_cast<RECT*>(Impl->LParam);

                return std::format(L"WM_SIZING: Side: {} Rect: {},{},{},{}", Side, Rect->left, Rect->top, Rect->right, Rect->bottom);
            }
        }

        return std::format(L"{}: LParam={} WParam={}", Enum<WindowsMessages>::GetName(Impl->MessageId), LParam, WParam);
    }
} // namespace Mercatec::WinUIEx::Messaging
