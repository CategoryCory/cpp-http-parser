#pragma once

#include <sstream>
#include <string>
#include <unordered_set>
#include <vector>
#include "type_aliases.h"

#if defined(_WIN32) || defined(_WIN64)
    #ifdef HTTP_PARSER_EXPORTS
        #define HTTP_PARSER_API __declspec(dllexport)
    #else
        #define HTTP_PARSER_API __declspec(dllimport)
    #endif
#else
    #define HTTP_PARSER_API
#endif

enum class ParserStatusCode
{
    SUCCESS,
    INVALID_REQUEST,
    INVALID_METHOD,
};

typedef struct 
{
    uint16_t major = 0;
    uint16_t minor = 0;

    std::string to_string() const
    {
        std::ostringstream oss;
        oss << major << '.' << minor;
        return oss.str();
    }
} HttpVersion;

class HTTP_PARSER_API HttpParser
{
public:
    HttpParser();
    ParserStatusCode parse_request(const std::string &request);
    bool is_valid_method(const std::string &method) const;
    std::string get_method() const;
    std::string get_path() const;
    HttpVersion get_version() const;
private:
    std::string m_method;
    std::string m_path;
    HttpVersion m_http_version;
    string_map m_headers;
    static const string_set m_valid_http_methods;
};