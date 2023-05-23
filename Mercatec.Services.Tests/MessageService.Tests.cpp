#include "pch.h"
#include <Mercatec.Services.MessageService.hpp>

#pragma push_macro("WINRT_LEAN_AND_MEAN")
#undef WINRT_LEAN_AND_MEAN
#include <winrt/Mercatec.Helpers.h>
#pragma pop_macro("WINRT_LEAN_AND_MEAN")

using namespace Mercatec::Services;
using namespace std::string_view_literals;

using AgileObject = winrt::Mercatec::Helpers::IAgileObject;

struct Sender : winrt::implements<Sender, AgileObject>
{
};

struct Client : winrt::implements<Client, AgileObject>
{
};

template <typename TValue>
struct Argument
{
    TValue Value;
};

TEST(MessageServiceTests, Subscriptions)
{
    auto DefaultSender{ winrt::make_self<Sender>() };
    bool InvokedString{ false }, InvokedInt32{ false };

    Subscriptions Subs;
    EXPECT_TRUE(Subs.IsEmpty);

    Subs.AddSubscription(
      [&](const winrt::com_ptr<Sender>& Sender, const std::wstring_view Message, const Argument<std::wstring>& Arg)
      {
          EXPECT_EQ(DefaultSender.get(), Sender.get());
          EXPECT_EQ(Message, L"Argument::String");
          EXPECT_EQ(Arg.Value, L"Argument::Value");

          InvokedString = true;
      }
    );

    EXPECT_FALSE(Subs.IsEmpty);
    EXPECT_FALSE(InvokedString);

    Subs.TryInvoke(DefaultSender, L"Argument::String", Argument<std::wstring>{ L"Argument::Value" });

    EXPECT_TRUE(InvokedString);

    InvokedString = false;

    Subs.AddSubscription(
      [&](const winrt::com_ptr<Sender>& Sender, const std::wstring_view Message, const Argument<int32_t>& Arg)
      {
          EXPECT_EQ(DefaultSender.get(), Sender.get());
          EXPECT_EQ(Message, L"Argument::Int32");
          EXPECT_EQ(Arg.Value, 1'024);

          InvokedInt32 = true;
      }
    );

    EXPECT_FALSE(InvokedString);
    EXPECT_FALSE(InvokedInt32);

    Subs.TryInvoke(DefaultSender, L"Argument::Int32", Argument<int32_t>{ 1'024 });

    EXPECT_FALSE(InvokedString);
    EXPECT_TRUE(InvokedInt32);

    Subs.TryInvoke(DefaultSender, L"Argument::String", Argument<std::wstring>{ L"Argument::Value" });

    EXPECT_TRUE(InvokedString);
    EXPECT_TRUE(InvokedInt32);

    InvokedString = false;
    InvokedInt32  = false;

    Subs.RemoveSubscription<Argument<std::wstring>>();
    EXPECT_FALSE(Subs.IsEmpty);

    Subs.TryInvoke(DefaultSender, L"Argument::String", Argument<std::wstring>{ L"Argument::Value" });

    EXPECT_FALSE(InvokedString);
    EXPECT_FALSE(InvokedInt32);

    Subs.RemoveSubscription<Argument<int32_t>>();
    EXPECT_TRUE(Subs.IsEmpty);

    Subs.TryInvoke(DefaultSender, L"Argument::Int32", Argument<int32_t>{ 1'024 });

    EXPECT_FALSE(InvokedString);
    EXPECT_FALSE(InvokedInt32);
}

TEST(MessageServiceTests, Subscriber)
{
    auto    DefaultClient{ winrt::make_self<Client>() };
    auto    DefaultSender{ winrt::make_self<Sender>() };
    int32_t InvokeStringCount{ 0 }, InvokeInt32Count{ 0 };

    Subscriber Subs{ *DefaultClient };

    EXPECT_NE(Subs.Target, nullptr);
    EXPECT_EQ(Subs.Target, *DefaultClient);
    EXPECT_TRUE(Subs.IsEmpty);

    Subs.AddSubscription(
      [&](const winrt::com_ptr<Sender>& Sender, const std::wstring_view Message, const Argument<int32_t>& Arg)
      {
          EXPECT_EQ(DefaultSender.get(), Sender.get());
          EXPECT_EQ(Message, L"Subscriber::Argument::Int32");
          EXPECT_EQ(Arg.Value, 1'024);
          ++InvokeInt32Count;
      }
    );

    Subs.AddSubscription(
      [&](const winrt::com_ptr<Sender>& Sender, const std::wstring_view Message, const Argument<std::wstring_view>& Arg)
      {
          EXPECT_EQ(DefaultSender.get(), Sender.get());

          if ( not Message.ends_with(L"Version #2") )
          {
              EXPECT_EQ(Message, L"Subscriber::Argument::StringView");
          }
          else
          {
              EXPECT_EQ(Message, L"Subscriber::Argument::StringView Version #2");
          }

          EXPECT_EQ(Arg.Value, L"Argument<WStringView>");
          ++InvokeStringCount;
      }
    );

    EXPECT_EQ(InvokeStringCount, 0);
    EXPECT_FALSE(Subs.IsEmpty);

    Subs.TryInvoke(DefaultSender, L"Subscriber::Argument::StringView", Argument<std::wstring_view>{ L"Argument<WStringView>" });
    EXPECT_EQ(InvokeStringCount, 1);

    Subs.AddSubscription(
      [&](const winrt::com_ptr<Sender>& Sender, const std::wstring_view Message, const Argument<std::wstring_view>& Arg)
      {
          EXPECT_EQ(DefaultSender.get(), Sender.get());
          EXPECT_EQ(Message, L"Subscriber::Argument::StringView Version #2");
          EXPECT_EQ(Arg.Value, L"Argument<WStringView>");
          ++InvokeStringCount;
      }
    );

    Subs.TryInvoke(DefaultSender, L"Subscriber::Argument::StringView Version #2", Argument<std::wstring_view>{ L"Argument<WStringView>" });
    EXPECT_EQ(InvokeStringCount, 3);

    Subs.TryInvoke(DefaultSender, L"Subscriber::Argument::Int32", Argument{ 1'024 });
    EXPECT_EQ(InvokeInt32Count, 1);

    Subs.RemoveSubscription<winrt::com_ptr<Sender>&, Argument<std::wstring_view>>();
    EXPECT_FALSE(Subs.IsEmpty);

    Subs.TryInvoke(DefaultSender, L"Subscriber::Argument::StringView", Argument<std::wstring_view>{ L"Argument<WStringView>" });
    EXPECT_EQ(InvokeStringCount, 3);

    DefaultClient = nullptr;
    EXPECT_EQ(Subs.Target, nullptr);

    Subs.TryInvoke(DefaultSender, L"Subscriber::Argument::Int32", Argument{ 1'024 });
    EXPECT_EQ(InvokeInt32Count, 1);

    Subs.RemoveSubscription<winrt::com_ptr<Sender>&>();
    EXPECT_TRUE(Subs.IsEmpty);
}

TEST(MessageServiceTests, MessageService)
{
    auto DefaultClient{ winrt::make_self<Client>() };
    auto DefaultSender{ winrt::make_self<Sender>() };
    auto Subs{ winrt::make_self<MessageService>() };

    int32_t InvokeStringCount{ 0 }, InvokeInt32Count{ 0 };
    EXPECT_TRUE(Subs->IsEmpty);

    Subs->Subscribe(
      *DefaultClient,
      [&](const Sender& Sender, const std::wstring_view Message, const winrt::IInspectable Arg)
      {
          EXPECT_EQ(DefaultSender.get(), std::addressof(Sender));
          EXPECT_EQ(Message, L"MessageServiceTests::WString::Invoke");
          EXPECT_EQ(winrt::unbox_value<winrt::hstring>(Arg), L"Param");
          ++InvokeStringCount;
      }
    );

    Subs->Send(*DefaultSender, L"MessageServiceTests::WString::Invoke", winrt::box_value(L"Param"));
    EXPECT_EQ(InvokeStringCount, 1);

    Subs->Subscribe(
      *DefaultClient,
      [&](const Sender& Sender, const std::wstring_view Message, const int32_t Arg)
      {
          EXPECT_EQ(DefaultSender.get(), std::addressof(Sender));
          EXPECT_EQ(Message, L"MessageServiceTests::Int32::Invoke");
          EXPECT_EQ(Arg, 1'024);
          ++InvokeInt32Count;
      }
    );

    Subs->Send(*DefaultSender, L"MessageServiceTests::Int32::Invoke", 1'024);
    EXPECT_EQ(InvokeInt32Count, 1);

    Subs->Subscribe(
      *DefaultClient,
      [&](const Sender& Sender, const std::wstring_view Message, const std::wstring_view Arg)
      {
          EXPECT_EQ(DefaultSender.get(), std::addressof(Sender));
          EXPECT_EQ(Message, L"MessageServiceTests::WString::Invoke");
          EXPECT_EQ(Arg, L"Param");
          ++InvokeStringCount;
      }
    );

    Subs->Send(*DefaultSender, L"MessageServiceTests::WString::Invoke", L"Param"sv);
    EXPECT_EQ(InvokeStringCount, 2);

    Subs->Unsubscribe<Sender&, winrt::IInspectable>(*DefaultClient);
    Subs->Send(*DefaultSender, L"MessageServiceTests::WString::Invoke", winrt::box_value(L"Param"));
    EXPECT_EQ(InvokeStringCount, 2);
    EXPECT_FALSE(Subs->IsEmpty);

    Subs->Unsubscribe<Sender&>(*DefaultClient);
    Subs->Send(*DefaultSender, L"MessageServiceTests::Int32::Invoke", 1'024);
    EXPECT_EQ(InvokeInt32Count, 1);
    EXPECT_TRUE(Subs->IsEmpty);

    Subs->Subscribe(
      *DefaultClient,
      [&](const Sender& Sender, const std::wstring_view Message, const int32_t Arg)
      {
          EXPECT_EQ(DefaultSender.get(), std::addressof(Sender));
          EXPECT_EQ(Message, L"MessageServiceTests::Int32::Invoke");
          EXPECT_EQ(Arg, 1'024);
          ++InvokeInt32Count;
      }
    );

    Subs->Send(*DefaultSender, L"MessageServiceTests::Int32::Invoke", 1'024);
    EXPECT_EQ(InvokeInt32Count, 2);

    Subs->Unsubscribe(*DefaultClient);
    Subs->Send(*DefaultSender, L"MessageServiceTests::Int32::Invoke", 1'024);
    EXPECT_EQ(InvokeInt32Count, 2);
    EXPECT_TRUE(Subs->IsEmpty);
}
