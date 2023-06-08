#include "pch.h"
#include "Mercatec.Helpers.Strings.hpp"

namespace Mercatec::Helpers::Strings
{
    std::vector<std::wstring> SplitStrings(const std::wstring_view text) noexcept
    {
        return Split<StringSplitOptions::RemoveEmptyEntries>(text, L" "sv) | std::ranges::to<std::vector<std::wstring>>();
    }

    std::vector<winrt::hstring> SplitHStrings(const std::wstring_view text) noexcept
    {
        return Split<StringSplitOptions::RemoveEmptyEntries>(text, L" "sv) | std::ranges::to<std::vector<winrt::hstring>>();
    }
} // namespace Mercatec::Helpers::Strings
