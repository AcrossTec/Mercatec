#pragma once

#ifdef MERCATEC_APPLICATION_API_EXPORTS
# define MERCATEC_APPLICATION_API __declspec(dllexport)
#else
# define MERCATEC_APPLICATION_API __declspec(dllimport)
#endif
