
#include "filesys/file_handler.h"

#include <cassert>
#include <cstdio>
#include <fstream>
#include <iostream>
#include <string>

void test_read_existing_file() {
    const std::string filepath = "tests/test_file.txt";
    const std::string expected = "Hello, world!";

    // Create a test file.
    {
        std::ofstream file(filepath);
        file << expected;
    }

    // Read the file.
    std::string result = read_file(filepath);

    assert(result == expected);

    std::remove(filepath.c_str());

    std::cout << "PASS: test_read_existing_file\n";
}

void test_read_missing_file() {
    const std::string filepath = "tests/nonexistent.txt";

    std::string result = read_file(filepath);

    assert(result.empty());

    std::cout << "PASS: test_read_missing_file\n";
}

void test_read_empty_file() {
    const std::string filepath = "tests/empty.txt";

    // Create an empty file.
    {
        std::ofstream file(filepath);
    }

    std::string result = read_file(filepath);

    assert(result.empty());

    std::remove(filepath.c_str());

    std::cout << "PASS: test_read_empty_file\n";
}

int main() {
    test_read_existing_file();
    test_read_missing_file();
    test_read_empty_file();

    std::cout << "\nAll tests passed!\n";

    return 0;
}
