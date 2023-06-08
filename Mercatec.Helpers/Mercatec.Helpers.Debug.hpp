#pragma once
#ifdef _DEBUG
# include <Windows.h>

# include <winrt/Windows.Foundation.h>
# include <winrt/Windows.Foundation.Collections.h>

# include <format>
# include <iterator>
# include <string_view>
# include <ranges>

namespace Mercatec::Helpers::inline Debug
{
    template <typename... Types>
    void OutputDebug(const std::wstring_view format, Types&&... arguments)
    {
        std::wstring output;
        std::vformat_to(std::back_inserter(output), format, std::make_wformat_args(std::forward<Types>(arguments)...));
        OutputDebugStringW(output.c_str());
    }

    template <std::ranges::range Range> // clang-format off
    requires
    (
           not std::is_constructible_v<std::string_view, Range>
       and not std::is_constructible_v<std::wstring_view, Range>
    )
    void OutputDebug(Range&& values, const std::wstring_view message = L"") // clang-format on
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
} // namespace Mercatec::Helpers::inline Debug
#else

namespace Mercatec::Helpers::inline Debug
{
    template <typename... Types>
    inline constexpr void OutputDebug(const std::wstring_view, Types&&...)
    {
    }

    template <typename Type>
    inline constexpr void OutputDebug(const winrt::Windows::Foundation::Collections::IObservableVector<Type>&, const std::wstring_view = L"")
    {
    }
} // namespace Mercatec::Helpers::inline Debug

#endif