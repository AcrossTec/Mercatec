#include "pch.h"
#include "Mercatec.Services.MessageService.hpp"

namespace Mercatec::Services
{
    Subscriber::Subscriber(const IInspectable& Target)
      : m_Reference{ winrt::make_weak(Target) }
    {
    }

    IInspectable Subscriber::GetTarget() const noexcept
    {
        return m_Reference.get();
    }

    bool Subscriber::GetIsEmpty() const noexcept
    {
        return m_Subscriptions.empty();
    }
} // namespace Mercatec::Services
