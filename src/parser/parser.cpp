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
    
    auto raw_version = request_line_parts[2].substr(version_prefix.length());
    string_vector version_parts = split_string(raw_version, '.');
    if (version_parts.size() != 2) return ParserStatusCode::INVALID_REQUEST;

    m_http_version.major = std::stoi(version_parts[0]);
    m_http_version.minor = std::stoi(version_parts[1]);

    // Get headers
    auto header_start = std::next(request_lines.begin(), 1);    // Headers begin on the second line
    std::size_t header_end = 1;                                 // Keep track of where header section ends
    for (auto it = header_start; it != request_lines.end(); ++it)
    {
        if (is_empty_or_whitespace(it->data())) break;     // A blank line indicates the end of the header section

        // Split the header name from value
        std::size_t header_split_pos = it->find(':');

        if (header_split_pos != std::string::npos)
        {
            auto header_name = std::string_view(it->data(), header_split_pos);
            auto header_value = std::string_view(it->data() + header_split_pos + 1, 
                                                 it->size() - header_split_pos - 1);
            header_value = trim_whitespace(header_value);

            m_headers.emplace(header_name, header_value);
        }

        ++header_end;
    }

    // A host header is required for HTTP/1.1
    if (m_headers.find("Host") == m_headers.end()) return ParserStatusCode::MISSING_HEADER;

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

string_map HttpParser::get_headers() const
{
    return m_headers;
}
