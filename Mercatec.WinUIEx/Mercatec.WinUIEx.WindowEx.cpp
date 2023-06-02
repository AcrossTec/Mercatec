#include "pch.h"
#include "Mercatec.WinUIEx.WindowEx.h"
#if __has_include("WindowEx.g.cpp")
# include "WindowEx.g.cpp"
#endif

#include "Mercatec.WinUIEx.HwndExtensions.hpp"
#include "Mercatec.WinUIEx.WindowExtensions.hpp"
#include "Internal/Mercatec.WinUIEx.Internal.Icon.hpp"

using namespace winrt::Microsoft::UI::Xaml;
using namespace winrt::Microsoft::UI::Xaml::Controls;
using namespace winrt::Microsoft::UI::Xaml::Markup;
using namespace winrt::Microsoft::UI::Windowing;

using namespace winrt::Windows::UI::Popups;
using namespace winrt::Windows::Foundation;
using namespace winrt::Windows::Graphics;

using Mercatec::WinUIEx::Enum;
using Mercatec::WinUIEx::HwndExtensions;
using Mercatec::WinUIEx::WindowExtensions;

namespace winrt::Mercatec::WinUIEx::implementation
{
    /// <summary>
    ///     Initializes a new instance of the <see cref="WindowEx"/> class.
    /// </summary>
    WindowEx::WindowEx()
      : m_Manager{ WindowManager::Get(*this) }
      , m_IconArea{}
      , m_TitleBarArea{}
      , m_TitleBarContainer{}
      , m_WindowArea{}
      , m_TaskBarIcon{ nullptr }
      , m_PropChangedCallbackId{ 0 }
    {
        m_Manager.PresenterChanged(
          [this](const auto&, const auto& Args)
          {
              OnPresenterChanged(Presenter());
              m_PresenterChanged(*this, Args);
          }
        );

        m_Manager.PositionChanged(
          [this](const auto&, const auto& Args)
          {
              OnPositionChanged(Args);
              m_PositionChanged(*this, Args);
          }
        );

        m_Manager.ZOrderChanged(
          [this](const auto&, const auto& Args)
          {
              OnZOrderChanged(Args);
              m_ZOrderChanged(*this, Args);
          }
        );

        SizeChanged([this](const auto&, const auto& Args) { OnSizeChanged(Args); });

        Grid RootContent;
        {
            RowDefinition Row1;
            Row1.Height({ 0, GridUnitType::Auto });
            Row1.MinHeight(0);

            RowDefinition Row2;
            Row1.Height({ 0, GridUnitType::Star });

            RootContent.RowDefinitions().Append(Row1);
            RootContent.RowDefinitions().Append(Row2);
        }
        {
            ColumnDefinition Column1;
            Column1.Width({ 0, GridUnitType::Auto });

            ColumnDefinition Column2;
            Column2.Width({ 0, GridUnitType::Star });

            m_TitleBarArea.Visibility(Visibility::Collapsed);
            m_TitleBarArea.ColumnDefinitions().Append(Column1);
            m_TitleBarArea.ColumnDefinitions().Append(Column2);
            RootContent.Children().Append(m_TitleBarArea);
        }
        {
            m_IconArea.VerticalAlignment(VerticalAlignment::Center);
            m_TitleBarArea.Children().Append(m_IconArea);
        }
        {
            m_TitleBarContainer.VerticalAlignment(VerticalAlignment::Stretch);
            m_TitleBarContainer.VerticalContentAlignment(VerticalAlignment::Stretch);

            Grid::SetColumn(m_TitleBarContainer, 1);
            m_TitleBarArea.Children().Append(m_TitleBarContainer);
        }
        {
            m_WindowArea.HorizontalContentAlignment(HorizontalAlignment::Stretch);
            m_WindowArea.VerticalContentAlignment(VerticalAlignment::Stretch);

            Grid::SetRow(m_WindowArea, 1);
            RootContent.Children().Append(m_WindowArea);
        }

        this->Content(RootContent);
    }

