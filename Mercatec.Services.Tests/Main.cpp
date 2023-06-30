#include "pch.h"

using namespace winrt;

extern void LoadExternalDLLFiles();

int32_t main(int32_t argc, char** argv)
{
    init_apartment();
    Uri uri(L"http://aka.ms/cppwinrt");
    printf("Hello, %ls!\n", uri.AbsoluteUri().c_str());

    LoadExternalDLLFiles();

    printf("\n__cplusplus = %ld", __cplusplus);
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
