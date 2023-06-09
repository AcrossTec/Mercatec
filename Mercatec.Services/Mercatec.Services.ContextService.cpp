#include "pch.h"
#include "Mercatec.Services.ContextService.h"
#if __has_include("ContextService.g.cpp")
# include "ContextService.g.cpp"
#endif

//!
//! Threading functionality migration
//! https://learn.microsoft.com/en-us/windows/apps/windows-app-sdk/migrate-to-windows-app-sdk/guides/threading
//!

namespace winrt::Mercatec::Services::implementation
{
    ContextService::ContextService() noexcept
      : m_Dispatcher{ nullptr }
    {
    }

    void ContextService::Initialize(const Microsoft::UI::Dispatching::DispatcherQueue& Dispatcher) noexcept
    {
        m_Dispatcher = Dispatcher;
    }

    bool ContextService::Run(const Microsoft::UI::Dispatching::DispatcherQueueHandler& Action)
    {
        return m_Dispatcher.TryEnqueue(Microsoft::UI::Dispatching::DispatcherQueuePriority::Normal, Action);
    }
} // namespace winrt::Mercatec::Services::implementation