    IAsyncAction WindowEx::ShowMessageDialogAsync(const std::wstring_view Content)
    {
        co_await ShowMessageDialogAsync(Content, nullptr, 0, 1, L"");
    }

    /// <summary>
    ///     Shows a message dialog.
    /// </summary>
    /// <param name="Content">The message displayed to the user.</param>
    /// <param name="Title">The title to display on the dialog, if any.</param>
    /// <returns>An object that represents the asynchronous operation.</returns>
    IAsyncAction WindowEx::ShowMessageDialogAsync(const std::wstring_view Content, const std::wstring_view Title)
    {
        co_await ShowMessageDialogAsync(Content, nullptr, 0, 1, Title);
    }

    IAsyncOperation<IUICommand> WindowEx::ShowMessageDialogAsync(const std::wstring_view Content, const IVector<IUICommand>& Commands)
    {
        return ShowMessageDialogAsync(Content, Commands, 0, 1, L"");
    }

    IAsyncOperation<IUICommand> WindowEx::ShowMessageDialogAsync(const std::wstring_view Content, const IVector<IUICommand>& Commands, const std::wstring_view Title)
    {
        return ShowMessageDialogAsync(Content, Commands, 0, 1, Title);
    }

    IAsyncOperation<IUICommand> WindowEx::ShowMessageDialogAsync(const std::wstring_view Content, const IVector<IUICommand>& Commands, const uint32_t DefaultCommandIndex)
    {
        return ShowMessageDialogAsync(Content, Commands, DefaultCommandIndex, 1, L"");
    }

    IAsyncOperation<IUICommand> WindowEx::ShowMessageDialogAsync(const std::wstring_view Content, const IVector<IUICommand>& Commands, const uint32_t DefaultCommandIndex, const std::wstring_view Title)
    {
        return ShowMessageDialogAsync(Content, Commands, DefaultCommandIndex, 1, Title);
    }

    IAsyncOperation<IUICommand> WindowEx::ShowMessageDialogAsync(const std::wstring_view Content, const IVector<IUICommand>& Commands, const uint32_t DefaultCommandIndex, const uint32_t CancelCommandIndex)
    {
        return ShowMessageDialogAsync(Content, Commands, DefaultCommandIndex, CancelCommandIndex, L"");
    }

