#include "pch.h"
#include "Mercatec.Helpers.ViewModels.ViewModelBase.h"
#if __has_include("ViewModels.ViewModelBase.g.cpp")
# include "ViewModels.ViewModelBase.g.cpp"
#endif

#include <Mercatec.Helpers.Strings.hpp>

using namespace ::Mercatec::Types;

using ::Mercatec::Helpers::Empty;

namespace winrt::Mercatec::Helpers::ViewModels::implementation
{
    ViewModelBase::ViewModelBase(const Services::ICommonServices& common_services) noexcept
      : m_ContextService{ common_services.ContextService() }
      , m_NavigationService{ common_services.NavigationService() }
      , m_MessageService{ common_services.MessageService() }
      , m_DialogService{ common_services.DialogService() }
      , m_LogService{ common_services.LogService() }
    {
    }

    hstring ViewModelBase::Title() const noexcept
    {
        return Empty<Char>;
    }

    Services::IContextService ViewModelBase::ContextService() const noexcept
    {
        return m_ContextService;
    }

    Services::INavigationService ViewModelBase::NavigationService() const noexcept
    {
        return m_NavigationService;
    }

    Services::IMessageService ViewModelBase::MessageService() const noexcept
    {
        return m_MessageService;
    }

    Services::IDialogService ViewModelBase::DialogService() const noexcept
    {
        return m_DialogService;
    }

    Services::ILogService ViewModelBase::LogService() const noexcept
    {
        return m_LogService;
    }

    fire_and_forget ViewModelBase::LogInformation(const std::wstring_view source, const std::wstring_view action, const std::wstring_view message, const std::wstring_view description) const noexcept
    {
        co_await m_LogService.WriteAsync(Mercatec::Helpers::LogType::Information, source, action, message, description);
    }

    fire_and_forget ViewModelBase::LogWarning(const std::wstring_view source, const std::wstring_view action, const std::wstring_view message, const std::wstring_view description) const noexcept
    {
        co_await m_LogService.WriteAsync(Mercatec::Helpers::LogType::Warning, source, action, message, description);
    }

    fire_and_forget ViewModelBase::LogException(const std::wstring_view source, const std::wstring_view action, const hresult code, const std::wstring_view message) const noexcept
    {
        co_await m_LogService.WriteAsync(Mercatec::Helpers::LogType::Error, source, action, code, message);
    }

    fire_and_forget ViewModelBase::LogError(const std::wstring_view source, const std::wstring_view action, const std::wstring_view message, const std::wstring_view description) const noexcept
    {
        co_await m_LogService.WriteAsync(Mercatec::Helpers::LogType::Error, source, action, message, description);
    }
} // namespace winrt::Mercatec::Helpers::ViewModels::implementation
