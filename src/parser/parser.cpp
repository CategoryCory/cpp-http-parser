#include <string>
#include <unordered_set>
#include <vector>
#include "parser.h"
#include "string_utilities.h"

HttpParser::HttpParser() = default;

const string_set HttpParser::m_valid_http_methods = 
{
    "GET", "POST", "PUT", "DELETE", "HEAD", "OPTIONS", "PATCH", "TRACE", "CONNECT"
};

ParserStatusCode HttpParser::parse_request(const std::string &request)
{
    // Make sure request isn't empty
    if (request.empty()) return ParserStatusCode::INVALID_REQUEST;

    // Split request into lines
    string_vector request_lines = split_string_by_newline(request);

    // A valid header must include at minimum a request line and a host header
    if (request_lines.size() < 2) return ParserStatusCode::INVALID_REQUEST;

    // Split request line into method, path, and version
    string_vector request_line_parts = split_string(request_lines[0], ' ');
    if (request_line_parts.size() != 3) return ParserStatusCode::INVALID_REQUEST;

    // Get request method
    if (!is_valid_method(request_line_parts[0])) return ParserStatusCode::INVALID_METHOD;
    m_method = request_line_parts[0];

    // Get request path
    m_path = request_line_parts[1];

    // Get HTTP version
    std::string version_prefix("HTTP/");
    if (!request_line_parts[2].starts_with(version_prefix)) return ParserStatusCode::INVALID_REQUEST;
    
    auto slash_position = request_line_parts[2].find('/');
    auto raw_version = request_line_parts[2].substr(slash_position + 1);
    string_vector version_parts = split_string(raw_version, '.');
    if (version_parts.size() != 2) return ParserStatusCode::INVALID_REQUEST;

    m_http_version.major = std::stoi(version_parts[0]);
    m_http_version.minor = std::stoi(version_parts[1]);

    return ParserStatusCode::SUCCESS;
}

bool HttpParser::is_valid_method(const std::string &method) const
{
    return m_valid_http_methods.find(method) != m_valid_http_methods.end();
}

std::string HttpParser::get_method() const
{
    return m_method;
}

std::string HttpParser::get_path() const
{
    return m_path;
}

HttpVersion HttpParser::get_version() const
{
    return m_http_version;
}
