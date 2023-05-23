#include "pch.h"
#include "Mercatec.Services.MessageService.hpp"

namespace Mercatec::Services
{
    Subscriptions::Subscriptions()
    {
    }

    bool Subscriptions::GetIsEmpty() const noexcept
    {
        return m_Subscriptions.empty();
    }
} // namespace Mercatec::Services
