#pragma once

#ifdef MERCATEC_VIEW_MODELS_API_EXPORTS
# define MERCATEC_VIEW_MODELS_API __declspec(dllexport)
#else
# define MERCATEC_VIEW_MODELS_API __declspec(dllimport)
#endif
