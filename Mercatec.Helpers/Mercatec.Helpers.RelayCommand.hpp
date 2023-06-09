#pragma once

#include <Mercatec.Helpers.Exports.Api.hpp>
#include <winrt/Microsoft.UI.Xaml.Input.h>
#include <winrt/Windows.Foundation.h>

#include <functional>

namespace Mercatec::Helpers
{
    struct DelegateCommand : winrt::implements<DelegateCommand, winrt::Microsoft::UI::Xaml::Input::ICommand>
    {
    public:
        MERCATEC_HELPERS_API DelegateCommand(std::function<void()> execute);
        MERCATEC_HELPERS_API DelegateCommand(std::function<void()> execute, std::function<bool()> can_execute);

        MERCATEC_HELPERS_API winrt::event_token CanExecuteChanged(const winrt::Windows::Foundation::EventHandler<winrt::Windows::Foundation::IInspectable>& handler);

        MERCATEC_HELPERS_API void CanExecuteChanged(const winrt::event_token& token) noexcept;
        MERCATEC_HELPERS_API void OnCanExecuteChanged();
        MERCATEC_HELPERS_API bool CanExecute(const winrt::Windows::Foundation::IInspectable&) const;
        MERCATEC_HELPERS_API void Execute(const winrt::Windows::Foundation::IInspectable&) const;

    private:
        winrt::event<winrt::Windows::Foundation::EventHandler<winrt::Windows::Foundation::IInspectable>> m_CanExecuteChanged;

        std::function<void()> m_Execute;
        std::function<bool()> m_CanExecute;
    };

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
