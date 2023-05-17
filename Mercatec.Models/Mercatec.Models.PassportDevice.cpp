#include "pch.h"
#include "Mercatec.Models.PassportDevice.hpp"
#include "Mercatec.Helpers.Strings.hpp"

using Mercatec::Helpers::Empty;

Mercatec::Models::PassportDevice::PassportDevice() noexcept
  : DeviceId{ Empty<Char> } // Note: Only UWP Package: DeviceId{ GuidHelper::Empty() }
{
}

Mercatec::Models::PassportDevice::~PassportDevice() noexcept
{
}
