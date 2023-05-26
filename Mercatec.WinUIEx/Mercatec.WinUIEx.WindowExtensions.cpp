#include "pch.h"
#include "Mercatec.WinUIEx.WindowExtensions.hpp"

using namespace winrt;
using namespace Microsoft::UI;
using namespace Microsoft::UI::Xaml;
using namespace Windows::Storage::Pickers;

namespace Mercatec::WinUIEx
{
    // static void UpdateOverlappedPresenter( Microsoft.UI.Xaml.Window window, Action<OverlappedPresenter> action)
    // {
    //     if ( window is null )
    //         throw new ArgumentNullException(nameof(window));
    //     var appwindow = window.AppWindow;
    //     if ( appwindow.Presenter is OverlappedPresenter overlapped )
    //         action(overlapped);
    //     else
    //         throw new NotSupportedException($ "Not supported with a {appwindow.Presenter.Kind} presenter");
    // }

    // static T GetOverlappedPresenterValue<T>( Microsoft.UI.Xaml.Window window, Func<OverlappedPresenter?,T> action)
    // {
    //     if ( window is null )
    //         throw new ArgumentNullException(nameof(window));
    //     var appwindow = window.AppWindow;
    //     return action(appwindow.Presenter as OverlappedPresenter);
    // }

    /// <summary>
    /// Gets the native HWND pointer handle for the window
    /// </summary>
    /// <param name="window">The window to return the handle for</param>
    /// <returns>HWND handle</returns>
    HWND WindowExtensions::GetWindowHandle(const Window& Window) noexcept
    {
        if ( Window == nullptr )
        {
            throw hresult_invalid_argument(L"Argument Null Exception: Window");
        }

        // Retrieve the window handle (HWND) of the current WinUI 3 window.
        auto WindowNative{ Window.try_as<::IWindowNative>() };
        winrt::check_bool(WindowNative);

        HWND Hwnd{ nullptr };
        WindowNative->get_WindowHandle(&Hwnd);

        return Hwnd;
    }

    HRESULT WindowExtensions::GetWindowHandleFromWindowId(const WindowId& WindowId, HWND* Result) noexcept
    {
        winrt::Microsoft::UI::EnsureInteropImplLoaded();
        return winrt::Microsoft::UI::s_impl.pfnGetWindowFromWindowId(WindowId, Result);
    }
} // namespace Mercatec::WinUIEx
