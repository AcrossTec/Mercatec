#pragma once

#include "Mercatec.Models.PassportDevice.hpp"

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
