#include "pch.h"
#include "Mercatec.WinUIEx.WindowExtensions.hpp"
#include "Mercatec.WinUIEx.HwndExtensions.hpp"
#include "Mercatec.Microsoft.UI.Windowing.hpp"

using namespace winrt;
using namespace winrt::Microsoft::UI;
using namespace winrt::Microsoft::UI::Xaml;
using namespace winrt::Microsoft::UI::Windowing;
using namespace winrt::Windows::Storage::Pickers;

using std::format;
using std::function;
using std::optional;
using std::wstring_view;

namespace Mercatec::WinUIEx
{
    static void UpdateOverlappedPresenter(const Window& Window, function<void(const OverlappedPresenter&)> Action)
    {
        if ( Window == nullptr )
        {
            throw hresult_invalid_argument(L"Argument Null Exception: Window");
        }

        if ( const auto Overlapped = Window.AppWindow().Presenter().try_as<OverlappedPresenter>() )
        {
            Action(Overlapped);
        }
        else
        {
            throw winrt::hresult_error( //
              winrt::impl::error_fail,  //
              std::format(              //
                L"NotSupportedException: Not supported with a {} presenter",
                Enum<AppWindowPresenterKind>::GetName(Window.AppWindow().Presenter().Kind())
              )
            );
        }
    }

    template <typename T>
    static T GetOverlappedPresenterValue(const Window& Window, function<T(const OverlappedPresenter&)> Action)
    {
        if ( Window == nullptr )
        {
            throw hresult_invalid_argument(L"Argument Null Exception: Window");
        }

        return Action(Window.AppWindow().Presenter().try_as<OverlappedPresenter>());
    }

    /// <summary>
    /// Gets the AppWindow from the handle
    /// </summary>
    /// <param name="window"></param>
    /// <returns></returns>
    AppWindow WindowExtensions::GetAppWindow(const Window& Window) noexcept
    {
        return Window.AppWindow();
    }

    /// <summary>Returns the dots per inch (dpi) value for the associated window.</summary>
    /// <param name = "window">The window you want to get information about.</param>
    /// <returns>The DPI for the window which depends on the <a href = "/windows/desktop/api/windef/ne-windef-dpi_awareness">DPI_AWARENESS</a> of the window. See the Remarks for more information. An invalid <i>hwnd</i> value will result in a return value of 0.</returns>
    /// <remarks>
    /// <para><see href = "https://docs.microsoft.com/windows/win32/api//winuser/nf-winuser-getdpiforwindow">Learn more about this API from docs.microsoft.com</see>.</para>
    /// </remarks>
    UINT WindowExtensions::GetDpiForWindow(const Window& Window) noexcept
    {
        return HwndExtensions::GetDpiForWindow(GetWindowHandle(Window));
    }

    /// <summary>Brings the thread that created the specified window into the foreground and activates the window.</summary>
    /// <param name="window">
    /// <para>The window that should be activated and brought to the foreground.</para>
    /// </param>
    /// <returns>
    /// <para><c>true</c> if the window was brought to the foreground.</para>
    /// <para><c>false</c> if the window was not brought to the foreground.</para>
    /// </returns>
    bool WindowExtensions::SetForegroundWindow(const Window& Window) noexcept
    {
        return HwndExtensions::SetForegroundWindow(GetWindowHandle(Window));
    }

    /// <summary>
    /// Configures whether the window should always be displayed on top of other windows or not
    /// </summary>
    /// <remarks>The presenter must be an overlapped presenter.</remarks>
    /// <exception cref="NotSupportedException">Throw if the AppWindow Presenter isn't an overlapped presenter.</exception>
    /// <param name="window">Window</param>
    /// <param name="enable">Whether to display on top</param>
    void WindowExtensions::SetIsAlwaysOnTop(const Window& Window, const bool Enable) noexcept
    {
        UpdateOverlappedPresenter(Window, [&Enable](const OverlappedPresenter& Presenter) { Presenter.IsAlwaysOnTop(Enable); });
    }

