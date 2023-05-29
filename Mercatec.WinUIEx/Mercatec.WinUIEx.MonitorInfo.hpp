#pragma once

#include "Mercatec.WinUIEx.Exports.Api.hpp"

#include <winrt/Windows.Foundation.h>

#include <Windows.h>
#include <vector>
#include <string>
#include <memory>

#pragma warning(push)
//! Compiler Warning (level 1) C4251
//! 'type' : class 'type1' needs to have dll-interface to be used by clients of class 'type2'
//! https://learn.microsoft.com/en-us/cpp/error-messages/compiler-warnings/compiler-warning-level-1-c4251?view=msvc-170
#pragma warning(disable : 4251)

namespace Mercatec::WinUIEx
{
    /// <summary>
    ///     Contains information about a display monitor.
    /// </summary>
    class MERCATEC_WINUIEX_API MonitorInfo
    {
    public:
        MonitorInfo(HMONITOR Monitor, LPCRECT Rect);
        MonitorInfo(const MonitorInfo&)            = default;
        MonitorInfo(MonitorInfo&&)                 = default;
        MonitorInfo& operator=(const MonitorInfo&) = default;
        MonitorInfo& operator=(MonitorInfo&&)      = default;
        ~MonitorInfo() noexcept                    = default;

        /// <summary>
        ///     Gets the display monitors (including invisible pseudo-monitors associated with the mirroring drivers).
        /// </summary>
        /// <returns>
        ///     A list of display monitors.
        /// </returns>
        static std::vector<MonitorInfo> GetDisplayMonitors();

        /// <summary>
        ///     Gets the name of the display.
        /// </summary>
        std::wstring GetName() const noexcept;
        __declspec(property(get = GetName)) std::wstring Name;

        /// <summary>
        ///     Gets the display monitor rectangle, expressed in virtual-screen coordinates. Note that if the monitor is not the primary
        ///     display monitor, some of the rectangle's coordinates may be negative values.
        /// </summary>
        winrt::Windows::Foundation::Rect GetRectMonitor() const noexcept;
        __declspec(property(get = GetRectMonitor)) winrt::Windows::Foundation::Rect RectMonitor;

        /// <summary>
        ///     Gets the work area rectangle of the display monitor, expressed in virtual-screen coordinates. Note that if the monitor is
        ///     not the primary display monitor, some of the rectangle's coordinates may be negative values.
        /// </summary>
        winrt::Windows::Foundation::Rect GetRectWork() const noexcept;
        __declspec(property(get = GetRectWork)) winrt::Windows::Foundation::Rect RectWork;

        std::wstring ToString() const noexcept;

    private:
        struct MonitorInfoImpl;
        std::unique_ptr<MonitorInfoImpl> Impl;
    };
} // namespace Mercatec::WinUIEx

#pragma warning(pop)
