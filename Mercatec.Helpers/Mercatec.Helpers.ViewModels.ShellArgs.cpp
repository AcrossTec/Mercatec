#include "pch.h"
#include "Mercatec.Helpers.ViewModels.ShellArgs.h"
#if __has_include("ViewModels.ShellArgs.g.cpp")
# include "ViewModels.ShellArgs.g.cpp"
#endif

#include "Mercatec.Helpers.Types.hpp"
#include "Mercatec.Helpers.Strings.hpp"

using namespace Mercatec::Types;
using Mercatec::Helpers::Empty;

namespace winrt::Mercatec::Helpers::ViewModels::implementation
{
    ShellArgs::ShellArgs()
      : m_ViewModel{ Empty<Char>, Windows::UI::Xaml::Interop::TypeKind{ -1 } }
    {
    }

    Windows::UI::Xaml::Interop::TypeName ShellArgs::ViewModel() const noexcept
    {
        return m_ViewModel;
    }

    Helpers::UserInfo ShellArgs::UserInfo() const noexcept
    {
        return m_UserInfo;
    }

    IInspectable ShellArgs::Parameter() const noexcept
    {
        return m_Parameter;
    }

    void ShellArgs::ViewModel(const Windows::UI::Xaml::Interop::TypeName& view_model) noexcept
    {
        m_ViewModel = view_model;
    }

    void ShellArgs::UserInfo(const Helpers::UserInfo& user_info) noexcept
    {
        m_UserInfo = user_info;
    }

    void ShellArgs::Parameter(const IInspectable& parameter) noexcept
    {
        m_Parameter = parameter;
    }
} // namespace winrt::Mercatec::Helpers::ViewModels::implementation
