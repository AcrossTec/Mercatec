#pragma once

#ifdef MERCATEC_WINUIEX_API_EXPORTS
# define MERCATEC_WINUIEX_API __declspec(dllexport)
#else
# define MERCATEC_WINUIEX_API __declspec(dllimport)
#endif
