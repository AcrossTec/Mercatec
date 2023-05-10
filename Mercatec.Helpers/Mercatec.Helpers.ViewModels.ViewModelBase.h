#pragma once

#include "ViewModels.ViewModelBase.g.h"

#include "Mercatec.Helpers.Types.hpp"
#include "Mercatec.Helpers.ViewModels.ObservableObject.h"

namespace winrt::Mercatec::Helpers::ViewModels::implementation
{
    struct ViewModelBase : ViewModelBaseT<ViewModelBase, ObservableObject>
    {
    public:
        ViewModelBase(const Services::ICommonServices& common_services) noexcept;

        hstring Title() const noexcept;

        bool IsMainView() const noexcept;

        Services::IContextService ContextService() const noexcept;

        Services::INavigationService NavigationService() const noexcept;

        Services::IMessageService MessageService() const noexcept;

        Services::IDialogService DialogService() const noexcept;

        Services::ILogService LogService() const noexcept;

        fire_and_forget LogInformation(const std::wstring_view source, const std::wstring_view action, const std::wstring_view message, const std::wstring_view description) const noexcept;
        fire_and_forget LogWarning(const std::wstring_view source, const std::wstring_view action, const std::wstring_view message, const std::wstring_view description) const noexcept;
        fire_and_forget LogException(const std::wstring_view source, const std::wstring_view action, const uint64_t code, const std::wstring_view message) const noexcept;
        fire_and_forget LogError(const std::wstring_view source, const std::wstring_view action, const std::wstring_view message, const std::wstring_view description) const noexcept;

    private:
        Services::IContextService    m_ContextService;
        Services::INavigationService m_NavigationService;
        Services::IMessageService    m_MessageService;
        Services::IDialogService     m_DialogService;
        Services::ILogService        m_LogService;
    };
} // namespace winrt::Mercatec::Helpers::ViewModels::implementation

namespace winrt::Mercatec::Helpers::ViewModels::factory_implementation
{
    struct ViewModelBase : ViewModelBaseT<ViewModelBase, implementation::ViewModelBase>
    {
    };
} // namespace winrt::Mercatec::Helpers::ViewModels::factory_implementation
