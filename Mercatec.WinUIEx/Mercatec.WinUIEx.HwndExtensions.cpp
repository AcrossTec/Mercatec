#include "pch.h"
#include "Mercatec.WinUIEx.HwndExtensions.hpp"
#include "Mercatec.WinUIEx.WindowExtensions.hpp"
#include "Mercatec.WinUIEx.Messaging.WindowsMessages.hpp"

using namespace Mercatec::WinUIEx::Messaging;
using namespace Windows::Win32::UI::WindowsAndMessaging;
using namespace Windows::Win32::Graphics::Gdi;

namespace Mercatec::WinUIEx
{
    UINT HwndExtensions::GetDpiForWindow(HWND Hwnd) noexcept
    {
        return ::GetDpiForWindow(Hwnd);
    }

    UINT HwndExtensions::GetDpiForWindowsMonitor(HWND Hwnd) noexcept
    {
        using Enum = Enum<MonitorFromFlags>;
        using enum MonitorFromFlags;

        HMONITOR HwndDesktop{ ::MonitorFromWindow(Hwnd, Enum::GetValue(MonitorDefaultToNearest)) };
        return ::GetDpiForWindow(reinterpret_cast<HWND>(HwndDesktop));
    }

    bool HwndExtensions::SetForegroundWindow(HWND Hwnd) noexcept
    {
        return static_cast<bool>(::SetForegroundWindow(Hwnd));
    }

    HWND HwndExtensions::GetActiveWindow() noexcept
    {
        return ::GetActiveWindow();
    }

    HWND HwndExtensions::GetDesktopWindow() noexcept
    {
        return ::GetDesktopWindow();
    }

    void SetWindowPosOrThrow(HWND Hwnd, HWND HwndInsertAfter, const int32_t X, const int32_t Y, const int32_t CX, const int32_t CY, const SetWindowPosFlags Flags)
    {
        using enum SetWindowPosFlags;
        using Enum = Enum<SetWindowPosFlags>;

        BOOL Result = ::SetWindowPos(Hwnd, HwndInsertAfter, X, Y, CX, CY, Enum::GetValue(Flags));

        if ( not Result )
        {
            winrt::throw_last_error();
        }
    }

    void HwndExtensions::SetAlwaysOnTop(HWND Hwnd, const bool Enable)
    {
        using enum SetWindowPosFlags;
        SetWindowPosOrThrow(Hwnd, (Enable ? HWND_TOPMOST : HWND_NOTOPMOST), 0, 0, 0, 0, SwpNoSize | SwpNoMove);
    }

    HWND HwndExtensions::UpdateLayeredWindow(HWND Hwnd)
    {
        throw winrt::hresult_not_implemented();
        // return ::UpdateLayeredWindow(Hwnd, );
    }

    void HwndExtensions::CenterOnScreen(HWND Hwnd, const std::optional<double>& Width, const std::optional<double>& Height)
    {
        using Enum = Enum<MonitorFromFlags>;

        using enum MonitorFromFlags;
        using enum SetWindowPosFlags;

        HMONITOR HwndDesktop = ::MonitorFromWindow(Hwnd, Enum::GetValue(MonitorDefaultToNearest));

        MONITORINFOEXW Info;
        memset(&Info, 0, sizeof(MONITORINFOEXW));
        Info.cbSize = sizeof(MONITORINFOEXW);
        ::GetMonitorInfoW(HwndDesktop, &Info);

        const UINT Dpi = ::GetDpiForWindow(Hwnd);

        RECT WindowRect;
        ::GetWindowRect(Hwnd, &WindowRect);

        const double_t ScalingFactor = Dpi / 96.0;
        const int32_t  W             = Width.has_value() ? int32_t(*Width * ScalingFactor) : (WindowRect.right - WindowRect.left);
        const int32_t  H             = Height.has_value() ? int32_t(*Height * ScalingFactor) : (WindowRect.bottom - WindowRect.top);
        const int32_t  CX            = (Info.rcMonitor.left + Info.rcMonitor.right) / 2;
        const int32_t  CY            = (Info.rcMonitor.bottom + Info.rcMonitor.top) / 2;
        const int32_t  Left          = CX - (W / 2);
        const int32_t  Top           = CY - (H / 2);

        SetWindowPosOrThrow(Hwnd, HWND_TOP, Left, Top, W, H, SwpShowWindow);
    }

    void HwndExtensions::SetIcon(HWND Hwnd, const winrt::Microsoft::UI::IconId& IconId) noexcept
    {
        auto AppWindow{ WindowExtensions::GetAppWindowFromWindowHandle(Hwnd) };
        AppWindow.SetIcon(IconId);
    }

    void HwndExtensions::SetIcon(HWND Hwnd, const std::wstring_view IconPath) noexcept
    {
        auto AppWindow{ WindowExtensions::GetAppWindowFromWindowHandle(Hwnd) };
        AppWindow.SetIcon(IconPath);
    }

