#pragma once

#ifdef MERCATEC_SERVICES_API_EXPORTS
# define MERCATEC_SERVICES_API __declspec(dllexport)
#else
# define MERCATEC_SERVICES_API __declspec(dllimport)
#endif
