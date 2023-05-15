#include "pch.h"
#include "Mercatec.Helpers.IndexRange.h"
#if __has_include("IndexRange.g.cpp")
# include "IndexRange.g.cpp"
#endif

namespace winrt::Mercatec::Helpers::implementation
{
    IndexRange::IndexRange()
      : m_Index{ 0 }
      , m_Length{ 0 }
    {
    }

    void IndexRange::Index(const int32_t index) noexcept
    {
        m_Index = index;
    }

    int32_t IndexRange::Index() const noexcept
    {
        return m_Index;
    }

    void IndexRange::Length(const int32_t length) noexcept
    {
        m_Length = length;
    }

    int32_t IndexRange::Length() const noexcept
    {
        return m_Length;
    }
} // namespace winrt::Mercatec::Helpers::implementation
