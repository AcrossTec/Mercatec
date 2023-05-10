#pragma once

#include "Mercatec.Models.Entity.hpp"

namespace Mercatec::Models
{
    struct MERCATEC_MODELS_API PassportDevice : public Entity
    {
        PassportDevice() noexcept;
        virtual ~PassportDevice() noexcept;

        Guid              DeviceId;
        std::vector<Byte> PublicKey;
    };
} // namespace Mercatec::Models