#include <cstdlib>
#include <iostream>
#include <string>
#include "parser/parser.h"

int main()
{
    HttpParser parser;
    std::string request("GET /blog/posts/1234.html HTTP/1.1\r\nHost: www.sample.org\r\n\r\n");
    [[maybe_unused]] ParserStatusCode status_code = parser.parse_request(request);

    if (status_code == ParserStatusCode::SUCCESS)
    {
        std::cout << "Request method: " << parser.get_method() << "\n";
        std::cout << "Request path: " << parser.get_path() << "\n";
        std::cout << "Request HTTP version: " << parser.get_version().to_string() << "\n";
        return EXIT_SUCCESS;
    }
    else
    {
        std::cout << "An error occurred when processing the request.\n";
        return EXIT_SUCCESS;
    }
}