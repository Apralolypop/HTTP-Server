#include "filesys/path_resolver.h"

#include <string>
#include <iostream>

std::string resolve_path(const std::string& base_path) {
 
    if(base_path.empty() || base_path[0] != '/') {
        std::cerr << "Invalid base path: " << base_path << std::endl;
        return "";
    }

    if(base_path == "/") {
        return "www/index.html";
    }

    if(base_path == "/about.html" || base_path == "/contact.html") {
        return "www" + base_path;
    }

    if(base_path.find("/css/") == 0 || base_path.find("/images/") == 0) {
        return "www" + base_path;
    }

    if(base_path.find("/..") != std::string::npos || base_path.find("../") != std::string::npos) {
        std::cerr << "Path traversal attempt detected: " << base_path << std::endl;
        return "";
    }
    
    return base_path;
}