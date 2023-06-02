// Copyright (c) Microsoft Corporation and Contributors.
// Licensed under the MIT License.

#pragma once

#include "MainWindow.g.h"
#include <Mercatec.WinUIEx.Messaging.WindowMessageMonitor.hpp>

namespace winrt::Mercatec::Application::implementation
{
    struct MainWindow : MainWindowT<MainWindow>
    {
    public:
        MainWindow();

    private:
        void SetUpComponent() noexcept;

    private:
        com_ptr<::Mercatec::WinUIEx::Messaging::WindowMessageMonitor> m_Monitor;
        Mercatec::WinUIEx::WindowManager                              m_Manager;
    };
} // namespace winrt::Mercatec::Application::implementation

namespace winrt::Mercatec::Application::factory_implementation
{
    struct MainWindow : MainWindowT<MainWindow, implementation::MainWindow>
    {
    };
} // namespace winrt::Mercatec::Application::factory_implementation