    /// <summary>
    /// Gets a value indicating whether this window is on top or not.
    /// </summary>
    /// <param name="window">window</param>
    /// <returns><c>True</c> if the overlapped presenter is on top, otherwise <c>false</c>.</returns>
    bool WindowExtensions::GetIsAlwaysOnTop(const Window& Window) noexcept
    {
        return GetOverlappedPresenterValue<bool>(
          Window,                                  //
          [](const OverlappedPresenter& Presenter) //
          {                                        //
              return Presenter == nullptr ? false : Presenter.IsAlwaysOnTop();
          }
        );
    }

    /// <summary>
    /// Enables or disables the ability to resize the window.
    /// </summary>
    /// <remarks>The presenter must be an overlapped presenter.</remarks>
    /// <exception cref="NotSupportedException">Throw if the AppWindow Presenter isn't an overlapped presenter.</exception>
    /// <param name="window"></param>
    /// <param name="enable"></param>
    void WindowExtensions::SetIsResizable(const Window& Window, const bool Enable) noexcept
    {
        UpdateOverlappedPresenter(Window, [&Enable](const OverlappedPresenter& Presenter) { Presenter.IsResizable(Enable); });
    }

    /// <summary>
    /// Gets a value indicating whether this resizable or not.
    /// </summary>
    /// <param name="window">window</param>
    /// <returns><c>True</c> if the overlapped presenter is resizeable, otherwise <c>false</c>.</returns>
    bool WindowExtensions::GetIsResizable(const Window& Window) noexcept
    {
        return GetOverlappedPresenterValue<bool>(
          Window,                                  //
          [](const OverlappedPresenter& Presenter) //
          {                                        //
              return Presenter == nullptr ? false : Presenter.IsResizable();
          }
        );
    }

    /// <summary>
    /// </summary>
    /// <remarks>The presenter must be an overlapped presenter.</remarks>
    /// <exception cref="NotSupportedException">Throw if the AppWindow Presenter isn't an overlapped presenter.</exception>
    /// <param name="window">window</param>
    /// <param name="enable"><c>true</c> if this window should be maximizable.</param>
    void WindowExtensions::SetIsMaximizable(const Window& Window, const bool Enable) noexcept
    {
        UpdateOverlappedPresenter(Window, [&Enable](const OverlappedPresenter& Presenter) { Presenter.IsMaximizable(Enable); });
    }

    /// <summary>
    /// Gets a value indicating whether this window is maximizeable or not.
    /// </summary>
    /// <param name="window">window</param>
    /// <returns><c>True</c> if the overlapped presenter is on maximizable, otherwise <c>false</c>.</returns>
    bool WindowExtensions::GetIsMaximizable(const winrt::Microsoft::UI::Xaml::Window& Window) noexcept
    {
        return GetOverlappedPresenterValue<bool>(
          Window,                                  //
          [](const OverlappedPresenter& Presenter) //
          {                                        //
              return Presenter == nullptr ? false : Presenter.IsMaximizable();
          }
        );
    }

    /// <summary>
    /// </summary>
    /// <remarks>The presenter must be an overlapped presenter.</remarks>
    /// <exception cref="NotSupportedException">Throw if the AppWindow Presenter isn't an overlapped presenter.</exception>
    /// <param name="window">window</param>
    /// <param name="enable"><c>true</c> if this window should be minimizable.</param>
    void WindowExtensions::SetIsMinimizable(const Window& Window, const bool Enable) noexcept
    {
        UpdateOverlappedPresenter(Window, [&Enable](const OverlappedPresenter& Presenter) { Presenter.IsMinimizable(Enable); });
    }

    /// <summary>
    /// Gets a value indicating whether this window is minimizeable or not.
    /// </summary>
    /// <param name="window">window</param>
    /// <returns><c>True</c> if the overlapped presenter is on minimizable, otherwise <c>false</c>.</returns>
    bool WindowExtensions::GetIsMinimizable(const Window& Window) noexcept
    {
        return GetOverlappedPresenterValue<bool>(
          Window,                                  //
          [](const OverlappedPresenter& Presenter) //
          {                                        //
              return Presenter == nullptr ? false : Presenter.IsMinimizable();
          }
        );
    }

    /// <summary>
    /// Enables or disables showing the window in the task switchers.
    /// </summary>
    /// <param name="window">window</param>
    /// <param name="enable"><c>true</c> if this window should be shown in the task switchers, otherwise <c>false</c>.</param>
    void WindowExtensions::SetIsShownInSwitchers(const Window& Window, const bool Enable) noexcept
    {
        Window.AppWindow().IsShownInSwitchers(Enable);
    }

