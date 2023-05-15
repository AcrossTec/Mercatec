#pragma once

#include <winrt/Windows.Foundation.h>
#include <winrt/Microsoft.UI.Xaml.Input.h>

#include <functional>

namespace Mercatec::Helpers
{
    template <typename T = winrt::Windows::Foundation::IInspectable>
    struct RelayCommand : winrt::implements<RelayCommand<T>, winrt::Microsoft::UI::Xaml::Input::ICommand>
    {
    public:
        RelayCommand(std::function<void(const T&)> execute)
          : RelayCommand(execute, [](const T&) { return true; })
        {
        }

        RelayCommand(std::function<void(const T&)> execute, std::function<bool(const T&)> can_execute)
          : m_Execute{ execute }
          , m_CanExecute{ can_execute }
        {
        }

        winrt::event_token CanExecuteChanged(const winrt::Windows::Foundation::EventHandler<winrt::Windows::Foundation::IInspectable>& handler)
        {
            return m_CanExecuteChanged.add(handler);
        }

        void CanExecuteChanged(const winrt::event_token& token) noexcept
        {
            m_CanExecuteChanged.remove(token);
        }

        void OnCanExecuteChanged()
        {
            m_CanExecuteChanged(*this, nullptr);
        }

        bool CanExecute(const winrt::Windows::Foundation::IInspectable& parameter) const
        {
            return m_CanExecute(winrt::unbox_value<T>(parameter));
        }

        void Execute(const winrt::Windows::Foundation::IInspectable& parameter) const
        {
            m_Execute(winrt::unbox_value<T>(parameter));
        }

    private:
        winrt::event<winrt::Windows::Foundation::EventHandler<winrt::Windows::Foundation::IInspectable>> m_CanExecuteChanged;

        std::function<void(const T&)> m_Execute;
        std::function<bool(const T&)> m_CanExecute;
    };
} // namespace Mercatec::Helpers
