#pragma once

#include <string>
#include <vector>

#if defined(_WIN32) || defined(_WIN64)
    #ifdef STRING_UTILITIES_EXPORTS
        #define STRING_UTILITIES_API __declspec(dllexport)
    #else
        #define STRING_UTILITIES_API __declspec(dllimport)
    #endif
#else
    #define STRING_UTILITIES_API
#endif

STRING_UTILITIES_API std::vector<std::string> split_string(const std::string &str, char delimiter);