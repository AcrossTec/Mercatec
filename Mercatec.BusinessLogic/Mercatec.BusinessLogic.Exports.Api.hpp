#pragma once

#ifdef MERCATEC_BUSINESS_LOGIC_API_EXPORTS
# define MERCATEC_BUSINESS_LOGIC_API __declspec(dllexport)
#else
# define MERCATEC_BUSINESS_LOGIC_API __declspec(dllimport)
#endif
