// Copyright (c) Microsoft Corporation and Contributors.
// Licensed under the MIT License.

#include "pch.h"
#include "LoginPage.xaml.h"
#if __has_include("LoginPage.g.cpp")
# include "LoginPage.g.cpp"
#endif

#include <Mercatec.Helpers.ServiceLocator.hpp>

#include <winrt/Mercatec.Helpers.h>
#include <winrt/Mercatec.Helpers.Services.h>

#pragma warning(push)

//! https://learn.microsoft.com/en-us/cpp/code-quality/c26811?view=msvc-170
//! https://learn.microsoft.com/en-us/windows/uwp/cpp-and-winrt-apis/concurrency#parameter-passing
//! Warning C26811 Lifetime of the memory referenced by parameter ''args'' might end by the time the coroutine is resumed(lifetime .1)
#pragma warning(disable : 26811)

using namespace winrt;
using namespace winrt::Microsoft::UI::Xaml;
using namespace Cxx::DesignPatterns;
using namespace std::chrono_literals;

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

    fire_and_forget LoginPage::OnNavigatedTo(const Microsoft::UI::Xaml::Navigation::NavigationEventArgs& Args)
    {
        m_EffectMode = EffectMode::None;
        co_await m_ViewModel.LoadAsync(Args.Parameter().as<Helpers::ViewModels::ShellArgs>());
        InitializeNavigation();
    }

    fire_and_forget LoginPage::OnKeyDown(const Microsoft::UI::Xaml::Input::KeyRoutedEventArgs& Args)
    {
        if ( Args.Key() == Windows::System::VirtualKey::Enter )
        {
            DoEffectOut();
            co_await 100ms;
            m_ViewModel.Login();
        }

        base_type::OnKeyDown(Args);
    }

    fire_and_forget LoginPage::OnShowLoginWithPassword([[maybe_unused]] const IInspectable& Sender, [[maybe_unused]] const RoutedEventArgs& Args)
    {
        co_await 100ms;
        // passwordView.Focus();
    }

    void LoginPage::OnBackgroundFocus([[maybe_unused]] const IInspectable& Sender, [[maybe_unused]] const RoutedEventArgs& Args)
    {
    }

    void LoginPage::OnForegroundFocus([[maybe_unused]] const IInspectable& Sender, [[maybe_unused]] const RoutedEventArgs& Args)
    {
    }

    void LoginPage::DoEffectIn([[maybe_unused]] const double_t MilliSeconds)
    {
    }

    void LoginPage::DoEffectOut([[maybe_unused]] const double_t MilliSeconds)
    {
        /* if ( m_EffectMode == EffectMode::Background or m_EffectMode == EffectMode::None )
         {
             m_EffectMode = EffectMode::Foreground;

             background.Scale(milliseconds, 1.1, 1.0);
             background.Blur(milliseconds, 0.0, 6.0);
             foreground.Scale(500, 0.95, 1.0);
             foreground.Fade(milliseconds, 0.75, 1.0);
         }*/
    }
} // namespace winrt::Mercatec::Application::implementation

#pragma warning(pop)