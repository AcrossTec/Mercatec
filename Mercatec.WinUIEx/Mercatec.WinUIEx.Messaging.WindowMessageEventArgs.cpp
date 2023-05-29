#include "pch.h"
#include "Mercatec.WinUIEx.Messaging.WindowMessageEventArgs.h"
#if __has_include("Messaging.WindowMessageEventArgs.g.cpp")
# include "Messaging.WindowMessageEventArgs.g.cpp"
#endif

#include "Mercatec.WinUIEx.Messaging.WindowsMessages.hpp"

using Mercatec::WinUIEx::Enum;

namespace winrt::Mercatec::WinUIEx::Messaging::implementation
{
    WindowMessageEventArgs::WindowMessageEventArgs(const uint64_t Hwnd, const uint32_t MessageId, const uint64_t WParam, const int64_t LParam)
      : m_Handled{ false }
      , m_Result{ 0 }
      , m_Message{ Hwnd, MessageId, WParam, LParam }
    {
    }

    /// <summary>
    ///     The result after processing the message.
    ///     Use this to set the return result, after also setting <see cref="Handled"/> to <c>true</c>.
    /// </summary>
    /// <seealso cref="Handled"/>
    int64_t WindowMessageEventArgs::Result() const noexcept
    {
        return m_Result;
    }

    void WindowMessageEventArgs::Result(const int64_t Result) noexcept
    {
        m_Result = Result;
    }

    /// <summary>
    ///     Indicates whether this message was handled and the <see cref="Result"/> value should be returned.
    /// </summary>
    /// <remarks><c>True</c> is the message was handled and the <see cref="Result"/> should be returned, otherwise <c>false</c> and continue processing this message by other subsclasses.</remarks>
    /// <seealso cref="Result"/>
    bool WindowMessageEventArgs::Handled() const noexcept
    {
        return m_Handled;
    }

    void WindowMessageEventArgs::Handled(const bool Handled) noexcept
    {
        m_Handled = Handled;
    }

    /// <summary>
    ///     The Windows WM Message
    /// </summary>
    Messaging::Message WindowMessageEventArgs::Message() const noexcept
    {
        return m_Message;
    }

    WindowsMessages WindowMessageEventArgs::MessageType() const noexcept
    {
        return Enum<WindowsMessages>::GetValue(m_Message.MessageId());
    }
} // namespace winrt::Mercatec::WinUIEx::Messaging::implementation
