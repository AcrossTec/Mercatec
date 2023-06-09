#pragma once

#include "DataRequest.g.h"

namespace winrt::Mercatec::Helpers::implementation
{
    struct DataRequest : DataRequestT<DataRequest>
    {
    public:
        DataRequest() noexcept;

        hstring Query() const noexcept;
        void    Query(const std::wstring_view Value) noexcept;

        SQLExpressionFunc Where() const noexcept;
        void              Where(const SQLExpressionFunc& Expression) noexcept;

        SQLExpressionFunc OrderBy() const noexcept;
        void              OrderBy(const SQLExpressionFunc& Expression) noexcept;

        SQLExpressionFunc OrderByDesc() const noexcept;
        void              OrderByDesc(const SQLExpressionFunc& Expression) noexcept;

    private:
        hstring           m_Query;
        SQLExpressionFunc m_Where;
        SQLExpressionFunc m_OrderBy;
        SQLExpressionFunc m_OrderByDesc;
    };
} // namespace winrt::Mercatec::Helpers::implementation

namespace winrt::Mercatec::Helpers::factory_implementation
{
    struct DataRequest : DataRequestT<DataRequest, implementation::DataRequest>
    {
    };
} // namespace winrt::Mercatec::Helpers::factory_implementation
