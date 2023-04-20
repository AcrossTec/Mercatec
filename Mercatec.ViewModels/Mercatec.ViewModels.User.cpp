// Copyright (c) Microsoft Corporation and Contributors.
// Licensed under the MIT License.

#include "pch.h"
#include "Mercatec.ViewModels.User.h"
#if __has_include("User.g.cpp")
#include "User.g.cpp"
#endif

using namespace winrt;
using namespace Microsoft::UI::Xaml;

// To learn more about WinUI, the WinUI project structure,
// and more about our project templates, see: http://aka.ms/winui-project-info.

namespace winrt::Mercatec::ViewModels::implementation
{
    User::User()
    {
    }

    int32_t User::MyProperty()
    {
        throw hresult_not_implemented();
    }

    void User::MyProperty( int32_t /* value */ )
    {
        throw hresult_not_implemented();
    }
}
