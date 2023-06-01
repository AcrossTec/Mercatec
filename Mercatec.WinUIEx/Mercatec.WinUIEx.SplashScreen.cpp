#include "pch.h"
#include "Mercatec.WinUIEx.SplashScreen.h"
#if __has_include("SplashScreen.g.cpp")
# include "SplashScreen.g.cpp"
#endif

#include "Mercatec.WinUIEx.HwndExtensions.hpp"
#include "Mercatec.WinUIEx.WindowExtensions.hpp"

using Mercatec::WinUIEx::HwndExtensions;
using Mercatec::WinUIEx::WindowExtensions;
using Mercatec::WinUIEx::WindowStyle;

using namespace winrt::Microsoft::UI::Xaml;
using namespace winrt::Microsoft::UI::Dispatching;

namespace winrt::Mercatec::WinUIEx::implementation
{
    SplashScreen::SplashScreen()
      : m_Manager{ nullptr }
      , m_Width{ 640 }
      , m_Height{ 480 }
      , m_IsAlwaysOnTop{ false }
      , m_Window{ nullptr }
      , m_WindowType{ std::nullopt }
    {
        m_SplashScreenActivatedToken = this->Activated({ this, &SplashScreen::SplashScreen_Activated });
        this->DispatcherQueue().TryEnqueue(DispatcherQueuePriority::Normal, [this] { this->Activate(); });
        m_Manager = WindowManager::Get(*this);
    }

    SplashScreen::SplashScreen(const Microsoft::UI::Xaml::Window& Window)
      : SplashScreen()
    {
        if ( not Window )
        {
            throw hresult_invalid_argument(L"Argument Null Exception: Window");
        }

        m_Window = Window;
    }

    WinUIEx::SplashScreen SplashScreen::Create(const Microsoft::UI::Xaml::Window& Window)
    {
        return make<SplashScreen>(Window);
    }

    SplashScreen::SplashScreen(const Windows::UI::Xaml::Interop::TypeName& WindowType)
      : SplashScreen()
    {
        m_WindowType = WindowType;

        //! TODO: Se debe verificar que WindowType sea una ventana.
        //!       Además ser capas de poder crear el objeto en Runtime.
        throw hresult_not_implemented();
    }

    WinUIEx::SplashScreen SplashScreen::Create(const Windows::UI::Xaml::Interop::TypeName& WindowType)
    {
        return make<SplashScreen>(WindowType);
    }

    WinUIEx::BackdropType SplashScreen::BackdropType() const noexcept
    {
        return m_Manager.BackdropType();
    }

    void SplashScreen::BackdropType(const WinUIEx::BackdropType Value) noexcept
    {
        m_Manager.BackdropType(Value);
    }

    Windows::Foundation::IAsyncAction SplashScreen::OnLoading()
    {
        co_return;
    }

    double_t SplashScreen::Width() const noexcept
    {
        return m_Width;
    }

    void SplashScreen::Width(const double_t Value) noexcept
    {
        m_Width = Value;
    }

    double_t SplashScreen::Height() const noexcept
    {
        return m_Height;
    }

    void SplashScreen::Height(const double_t Value) noexcept
    {
        m_Height = Value;
    }

    bool SplashScreen::IsAlwaysOnTop() const noexcept
    {
        return m_IsAlwaysOnTop;
    }

    void SplashScreen::IsAlwaysOnTop(const bool Value) noexcept
    {
        m_IsAlwaysOnTop = Value;
    }

    winrt::event_token SplashScreen::Completed(const Windows::Foundation::EventHandler<Microsoft::UI::Xaml::Window>& Handler)
    {
        return m_Completed.add(Handler);
    }

    void SplashScreen::Completed(const event_token& Token) noexcept
    {
        m_Completed.remove(Token);
    }

    fire_and_forget SplashScreen::Content_Loaded([[maybe_unused]] const IInspectable& Sender, [[maybe_unused]] const RoutedEventArgs& Args)
    {

        if ( m_IsAlwaysOnTop )
        {
            WindowExtensions::SetIsAlwaysOnTop(*this, true);
        }
        else
        {
            WindowExtensions::SetForegroundWindow(*this);
        }

        double_t H = m_Height;
        double_t W = m_Width;

        if ( FrameworkElement F = Content().try_as<FrameworkElement>() )
        {
            if ( std::isnan(m_Width) and F.DesiredSize().Width > 0 )
            {
                W = F.DesiredSize().Width;
            }

            if ( std::isnan(m_Height) and F.DesiredSize().Height > 0 )
            {
                H = F.DesiredSize().Height;
            }
        }

        if ( std::isnan(W) )
        {
            W = 640;
        }

        if ( std::isnan(H) )
        {
            H = 480;
        }

        WindowExtensions::CenterOnScreen(*this, W, H);
        co_await OnLoading();

        if ( m_WindowType != std::nullopt )
        {
            // TODO: Crear alguna implemantación para crear una ventana desde un TypeName
            // m_Window = Activator.CreateInstance(m_WindowType) as Window;
        }

        if ( m_Window )
        {
            m_Window.Activate();
        }
        this->Close();

        if ( m_Window )
        {
            WindowExtensions::SetForegroundWindow(m_Window);
        }
        m_Completed(*this, m_Window);
        m_Window = nullptr;
    }

    void SplashScreen::SplashScreen_Activated([[maybe_unused]] const IInspectable& Sender, [[maybe_unused]] const WindowActivatedEventArgs& Args)
    {
        this->Activated(m_SplashScreenActivatedToken);
        WindowExtensions::Hide(*this); // Hides until content is loaded

        HWND Hwnd = WindowExtensions::GetWindowHandle(*this);
        HwndExtensions::ToggleWindowStyle(Hwnd, false, WindowStyle::WsTiledWindow);

        FrameworkElement Content = this->Content().try_as<FrameworkElement>();

        if ( not Content or Content.IsLoaded() )
        {
            Content_Loaded(*this, nullptr);
        }
        else
        {
            Content.Loaded({ this, &SplashScreen::Content_Loaded });
        }
    }
} // namespace winrt::Mercatec::WinUIEx::implementation