    /// <summary>
    /// Sets the icon for the window, using the specified icon ID.
    /// </summary>
    /// <param name="window">Window</param>
    /// <param name="iconId">The ID of the icon.</param>
    void WindowExtensions::SetIcon(const Window& Window, const IconId& IconId) noexcept
    {
        HwndExtensions::SetIcon(GetWindowHandle(Window), IconId);
    }

    /// <summary>
    /// Centers the window on the current monitor
    /// </summary>
    /// <param name="window">Window</param>
    /// <param name="width">Width of the window in device independent pixels, or <c>null</c> if keeping the current size</param>
    /// <param name="height">Height of the window in device independent pixels, or <c>null</c> if keeping the current size</param>
    void WindowExtensions::CenterOnScreen(const Window& Window, const std::optional<double_t>& Width, const std::optional<double_t>& Height) noexcept
    {
        HwndExtensions::CenterOnScreen(GetWindowHandle(Window), Width, Height);
    }

    /// <summary>
    /// Positions and resizes the window
    /// </summary>
    /// <param name="window">Window</param>
    /// <param name="x">Left side of the window</param>
    /// <param name="y">Top side of the window</param>
    /// <param name="width">Width of the window in device independent pixels.</param>
    /// <param name="height">Height of the window in device independent pixels.</param>
    void WindowExtensions::MoveAndResize(const Window& Window, const double_t X, const double_t Y, const double_t Width, const double_t Height) noexcept
    {
        const double_t Scale = HwndExtensions::GetDpiForWindow(GetWindowHandle(Window)) / 96.0;
        Window.AppWindow().MoveAndResize({ .X = int32_t(X), .Y = int32_t(Y), .Width = int32_t(Width * Scale), .Height = int32_t(Height * Scale) });
    }

    /// <summary>
    /// Positions the window
    /// </summary>
    /// <param name="window">Window</param>
    /// <param name="x">Left side of the window</param>
    /// <param name="y">Top side of the window</param>
    void WindowExtensions::Move(const Window& Window, const int32_t X, const int32_t Y) noexcept
    {
        Window.AppWindow().MoveAndResize({ X, Y, Window.AppWindow().Size().Width, Window.AppWindow().Size().Height });
    }

    /// <summary>
    /// Sets the width and height of the window in device-independent pixels.
    /// </summary>
    /// <param name="window">Window to set the size for.</param>
    /// <param name="width">Width of the window in device-independent units.</param>
    /// <param name="height">Height of the window in device-independent units.</param>
    void WindowExtensions::SetWindowSize(const Window& Window, const double_t Width, const double_t Height) noexcept
    {
        const double_t Scale = HwndExtensions::GetDpiForWindow(GetWindowHandle(Window)) / 96.0;
        Window.AppWindow().Resize({ int32_t(Width * Scale), int32_t(Height * Scale) });
    }

