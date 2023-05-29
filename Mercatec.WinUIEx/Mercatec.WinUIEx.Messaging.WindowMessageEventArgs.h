#pragma once

#include "Messaging.WindowMessageEventArgs.g.h"

namespace winrt::Mercatec::WinUIEx::Messaging::implementation
{
    /// <summary>
    ///     Event arguments for the <see cref="WindowMessageMonitor.WindowMessageReceived"/> event.
    /// </summary>
    struct WindowMessageEventArgs : WindowMessageEventArgsT<WindowMessageEventArgs>
    {
    public:
        WindowMessageEventArgs(const uint64_t Hwnd, const uint32_t MessageId, const uint64_t WParam, const int64_t LParam);

        /// <summary>
        ///     The result after processing the message.
        ///     Use this to set the return result, after also setting <see cref="Handled"/> to <c>true</c>.
        /// </summary>
        /// <seealso cref="Handled"/>
        int64_t Result() const noexcept;
        void    Result(const int64_t Result) noexcept;

        /// <summary>
        ///     Indicates whether this message was handled and the <see cref="Result"/> value should be returned.
        /// </summary>
        /// <remarks><c>True</c> is the message was handled and the <see cref="Result"/> should be returned, otherwise <c>false</c> and continue processing this message by other subsclasses.</remarks>
        /// <seealso cref="Result"/>
        bool Handled() const noexcept;
        void Handled(const bool Handled) noexcept;

        /// <summary>
        ///     The Windows WM Message
        /// </summary>
        Messaging::Message Message() const noexcept;
        WindowsMessages    MessageType() const noexcept;

    private:
        bool    m_Handled;
        int64_t m_Result;

        Messaging::Message m_Message;
    };
} // namespace winrt::Mercatec::WinUIEx::Messaging::implementation

namespace winrt::Mercatec::WinUIEx::Messaging::factory_implementation
{
    struct WindowMessageEventArgs : WindowMessageEventArgsT<WindowMessageEventArgs, implementation::WindowMessageEventArgs>
    {
    };
} // namespace winrt::Mercatec::WinUIEx::Messaging::factory_implementation
