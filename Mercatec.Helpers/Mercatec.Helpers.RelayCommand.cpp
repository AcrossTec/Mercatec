#include "pch.h"
#include "Mercatec.Helpers.RelayCommand.hpp"

#include <chrono>

namespace Mercatec::Helpers
{
    DelegateCommand::DelegateCommand(std::function<void()> execute)
      : DelegateCommand(execute, [] { return true; })
    {
    }

    DelegateCommand::DelegateCommand(std::function<void()> execute, std::function<bool()> can_execute)
      : m_Execute{ execute }
      , m_CanExecute{ can_execute }
    {
    }

    winrt::event_token DelegateCommand::CanExecuteChanged(const winrt::Windows::Foundation::EventHandler<winrt::Windows::Foundation::IInspectable>& handler)
    {
        return m_CanExecuteChanged.add(handler);
    }

    void DelegateCommand::CanExecuteChanged(const winrt::event_token& token) noexcept
    {
        m_CanExecuteChanged.remove(token);
    }

    void DelegateCommand::OnCanExecuteChanged()
    {
        m_CanExecuteChanged(*this, nullptr);
    }

    bool DelegateCommand::CanExecute(const winrt::Windows::Foundation::IInspectable&) const
    {
        return m_CanExecute();
    }

    void DelegateCommand::Execute(const winrt::Windows::Foundation::IInspectable&) const
    {
        m_Execute();
    }
} // namespace Mercatec::Helpers