#include "http/http_response.h"

std::string build_response(int status_code, const std::string& status_message, const std::string& body) {
    std::string response =
        "HTTP/1.1 " + std::to_string(status_code) + " " + status_message + "\r\n"
        "Content-Type: text/plain\r\n"
        "Content-Length: " + std::to_string(body.size()) + "\r\n"
        "Connection: close\r\n"
        "\r\n" +
        body;

    return response;
}