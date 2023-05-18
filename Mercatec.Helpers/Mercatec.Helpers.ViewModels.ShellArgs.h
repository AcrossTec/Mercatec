#pragma once

#include "ViewModels.ShellArgs.g.h"

#include <winrt/Mercatec.Helpers.h>

namespace winrt::Mercatec::Helpers::ViewModels::implementation
{
    struct ShellArgs : ShellArgsT<ShellArgs>
    {
    public:
        ShellArgs();

        Windows::UI::Xaml::Interop::TypeName ViewModel() const noexcept;
        Helpers::UserInfo                    UserInfo() const noexcept;
        IInspectable                         Parameter() const noexcept;

        void ViewModel(const Windows::UI::Xaml::Interop::TypeName& view_model) noexcept;
        void UserInfo(const Helpers::UserInfo& user_info) noexcept;
        void Parameter(const IInspectable& parameter) noexcept;

    private:
        Windows::UI::Xaml::Interop::TypeName m_ViewModel;
        Helpers::UserInfo                    m_UserInfo;
        IInspectable                         m_Parameter;
    };
} // namespace winrt::Mercatec::Helpers::ViewModels::implementation

namespace winrt::Mercatec::Helpers::ViewModels::factory_implementation
{
    struct ShellArgs : ShellArgsT<ShellArgs, implementation::ShellArgs>
    {
    };
} // namespace winrt::Mercatec::Helpers::ViewModels::factory_implementation
