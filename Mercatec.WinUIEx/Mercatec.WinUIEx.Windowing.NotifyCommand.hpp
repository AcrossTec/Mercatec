//!
//! https://learn.microsoft.com/en-us/windows/win32/api/shellapi/nf-shellapi-shell_notifyiconw
//! Shell_NotifyIconW function (shellapi.h)
//!
//! NOTIFYICONDATAW structure (shellapi.h)
//! https://learn.microsoft.com/en-us/windows/win32/api/shellapi/ns-shellapi-notifyicondataw
//!

#include "Mercatec.WinUIEx.Enum.hpp"

#include <Windows.h>
#include <shellapi.h>

#include <cinttypes>

#pragma once

namespace Mercatec::WinUIEx
{
    /// <summary>
    /// Main operations performed on the Shell_NotifyIcon(uint, in Windows.Win32.NOTIFYICONDATAW32) function.
    /// </summary>
    enum struct NotifyCommand : uint32_t
    {
        /// <summary>
        /// The taskbar icon is being created.
        /// </summary>
        Add = NIM_ADD,

        /// <summary>
        /// The settings of the taskbar icon are being updated.
        /// </summary>
        Modify = NIM_MODIFY,

        /// <summary>
        /// The taskbar icon is deleted.
        /// </summary>
        Delete = NIM_DELETE,

        /// <summary>
        /// Focus is returned to the taskbar icon. Currently not in use.
        /// </summary>
        SetFocus = NIM_SETFOCUS,

        /// <summary>
        /// Shell32.dll version 5.0 and later only. Instructs the taskbar
        /// to behave according to the version number specified in the
        /// uVersion member of the structure pointed to by lpdata.
        /// This message allows you to specify whether you want the version
        /// 5.0 behavior found on Microsoft Windows 2000 systems, or the
        /// behavior found on earlier Shell versions. The default value for
        /// uVersion is zero, indicating that the original Windows 95 notify
        /// icon behavior should be used.
        /// </summary>
        SetVersion = NIM_SETVERSION
    };
} // namespace Mercatec::WinUIEx

//
// clang-format off
//
#define X Add, Modify, Delete, SetFocus, SetVersion
MAKE_ENUM_TRAITS(Mercatec::WinUIEx, NotifyCommand)
ENUM_BITMASK_OPS(Mercatec::WinUIEx::NotifyCommand)
#undef X
//
// clang-format on
//
