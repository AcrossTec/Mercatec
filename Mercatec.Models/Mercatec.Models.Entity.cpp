#include "pch.h"
#include "Mercatec.Models.Entity.hpp"

Mercatec::Models::Entity::Entity() noexcept
  : CreatedDate{ DateTime::clock::now() }
  , ModifiedDate{ std::nullopt }
  , DeletedDate{ std::nullopt }
  , IsEdit{ false }
  , IsDelete{ false }
{
}

Mercatec::Models::Entity::~Entity() noexcept
{
}
