#pragma once

#include <winrt/Mercatec.Helpers.ViewModels.h>

#include <Mercatec.Helpers.Exports.Api.hpp>
#include <Mercatec.Helpers.Models.hpp>

namespace Mercatec::Helpers::ViewModels
{
    struct Entity // : winrt::implements<Entity, winrt::Mercatec::Helpers::ViewModels::IModel, winrt::Mercatec::Helpers::ViewModels::IEntity>
    {
        using DateTime         = winrt::Windows::Foundation::DateTime;
        using NullableDateTime = winrt::Windows::Foundation::IReference<winrt::Windows::Foundation::DateTime>;

        template <typename Self>
        uint64_t Model(this Self&& self) noexcept
        {
            return reinterpret_cast<uint64_t>(std::addressof(self.m_Model));
        }

        template <typename Self>
        void CreatedDate(this Self&& self, const DateTime& created_date) noexcept
        {
            if ( self.m_Model.CreatedDate != created_date )
            {
                self.m_Model.CreatedDate = created_date;
                self.NotifyPropertyChanged(L"CreatedDate");
            }
        }

        template <typename Self>
        DateTime CreatedDate(this Self&& self) noexcept
        {
            return self.m_Model.CreatedDate;
        }

        template <typename Self>
        void ModifiedDate(this Self&& self, const NullableDateTime& modified_date) noexcept
        {
            if ( NullableDateTime(self.m_Model.ModifiedDate) != modified_date )
            {
                self.m_Model.ModifiedDate = modified_date;
                self.NotifyPropertyChanged(L"ModifiedDate");
            }
        }

        template <typename Self>
        NullableDateTime ModifiedDate(this Self&& self) noexcept
        {
            return self.m_Model.ModifiedDate;
        }

        template <typename Self>
        void DeletedDate(this Self&& self, const NullableDateTime& deleted_date) noexcept
        {
            if ( NullableDateTime(self.m_Model.DeletedDate) != deleted_date )
            {
                self.m_Model.DeletedDate = deleted_date;
                self.NotifyPropertyChanged(L"DeletedDate");
            }
        }

        template <typename Self>
        NullableDateTime DeletedDate(this Self&& self) noexcept
        {
            return self.m_Model.DeletedDate;
        }

        template <typename Self>
        void IsEdit(this Self&& self, const bool is_edit) noexcept
        {
            if ( self.m_Model.IsEdit != is_edit )
            {
                self.m_Model.IsEdit = is_edit;
                self.NotifyPropertyChanged(L"IsEdit");
            }
        }

        template <typename Self>
        bool IsEdit(this Self&& self) noexcept
        {
            return self.m_Model.IsEdit;
        }

        template <typename Self>
        void IsDelete(this Self&& self, const bool is_delete) noexcept
        {
            if ( self.m_Model.IsDelete != is_delete )
            {
                self.m_Model.IsDelete = is_delete;
                self.NotifyPropertyChanged(L"IsDelete");
            }
        }

        template <typename Self>
        bool IsDelete(this Self&& self) noexcept
        {
            return self.m_Model.IsDelete;
        }
    };
} // namespace Mercatec::Helpers::ViewModels