    /// <summary>
    ///     Shows a message dialog.
    /// </summary>
    /// <param name="Content">The message displayed to the user.</param>
    /// <param name="Commands">an array of commands that appear in the command bar of the message dialog. These commands makes the dialog actionable.</param>
    /// <param name="DefaultCommandIndex">The index of the command you want to use as the default. This is the command that fires by default when users press the ENTER key.</param>
    /// <param name="CancelCommandIndex">The index of the command you want to use as the cancel command. This is the command that fires when users press the ESC key.</param>
    /// <param name="Title">The title to display on the dialog, if any.</param>
    /// <returns>An object that represents the asynchronous operation.</returns>
    IAsyncOperation<IUICommand> WindowEx::ShowMessageDialogAsync(const std::wstring_view Content, const IVector<IUICommand>& Commands, const uint32_t DefaultCommandIndex, const uint32_t CancelCommandIndex, const std::wstring_view Title)
    {
        if ( Commands != nullptr and Commands.Size() > 3 )
        {
            throw hresult_invalid_argument(L"Invalid Operation Exception: A maximum of 3 commands can be specified.");
        }

        IUICommand DefaultCommand   = UICommand(L"OK");
        IUICommand SecondaryCommand = nullptr;
        IUICommand CancelCommand    = nullptr;

        if ( Commands != nullptr )
        {
            DefaultCommand = Commands.Size() > DefaultCommandIndex ? Commands.GetAt(DefaultCommandIndex) : (Commands.Size() > 0 ? Commands.GetAt(0) : DefaultCommand);
            CancelCommand  = Commands.Size() > CancelCommandIndex ? Commands.GetAt(CancelCommandIndex) : nullptr;

            auto Query = std::views::all(Commands) //
                       | std::views::filter([&](const auto& Command) { return Command != DefaultCommand and Command != CancelCommand; });
            SecondaryCommand = Query.begin() != Query.end() ? Query.front() : nullptr;
        }

        ContentDialog Dialog;
        Dialog.XamlRoot(this->Content().XamlRoot());

        if ( FrameworkElement Element = this->Content().try_as<FrameworkElement>() )
        {
            Dialog.RequestedTheme(Element.RequestedTheme());
        }

        {
            TextBlock TxtBlock;
            TxtBlock.Text(Content);
            TxtBlock.TextWrapping(TextWrapping::Wrap);

            Dialog.Content(TxtBlock);
            Dialog.Title(box_value(Title));
            Dialog.PrimaryButtonText(DefaultCommand.Label());
        }

        if ( SecondaryCommand != nullptr )
        {
            Dialog.SecondaryButtonText(SecondaryCommand.Label());
        }

        if ( CancelCommand != nullptr )
        {
            Dialog.CloseButtonText(CancelCommand.Label());
        }

        auto DialogTask = Dialog.ShowAsync(ContentDialogPlacement::InPlace);
        this->BringToFront();

        auto Result = co_await DialogTask;

        switch ( Result )
        {
            case ContentDialogResult::Primary:
            {
                co_return DefaultCommand;
            }
            case ContentDialogResult::Secondary:
            {
                co_return SecondaryCommand;
            }
            case ContentDialogResult::None:
            default:
            {
                co_return CancelCommand ? CancelCommand : UICommand();
            }
        }
    }

    /*
        /// <summary>
        ///     Gets a reference to the AppWindow for the app.
        /// </summary>
        AppWindow WindowEx::AppWindow() const noexcept
        {
            return base_type::AppWindow();
        }
    */

    /// <summary>
    ///     Brings the window to the front.
    /// </summary>
    /// <returns></returns>
    bool WindowEx::BringToFront() const noexcept
    {
        return WindowExtensions::SetForegroundWindow(*this);
    }

    /// <summary>
    ///     Gets or sets the task bar icon.
    /// </summary>
    Icon WindowEx::TaskBarIcon() const noexcept
    {
        return m_TaskBarIcon;
    }

    void WindowEx::TaskBarIcon(const Icon& Value) noexcept
    {
        m_TaskBarIcon = Value;
        WindowExtensions::SetTaskBarIcon(*this, reinterpret_cast<::Mercatec::WinUIEx::Internal::Icon*>(Value.NativeIcon()));
    }

    /*
        /// <summary>
        ///     Gets or sets the window title.
        ///     Old Workaround for https://github.com/microsoft/microsoft-ui-xaml/issues/3689.
        ///     Needs to stay for binary compat.
        /// </summary>
        hstring WindowEx::Title() const noexcept
        {
            return base_type::Title();
        }

        void WindowEx::Title(const std::wstring_view Value) noexcept
        {
            base_type::Title(Value);
        }
    */

    /// <summary>
    ///     Gets or sets a unique ID used for saving and restoring window size and position across sessions.
    /// </summary>
    /// <remarks>
    ///     The ID must be set before the window activates.
    ///     The window size and position will only be restored if the monitor layout hasn't changed between application settings.
    ///     The property uses ApplicationData storage, and therefore is currently only functional for packaged applications.
    /// </remarks>
    hstring WindowEx::PersistenceId() const noexcept
    {
        return m_Manager.PersistenceId();
    }

    void WindowEx::PersistenceId(const std::wstring_view Value) noexcept
    {
        m_Manager.PersistenceId(Value);
    }

    /// <summary>
    ///     Gets or sets the Window content.
    /// </summary>
    /// <value>The window content.</value>
    IInspectable WindowEx::WindowContent() const noexcept
    {
        return m_WindowArea.Content();
    }

