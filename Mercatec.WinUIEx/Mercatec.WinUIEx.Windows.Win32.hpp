#pragma once

#include <Windows.h>

namespace Windows::Win32
{
    namespace UI::WindowsAndMessaging
    {
        enum struct SetWindowPosFlags : UINT
        {
            AsyncWindowPos = SWP_ASYNCWINDOWPOS,
            DeferErase     = SWP_DEFERERASE,
            DrawFrame      = SWP_DRAWFRAME,
            FrameChanged   = SWP_FRAMECHANGED,
            HideWindow     = SWP_HIDEWINDOW,
            NoActivate     = SWP_NOACTIVATE,
            NoCopyBits     = SWP_NOCOPYBITS,
            NoMove         = SWP_NOMOVE,
            NoOwnerZOrder  = SWP_NOOWNERZORDER,
            NoReDraw       = SWP_NOREDRAW,
            NoRePosition   = SWP_NOREPOSITION,
            NoSendChanging = SWP_NOSENDCHANGING,
            NoSize         = SWP_NOSIZE,
            NoZOrder       = SWP_NOZORDER,
            ShowWindow     = SWP_SHOWWINDOW,
        };
    } // namespace UI::WindowsAndMessaging
} // namespace Windows::Win32
