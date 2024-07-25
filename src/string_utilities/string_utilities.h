#pragma once

#include <string>
#include <string_view>
#include <vector>
#include "type_aliases.h"

#if defined(_WIN32) || defined(_WIN64)
    #ifdef STRING_UTILITIES_EXPORTS
        #define STRING_UTILITIES_API __declspec(dllexport)
    #else
        #define STRING_UTILITIES_API __declspec(dllimport)
    #endif
#else
    #define STRING_UTILITIES_API
#endif

STRING_UTILITIES_API string_vector split_string(std::string_view str, char delimiter);