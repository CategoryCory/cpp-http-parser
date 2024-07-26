#include <algorithm>
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

STRING_UTILITIES_API std::string_view trim_whitespace(std::string_view str)
{
    auto begin = str.begin();
    auto end = str.end();

    // Remove leading whitespace
    while (begin != end && std::isspace(*begin)) ++begin;

    // Remove trailing whitespace
    while (begin != end && std::isspace(*(end - 1))) --end;

    return std::string_view(begin, end - begin);
}

STRING_UTILITIES_API bool is_empty_or_whitespace(std::string_view str)
{
    return std::all_of(str.begin(), str.end(), [](unsigned char c) { return std::isspace(c); });
}