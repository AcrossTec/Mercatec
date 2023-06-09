#pragma once

#include "Models.AppLogModel.g.h"
#include "Mercatec.Helpers.ViewModels.Entity.hpp"

namespace winrt::Mercatec::Helpers::Models::implementation
{
    struct AppLogModel : AppLogModelT<AppLogModel>, ::Mercatec::Helpers::ViewModels::EntityModel
    {
    public:
        using DateTime    = winrt::Windows::Foundation::DateTime;
        using RefDateTime = winrt::Windows::Foundation::IReference<winrt::Windows::Foundation::DateTime>;

        AppLogModel() noexcept;
        static Models::AppLogModel CreateEmpty();

        guid AppLogId() const noexcept;
        void AppLogId(const guid& Value) noexcept;

        bool IsRead() const noexcept;
        void IsRead(const bool Value) noexcept;

        DateTime DateTimeOffset() const noexcept;
        void     DateTimeOffset(const DateTime& Value) noexcept;

        hstring User() const noexcept;
        void    User(const std::wstring_view Value) noexcept;

        LogType Type() const noexcept;
        void    Type(const LogType Value) noexcept;

        hstring Source() const noexcept;
        void    Source(const std::wstring_view Value) noexcept;

        hstring Action() const noexcept;
        void    Action(const std::wstring_view Value) noexcept;

        hstring Message() const noexcept;
        void    Message(const std::wstring_view Value) noexcept;

        hstring Description() const noexcept;
        void    Description(const std::wstring_view Value) noexcept;

        bool IsEmpty() const noexcept;
        void IsEmpty(const bool Value) noexcept;

    private:
        guid     m_AppLogId;
        bool     m_IsRead;
        DateTime m_DateTimeOffset;
        hstring  m_User;
        LogType  m_Type;
        hstring  m_Source;
        hstring  m_Action;
        hstring  m_Message;
        hstring  m_Description;
        bool     m_IsEmpty;
    };
} // namespace winrt::Mercatec::Helpers::Models::implementation

namespace winrt::Mercatec::Helpers::Models::factory_implementation
{
    struct AppLogModel : AppLogModelT<AppLogModel, implementation::AppLogModel>
    {
    };
} // namespace winrt::Mercatec::Helpers::Models::factory_implementation
