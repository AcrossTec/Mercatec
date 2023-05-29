#pragma once
#ifdef _DEBUG
# include <Windows.h>

# include <winrt/Windows.Foundation.h>
# include <winrt/Windows.Foundation.Collections.h>

# include <format>
# include <iterator>
# include <string_view>

namespace Mercatec::WinUIEx
{
    template <typename... Types>
    void OutputDebug(const std::wstring_view format, Types&&... arguments)
    {
        std::wstring output;
        std::vformat_to(std::back_inserter(output), format, std::make_wformat_args(std::forward<Types>(arguments)...));
        OutputDebugStringW(output.c_str());
    }

    template <typename Type>
    void OutputDebug(const winrt::Windows::Foundation::Collections::IObservableVector<Type>& values, const std::wstring_view message = L"")
    {
        OutputDebug(L"{}\n", std::wstring(15, L'-'));

        if ( not message.empty() )
        {
            OutputDebug(L"Message: {}\n", message);
        }

        for ( int32_t index = -1; const auto& value : values )
        {
            OutputDebug(L"[{}]: {}\n", ++index, value);
        }

        OutputDebug(L"{}\n", std::wstring(15, L'-'));
    }

} // namespace Mercatec::WinUIEx
#else
# define OutputDebug(...)
#endif
