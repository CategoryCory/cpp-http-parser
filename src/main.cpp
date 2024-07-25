#include <cstdlib>
#include <iostream>
#include <string>
#include "parser/parser.h"

int main()
{
    HttpParser parser;
    std::string request = "GET /blog/posts/1234 HTTP/1.1";
    parser.parse_request(request);

    std::cout << "Request method: " << parser.get_method() << "\n";

    return EXIT_SUCCESS;
}