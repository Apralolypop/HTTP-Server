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
    
    return base_path;
}