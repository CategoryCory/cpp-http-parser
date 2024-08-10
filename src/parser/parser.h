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

/**
 * @brief An enum containing status codes for the HTTP parser.
 * 
 */
enum class ParserStatusCode
{
    SUCCESS,            ///< Request was parsed successfully.
    INVALID_REQUEST,    ///< Request was invalid.
    INVALID_METHOD,     ///< Request method was invalid or unsupported.
    MISSING_HEADER,     ///< Request was missing a required header.
};

/**
 * @brief A struct representing an HTTP version number.
 * 
 */
typedef struct 
{
    int major = 0;      ///< HTTP major version number.
    int minor = 0;      ///< HTTP minor version number.

    /**
     * @brief Returns the HTTP version number as a string.
     * 
     * @return The string representation of the HTTP version.
     */
    std::string to_string() const
    {
        std::ostringstream oss;
        oss << major << '.' << minor;
        return oss.str();
    }
} HttpVersion;

/**
 * 
 * @class HttpParser
 * @brief A class that parses an HTTP request, given as a string.
 * 
 */
class HTTP_PARSER_API HttpParser
{
public:
    /**
     * @brief Construct a new Http Parser object.
     * 
     */
    HttpParser();

    /**
     * @brief Parses an HTTP request object given as a string.
     * 
     * @param request A string representing an HTTP request to parse.
     * @return A status code representing the result of parsing the request.
     */
    ParserStatusCode parse_request(const std::string &request);

    /**
     * @brief Checks if a given HTTP method is valid.
     * 
     * @param method The method to check.
     * @return True if @p method is a valid method; false otherwise.
     */
    bool is_valid_method(const std::string &method) const;

    /**
     * @brief Retrieves the current HTTP method.
     * 
     * @return The method value as a string.
     */
    const std::string_view get_method() const;

    /**
     * @brief Retrieves the current path object.
     * 
     * @return The path value as a string.
     */
    const std::string_view get_path() const;

    /**
     * @brief Retrieves the current version object.
     * 
     * @return The version value as an HttpVersion object.
     */
    const HttpVersion& get_version() const;

    /**
     * @brief Retrieves the current headers object.
     * 
     * @return The headers as a hashmap.
     */
    const string_map& get_headers() const;

private:
    std::string m_method;                           ///< Private member variable to store an HTTP method.
    std::string m_path;                             ///< Private member variable to store a URL path.
    HttpVersion m_http_version;                     ///< Private member variable to store an HTTP version.
    string_map m_headers;                           ///< Private member variable to store HTTP headers.
    static const string_set m_valid_http_methods;   ///< Private member variable to store a list of valid HTTP headers.
};