#include "filesys/path_resolver.h"

#include <string>
#include <iostream>

std::string resolve_path(const std::string& base_path) {
 
    if(base_path.empty()) {
        std::cerr << "Invalid base path: " << base_path << std::endl;
        return "";
    }

    if(base_path == "www/index.html") {
        return "www/index.html";
    }

    if(base_path == "www/about.html" || base_path == "www/contact.html") {
        return base_path;
    }

    if(base_path.find("www/css/") == 0 || base_path.find("www/images/") == 0) {
        return base_path;
    }

    if(base_path.find("www/..") != std::string::npos || base_path.find("www/../") != std::string::npos) {
        std::cerr << "Path traversal attempt detected: " << base_path << std::endl;
        return "";
    }
    
    return base_path;
}