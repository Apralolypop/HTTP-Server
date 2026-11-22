#ifndef HTTP_RESPONSE_H
#define HTTP_RESPONSE_H

#include <string>

std::string build_response(int status_code, const std::string& status_message, const std::string& body);

#endif