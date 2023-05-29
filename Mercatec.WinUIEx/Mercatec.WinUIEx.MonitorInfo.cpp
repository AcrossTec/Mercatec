#include "pch.h"
#include "Mercatec.WinUIEx.MonitorInfo.hpp"
#include "Mercatec.WinUIEx.Windows.Win32.hpp"

namespace Mercatec::WinUIEx
{
    struct MonitorInfo::MonitorInfoImpl
    {
        HMONITOR                         Monitor;
        std::wstring                     Name;
        winrt::Windows::Foundation::Rect RectMonitor;
        winrt::Windows::Foundation::Rect RectWork;
    };

    MonitorInfo::MonitorInfo(HMONITOR Monitor, LPCRECT Rect)
      : Impl{ std::make_unique<MonitorInfoImpl>() }
    {
        Impl->Monitor     = Monitor;
        Impl->RectMonitor = winrt::Windows::Foundation::Rect( //
          winrt::Windows::Foundation::Point(float_t(Rect->left), float_t(Rect->top)),
          winrt::Windows::Foundation::Size(float_t(Rect->right), float_t(Rect->bottom))
        );

        MONITORINFOEXW Info{};
        Info.cbSize = sizeof(MONITORINFOEXW);

        GetMonitorInfoW(Impl->Monitor, &Info);

        Impl->Name = Info.szDevice;

        Impl->RectWork = winrt::Windows::Foundation::Rect( //
          winrt::Windows::Foundation::Point(float_t(Info.rcWork.left), float_t(Info.rcWork.top)),
          winrt::Windows::Foundation::Size(float_t(Info.rcWork.right), float_t(Info.rcWork.bottom))
        );
    }

    /// <summary>
    ///     Gets the display monitors (including invisible pseudo-monitors associated with the mirroring drivers).
    /// </summary>
    /// <returns>
    ///     A list of display monitors.
    /// </returns>
    std::vector<MonitorInfo> MonitorInfo::GetDisplayMonitors()
    {
        using enum Windows::Win32::UI::WindowsAndMessaging::SystemMetricsIndex;
        using Enum = Enum<Windows::Win32::UI::WindowsAndMessaging::SystemMetricsIndex>;

        std::vector<MonitorInfo> List;

        const int32_t MonitorCount = GetSystemMetrics(Enum::GetValue(SmCMonitors));
        List.reserve(MonitorCount);

        auto Callback = [](HMONITOR Monitor, [[maybe_unused]] HDC DeviceContext, LPRECT Rect, LPARAM Data) -> BOOL
        {
            reinterpret_cast<std::vector<MonitorInfo>*>(Data)->emplace_back(Monitor, Rect);
            return true;
        };

        BOOL IsOk = EnumDisplayMonitors(nullptr, nullptr, Callback, reinterpret_cast<LPARAM>(&List));

        if ( not IsOk )
        {
            winrt::throw_last_error();
        }

        return List;
    }

    /// <summary>
    ///     Gets the name of the display.
    /// </summary>
    std::wstring MonitorInfo::GetName() const noexcept
    {
        return Impl->Name;
    }

    /// <summary>
    ///     Gets the display monitor rectangle, expressed in virtual-screen coordinates. Note that if the monitor is not the primary
    ///     display monitor, some of the rectangle's coordinates may be negative values.
    /// </summary>
    winrt::Windows::Foundation::Rect MonitorInfo::GetRectMonitor() const noexcept
    {
        return Impl->RectMonitor;
    }

    /// <summary>
    ///     Gets the work area rectangle of the display monitor, expressed in virtual-screen coordinates. Note that if the monitor is
    ///     not the primary display monitor, some of the rectangle's coordinates may be negative values.
    /// </summary>
    winrt::Windows::Foundation::Rect MonitorInfo::GetRectWork() const noexcept
    {
        return Impl->RectWork;
    }

    std::wstring MonitorInfo::ToString() const noexcept
    {
        return std::format(L"{} {}x{}", Impl->Name, Impl->RectMonitor.Width, Impl->RectMonitor.Height);
    }
} // namespace Mercatec::WinUIEx
