#include "pch.h"
#include "Mercatec.Application.Startup.hpp"
#include "Mercatec.Application.NavigationService.hpp"
#include "Mercatec.Helpers.Types.hpp"
#include "Mercatec.Helpers.ServiceLocator.hpp"
#include "Mercatec.Services.MessageService.hpp"

using Cxx::DesignPatterns::ServiceLocator;
using Mercatec::Services::MessageService;

namespace Mercatec::Application::Configurations
{
    IAsyncAction Startup::ConfigureAsync()
    {
        ConfigureServiceLocator();
        ConfigureNavigation();
        co_return;
    }

    void Startup::ConfigureServiceLocator()
    {
        ServiceLocator::Default().Register<com_ptr<MessageService>>(make_self<MessageService>());
    }

    void Startup::ConfigureNavigation()
    {
    }
} // namespace Mercatec::Application::Configurations
