#include <sstream>
#include <string>
#include <string_view>
#include <vector>
#include "string_utilities.h"

STRING_UTILITIES_API string_vector split_string(const std::string_view str, char delimiter)
{
    string_vector tokens;
    size_t start = 0;
    size_t end = str.find(delimiter);

    while (end != std::string_view::npos)
    {
        tokens.emplace_back(str.substr(start, end - start));
        start = end + 1;
        end = str.find(delimiter, start);
    }

    tokens.emplace_back(str.substr(start));

    return tokens;
}

STRING_UTILITIES_API string_vector split_string_by_newline(const std::string_view str)
{
    string_vector lines;
    std::istringstream stream { std::string(str) };
    std::string line;

    while (std::getline(stream, line))
    {
        lines.push_back(line);
    }

    return lines;
}