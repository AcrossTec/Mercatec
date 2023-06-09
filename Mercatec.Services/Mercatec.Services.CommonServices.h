#pragma once

#include "CommonServices.g.h"
#include "Mercatec.Services.hpp"

namespace winrt::Mercatec::Services::implementation
{
    struct CommonServices : CommonServicesT<CommonServices>
    {
    public:
        CommonServices( //!
          const Helpers::Services::IContextService&    context_service,
          const Helpers::Services::INavigationService& navigation_service,
          const Helpers::Services::IMessageService&    message_service,
          const Helpers::Services::IDialogService&     dialog_service,
          const Helpers::Services::ILogService&        log_service
        ) noexcept;

        Helpers::Services::IContextService    ContextService() const noexcept;
        Helpers::Services::INavigationService NavigationService() const noexcept;
        Helpers::Services::IMessageService    MessageService() const noexcept;
        Helpers::Services::IDialogService     DialogService() const noexcept;
        Helpers::Services::ILogService        LogService() const noexcept;

    private:
        Helpers::Services::IContextService    m_ContextService;
        Helpers::Services::INavigationService m_NavigationService;
        Helpers::Services::IMessageService    m_MessageService;
        Helpers::Services::IDialogService     m_DialogService;
        Helpers::Services::ILogService        m_LogService;
    };
} // namespace winrt::Mercatec::Services::implementation

namespace winrt::Mercatec::Services::factory_implementation
{
    struct CommonServices : CommonServicesT<CommonServices, implementation::CommonServices>
    {
    };
} // namespace winrt::Mercatec::Services::factory_implementation
