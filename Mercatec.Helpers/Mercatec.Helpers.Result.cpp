#include "pch.h"
#include "Mercatec.Helpers.Result.h"
#if __has_include("Result.g.cpp")
# include "Result.g.cpp"
#endif

#include "Mercatec.Helpers.Strings.hpp"
#include "Mercatec.Helpers.Types.hpp"

using namespace Mercatec::Helpers::Strings;
using namespace Mercatec::Types;

namespace winrt::Mercatec::Helpers::implementation
{
    Result::Result() noexcept
      : m_IsOk{ false }
      , m_Message{ Empty<Char> }
      , m_Description{ Empty<Char> }
      , m_HResult{ winrt::impl::error_ok }
    {
    }

    bool Result::IsOk() const noexcept
    {
        return m_IsOk;
    }

    void Result::IsOk(const bool Value) noexcept
    {
        m_IsOk = Value;
    }

    hstring Result::Message() const noexcept
    {
        return m_Message;
    }

    void Result::Message(const std::wstring_view Value) noexcept
    {
        m_Message = Value;
    }

    hstring Result::Description() const noexcept
    {
        return m_Description;
    }

    void Result::Description(const std::wstring_view Value) noexcept
    {
        m_Description = Value;
    }

    hresult Result::HResult() const noexcept
    {
        return m_HResult;
    }

    void Result::HResult(const hresult Value) noexcept
    {
        m_HResult = Value;
    }

    hstring Result::ToString() const noexcept
    {
        return hstring{ std::format(L"{}\r\n{}", m_Message, m_Description) };
    }

    Helpers::Result Result::Ok() noexcept
    {
        return Ok(Empty<Char>, Empty<Char>);
    }

    Helpers::Result Result::Ok(const hstring& Message) noexcept
    {
        return Ok(Message, Empty<Char>);
    }

    Helpers::Result Result::Ok(const hstring& Message, const hstring& Description) noexcept
    {
        Helpers::Result result;
        result.IsOk(true);
        result.Message(Message);
        result.Description(Description);
        result.HResult(winrt::impl::error_ok);
        return result;
    }

    Helpers::Result Result::Error(const hstring& Message) noexcept
    {
        return Error(Message, Empty<Char>);
    }

    Helpers::Result Result::Error(const hstring& Message, const hstring& Description) noexcept
    {
        Helpers::Result result;
        result.IsOk(false);
        result.Message(Message);
        result.Description(Description);
        result.HResult(winrt::impl::error_fail);
        return result;
    }

    Helpers::Result Result::Error(const hresult Code, const hstring& Message) noexcept
    {
        Helpers::Result result;
        result.IsOk(false);
        result.Message(Message);
        result.Description(L"hresult_error");
        result.HResult(Code);
        return result;
    }
} // namespace winrt::Mercatec::Helpers::implementation
