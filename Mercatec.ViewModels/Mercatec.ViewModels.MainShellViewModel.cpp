#include "pch.h"
#include "Mercatec.ViewModels.MainShellViewModel.h"
#if __has_include("MainShellViewModel.g.cpp")
# include "MainShellViewModel.g.cpp"
#endif

namespace winrt::Mercatec::ViewModels::implementation
{
    MainShellViewModel::MainShellViewModel(const Helpers::Services::ILoginService& login_service, const Helpers::Services::ICommonServices& common_services)
      : MainShellViewModelT<MainShellViewModel, ShellViewModel>(login_service, common_services)
    {
    }
} // namespace winrt::Mercatec::ViewModels::implementation
