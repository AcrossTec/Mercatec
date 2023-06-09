#include "pch.h"
#include "Mercatec.Helpers.Models.AppLogModel.h"
#if __has_include("Models.AppLogModel.g.cpp")
# include "Models.AppLogModel.g.cpp"
#endif

#include "Mercatec.Helpers.Types.hpp"
#include "Mercatec.Helpers.Strings.hpp"

using namespace Mercatec::Types;
using namespace Mercatec::Helpers::Strings;

namespace winrt::Mercatec::Helpers::Models::implementation
{
    AppLogModel::AppLogModel() noexcept
      : m_AppLogId{ GuidHelper::Empty() }
      , m_IsRead{ false }
      , m_DateTimeOffset{ DateTime::clock::now() }
      , m_User{ Empty<Char> }
      , m_Type{ LogType ::Information }
      , m_Source{ Empty<Char> }
      , m_Action{ Empty<Char> }
      , m_Message{ Empty<Char> }
      , m_Description{ Empty<Char> }
      , m_IsEmpty{ false }
    {
    }

    Models::AppLogModel AppLogModel::CreateEmpty()
    {
        Models::AppLogModel Default;
        Default.AppLogId(GuidHelper::Empty());
        Default.IsEmpty(true);
        return Default;
    }

    guid AppLogModel::AppLogId() const noexcept
    {
        return m_AppLogId;
    }

    void AppLogModel::AppLogId(const guid& Value) noexcept
    {
        SET_PROPERTY(m_AppLogId, Value);
    }

    bool AppLogModel::IsRead() const noexcept
    {
        return m_IsRead;
    }

    void AppLogModel::IsRead(const bool Value) noexcept
    {
        SET_PROPERTY(m_IsRead, Value);
    }

    DateTime AppLogModel::DateTimeOffset() const noexcept
    {
        return m_DateTimeOffset;
    }

    void AppLogModel::DateTimeOffset(const DateTime& Value) noexcept
    {
        SET_PROPERTY(m_DateTimeOffset, Value);
    }

    hstring AppLogModel::User() const noexcept
    {
        return m_User;
    }

    void AppLogModel::User(const std::wstring_view Value) noexcept
    {
        SET_PROPERTY(m_User, Value);
    }

    LogType AppLogModel::Type() const noexcept
    {
        return m_Type;
    }

    void AppLogModel::Type(const LogType Value) noexcept
    {
        SET_PROPERTY(m_Type, Value);
    }

    hstring AppLogModel::Source() const noexcept
    {
        return m_Source;
    }

    void AppLogModel::Source(const std::wstring_view Value) noexcept
    {
        SET_PROPERTY(m_Source, Value);
    }

    hstring AppLogModel::Action() const noexcept
    {
        return m_Action;
    }

    void AppLogModel::Action(const std::wstring_view Value) noexcept
    {
        SET_PROPERTY(m_Action, Value);
    }

    hstring AppLogModel::Message() const noexcept
    {
        return m_Message;
    }

    void AppLogModel::Message(const std::wstring_view Value) noexcept
    {
        SET_PROPERTY(m_Message, Value);
    }

    hstring AppLogModel::Description() const noexcept
    {
        return m_Description;
    }

    void AppLogModel::Description(const std::wstring_view Value) noexcept
    {
        SET_PROPERTY(m_Description, Value);
    }

    bool AppLogModel::IsEmpty() const noexcept
    {
        return m_IsEmpty;
    }

    void AppLogModel::IsEmpty(const bool Value) noexcept
    {
        SET_PROPERTY(m_IsEmpty, Value);
    }
} // namespace winrt::Mercatec::Helpers::Models::implementation
