#pragma once

#include <Mercatec.WinUIEx.Exports.Api.hpp>
#include <Mercatec.WinUIEx.Windowing.MouseEvent.hpp>
#include <winrt/Windows.Foundation.h>
#include <Windows.h>
#include <optional>
#include <memory>

#pragma warning(push)
//! Compiler Warning (level 1) C4251
//! 'type' : class 'type1' needs to have dll-interface to be used by clients of class 'type2'
//! https://learn.microsoft.com/en-us/cpp/error-messages/compiler-warnings/compiler-warning-level-1-c4251?view=msvc-170
#pragma warning(disable : 4251)

namespace Mercatec::WinUIEx
{
    struct WindowMessageSink : winrt::implements<WindowMessageSink, winrt::Windows::Foundation::IInspectable>
    {
    public:
#pragma region    Members
        /// <summary>
        ///     The ID of messages that are received from the the taskbar icon.
        /// </summary>
        inline static constexpr int32_t CallbackMessageId = 0x400;

        /// <summary>
        ///     Window class ID.
        /// </summary>
        MERCATEC_WINUIEX_API std::optional<winrt::hstring> GetWindowId() const noexcept;
        __declspec(property(get = GetWindowId)) std::optional<winrt::hstring> WindowId;

        /// <summary>
        ///     Handle for the message window.
        /// </summary>
        MERCATEC_WINUIEX_API HWND GetMessageWindowHandle() const noexcept;
        __declspec(property(get = GetMessageWindowHandle)) HWND MessageWindowHandle;
#pragma endregion Members

#pragma region    Events
        /// <summary>
        ///     The custom tooltip should be closed or hidden.
        /// </summary>
        MERCATEC_WINUIEX_API winrt::event_token ChangeToolTipStateRequest(const winrt::Windows::Foundation::EventHandler<bool>& handler);
        MERCATEC_WINUIEX_API void               ChangeToolTipStateRequest(const winrt::event_token& token) noexcept;

        /// <summary>
        ///     Fired in case the user clicked or moved within the taskbar icon area.
        /// </summary>
        MERCATEC_WINUIEX_API winrt::event_token MouseEventReceived(const winrt::Windows::Foundation::EventHandler<MouseEvent>& handler);
        MERCATEC_WINUIEX_API void               MouseEventReceived(const winrt::event_token& token) noexcept;

        /// <summary>
        ///     Fired if a balloon ToolTip was either displayed or closed (indicated by the boolean flag).
        /// </summary>
        MERCATEC_WINUIEX_API winrt::event_token BalloonToolTipChanged(const winrt::Windows::Foundation::EventHandler<bool>& handler);
        MERCATEC_WINUIEX_API void               BalloonToolTipChanged(const winrt::event_token& token) noexcept;

        /// <summary>
        ///     Fired if the taskbar was created or restarted. Requires the taskbar icon to be reset.
        /// </summary>
        MERCATEC_WINUIEX_API winrt::event_token TaskbarCreated(const winrt::Windows::Foundation::EventHandler<winrt::Windows::Foundation::IInspectable>& handler);
        MERCATEC_WINUIEX_API void               TaskbarCreated(const winrt::event_token& token) noexcept;
#pragma endregion Events

#pragma region    Construction
        /// <summary>
        ///     Creates a new message sink that receives message from a given taskbar icon.
        /// </summary>
        MERCATEC_WINUIEX_API WindowMessageSink() noexcept;
        MERCATEC_WINUIEX_API WindowMessageSink(const bool AsEmpty) noexcept;
        MERCATEC_WINUIEX_API ~WindowMessageSink() noexcept;

        WindowMessageSink(const WindowMessageSink&)            = default;
        WindowMessageSink(WindowMessageSink&&)                 = default;
        WindowMessageSink& operator=(const WindowMessageSink&) = default;
        WindowMessageSink& operator=(WindowMessageSink&&)      = default;

        /// <summary>
        ///     Creates a dummy instance that provides an empty pointer rather than a real window handler.<br/>
        ///     Used at design time.
        /// </summary>
        /// <returns>
        ///     WindowMessageSink
        /// </returns>
        MERCATEC_WINUIEX_API static winrt::com_ptr<WindowMessageSink> CreateEmpty() noexcept;
#pragma endregion Construction

    private:
#pragma region    CreateMessageWindow
        /// <summary>
        ///     Creates the helper message window that is used to receive messages from the taskbar icon.
        /// </summary>
        MERCATEC_WINUIEX_API void CreateMessageWindow();
#pragma endregion CreateMessageWindow

#pragma region Handle Window    Messages
        /// <summary>
        ///     Callback method that receives messages from the taskbar area.
        /// </summary>
        MERCATEC_WINUIEX_API static LRESULT OnWindowMessageReceived(HWND Hwnd, const UINT MessageId, const WPARAM WParam, const LPARAM LParam);

        /// <summary>
        ///     Processes incoming system messages.
        /// </summary>
        /// <param name="Msg">Callback ID.</param>
        /// <param name="WParam">
        ///     If the version is Vista or higher, this parameter can be used to resolve mouse coordinates.
        ///     Currently not in use.
        /// </param>
        /// <param name="LParam">Provides information about the event.</param>
        MERCATEC_WINUIEX_API void ProcessWindowMessage(const UINT Msg, const WPARAM WParam, const LPARAM LParam);
#pragma endregion Handle Window Messages

#pragma region Members
        struct WindowMessageSinkImpl;
        std::unique_ptr<WindowMessageSinkImpl> Impl;
#pragma endregion Members
    };
} // namespace Mercatec::WinUIEx

#pragma warning(pop)
