#pragma once

#ifdef MERCATEC_REPOSITORIES_API_EXPORTS
# define MERCATEC_REPOSITORIES_API __declspec(dllexport)
#else
# define MERCATEC_REPOSITORIES_API __declspec(dllimport)
#endif
