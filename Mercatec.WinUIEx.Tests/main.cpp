#include "pch.h"

using namespace winrt;

struct App : Microsoft::UI::Xaml::ApplicationT<App>
{
    App(const int32_t argc, char** argv) noexcept
      : argc{ argc }
      , argv{ argv }
    {
    }

    void OnLaunched(const Microsoft::UI::Xaml::LaunchActivatedEventArgs&) const
    {
        Microsoft::UI::Xaml::Application::Current() //
          .Resources()
          .Insert(box_value(L"AppName"), box_value(L"Mercatec"));

        printf("\n__cplusplus = %ld", __cplusplus);

        int32_t argc = this->argc;
        ::testing::InitGoogleTest(&argc, argv);
        ::RUN_ALL_TESTS();

        Exit();
    }

    int32_t argc;
    char**  argv;
};

int32_t main(int32_t argc, char** argv)
{
    init_apartment();
    Uri uri(L"http://aka.ms/cppwinrt");
    printf("Hello, %ls!\n", uri.AbsoluteUri().c_str());

    Microsoft::UI::Xaml::Application::Start( //
      [&](auto&&)                            //
      {                                      //
          ::winrt::make<App>(argc, argv);
      }
    );
}
