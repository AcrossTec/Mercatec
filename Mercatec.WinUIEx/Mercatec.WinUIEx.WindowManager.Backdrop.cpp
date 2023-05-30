#include "pch.h"
#include "Internal/Mercatec.WinUIEx.Internal.WindowManager.hpp"

namespace Mercatec::WinUIEx
{
    void WindowManager::Window_ThemeChanged(const FrameworkElement& Sender, const winrt::IInspectable& Args)
    {
        if ( Impl->BackdropConfiguration != nullptr )
        {
            SetConfigurationSourceTheme();
        }
    }

    void WindowManager::Window_Activated(const winrt::IInspectable& Sender, const WindowActivatedEventArgs& Args)
    {
        if ( Impl->BackdropConfiguration != nullptr )
        {
            Impl->BackdropConfiguration.IsInputActive(Args.WindowActivationState() != WindowActivationState::Deactivated);
        }
    }

    void WindowManager::Window_Closed(const winrt::IInspectable& Sender, const WindowEventArgs& Args)
    {
        // Make sure any Mica/Acrylic controller is disposed so it doesn't try to se this closed window.
        if ( Impl->CurrentController != nullptr )
        {
            Impl->CurrentController.Close();
            Impl->CurrentController = nullptr;
        }

        Impl->Window.Activated(Impl->WindowActivatedToken);
        Impl->BackdropConfiguration = nullptr;
    }

    winrt::Mercatec::WinUIEx::BackdropType WindowManager::GetBackdropType() const noexcept
    {
        return Impl->BackdropType;
    }

    void WindowManager::SetBackdropType(winrt::Mercatec::WinUIEx::BackdropType BackdropType) noexcept
    {
        if ( BackdropType == Impl->BackdropType )
        {
            return;
        }

        // Reset to default color. If the requested type is supported, we'll update to that.
        // Note: This sample completely removes any previous controller to reset to the default
        //       state. This is done so this sample can show what is expected to be the most
        //       common pattern of an app simply choosing one controller type which it sets at
        //       startup. If an app wants to toggle between Mica and Acrylic it could simply
        //       call RemoveSystemBackdropTarget() on the old controller and then setup the new
        //       controller, reusing any existing Impl->BackdropConfiguration and Activated/Closed
        //       event handlers.

        if ( Impl->CurrentController != nullptr )
        {
            Impl->CurrentController.Close();
            Impl->CurrentController = nullptr;
        }

        Impl->Window.Closed(Impl->WindowClosedToken);
        Impl->Window.Activated(Impl->WindowActivatedToken);
        Impl->Window.as<FrameworkElement>().ActualThemeChanged(Impl->WindowThemeChangedToken);

        Impl->BackdropType          = BackdropType::DefaultColor;
        Impl->BackdropConfiguration = nullptr;

        if ( BackdropType == BackdropType::Mica )
        {
            if ( TrySetMicaBackdrop(false) )
            {
                Impl->BackdropType = BackdropType;
                return;
            }
            else
            {
                // Mica isn't supported. Try Acrylic.
                BackdropType = BackdropType::DesktopAcrylic;
            }
        }

        if ( BackdropType == BackdropType::MicaAlt )
        {
            if ( TrySetMicaBackdrop(true) )
            {
                Impl->BackdropType = BackdropType;
                return;
            }
            else
            {
                // MicaAlt isn't supported. Try Acrylic.
                BackdropType = BackdropType::DesktopAcrylic;
            }
        }

        if ( BackdropType == BackdropType::DesktopAcrylic )
        {
            if ( TrySetAcrylicBackdrop() )
            {
                Impl->BackdropType = BackdropType;
                return;
            }
            else
            {
                // Acrylic isn't supported, so take the next option, which is DefaultColor, which is already set.
                // Acrylic isn't supported. Switching to default color.
            }
        }
    }

