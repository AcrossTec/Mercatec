#pragma once

#include "Mercatec.WinUIEx.Exports.Api.hpp"

#include <Windows.h>

#include <string>
#include <memory>

namespace Mercatec::WinUIEx::Messaging
{
    /// <summary>
    ///     Represents a Windows Message.
    /// </summary>
    /// <remarks>
    ///     Refer to Windows MSG structure documentation for more info: <a href="https://docs.microsoft.com/en-us/windows/win32/api/winuser/ns-winuser-msg" />.
    /// </remarks>
    class MERCATEC_WINUIEX_API Message
    {
    public:
        Message() noexcept;
        Message(HWND Hwnd, const UINT MessageId, const WPARAM WParam, const LPARAM LParam) noexcept;
        ~Message() noexcept;

        /// <summary>
        ///     Gets the window handle of the message.
        /// </summary>
        /// <remarks>Window handle is a value that uniquely identifies a window on the system. This property returns a handle of the window whose window procedure receives this message. It is useful when your code need to interact with some native Windows API functions that expect window handles as parameters.</remarks>
        HWND     GetHwnd() const noexcept;
        Message& SetHwnd(HWND Hwnd) noexcept;
        __declspec(property(get = GetHwnd, put = SetHwnd)) HWND Hwnd;

        /// <summary>
        ///     Gets the ID number for the message.
        /// </summary>
        UINT     GetMessageId() const noexcept;
        Message& SetMessageId(const UINT MessageId) noexcept;
        __declspec(property(get = GetMessageId, put = SetMessageId)) UINT MessageId;

        /// <summary>
        ///     Gets or sets the WParam field of the message.
        /// </summary>
        WPARAM   GetWParam() const noexcept;
        Message& SetWParam(const WPARAM WParam) noexcept;
        __declspec(property(get = GetWParam, put = SetWParam)) WPARAM WParam;

        /// <summary>
        ///     Specifies the LParam field of the message.
        /// </summary>
        LPARAM   GetLParam() const noexcept;
        Message& SetLParam(const LPARAM LParam) noexcept;
        __declspec(property(get = GetLParam, put = SetLParam)) LPARAM LParam;

        /// <summary>
        ///
        /// </summary>
        /// <returns></returns>
        WORD GetLowOrder() const noexcept;
        __declspec(property(get = GetLowOrder)) WORD LowOrder;

        /// <summary>
        ///
        /// </summary>
        /// <returns></returns>
        WORD GetHighOrder() const noexcept;
        __declspec(property(get = GetHighOrder)) WORD HighOrder;

        /// <summary>
        ///
        /// </summary>
        /// <returns></returns>
        std::wstring ToString() const noexcept;

    private:
        struct MessageImpl;
        std::unique_ptr<MessageImpl> Impl;
    };
} // namespace Mercatec::WinUIEx::Messaging
