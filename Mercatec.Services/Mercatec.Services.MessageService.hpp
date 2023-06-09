#pragma once

#include <winrt/Windows.Foundation.h>
#include <winrt/Windows.Foundation.Collections.h>

#include <winrt/Mercatec.Helpers.h>
#include <winrt/Mercatec.Helpers.Services.h>

#include <Mercatec.Services.Exports.Api.hpp>
#include <Mercatec.Helpers.FunctionTraits.hpp>

#include <mutex>
#include <unordered_map>
#include <string_view>
#include <vector>
#include <ranges>
#include <functional>
#include <typeindex>
#include <any>

#pragma warning(push)
//! Compiler Warning (level 1) C4251
//! 'type' : class 'type1' needs to have dll-interface to be used by clients of class 'type2'
//! https://learn.microsoft.com/en-us/cpp/error-messages/compiler-warnings/compiler-warning-level-1-c4251?view=msvc-170
#pragma warning(disable : 4251)

namespace Mercatec::Services
{
    class MERCATEC_SERVICES_API Subscriptions
    {
    public:
        template <typename TSender, typename TArgs>
        using DelegateT = std::function<void(TSender, const std::wstring_view, TArgs)>;

        Subscriptions();
        bool GetIsEmpty() const noexcept;
        __declspec(property(get = GetIsEmpty)) bool IsEmpty;

        template <typename TAction>
        void AddSubscription(TAction&& Action)
        {
            static_assert(Cxx::Traits::FunctionTraits<TAction>::ArgumentCount == 3);

            m_Subscriptions[std::type_index(typeid(typename Cxx::Traits::FunctionTraits<TAction>::template Argument<2>))].emplace_back( //
              [&](void* Sender, const void* Message, void* Args)                                                                        //
              {
                  if constexpr ( not std::is_lvalue_reference_v<typename Cxx::Traits::FunctionTraits<TAction>::template Argument<2>> )
                  {
                      std::invoke(                                                                                                //
                        std::forward<TAction>(Action),                                                                            //
                        *(std::add_pointer_t<typename Cxx::Traits::FunctionTraits<TAction>::template Argument<0>>)Sender,         //
                        *(std::add_pointer_t<typename Cxx::Traits::FunctionTraits<TAction>::template Argument<1>>)Message,        //
                        std::move(*(std::add_pointer_t<typename Cxx::Traits::FunctionTraits<TAction>::template Argument<2>>)Args) //
                      );
                  }
                  else
                  {
                      std::invoke(                                                                                         //
                        std::forward<TAction>(Action),                                                                     //
                        *(std::add_pointer_t<typename Cxx::Traits::FunctionTraits<TAction>::template Argument<0>>)Sender,  //
                        *(std::add_pointer_t<typename Cxx::Traits::FunctionTraits<TAction>::template Argument<1>>)Message, //
                        *(std::add_pointer_t<typename Cxx::Traits::FunctionTraits<TAction>::template Argument<2>>)Args     //
                      );
                  }
              }
            );
        }

        template <typename TArgs>
        void RemoveSubscription()
        {
            m_Subscriptions.erase(std::type_index(typeid(TArgs)));
        }

        template <typename TSender, typename TArgs>
        void TryInvoke(TSender&& Sender, const std::wstring_view Message, TArgs&& Args)
        {
            const auto ArgsType = std::type_index(typeid(TArgs));

            for ( auto& [Type, Actions] : m_Subscriptions | std::views::filter([&](auto&& Value) { return Value.first == ArgsType; }) )
            {
                for ( auto& Action : Actions )
                {
                    Action(                                          //
                      std::addressof(std::forward<TSender>(Sender)), //
                      std::addressof(Message),
                      reinterpret_cast<std::remove_cvref_t<TArgs>*>( //
                        &const_cast<char&>(                          //
                          reinterpret_cast<const volatile char&>(Args)
                        )
                      )
                    );
                }
            }
        }

    private:
        std::unordered_map<std::type_index, std::vector<std::function<void(void*, const void*, void*)>>> m_Subscriptions;
    };

    class MERCATEC_SERVICES_API Subscriber
    {
    public:
        template <typename TSender, typename TArgs>
        using DelegateT = std::function<void(TSender, const std::wstring_view, TArgs)>;

        Subscriber(const winrt::Windows::Foundation::IInspectable& Target);

        winrt::Windows::Foundation::IInspectable GetTarget() const noexcept;
        __declspec(property(get = GetTarget)) winrt::Windows::Foundation::IInspectable Target;

        bool GetIsEmpty() const noexcept;
        __declspec(property(get = GetIsEmpty)) bool IsEmpty;

        template <typename TAction>
        void AddSubscription(TAction&& Action)
        {
            m_Subscriptions[std::type_index(typeid(typename Cxx::Traits::FunctionTraits<TAction>::template Argument<0>))] //
              .AddSubscription(std::forward<TAction>(Action));
        }

        template <typename TSender>
        void RemoveSubscription()
        {
            m_Subscriptions.erase(std::type_index(typeid(TSender)));
        }

