#pragma once

#include "ContextService.g.h"
#include <winrt/Microsoft.UI.Dispatching.h>
#include <winrt/Mercatec.Helpers.h>

namespace winrt::Mercatec::Services::implementation
{
    struct ContextService : ContextServiceT<ContextService>
    {
    public:
        ContextService() noexcept;
        void Initialize(const Microsoft::UI::Dispatching::DispatcherQueue& Dispatcher) noexcept;
        bool Run(const Microsoft::UI::Dispatching::DispatcherQueueHandler& Action);

    private:
        Microsoft::UI::Dispatching::DispatcherQueue m_Dispatcher;
    };
} // namespace winrt::Mercatec::Services::implementation

namespace winrt::Mercatec::Services::factory_implementation
{
    struct ContextService : ContextServiceT<ContextService, implementation::ContextService>
    {
    };
} // namespace winrt::Mercatec::Services::factory_implementation
