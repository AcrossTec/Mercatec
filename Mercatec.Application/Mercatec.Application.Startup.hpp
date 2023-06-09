#pragma once

#include "Mercatec.Application.Exports.Api.hpp"

#include <winrt/Windows.Foundation.h>
#include <winrt/Windows.Foundation.Collections.h>

namespace Mercatec::Application::Configurations
{
    class MERCATEC_APPLICATION_API Startup sealed abstract
    {
    public:
        static winrt::Windows::Foundation::IAsyncActionWithProgress<double_t> ConfigureAsync();

    private:
        static void ConfigureNavigation();
        static void ConfigureServiceLocator();
    };
} // namespace Mercatec::Application::Configurations
