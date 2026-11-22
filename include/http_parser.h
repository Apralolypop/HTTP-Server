#ifndef HTTP_PARSER_H
#define HTTP_PARSER_H

#include <string>
#include <optional>
#include <sstream>
#include <iostream>

struct HTTPRequest {
    std::string method;
    std::string path;
    std::string version;
};

std::optional<HTTPRequest> parse_request(const std::string& request);

#endif