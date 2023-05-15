#pragma once

#include "IndexRange.g.h"

namespace winrt::Mercatec::Helpers::implementation
{
    struct IndexRange : IndexRangeT<IndexRange>
    {
    public:
        IndexRange();

        void    Index(const int32_t index) noexcept;
        int32_t Index() const noexcept;

        void    Length(const int32_t length) noexcept;
        int32_t Length() const noexcept;

    private:
        int32_t m_Index;
        int32_t m_Length;
    };
} // namespace winrt::Mercatec::Helpers::implementation

namespace winrt::Mercatec::Helpers::factory_implementation
{
    struct IndexRange : IndexRangeT<IndexRange, implementation::IndexRange>
    {
    };
} // namespace winrt::Mercatec::Helpers::factory_implementation
