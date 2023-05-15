#pragma once

#include "Mercatec.Models.PassportDevice.hpp"

#pragma warning(push)
//! Compiler Warning (level 1) C4251
//! 'type' : class 'type1' needs to have dll-interface to be used by clients of class 'type2'
//! https://learn.microsoft.com/en-us/cpp/error-messages/compiler-warnings/compiler-warning-level-1-c4251?view=msvc-170
#pragma warning(disable : 4251)

namespace Mercatec::Models
{
    struct MERCATEC_MODELS_API UserAccount : public Entity
    {
        UserAccount() noexcept;
        virtual ~UserAccount() noexcept;

        Guid   UserId;
        String UserName;
        String Email;
        String Phone;
        String Address;
        String Password;

        std::vector<PassportDevice> PassportDevices;
    };
} // namespace Mercatec::Models

#pragma warning(pop)