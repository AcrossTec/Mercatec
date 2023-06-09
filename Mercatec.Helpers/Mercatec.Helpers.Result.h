#pragma once

#include "Result.g.h"

namespace winrt::Mercatec::Helpers::implementation
{
    struct Result : ResultT<Result>
    {
    public:
        Result() noexcept;

        bool IsOk() const noexcept;
        void IsOk(const bool Value) noexcept;

        hstring Message() const noexcept;
        void    Message(const std::wstring_view Value) noexcept;

        hstring Description() const noexcept;
        void    Description(const std::wstring_view Value) noexcept;

        hresult HResult() const noexcept;
        void    HResult(const hresult Value) noexcept;

        hstring ToString() const noexcept;

        static Helpers::Result Ok() noexcept;
        static Helpers::Result Ok(const hstring& Message) noexcept;
        static Helpers::Result Ok(const hstring& Message, const hstring& Description) noexcept;

        static Helpers::Result Error(const hstring& Message) noexcept;
        static Helpers::Result Error(const hstring& Message, const hstring& Description) noexcept;
        static Helpers::Result Error(const hresult Code, const hstring& Message) noexcept;

    private:
        bool    m_IsOk;
        hstring m_Message;
        hstring m_Description;
        hresult m_HResult;
    };
} // namespace winrt::Mercatec::Helpers::implementation

namespace winrt::Mercatec::Helpers::factory_implementation
{
    struct Result : ResultT<Result, implementation::Result>
    {
    };
} // namespace winrt::Mercatec::Helpers::factory_implementation
