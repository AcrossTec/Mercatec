#pragma once

#include "SplashScreen.g.h"

#include <winrt/Microsoft.UI.Dispatching.h>
#include <winrt/Microsoft.UI.Xaml.h>
#include <winrt/Windows.UI.Xaml.Interop.h>

namespace winrt::Mercatec::WinUIEx::implementation
{
    /// <summary>
    ///     A splash screen window that shows with no chrome, and once <see cref="SplashScreen.OnLoading"/> has completed,
    ///     opens a new window.
    /// </summary>
    struct SplashScreen : SplashScreenT<SplashScreen>
    {
    public:
        /// <summary>
        ///     Creates and activates a new splashscreen, and opens the specified window once complete.
        /// </summary>
        /// <param name="window">Window to open once splash screen is complete</param>
        SplashScreen(const CreateWindowDelegate& Factory);

        /// <summary>
        ///     Gets or sets the system backdrop of the window.
        ///     Note: Windows 10 doesn't support these, so will fall back to default backdrop.
        /// </summary>
        WinUIEx::BackdropType BackdropType() const noexcept;
        void                  BackdropType(const WinUIEx::BackdropType Value) noexcept;

        /// <summary>
        ///     Override to display loading progress or delay loading of main window
        /// </summary>
        /// <returns></returns>
        virtual Windows::Foundation::IAsyncAction OnLoading();

        /// <summary>
        /// Gets or sets the width of the splash screen. Set to NaN to size for content
        /// </summary>
        double_t Width() const noexcept;
        void     Width(const double_t Value) noexcept;

        /// <summary>
        /// Gets or sets the height of the splash screen. Set to NaN to size for content
        /// </summary>
        double_t Height() const noexcept;
        void     Height(const double_t Value) noexcept;

        /// <summary>
        /// Gets or sets a value indicating whether the splash screen should be top-most
        /// </summary>
        bool IsAlwaysOnTop() const noexcept;
        void IsAlwaysOnTop(const bool Value) noexcept;

        /// <summary>
        ///     Raised once the splash screen has completed <see cref="OnLoading"/>.
        /// </summary>
        winrt::event_token Completed(const Windows::Foundation::EventHandler<Microsoft::UI::Xaml::Window>& Handler);
        void               Completed(const event_token& Token) noexcept;

    private:
        fire_and_forget Content_Loaded(const IInspectable& Sender, const Microsoft::UI::Xaml::RoutedEventArgs& Args);
        void            SplashScreen_Activated(const IInspectable& Sender, const Microsoft::UI::Xaml::WindowActivatedEventArgs& Args);

    private:
        Mercatec::WinUIEx::CreateWindowDelegate                               m_CreateWindow;
        Mercatec::WinUIEx::WindowManager                                      m_Manager;
        event<Windows::Foundation::EventHandler<Microsoft::UI::Xaml::Window>> m_Completed;
        event_token                                                           m_SplashScreenActivatedToken;
        double_t                                                              m_Width;
        double_t                                                              m_Height;
        bool                                                                  m_IsAlwaysOnTop;
    };
} // namespace winrt::Mercatec::WinUIEx::implementation

namespace winrt::Mercatec::WinUIEx::factory_implementation
{
    struct SplashScreen : SplashScreenT<SplashScreen, implementation::SplashScreen>
    {
    };
} // namespace winrt::Mercatec::WinUIEx::factory_implementation
