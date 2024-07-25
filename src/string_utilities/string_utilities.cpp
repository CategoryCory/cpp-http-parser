#include <sstream>
#include <string>
#include <vector>
#include "string_utilities.h"

STRING_UTILITIES_API std::vector<std::string> split_string(const std::string &str, char delimiter)
{
    std::string token;
    std::vector<std::string> tokens;
    std::istringstream token_stream(str);

    while (std::getline(token_stream, token, delimiter))
    {
        tokens.push_back(token);
    }

    return tokens;
}