    void HwndExtensions::SetWindowPositionAndSize(HWND Hwnd, const double_t X, const double_t Y, const double_t Width, const double_t Height)
    {
        using enum SetWindowPosFlags;

        const UINT     Dpi           = GetDpiForWindow(Hwnd);
        const double_t ScalingFactor = Dpi / 96.0;

        SetWindowPosOrThrow(Hwnd, HWND_TOP, int32_t(X * ScalingFactor), int32_t(Y * ScalingFactor), int32_t(Width * ScalingFactor), int32_t(Height * ScalingFactor), SwpNoSendChanging);
    }

    void HwndExtensions::SetWindowSize(HWND Hwnd, const double_t Width, const double_t Height)
    {
        using enum SetWindowPosFlags;

        const UINT     Dpi           = GetDpiForWindow(Hwnd);
        const double_t ScalingFactor = Dpi / 96.0;

        SetWindowPosOrThrow(Hwnd, HWND_TOP, 0, 0, int32_t(Width * ScalingFactor), int32_t(Height * ScalingFactor), SwpNoRePosition | SwpNoSendChanging);
    }

    void HwndExtensions::SetTaskBarIcon(HWND Hwnd, const std::optional<Icon>& Icon) noexcept
    {
        using enum WindowsMessages;
        using Enum = Enum<WindowsMessages>;

        ::SendMessageW(Hwnd, Enum::GetValue(WmSetIcon), WPARAM(0), LPARAM(Icon.value_or(nullptr).Handle));
    }

    bool HwndExtensions::ShowWindow(HWND Hwnd) noexcept
    {
        using enum ShowWindowCmd;
        using Enum = Enum<ShowWindowCmd>;

        return static_cast<bool>(::ShowWindowAsync(Hwnd, Enum::GetValue(SwShow)));
    }

    bool HwndExtensions::HideWindow(HWND Hwnd) noexcept
    {
        using enum ShowWindowCmd;
        using Enum = Enum<ShowWindowCmd>;

        return static_cast<bool>(::ShowWindowAsync(Hwnd, Enum::GetValue(SwHide)));
    }

    bool HwndExtensions::MaximizeWindow(HWND Hwnd) noexcept
    {
        using enum ShowWindowCmd;
        using Enum = Enum<ShowWindowCmd>;

        return static_cast<bool>(::ShowWindowAsync(Hwnd, Enum::GetValue(SwShowMaximized)));
    }

    bool HwndExtensions::MinimizeWindow(HWND Hwnd) noexcept
    {
        using enum ShowWindowCmd;
        using Enum = Enum<ShowWindowCmd>;

        return static_cast<bool>(::ShowWindowAsync(Hwnd, Enum::GetValue(SwShowMinimized)));
    }

    bool HwndExtensions::RestoreWindow(HWND Hwnd) noexcept
    {
        using enum ShowWindowCmd;
        using Enum = Enum<ShowWindowCmd>;

        return static_cast<bool>(::ShowWindowAsync(Hwnd, Enum::GetValue(SwRestore)));
    }

    WindowStyle HwndExtensions::GetWindowStyle(HWND Hwnd) noexcept
    {
        using enum WindowLongPtrIndex;
        using Enum = Enum<WindowLongPtrIndex>;

        return static_cast<WindowStyle>(::GetWindowLongW(Hwnd, Enum::GetValue(GwlStyle)));
    }

    void HwndExtensions::ToggleWindowStyle(HWND Hwnd, const bool Visible, const WindowStyle Style)
    {
        using enum WindowLongPtrIndex;

        using EnumIndex = Enum<WindowLongPtrIndex>;
        using EnumStyle = Enum<WindowStyle>;

        const WindowStyle CurrentStyle = EnumStyle::GetValue(::GetWindowLongW(Hwnd, EnumIndex::GetValue(GwlStyle)));
        const WindowStyle NewStyle     = Visible ? (CurrentStyle & Style) : (CurrentStyle & ~Style);

        const WindowStyle ResultStyle = EnumStyle::GetValue(::SetWindowLongW(Hwnd, EnumIndex::GetValue(GwlStyle), EnumStyle::GetValue(NewStyle)));

        if ( ResultStyle != CurrentStyle )
        {
            winrt::throw_last_error();
        }
    }

    void HwndExtensions::SetWindowStyle(HWND Hwnd, const WindowStyle NewStyle)
    {
        using enum WindowLongPtrIndex;

        using EnumIndex = Enum<WindowLongPtrIndex>;
        using EnumStyle = Enum<WindowStyle>;

        const WindowStyle CurrentStyle = EnumStyle::GetValue(::GetWindowLongW(Hwnd, EnumIndex::GetValue(GwlStyle)));
        const WindowStyle ResultStyle  = EnumStyle::GetValue(::SetWindowLongW(Hwnd, EnumIndex::GetValue(GwlStyle), EnumStyle::GetValue(NewStyle)));

        if ( ResultStyle != CurrentStyle )
        {
            winrt::throw_last_error();
        }
    }
} // namespace Mercatec::WinUIEx