        template <typename TSender, typename TArgs>
        void RemoveSubscription()
        {
            if ( auto Subs = m_Subscriptions.find(std::type_index(typeid(TSender))); Subs != std::end(m_Subscriptions) )
            {
                Subs->second.RemoveSubscription<TArgs>();

                if ( Subs->second.IsEmpty )
                {
                    m_Subscriptions.erase(std::type_index(typeid(TSender)));
                }
            }
        }

        template <typename TSender, typename TArgs>
        void TryInvoke(TSender&& Sender, const std::wstring_view& Message, TArgs&& Args)
        {
            if ( m_Reference.get() )
            {
                const auto SenderType = std::type_index(typeid(TSender));

                for ( auto& [Type, Subs] : m_Subscriptions | std::views::filter([&](auto&& Value) { return Value.first == SenderType; }) )
                {
                    //! https://learn.microsoft.com/en-us/cpp/code-quality/c26800?view=msvc-170
                    //! Use of a moved from object: 'object'.
                    //! Code analysis name: USE_OF_A_MOVED_FROM_OBJECT
                    __pragma(warning(push));
                    __pragma(warning(disable : 26800));
                    Subs.TryInvoke(std::forward<TSender>(Sender), Message, std::forward<TArgs>(Args));
                    __pragma(warning(pop));
                }
            }
        }

    private:
        winrt::weak_ref<winrt::Windows::Foundation::IInspectable> m_Reference;
        std::unordered_map<std::type_index, Subscriptions>        m_Subscriptions;
    };

    class MessageService : public winrt::implements<MessageService, winrt::Mercatec::Helpers::Services::IMessageService>
    {
    public:
        template <typename TSender, typename TArgs>
        using DelegateT = std::function<void(TSender, const std::wstring_view, TArgs)>;

        MERCATEC_SERVICES_API bool GetIsEmpty() const noexcept;
        __declspec(property(get = GetIsEmpty)) bool IsEmpty;

        template <typename TAction>
        void Subscribe(const winrt::Windows::Foundation::IInspectable& Target, TAction&& Action)
        {
            if ( Target == nullptr )
            {
                throw winrt::hresult_invalid_argument(L"Argument Null Exception: Target");
            }

            std::lock_guard<std::mutex> Lock{ m_Sync };

            auto Subscriber = std::ranges::find_if(m_Subscribers, [&](const auto& Sub) { return Sub.Target == Target; });

            if ( Subscriber == std::ranges::end(m_Subscribers) )
            {
                m_Subscribers.emplace_back(Target).AddSubscription(std::forward<TAction>(Action));
            }
            else
            {
                Subscriber->AddSubscription(std::forward<TAction>(Action));
            }
        }

        template <typename TSender>
        void Unsubscribe(const winrt::Windows::Foundation::IInspectable& Target)
        {
            if ( Target == nullptr )
            {
                throw winrt::hresult_invalid_argument(L"Argument Null Exception: Target");
            }

            std::lock_guard<std::mutex> Lock{ m_Sync };

            auto Subscriber = std::ranges::find_if(m_Subscribers, [&](const auto& Sub) { return Sub.Target == Target; });

            if ( Subscriber != std::ranges::end(m_Subscribers) )
            {
                Subscriber->RemoveSubscription<TSender>();

                if ( Subscriber->IsEmpty )
                {
                    m_Subscribers.erase(Subscriber);
                }
            }
        }

        template <typename TSender, typename TArgs>
        void Unsubscribe(const winrt::Windows::Foundation::IInspectable& Target)
        {
            if ( Target == nullptr )
            {
                throw winrt::hresult_invalid_argument(L"Argument Null Exception: Target");
            }

            std::lock_guard<std::mutex> Lock{ m_Sync };

            auto Subscriber = std::ranges::find_if(m_Subscribers, [&](const auto& Sub) { return Sub.Target == Target; });

            if ( Subscriber != std::ranges::end(m_Subscribers) )
            {
                Subscriber->RemoveSubscription<TSender, TArgs>();

                if ( Subscriber->IsEmpty )
                {
                    m_Subscribers.erase(Subscriber);
                }
            }
        }

        MERCATEC_SERVICES_API void Unsubscribe(const winrt::Windows::Foundation::IInspectable& Target);

        template <typename TSender, typename TArgs>
        void Send(TSender&& Sender, const std::wstring_view Message, TArgs&& Args)
        {
            for ( auto Subscriber : GetSubscribersSnapshot() )
            {
                // Avoid sending message to self
                if ( Subscriber.Target != Sender )
                {
                    Subscriber.TryInvoke(std::forward<TSender>(Sender), Message, std::forward<TArgs>(Args));
                }
            }
        }

    private:
        MERCATEC_SERVICES_API std::vector<Subscriber> GetSubscribersSnapshot() noexcept;

        std::vector<Subscriber> m_Subscribers;
        std::mutex              m_Sync;
    };

} // namespace Mercatec::Services

#pragma warning(pop)