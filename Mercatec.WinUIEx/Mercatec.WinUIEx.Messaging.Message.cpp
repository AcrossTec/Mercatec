#include "pch.h"
#include "Mercatec.WinUIEx.Messaging.Message.h"
#if __has_include("Messaging.Message.g.cpp")
# include "Messaging.Message.g.cpp"
#endif

namespace winrt::Mercatec::WinUIEx::Messaging::implementation
{
    Message::Message() noexcept
    {
    }

    Message::Message(const uint64_t Hwnd, const uint32_t MessageId, const uint64_t WParam, const int64_t LParam) noexcept
      : m_Message{ reinterpret_cast<HWND>(Hwnd), MessageId, WParam, LParam }
    {
    }

    /// <summary>
    ///     Gets the window handle of the message.
    /// </summary>
    /// <remarks>Window handle is a value that uniquely identifies a window on the system. This property returns a handle of the window whose window procedure receives this message. It is useful when your code need to interact with some native Windows API functions that expect window handles as parameters.</remarks>
    uint64_t Message::Hwnd() const noexcept
    {
        return reinterpret_cast<uint64_t>(m_Message.Hwnd);
    }

    void Message::Hwnd(const uint64_t Hwnd) noexcept
    {
        m_Message.Hwnd = reinterpret_cast<HWND>(Hwnd);
    }

    /// <summary>
    ///     Gets the ID number for the message.
    /// </summary>
    uint32_t Message::MessageId() const noexcept
    {
        return m_Message.MessageId;
    }

    void Message::MessageId(const uint32_t MessageId) noexcept
    {
        m_Message.MessageId = MessageId;
    }

    /// <summary>
    ///     Gets or sets the WParam field of the message.
    /// </summary>
    uint64_t Message::WParam() const noexcept
    {
        return m_Message.WParam;
    }

    void Message::WParam(const uint64_t WParam) noexcept
    {
        m_Message.WParam = WParam;
    }

    /// <summary>
    ///     Specifies the LParam field of the message.
    /// </summary>
    int64_t Message::LParam() const noexcept
    {
        return m_Message.LParam;
    }

    void Message::LParam(const int64_t LParam) noexcept
    {
        m_Message.LParam = LParam;
    }

    /// <summary></summary
    uint32_t Message::LowOrder() const noexcept
    {
        return m_Message.LowOrder;
    }

    /// <summary></summary
    uint32_t Message::HighOrder() const noexcept
    {
        return m_Message.HighOrder;
    }

    /// <summary></summary>
    hstring Message::ToString() const noexcept
    {
        return hstring{ m_Message.ToString() };
    }
} // namespace winrt::Mercatec::WinUIEx::Messaging::implementation
