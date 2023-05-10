#include "pch.h"
#include "Mercatec.Models.UserAccount.hpp"

Mercatec::Models::UserAccount::UserAccount() noexcept
  : UserId{ GuidHelper::Empty() }
{
}

Mercatec::Models::UserAccount::~UserAccount() noexcept
{
}
