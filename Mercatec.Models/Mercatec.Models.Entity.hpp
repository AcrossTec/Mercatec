#pragma once

#include "Mercatec.Models.Exports.Api.hpp"
#include "Mercatec.Helpers.Types.hpp"

namespace Mercatec::Models
{
    struct MERCATEC_MODELS_API Entity abstract
    {
        Entity() noexcept;
        virtual ~Entity() noexcept;

        DateTime           CreatedDate;
        Nullable<DateTime> ModifiedDate;
        Nullable<DateTime> DeletedDate;
        Boolean            IsEdit;
        Boolean            IsDelete;
    };
} // namespace Mercatec::Models
