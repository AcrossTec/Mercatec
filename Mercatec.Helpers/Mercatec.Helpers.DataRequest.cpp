#include "pch.h"
#include "Mercatec.Helpers.DataRequest.h"
#if __has_include("DataRequest.g.cpp")
# include "DataRequest.g.cpp"
#endif

#include "Mercatec.Helpers.Types.hpp"
#include "Mercatec.Helpers.Strings.hpp"

using namespace Mercatec::Types;
using Mercatec::Helpers::Empty;

namespace winrt::Mercatec::Helpers::implementation
{
    DataRequest::DataRequest() noexcept
      : m_Query{ Empty<Char> }
      , m_Where{ nullptr }
      , m_OrderBy{ nullptr }
      , m_OrderByDesc{ nullptr }
    {
    }

    hstring DataRequest::Query() const noexcept
    {
        return m_Query;
    }

    void DataRequest::Query(const std::wstring_view Value) noexcept
    {
        m_Query = Value;
    }

    SQLExpressionFunc DataRequest::Where() const noexcept
    {
        return m_Where;
    }

    void DataRequest::Where(const SQLExpressionFunc& Expression) noexcept
    {
        m_Where = Expression;
    }

    SQLExpressionFunc DataRequest::OrderBy() const noexcept
    {
        return m_OrderBy;
    }

    void DataRequest::OrderBy(const SQLExpressionFunc& Expression) noexcept
    {
        m_OrderBy = Expression;
    }

    SQLExpressionFunc DataRequest::OrderByDesc() const noexcept
    {
        return m_OrderByDesc;
    }

    void DataRequest::OrderByDesc(const SQLExpressionFunc& Expression) noexcept
    {
        m_OrderByDesc = Expression;
    }

} // namespace winrt::Mercatec::Helpers::implementation
