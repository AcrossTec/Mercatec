#pragma once

#ifdef MERCATEC_REPORTS_API_EXPORTS
# define MERCATEC_REPORTS_API __declspec(dllexport)
#else
# define MERCATEC_REPORTS_API __declspec(dllimport)
#endif