    /// <summary>
    /// Sets the window presenter kind used.
    /// </summary>
    /// <param name="window"></param>
    /// <param name="kind"></param>
    /// <returns></returns>
    void WindowExtensions::SetWindowPresenter(const Window& Window, const AppWindowPresenterKind Kind) noexcept
    {
        Window.AppWindow().SetPresenter(Kind);
    }

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
        Microsoft::UI::EnsureInteropImplLoaded();
        return Microsoft::UI::s_impl.pfnGetWindowFromWindowId(WindowId, Result);
    }

    /// <summary>
    /// Gets the window HWND handle from a Window ID.
    /// </summary>
    /// <param name="windowId">Window ID to get handle from</param>
    /// <returns>Window HWND handle</returns>
    HWND WindowExtensions::GetWindowHandle(const WindowId& WindowId) noexcept
    {
        return Microsoft::UI::GetWindowFromWindowId(WindowId);
    }

    /// <summary>
    /// Gets the AppWindow from an HWND
    /// </summary>
    /// <param name="hwnd"></param>
    /// <returns>AppWindow</returns>
    AppWindow WindowExtensions::GetAppWindowFromWindowHandle(HWND Hwnd) noexcept
    {
        if ( Hwnd == nullptr )
        {
            throw hresult_invalid_argument(L"Argument Null Exception: Hwnd");
        }

        WindowId WindowId = Microsoft::UI::GetWindowIdFromWindow(Hwnd);
        return AppWindow::GetFromWindowId(WindowId);
    }

    /// <summary>
    /// Activates the window and displays it in its current size and position.
    /// </summary>
    /// <param name="window">Window</param>
    /// <returns><c>true</c> if the window was previously visible, or <c>false</c> if the window was previously hidden.</returns>
    bool WindowExtensions::Show(const Window& Window) noexcept
    {
        return HwndExtensions::ShowWindow(GetWindowHandle(Window));
    }

    /// <summary>
    /// Hides the window and activates another window.
    /// </summary>
    /// <param name="window">Window</param>
    /// <returns><c>true</c> if the window was previously visible, or <c>false</c> if the window was previously hidden.</returns>
    bool WindowExtensions::Hide(const Window& Window) noexcept
    {
        return HwndExtensions::HideWindow(GetWindowHandle(Window));
    }

    /// <summary>
    /// Maximizes the specified window.
    /// </summary>
    /// <remarks>The presenter must be an overlapped presenter.</remarks>
    /// <exception cref="NotSupportedException">Throw if the AppWindow Presenter isn't an overlapped presenter.</exception>
    /// <param name="window">Window</param>
    void WindowExtensions::Maximize(const Window& Window) noexcept
    {
        UpdateOverlappedPresenter(Window, [](const OverlappedPresenter& Presenter) { Presenter.Maximize(); });
    }

    /// <summary>
    /// Minimizes the specified window and activates the next top-level window in the Z order.
    /// </summary>
    /// <remarks>The presenter must be an overlapped presenter.</remarks>
    /// <exception cref="NotSupportedException">Throw if the AppWindow Presenter isn't an overlapped presenter.</exception>
    /// <param name="window">Window</param>
    void WindowExtensions::Minimize(const Window& Window) noexcept
    {
        UpdateOverlappedPresenter(Window, [](const OverlappedPresenter& Presenter) { Presenter.Minimize(); });
    }

    /// <summary>
    /// Activates and displays the window. If the window is minimized or maximized, the system restores
    /// it to its original size and position.
    /// </summary>
    /// <remarks>The presenter must be an overlapped presenter.</remarks>
    /// <exception cref="NotSupportedException">Throw if the AppWindow Presenter isn't an overlapped presenter.</exception>
    /// <param name="window">Window</param>
    void WindowExtensions::Restore(const Window& Window) noexcept
    {
        UpdateOverlappedPresenter(Window, [](const OverlappedPresenter& Presenter) { Presenter.Restore(); });
    }

    /// <summary>
    /// Sets the icon for the window, using the specified icon path.
    /// </summary>
    /// <param name="window">Window</param>
    /// <param name="iconPath">The path of the icon.</param>
    void WindowExtensions::SetIcon(const Window& Window, const std::wstring_view IconPath) noexcept
    {
        HwndExtensions::SetIcon(GetWindowHandle(Window), IconPath);
    }

    /// <summary>
    /// Sets the task bar icon to the provided icon
    /// </summary>
    /// <param name="window">Window</param>
    /// <param name="icon">Icon</param>
    void WindowExtensions::SetTaskBarIcon(const Window& Window, const std::optional<Icon>& Icon) noexcept
    {
        HwndExtensions::SetTaskBarIcon(GetWindowHandle(Window), Icon);
    }

    /// <summary>
    /// Gets the background color for the title bar and all its buttons and their states.
    /// </summary>
    /// <param name="window">window</param>
    /// <param name="color">color</param>
    void WindowExtensions::SetTitleBarBackgroundColors(const Window& Window, const winrt::Windows::UI::Color& Color) noexcept
    {
        const AppWindow AppWindow = Window.AppWindow();

        if ( AppWindowTitleBar::IsCustomizationSupported() )
        {
            AppWindow.TitleBar().ButtonBackgroundColor(Color);
            AppWindow.TitleBar().BackgroundColor(Color);
            AppWindow.TitleBar().ButtonInactiveBackgroundColor(Color);
            AppWindow.TitleBar().ButtonPressedBackgroundColor(Color);
            AppWindow.TitleBar().InactiveBackgroundColor(Color);
        }
    }

} // namespace Mercatec::WinUIEx
