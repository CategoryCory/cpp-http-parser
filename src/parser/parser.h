#pragma once

#include <string>
#include <vector>

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
    INVALID_METHOD,
};

class HTTP_PARSER_API HttpParser
{
public:
    HttpParser();
    ParserStatusCode parse_request(const std::string &request);
    std::string get_method() const;
private:
    std::string m_method;
};