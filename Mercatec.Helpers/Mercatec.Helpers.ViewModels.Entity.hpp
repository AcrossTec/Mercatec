#pragma once

#include <winrt/Mercatec.Helpers.ViewModels.h>

#include <Mercatec.Helpers.Exports.Api.hpp>
#include <Mercatec.Helpers.Models.hpp>

namespace Mercatec::Helpers::ViewModels
{
    //!
    //! winrt::Microsoft::UI::Xaml::Data::INotifyPropertyChanged
    //!
    struct NotifyProperty
    {
    public:
        MERCATEC_HELPERS_API NotifyProperty() noexcept;

        template <typename Self>
        void NotifyPropertyChanged(this Self&& self, const std::wstring_view property_name)
        {
            self.m_PropertyChanged(self, winrt::Microsoft::UI::Xaml::Data::PropertyChangedEventArgs(property_name));
        }

        template <typename Self>
        void NotifyChanges(this Self&& self)
        {
            self.NotifyPropertyChanged(L""); // Notify All Properties
        }

        template <typename Self>
        winrt::event_token PropertyChanged(this Self&& self, const winrt::Microsoft::UI::Xaml::Data::PropertyChangedEventHandler& handler)
        {
            return self.m_PropertyChanged.add(handler);
        }

        template <typename Self>
        void PropertyChanged(this Self&& self, const winrt::event_token& token)
        {
            self.m_PropertyChanged.remove(token);
        }

    protected:
        winrt::event<winrt::Microsoft::UI::Xaml::Data::PropertyChangedEventHandler> m_PropertyChanged;
    };

    //!
    //! winrt::Mercatec::Helpers::ViewModels::IEntity
    //! winrt::Microsoft::UI::Xaml::Data::INotifyPropertyChanged
    //!
    struct EntityModel : NotifyProperty
    {
    public:
        using DateTime         = winrt::Windows::Foundation::DateTime;
        using NullableDateTime = winrt::Windows::Foundation::IReference<winrt::Windows::Foundation::DateTime>;

        MERCATEC_HELPERS_API EntityModel() noexcept;

        template <typename Self>
        void CreatedDate(this Self&& self, const DateTime& created_date) noexcept
        {
            if ( self.m_CreatedDate != created_date )
            {
                self.m_CreatedDate = created_date;
                self.NotifyPropertyChanged(L"CreatedDate");
            }
        }

        template <typename Self>
        DateTime CreatedDate(this Self&& self) noexcept
        {
            return self.m_CreatedDate;
        }

        template <typename Self>
        void ModifiedDate(this Self&& self, const NullableDateTime& modified_date) noexcept
        {
            if ( NullableDateTime(self.m_ModifiedDate) != modified_date )
            {
                self.m_ModifiedDate = modified_date;
                self.NotifyPropertyChanged(L"ModifiedDate");
            }
        }

        template <typename Self>
        NullableDateTime ModifiedDate(this Self&& self) noexcept
        {
            return self.m_ModifiedDate;
        }

        template <typename Self>
        void DeletedDate(this Self&& self, const NullableDateTime& deleted_date) noexcept
        {
            if ( NullableDateTime(self.m_DeletedDate) != deleted_date )
            {
                self.m_DeletedDate = deleted_date;
                self.NotifyPropertyChanged(L"DeletedDate");
            }
        }

        template <typename Self>
        NullableDateTime DeletedDate(this Self&& self) noexcept
        {
            return self.m_DeletedDate;
        }

        template <typename Self>
        void IsEdit(this Self&& self, const bool is_edit) noexcept
        {
            if ( self.m_IsEdit != is_edit )
            {
                self.m_IsEdit = is_edit;
                self.NotifyPropertyChanged(L"IsEdit");
            }
        }

        template <typename Self>
        bool IsEdit(this Self&& self) noexcept
        {
            return self.m_IsEdit;
        }

        template <typename Self>
        void IsDelete(this Self&& self, const bool is_delete) noexcept
        {
            if ( self.m_IsDelete != is_delete )
            {
                self.m_IsDelete = is_delete;
                self.NotifyPropertyChanged(L"IsDelete");
            }
        }

        template <typename Self>
        bool IsDelete(this Self&& self) noexcept
        {
            return self.m_IsDelete;
        }

    protected:
        DateTime         m_CreatedDate;
        NullableDateTime m_ModifiedDate;
        NullableDateTime m_DeletedDate;
        bool             m_IsEdit;
        bool             m_IsDelete;
    };

    //!
    //! winrt::Mercatec::Helpers::ViewModels::IEntity
    //! winrt::Mercatec::Helpers::ViewModels::IModel
    //! winrt::Microsoft::UI::Xaml::Data::INotifyPropertyChanged
    //!
    struct Entity
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
