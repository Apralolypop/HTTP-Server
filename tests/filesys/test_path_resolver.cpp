#include "filesys/path_resolver.h"

#include <cassert>
#include <iostream>

int main() {
    // Test homepage
    assert(resolve_path("/") == "www/index.html");

    // Test regular HTML pages
    assert(resolve_path("/about.html") == "www/about.html");
    assert(resolve_path("/contact.html") == "www/contact.html");

    // Test nested paths
    assert(resolve_path("/css/style.css") == "www/css/style.css");
    assert(resolve_path("/images/logo.png") == "www/images/logo.png");

    std::cout << "All path resolver tests passed.\n";

    return 0;
}