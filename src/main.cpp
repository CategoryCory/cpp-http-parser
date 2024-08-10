#include <cstdlib>
#include <iostream>
#include <string>
#include "parser/parser.h"
#include "string_utilities/string_utilities.h"

int main()
{
    HttpParser parser;

    std::string request("GET /blog/posts/1234 HTTP/1.1\r\n"
                        "Host: www.sample.com\r\n"
                        "User-Agent: Mozilla/5.0 (Windows NT 6.1; Win64; x64; rv:47.0) Gecko/20100101 Firefox/47.0\r\n"
                        "Accept: text/html,application/xhtml+xml,application/xml;q=0.9,*/*;q=0.8\r\n"
                        "Accept-Language: en-US,en;q=0.5\r\n"
                        "Accept-Encoding: gzip, deflate\r\n"
                        "Connection: keep-alive\r\n"
                        "Upgrade-Insecure-Requests: 1\r\n"
                        "Content-Type: text/html; charset=UTF-8\r\n"
                        "Content-Length: 345\r\n"
                        "\r\n"
                        "{\"field1\": \"value1\", \"field2\": \"value2\"}");

    [[maybe_unused]] ParserStatusCode status_code = parser.parse_request(request);

    if (status_code == ParserStatusCode::SUCCESS)
    {
        std::cout << "Request method: " << parser.get_method() << "\n";
        std::cout << "Request path: " << parser.get_path() << "\n";
        std::cout << "Request HTTP version: " << parser.get_version().to_string() << "\n";

        for (const auto& kv_pair : parser.get_headers())
        {
            std::cout << kv_pair.first << ": " << kv_pair.second << "\n";
        }
        return EXIT_SUCCESS;
    }
    else
    {
        std::cout << "An error occurred when processing the request.\n";
        return EXIT_SUCCESS;
    }
}