#pragma once

#include <Windows.h>

#include <format>
#include <string_view>
#include <iterator>

namespace Mercatec::Helpers
{
    template <typename... Types>
    void OutputDebug(const std::wstring_view format, Types&&... arguments)
    {
        std::wstring output;
        std::vformat_to(std::back_inserter(output), format, std::make_wformat_args(std::forward<Types>(arguments)...));
        OutputDebugStringW(output.c_str());
    }
} // namespace Mercatec::Helpers
