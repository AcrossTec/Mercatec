// Copyright (c) Microsoft Corporation and Contributors.
// Licensed under the MIT License.

#include "pch.h"
#include "LoginPage.xaml.h"
#if __has_include("LoginPage.g.cpp")
# include "LoginPage.g.cpp"
#endif

#pragma warning(push)

//! https://learn.microsoft.com/en-us/cpp/code-quality/c26811?view=msvc-170
//! https://learn.microsoft.com/en-us/windows/uwp/cpp-and-winrt-apis/concurrency#parameter-passing
//! Warning C26811 Lifetime of the memory referenced by parameter ''args'' might end by the time the coroutine is resumed(lifetime .1)
#pragma warning(disable : 26811)

using namespace winrt;
using namespace winrt::Microsoft::UI::Xaml;
using namespace Cxx::DesignPatterns;
using namespace std::chrono_literals;

using ::Mercatec::Helpers::AnimationExtensions;

// To learn more about WinUI, the WinUI project structure,
// and more about our project templates, see: http://aka.ms/winui-project-info.

namespace winrt::Mercatec::Application::implementation
{
    LoginPage::LoginPage() noexcept
      : m_ViewModel{ ServiceLocator::Default().GetService<ViewModels::LoginViewModel>() }
      , m_EffectMode{ EffectMode::None }
    {
        InitializeContext();
        InitializeComponent();
        InitializeBindings();
    }

    ViewModels::LoginViewModel LoginPage::ViewModel() const noexcept
    {
        return m_ViewModel;
    }

    void LoginPage::InitializeContext()
    {
        auto Context = ServiceLocator::Default().GetService<Helpers::Services::IContextService>();
        Context.Initialize(DispatcherQueue());
    }

    void LoginPage::InitializeNavigation()
    {
        auto Navigation = ServiceLocator::Default().GetService<Helpers::Services::INavigationService>();
        Navigation.Initialize(Frame());
    }

    void LoginPage::InitializeBindings()
    {
        // ViewModel.UserName
        {
            Microsoft::UI::Xaml::Data::Binding Binding;
            Binding.Source(ViewModel());
            Binding.Path(Microsoft::UI::Xaml::PropertyPath{ L"UserName" });
            Binding.Mode(Microsoft::UI::Xaml::Data::BindingMode::TwoWay);
            Binding.UpdateSourceTrigger(Microsoft::UI::Xaml::Data::UpdateSourceTrigger::PropertyChanged);
            PasswordView().SetBinding(NamePasswordControl::UserNameProperty(), Binding);
            PasswordView().RegisterPropertyChangedCallback(
              NamePasswordControl::UserNameProperty(),
              [this](const DependencyObject& Sender, const DependencyProperty& Property)
              {
                  // Update Two Way binding
                  const hstring user_name = unbox_value<hstring>(Sender.GetValue(Property));
                  ViewModel().UserName(user_name);
              }
            );
        }

        // ViewModel.Password
        {
            Microsoft::UI::Xaml::Data::Binding Binding;
            Binding.Source(ViewModel());
            Binding.Path(Microsoft::UI::Xaml::PropertyPath{ L"Password" });
            Binding.Mode(Microsoft::UI::Xaml::Data::BindingMode::TwoWay);
            Binding.UpdateSourceTrigger(Microsoft::UI::Xaml::Data::UpdateSourceTrigger::PropertyChanged);
            PasswordView().SetBinding(NamePasswordControl::PasswordProperty(), Binding);
            PasswordView().RegisterPropertyChangedCallback(
              NamePasswordControl::PasswordProperty(),
              [this](const DependencyObject& Sender, const DependencyProperty& Property)
              {
                  // Update Two Way binding
                  const hstring password = unbox_value<hstring>(Sender.GetValue(Property));
                  ViewModel().Password(password);
              }
            );
        }
    }

    fire_and_forget LoginPage::OnNavigatedTo(const Microsoft::UI::Xaml::Navigation::NavigationEventArgs& Args)
    {
        m_EffectMode = EffectMode::None;
        co_await ViewModel().LoadAsync(Args.Parameter().as<Helpers::ViewModels::ShellArgs>());
        InitializeNavigation();
    }

    fire_and_forget LoginPage::OnKeyDown(const Microsoft::UI::Xaml::Input::KeyRoutedEventArgs& Args)
    {
        if ( Args.Key() == Windows::System::VirtualKey::Enter )
        {
            DoEffectOut();
            co_await 100ms;
            co_await wil::resume_foreground(DispatcherQueue());
            ViewModel().Login();
        }

        base_type::OnKeyDown(Args);
    }

    fire_and_forget LoginPage::OnShowLoginWithPassword([[maybe_unused]] const IInspectable& Sender, [[maybe_unused]] const RoutedEventArgs& Args)
    {
        co_await 100ms;
        co_await wil::resume_foreground(DispatcherQueue());
        PasswordView().Focus();
    }

    void LoginPage::OnBackgroundFocus([[maybe_unused]] const IInspectable& Sender, [[maybe_unused]] const RoutedEventArgs& Args)
    {
        DoEffectIn();
    }

    void LoginPage::OnForegroundFocus([[maybe_unused]] const IInspectable& Sender, [[maybe_unused]] const RoutedEventArgs& Args)
    {
        DoEffectOut();
    }

    void LoginPage::DoEffectIn([[maybe_unused]] const double_t MilliSeconds)
    {
        if ( m_EffectMode == EffectMode::Foreground or m_EffectMode == EffectMode::None )
        {
            m_EffectMode = EffectMode::Background;

            AnimationExtensions::Scale(BackgroundBorder(), MilliSeconds, 1.0, 1.1);
            AnimationExtensions::Blur(BackgroundBorder(), MilliSeconds, 6.0, 0.0);
            AnimationExtensions::Scale(ForegroundStackPanel(), 500, 1.0, 0.95);
            AnimationExtensions::Fade(ForegroundStackPanel(), MilliSeconds, 1.0, 0.75);
        }
    }

    void LoginPage::DoEffectOut([[maybe_unused]] const double_t MilliSeconds)
    {
        if ( m_EffectMode == EffectMode::Background or m_EffectMode == EffectMode::None )
        {
            m_EffectMode = EffectMode::Foreground;

            AnimationExtensions::Scale(BackgroundBorder(), MilliSeconds, 1.1, 1.0);
            AnimationExtensions::Blur(BackgroundBorder(), MilliSeconds, 0.0, 6.0);
            AnimationExtensions::Scale(ForegroundStackPanel(), 500, 0.95, 1.0);
            AnimationExtensions::Fade(ForegroundStackPanel(), MilliSeconds, 0.75, 1.0);
        }
    }
} // namespace winrt::Mercatec::Application::implementation

#pragma warning(pop)