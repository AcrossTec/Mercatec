// Copyright (c) Microsoft Corporation and Contributors.
// Licensed under the MIT License.

#pragma once

#include "UserSelectionPage.g.h"

namespace winrt::Mercatec::Application::implementation
{
    struct UserSelectionPage : UserSelectionPageT<UserSelectionPage>
    {
    public:
        UserSelectionPage();
        void UserSelectionChanged(const IInspectable& sender, const MUXC::SelectionChangedEventArgs& args);
        void UserSelectionLoaded(const IInspectable& sender, const MUX::RoutedEventArgs& args);
        void AddUserButton_Click(const IInspectable& sender, const MUX::RoutedEventArgs& args);

    private:
    };
} // namespace winrt::Mercatec::Application::implementation

namespace winrt::Mercatec::Application::factory_implementation
{
    struct UserSelectionPage : UserSelectionPageT<UserSelectionPage, implementation::UserSelectionPage>
    {
    };
} // namespace winrt::Mercatec::Application::factory_implementation
