#pragma once

#include "Messaging.Message.g.h"
#include "Internal/Messaging/Mercatec.WinUIEx.Messaging.Internal.Message.hpp"

namespace winrt::Mercatec::WinUIEx::Messaging::implementation
{
    struct Message : MessageT<Message>
    {
    public:
        Message() noexcept;
        Message(const uint64_t Hwnd, const uint32_t MessageId, const uint64_t WParam, const int64_t LParam) noexcept;

        /// <summary>
        ///     Gets the window handle of the message.
        /// </summary>
        /// <remarks>Window handle is a value that uniquely identifies a window on the system. This property returns a handle of the window whose window procedure receives this message. It is useful when your code need to interact with some native Windows API functions that expect window handles as parameters.</remarks>
        uint64_t Hwnd() const noexcept;
        void     Hwnd(const uint64_t Hwnd) noexcept;

        /// <summary>
        ///     Gets the ID number for the message.
        /// </summary>
        uint32_t MessageId() const noexcept;
        void     MessageId(const uint32_t MessageId) noexcept;

        /// <summary>
        ///     Gets or sets the WParam field of the message.
        /// </summary>
        uint64_t WParam() const noexcept;
        void     WParam(const uint64_t WParam) noexcept;

        /// <summary>
        ///     Specifies the LParam field of the message.
        /// </summary>
        int64_t LParam() const noexcept;
        void    LParam(const int64_t LParam) noexcept;

        /// <summary></summary>
        uint32_t LowOrder() const noexcept;

        /// <summary></summary>
        uint32_t HighOrder() const noexcept;

        /// <summary></summary>
        hstring ToString() const noexcept;

    private:
        ::Mercatec::WinUIEx::Messaging::Internal::Message m_Message;
    };
} // namespace winrt::Mercatec::WinUIEx::Messaging::implementation

namespace winrt::Mercatec::WinUIEx::Messaging::factory_implementation
{
    struct Message : MessageT<Message, implementation::Message>
    {
    };
} // namespace winrt::Mercatec::WinUIEx::Messaging::factory_implementation
