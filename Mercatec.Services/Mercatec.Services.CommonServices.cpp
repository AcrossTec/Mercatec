#include "pch.h"
#include "Mercatec.Services.CommonServices.h"
#if __has_include("CommonServices.g.cpp")
# include "CommonServices.g.cpp"
#endif

namespace winrt::Mercatec::Services::implementation
{
    CommonServices::CommonServices( //!
      const Helpers::Services::IContextService&    context_service,
      const Helpers::Services::INavigationService& navigation_service,
      const Helpers::Services::IMessageService&    message_service,
      const Helpers::Services::IDialogService&     dialog_service,
      const Helpers::Services::ILogService&        log_service
    ) noexcept
      : m_ContextService{ context_service }
      , m_NavigationService{ navigation_service }
      , m_MessageService{ message_service }
      , m_DialogService{ dialog_service }
      , m_LogService{ log_service }
    {
    }

    Helpers::Services::IContextService CommonServices::ContextService() const noexcept
    {
        return m_ContextService;
    }

    Helpers::Services::INavigationService CommonServices::NavigationService() const noexcept
    {
        return m_NavigationService;
    }

    Helpers::Services::IMessageService CommonServices::MessageService() const noexcept
    {
        return m_MessageService;
    }

    Helpers::Services::IDialogService CommonServices::DialogService() const noexcept
    {
        return m_DialogService;
    }

    Helpers::Services::ILogService CommonServices::LogService() const noexcept
    {
        return m_LogService;
    }
} // namespace winrt::Mercatec::Services::implementation
