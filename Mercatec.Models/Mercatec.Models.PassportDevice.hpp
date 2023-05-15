#pragma once

#include "Mercatec.Models.Entity.hpp"

#pragma warning(push)
//! Compiler Warning (level 1) C4251
//! 'type' : class 'type1' needs to have dll-interface to be used by clients of class 'type2'
//! https://learn.microsoft.com/en-us/cpp/error-messages/compiler-warnings/compiler-warning-level-1-c4251?view=msvc-170
#pragma warning(disable : 4251)

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

#pragma warning(pop)
