//!
//! NOTIFYICONDATAW structure (shellapi.h)
//! https://learn.microsoft.com/en-us/windows/win32/api/shellapi/ns-shellapi-notifyicondataw
//!

#pragma once

#include "Mercatec.WinUIEx.Enum.hpp"

#include <Windows.h>
#include <shellapi.h>

#include <cinttypes>

namespace Mercatec::WinUIEx
{
    /// <summary>
    /// Indicates which members of a <see cref="NOTIFYICONDATAW32"/> structure
    /// were set, and thus contain valid data or provide additional information
    /// to the ToolTip as to how it should display.
    /// </summary>
    enum struct IconDataMembers : uint32_t
    {
        /// <summary>
        /// The message ID is set.
        /// </summary>
        Message = NIF_MESSAGE,

        /// <summary>
        /// The notification icon is set.
        /// </summary>
        Icon = NIF_ICON,

        /// <summary>
        /// The tooltip is set.
        /// </summary>
        Tip = NIF_TIP,

        /// <summary>
        /// The <see cref="NOTIFYICONDATAW32.dwState"/> and <see cref="NOTIFYICONDATAW32.dwStateMask"/> members are valid.
        /// </summary>
        State = NIF_STATE,

        /// <summary>
        /// 0x00000010. Display a balloon notification. The <see cref="NOTIFYICONDATAW32.szInfo"/>,
        /// <see cref="NOTIFYICONDATAW32.szInfoTitle"/>, <see cref="NOTIFYICONDATAW32.dwInfoFlags"/>,
        /// and uTimeout members are valid. Note that uTimeout is valid only in Windows 2000 and Windows XP.
        /// </summary>
        /// <remarks>
        /// <para>To display the balloon notification, specify NIF_INFO and provide text in szInfo.</para>
        /// <para>To remove a balloon notification, specify NIF_INFO and provide an empty string through szInfo.</para>
        /// <para>To add a notification area icon without displaying a notification, do not set the NIF_INFO flag.</para>
        /// <para>See https://docs.microsoft.com/en-us/windows/win32/api/shellapi/ns-shellapi-notifyicondataw#nif_info-0x00000010</para>
        /// </remarks>
        Info = NIF_INFO,

        // Internal identifier is set. Reserved, thus commented out.
        // Guid = 0x20,

        /// <summary>
        /// Windows Vista (Shell32.dll version 6.0.6) and later. If the ToolTip
        /// cannot be displayed immediately, discard it.<br/>
        /// Use this flag for ToolTips that represent real-time information which
        /// would be meaningless or misleading if displayed at a later time.
        /// For example, a message that states "Your telephone is ringing."<br/>
        /// This modifies and must be combined with the <see cref="Info"/> flag.
        /// </summary>
        Realtime = NIF_REALTIME,

        /// <summary>
        /// Windows Vista (Shell32.dll version 6.0.6) and later.
        /// Use the standard ToolTip. Normally, when uVersion is set
        /// to NOTIFYICON_VERSION_4, the standard ToolTip is replaced
        /// by the application-drawn pop-up user interface (UI).
        /// If the application wants to show the standard tooltip
        /// in that case, regardless of whether the on-hover UI is showing,
        /// it can specify NIF_SHOWTIP to indicate the standard tooltip
        /// should still be shown.<br/>
        /// Note that the NIF_SHOWTIP flag is effective until the next call
        /// to Shell_NotifyIcon.
        /// </summary>
        UseLegacyToolTips = NIF_SHOWTIP
    };
} // namespace Mercatec::WinUIEx

//
// clang-format off
//
#define X Message, Icon, Tip, State, Info, Realtime, UseLegacyToolTips
MAKE_ENUM_TRAITS(Mercatec::WinUIEx, IconDataMembers)
ENUM_BITMASK_OPS(Mercatec::WinUIEx::IconDataMembers)
#undef X
//
// clang-format on
//
