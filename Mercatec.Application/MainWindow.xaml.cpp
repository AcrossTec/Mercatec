// Copyright (c) Microsoft Corporation and Contributors.
// Licensed under the MIT License.

#include "pch.h"
#include "MainWindow.xaml.h"
#if __has_include("MainWindow.g.cpp")
# include "MainWindow.g.cpp"
#endif

using namespace winrt;
using namespace Microsoft::UI::Xaml;
using namespace Windows::Foundation;

namespace MUX  = Microsoft::UI::Xaml;
namespace MUXC = Microsoft::UI::Xaml::Controls;

// To learn more about WinUI, the WinUI project structure,
// and more about our project templates, see: http://aka.ms/winui-project-info.

namespace winrt::Mercatec::Application::implementation
{
    MainWindow::MainWindow()
    {
        InitializeComponent();
    }

    int32_t MainWindow::MyProperty()
    {
        throw hresult_not_implemented();
    }

    void MainWindow::MyProperty(int32_t /* value */)
    {
        throw hresult_not_implemented();
    }

    void MainWindow::myButton_Click(const IInspectable&, const RoutedEventArgs&)
    {
        const auto app_name = MUX::Application::Current().Current().Resources().Lookup(box_value(L"AppName"));

        myButton().Content(app_name);

        // MUXC::ContentDialog content_dialog;
        // content_dialog.Title(app_name);
    }
} // namespace winrt::Mercatec::Application::implementation
