#include "router/routing.h"

static std::unordered_map<std::string, std::string> routes = {
    {"/", "www/index.html"},
    {"/about.html", "www/about.html"},
    {"/contact.html", "www/contact.html"},
    {"/css/style.css", "www/css/style.css"},
    {"/images/logo.png", "www/images/logo.png"}
};  

std::string routing_path(const std::string& base_path) {
    auto it = routes.find(base_path);
    if (it != routes.end()) {
        return it->second;
    }
    return ""; // Return an empty string if the path is not found
}