    void WindowEx::WindowContent(const IInspectable& Content) noexcept
    {
        if ( auto OldElement = m_WindowArea.Content().try_as<FrameworkElement>() )
        {
            if ( m_PropChangedCallbackId != 0 )
            {
                OldElement.UnregisterPropertyChangedCallback(FrameworkElement::RequestedThemeProperty(), m_PropChangedCallbackId);
                m_PropChangedCallbackId = 0;
            }
        }

        m_WindowArea.Content(Content);

        if ( auto NewElement = m_WindowArea.Content().try_as<FrameworkElement>() )
        {
            m_PropChangedCallbackId = NewElement.RegisterPropertyChangedCallback(FrameworkElement::RequestedThemeProperty(), { this, &WindowEx::RequestedThemePropertyChanged });
        }
    }

    bool WindowEx::IsTitleBarVisible() const noexcept
    {
        return m_Manager.IsTitleBarVisible();
    }

    void WindowEx::IsTitleBarVisible(const bool Value) noexcept
    {
        m_Manager.IsTitleBarVisible(Value);
    }

    bool WindowEx::IsMinimizable() const noexcept
    {
        return m_Manager.IsMinimizable();
    }

    void WindowEx::IsMinimizable(const bool Value) noexcept
    {
        m_Manager.IsMinimizable(Value);
    }

    bool WindowEx::IsMaximizable() const noexcept
    {
        return m_Manager.IsMaximizable();
    }

    void WindowEx::IsMaximizable(const bool Value) noexcept
    {
        m_Manager.IsMaximizable(Value);
    }

    bool WindowEx::IsResizable() const noexcept
    {
        return m_Manager.IsResizable();
    }

    void WindowEx::IsResizable(const bool Value) noexcept
    {
        m_Manager.IsResizable(Value);
    }

    bool WindowEx::IsModal() const noexcept
    {
        return false; // OverlappedPresenter.IsModal();
    }

    void WindowEx::IsModal([[maybe_unused]] const bool Value) noexcept
    {
        // OverlappedPresenter.IsModal(Value)
    }

    bool WindowEx::IsShownInSwitchers() const noexcept
    {
        return m_Manager.AppWindow().IsShownInSwitchers();
    }

    void WindowEx::IsShownInSwitchers(const bool Value) noexcept
    {
        m_Manager.AppWindow().IsShownInSwitchers(Value);
    }

    bool WindowEx::IsAlwaysOnTop() const noexcept
    {
        return m_Manager.IsAlwaysOnTop();
    }

    void WindowEx::IsAlwaysOnTop(const bool Value) noexcept
    {
        m_Manager.IsAlwaysOnTop(Value);
    }

    AppWindowPresenter WindowEx::Presenter() const noexcept
    {
        return m_Manager.AppWindow().Presenter();
    }

    AppWindowPresenterKind WindowEx::PresenterKind() const noexcept
    {
        return m_Manager.PresenterKind();
    }

    void WindowEx::PresenterKind(const AppWindowPresenterKind Value) noexcept
    {
        m_Manager.PresenterKind(Value);
    }

    double_t WindowEx::Width() const noexcept
    {
        return m_Manager.Width();
    }

    void WindowEx::Width(const double_t Value) noexcept
    {
        m_Manager.Width(Value);
    }

    double_t WindowEx::Height() const noexcept
    {
        return m_Manager.Height();
    }

    void WindowEx::Height(const double_t Value) noexcept
    {
        m_Manager.Height(Value);
    }

    double_t WindowEx::MinWidth() const noexcept
    {
        return m_Manager.MinWidth();
    }

    void WindowEx::MinWidth(const double_t Value) noexcept
    {
        m_Manager.MinWidth(Value);
    }

    double_t WindowEx::MinHeight() const noexcept
    {
        return m_Manager.MinHeight();
    }

