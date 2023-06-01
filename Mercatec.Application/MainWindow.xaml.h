// Copyright (c) Microsoft Corporation and Contributors.
// Licensed under the MIT License.

#pragma once

#include "MainWindow.g.h"

namespace winrt::Mercatec::Application::implementation
{
    struct MainWindow : MainWindowT<MainWindow>
    {
    public:
        MainWindow();

    private:
        void SetUpComponent() noexcept;
    };
} // namespace winrt::Mercatec::Application::implementation

namespace winrt::Mercatec::Application::factory_implementation
{
    struct MainWindow : MainWindowT<MainWindow, implementation::MainWindow>
    {
    };
} // namespace winrt::Mercatec::Application::factory_implementation
