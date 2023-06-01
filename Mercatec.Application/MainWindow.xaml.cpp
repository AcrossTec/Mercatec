// Copyright (c) Microsoft Corporation and Contributors.
// Licensed under the MIT License.

#include "pch.h"
#include "MainWindow.xaml.h"
#if __has_include("MainWindow.g.cpp")
# include "MainWindow.g.cpp"
#endif

#include "MainPage.xaml.h"

using namespace winrt;
using namespace Microsoft::UI::Xaml;
using namespace Windows::Foundation;

#include <Mercatec.Helpers.Application.hpp>

using namespace ::Mercatec::Helpers::Applications;

// To learn more about WinUI, the WinUI project structure,
// and more about our project templates, see: http://aka.ms/winui-project-info.

namespace winrt::Mercatec::Application::implementation
{
    MainWindow::MainWindow()
    {
        InitializeComponent();
        SetUpComponent();
    }

    void MainWindow::SetUpComponent() noexcept
    {
        Title(ApplicationName());
        FrameContent().Navigate(xaml_typename<Mercatec::Application::MainPage>());
    }
} // namespace winrt::Mercatec::Application::implementation