    void WindowManager::SetConfigurationSourceTheme() noexcept
    {
        switch ( Impl->Window.Content().as<FrameworkElement>().ActualTheme() )
        {
            case ElementTheme::Dark:
            {
                Impl->BackdropConfiguration.Theme(SystemBackdrops::SystemBackdropTheme::Dark);
                break;
            }
            case ElementTheme::Light:
            {
                Impl->BackdropConfiguration.Theme(SystemBackdrops::SystemBackdropTheme::Light);
                break;
            }
            case ElementTheme::Default:
            {
                Impl->BackdropConfiguration.Theme(SystemBackdrops::SystemBackdropTheme::Default);
                break;
            }
        }
    }

    bool WindowManager::TrySetMicaBackdrop(const bool UseMicaAlt) noexcept
    {
        if ( winrt::Microsoft::UI::Composition::SystemBackdrops::MicaController::IsSupported() )
        {
            // Hooking up the policy object.
            Impl->BackdropConfiguration = winrt::Microsoft::UI::Composition::SystemBackdrops::SystemBackdropConfiguration();

            Impl->WindowClosedToken       = Impl->Window.Closed({ this, &WindowManager::Window_Closed });
            Impl->WindowActivatedToken    = Impl->Window.Activated({ this, &WindowManager::Window_Activated });
            Impl->WindowThemeChangedToken = Impl->Window.Content().as<FrameworkElement>().ActualThemeChanged({ this, &WindowManager::Window_ThemeChanged });

            // Initial configuration state.
            Impl->BackdropConfiguration.IsInputActive(true);
            SetConfigurationSourceTheme();

            winrt::Microsoft::UI::Composition::SystemBackdrops::MicaController MicaController;
            MicaController.Kind(
              UseMicaAlt //
                ? winrt::Microsoft::UI::Composition::SystemBackdrops::MicaKind::BaseAlt
                : winrt::Microsoft::UI::Composition::SystemBackdrops::MicaKind::Base
            );

            // Enable the system backdrop.
            // Note: Be sure to have "using WinRT;" to support the Window.As<...>() call.
            MicaController.AddSystemBackdropTarget(Impl->Window.as<winrt::Microsoft::UI::Composition::ICompositionSupportsSystemBackdrop>());
            MicaController.SetSystemBackdropConfiguration(Impl->BackdropConfiguration);

            Impl->CurrentController = MicaController;
            return true; // Succeeded.
        }

        return false; // Mica is not supported on this system.
    }

    bool WindowManager::TrySetAcrylicBackdrop() noexcept
    {
        if ( winrt::Microsoft::UI::Composition::SystemBackdrops::DesktopAcrylicController::IsSupported() )
        {
            // Hooking up the policy object.
            Impl->BackdropConfiguration = winrt::Microsoft::UI::Composition::SystemBackdrops::SystemBackdropConfiguration();

            Impl->WindowClosedToken       = Impl->Window.Closed({ this, &WindowManager::Window_Closed });
            Impl->WindowActivatedToken    = Impl->Window.Activated({ this, &WindowManager::Window_Activated });
            Impl->WindowThemeChangedToken = Impl->Window.Content().as<FrameworkElement>().ActualThemeChanged({ this, &WindowManager::Window_ThemeChanged });

            // Initial configuration state.
            Impl->BackdropConfiguration.IsInputActive(true);
            SetConfigurationSourceTheme();

            winrt::Microsoft::UI::Composition::SystemBackdrops::DesktopAcrylicController AcrylicController;

            // Enable the system backdrop.
            // Note: Be sure to have "using WinRT;" to support the Window.As<...>() call.
            AcrylicController.AddSystemBackdropTarget(Impl->Window.as<winrt::Microsoft::UI::Composition::ICompositionSupportsSystemBackdrop>());
            AcrylicController.SetSystemBackdropConfiguration(Impl->BackdropConfiguration);

            Impl->CurrentController = AcrylicController;
            return true; // Succeeded.
        }

        return false; // Acrylic is not supported on this system
    }
} // namespace Mercatec::WinUIEx
