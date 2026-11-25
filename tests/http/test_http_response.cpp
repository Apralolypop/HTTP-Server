
#include "http/http_response.h"
#include <cassert>
#include <iostream>

void test_successful_response() {
    std::string response = build_response(200, "OK", "Hello World!");

    assert(response.find("HTTP/1.1 200 OK\r\n") == 0);
    assert(response.find("Content-Type: text/plain\r\n") != std::string::npos);
    assert(response.find("Content-Length: 12\r\n") != std::string::npos);
    assert(response.find("Connection: close\r\n") != std::string::npos);
    assert(response.find("\r\n\r\nHello World!") != std::string::npos);
}

void test_not_found_response() {
    std::string response = build_response(404, "Not Found", "Page not found.");

    assert(response.find("HTTP/1.1 404 Not Found\r\n") == 0);
    assert(response.find("Content-Length: 15\r\n") != std::string::npos);
    assert(response.find("\r\n\r\nPage not found.") != std::string::npos);
}

void test_empty_body() {
    std::string response = build_response(200, "OK", "");

    assert(response.find("Content-Length: 0\r\n") != std::string::npos);
    assert(response.find("\r\n\r\n") != std::string::npos);
}

void test_empty_body_has_no_content_after_headers() {
    std::string response = build_response(200, "OK", "");

    assert(response.substr(response.size() - 4) == "\r\n\r\n");
}

int main() {
    test_successful_response();
    test_not_found_response();
    test_empty_body();
    test_empty_body_has_no_content_after_headers();

    std::cout << "All HTTP response tests passed!\n";
}
