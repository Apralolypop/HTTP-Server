
#include "http_parser.h"
#include <cassert>
#include <iostream>

void test_valid_request() {
    auto result = parse_request(
        "GET /index.html HTTP/1.1\r\nHost: localhost\r\n\r\n"
    );

    assert(result.has_value());
    assert(result->method == "GET");
    assert(result->path == "/index.html");
    assert(result->version == "HTTP/1.1");
}

void test_invalid_method() {
    auto result = parse_request("POST / HTTP/1.1\r\n\r\n");

    assert(!result.has_value());
}

void test_invalid_version() {
    auto result = parse_request("GET / HTTP/2.0\r\n\r\n");

    assert(!result.has_value());
}

void test_missing_fields() {
    auto result = parse_request("GET\r\n\r\n");

    assert(!result.has_value());
}

void test_invalid_path() {
    auto result = parse_request("GET index.html HTTP/1.1\r\n\r\n");

    assert(!result.has_value());
}

void test_extra_field() {
    auto result = parse_request("GET / HTTP/1.1 EXTRA\r\n\r\n");

    assert(!result.has_value());
}

int main() {
    test_valid_request();
    test_invalid_method();
    test_invalid_version();
    test_missing_fields();
    test_invalid_path();
    test_extra_field();

    std::cout << "All tests passed!\n";
}
