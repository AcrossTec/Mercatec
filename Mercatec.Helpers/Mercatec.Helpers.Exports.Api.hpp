#pragma once

#ifdef MERCATEC_HELPERS_API_EXPORTS
# define MERCATEC_HELPERS_API __declspec(dllexport)
#else
# define MERCATEC_HELPERS_API __declspec(dllimport)
#endif
