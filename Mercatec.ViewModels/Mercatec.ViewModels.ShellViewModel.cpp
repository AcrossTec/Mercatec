#include "pch.h"
#include "Mercatec.ViewModels.ShellViewModel.h"
#if __has_include("ShellViewModel.g.cpp")
# include "ShellViewModel.g.cpp"
#endif

namespace winrt::Mercatec::ViewModels::implementation
{
    ShellViewModel::ShellViewModel( //!
      [[maybe_unused]] const Helpers::Services::ILoginService&   login_service,
      [[maybe_unused]] const Helpers::Services::ICommonServices& common_services
    )
      : ShellViewModelT<ShellViewModel>(common_services)
    {
    }
} // namespace winrt::Mercatec::ViewModels::implementation
