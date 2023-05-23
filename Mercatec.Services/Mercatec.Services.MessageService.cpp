#include "pch.h"
#include "Mercatec.Services.MessageService.hpp"

namespace Mercatec::Services
{
    void MessageService::Unsubscribe(const IInspectable& Target)
    {
        if ( Target == nullptr )
        {
            throw winrt::hresult_invalid_argument(L"Argument Null Exception: Target");
        }

        std::lock_guard<std::mutex> Lock{ m_Sync };

        auto Subscriber = std::ranges::find_if(m_Subscribers, [&](const auto& Sub) { return Sub.Target == Target; });

        if ( Subscriber != std::ranges::end(m_Subscribers) )
        {
            m_Subscribers.erase(Subscriber);
        }
    }

    bool MessageService::GetIsEmpty() const noexcept
    {
        return m_Subscribers.empty();
    }

    std::vector<Subscriber> MessageService::GetSubscribersSnapshot() noexcept
    {
        std::lock_guard<std::mutex> Lock{ m_Sync };
        return m_Subscribers;
    }
} // namespace Mercatec::Services
