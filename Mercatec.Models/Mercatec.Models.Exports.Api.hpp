#pragma once

#ifdef MERCATEC_MODELS_API_EXPORTS
# define MERCATEC_MODELS_API __declspec(dllexport)
#else
# define MERCATEC_MODELS_API __declspec(dllimport)
#endif
