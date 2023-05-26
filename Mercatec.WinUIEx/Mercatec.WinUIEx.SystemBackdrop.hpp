#pragma once

#include <winrt/Microsoft.UI.Xaml.Media.h>
#include <winrt/Microsoft.UI.Composition.SystemBackdrops.h>

namespace Mercatec::WinUIEx
{
    using MicaSystemBackdrop    = winrt::Microsoft::UI::Xaml::Media::MicaBackdrop;
    using AcrylicSystemBackdrop = winrt::Microsoft::UI::Xaml::Media::DesktopAcrylicBackdrop;

    /// <summary>
    /// Defines the Acrylic System Backdrop settings to apply to the window.
    /// </summary>
    /// <seealso cref="DesktopAcrylicController"/>
    /// <seealso cref="MicaSystemBackdrop"/>
    using winrt::Microsoft::UI::Xaml::Media::DesktopAcrylicBackdrop;

    /// <summary>
    /// Defines the Mica System Backdrop settings to apply to the window.
    /// Note: requires Windows 11 and up - Windows 10 will use fallback colors.
    /// </summary>
    /// <seealso cref="AcrylicSystemBackdrop"/>
    using winrt::Microsoft::UI::Xaml::Media::MicaBackdrop;

    /// <summary>
    /// The backdrop configuration for applying a backdrop.
    /// </summary>
    /// <seealso cref="WindowEx.Backdrop"/>
    /// <seealso cref="MicaSystemBackdrop"/>
    /// <seealso cref="AcrylicSystemBackdrop"/>
    /// <seealso cref="Microsoft.UI.Composition.SystemBackdrops.MicaController" />
    /// <seealso cref="Microsoft.UI.Composition.SystemBackdrops.DesktopAcrylicController" />
    using winrt::Microsoft::UI::Xaml::Media::SystemBackdrop;
} // namespace Mercatec::WinUIEx