    void WindowEx::MinHeight(const double_t Value) noexcept
    {
        m_Manager.MinHeight(Value);
    }

    double_t WindowEx::MaxWidth() const noexcept
    {
        return m_Manager.MaxWidth();
    }

    void WindowEx::MaxWidth(const double_t Value) noexcept
    {
        m_Manager.MaxWidth(Value);
    }

    double_t WindowEx::MaxHeight() const noexcept
    {
        return m_Manager.MaxHeight();
    }

    void WindowEx::MaxHeight(const double_t Value) noexcept
    {
        m_Manager.MaxHeight(Value);
    }

    WinUIEx::BackdropType WindowEx::BackdropType() const noexcept
    {
        return m_Manager.BackdropType();
    }

    void WindowEx::BackdropType(const WinUIEx::BackdropType Value) noexcept
    {
        m_Manager.BackdropType(Value);
    }

    event_token WindowEx::PositionChanged(const EventHandler<PointInt32>& Handler)
    {
        return m_PositionChanged.add(Handler);
    }

    void WindowEx::PositionChanged(const event_token& Token) noexcept
    {
        m_PositionChanged.remove(Token);
    }

    void WindowEx::OnPositionChanged([[maybe_unused]] const PointInt32& Position)
    {
    }

    event_token WindowEx::PresenterChanged(const EventHandler<AppWindowPresenter>& Handler)
    {
        return m_PresenterChanged.add(Handler);
    }

    void WindowEx::PresenterChanged(const event_token& Token) noexcept
    {
        m_PresenterChanged.remove(Token);
    }

    void WindowEx::OnPresenterChanged([[maybe_unused]] const AppWindowPresenter& NewPresenter)
    {
    }

    event_token WindowEx::ZOrderChanged(const EventHandler<ZOrderInfo>& Handler)
    {
        return m_ZOrderChanged.add(Handler);
    }

    void WindowEx::ZOrderChanged(const event_token& Token) noexcept
    {
        m_ZOrderChanged.remove(Token);
    }

    void WindowEx::OnZOrderChanged([[maybe_unused]] const ZOrderInfo& Info)
    {
    }

    /// <summary>
    ///     Called when the size of the window changes.
    /// </summary>
    /// <param name="newSize">The new size of the window in device independent units.</param>
    /// <returns>True if the resize event should be marked handled.</returns>
    /// <remarks>
    ///     While this event is equivalent to the <see cref="Window.SizeChanged"/> event,
    ///     the units provided here are in device independent units and not screen pixels.
    /// </remarks>
    bool WindowEx::OnSizeChanged([[maybe_unused]] const Size& NewSize)
    {
        return false;
    }

    void WindowEx::OnThemeChanged([[maybe_unused]] const ElementTheme Theme)
    {
    }

    ElementTheme WindowEx::ActualTheme() const noexcept
    {
        switch ( Application::Current().RequestedTheme() )
        {
            case ApplicationTheme::Dark:
            {
                return ElementTheme::Dark;
            }

            case ApplicationTheme::Light:
            {
                return ElementTheme::Light;
            }
        }

        return ElementTheme::Default;
    }

    void WindowEx::RequestedThemePropertyChanged([[maybe_unused]] const DependencyObject& Sender, [[maybe_unused]] const DependencyProperty& Property)
    {
        auto Element      = this->Content().try_as<FrameworkElement>();
        auto ChildElement = m_WindowArea.Content().try_as<FrameworkElement>();

        if ( Element and ChildElement )
        {
            Element.RequestedTheme(ChildElement.RequestedTheme());
        }
    }

    void WindowEx::OnSizeChanged(const WindowSizeChangedEventArgs& Args)
    {
        [[maybe_unused]] const UINT Dpi = WindowExtensions::GetDpiForWindow(*this);

        if ( OnSizeChanged(Args.Size()) )
        {
            Args.Handled(true);
        }
    }
} // namespace winrt::Mercatec::WinUIEx::implementation
