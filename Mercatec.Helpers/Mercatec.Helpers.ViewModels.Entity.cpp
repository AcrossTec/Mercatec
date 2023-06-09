#include "pch.h"
#include "Mercatec.Helpers.ViewModels.Entity.hpp"

namespace Mercatec::Helpers::ViewModels
{
    NotifyProperty::NotifyProperty() noexcept
      : m_PropertyChanged{}
    {
    }

    EntityModel::EntityModel() noexcept
      : m_CreatedDate{ DateTime::clock::now() }
      , m_ModifiedDate{ nullptr }
      , m_DeletedDate{ nullptr }
      , m_IsEdit{ false }
      , m_IsDelete{ false }
    {
    }
} // namespace Mercatec::Helpers::ViewModels
