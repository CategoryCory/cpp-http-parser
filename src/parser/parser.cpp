#include <string>
#include <vector>
#include "parser.h"
#include "string_utilities.h"

HttpParser::HttpParser() : m_method("") {}

ParserStatusCode HttpParser::parse_request(const std::string &request)
{
    std::vector<std::string> request_line_parts = split_string(request, ' ');
    if (request_line_parts.size() != 3)
    {
        return ParserStatusCode::INVALID_METHOD;
    }
    m_method = request_line_parts[0];
    return ParserStatusCode::SUCCESS;
}

std::string HttpParser::get_method() const
{
    return m_method;
}
