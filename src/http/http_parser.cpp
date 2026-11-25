#include "http/http_parser.h"

std::optional<HTTPRequest> parse_request(const std::string& request){
    HTTPRequest req;

    std::istringstream stream(request); // Separates the request when there is a space, and stores the parts in the stream
    std::string request_line; // The first line of the request, which contains the method, path, and version    
    //Only accepts 1 trailing '\r' at the end of the request line, ignores "\n\r\n", it stops reading at the first "\n"

    if (!std::getline(stream, request_line)) {
        return std::nullopt;
    }

    // Remove the trailing '\r' from the CRLF line ending.
    if (!request_line.empty() && request_line.back() == '\r') {
        request_line.pop_back();
    }

    std::istringstream line_stream(request_line); // Creates a new stream containing only the request line

    if(!(line_stream >> req.method >> req.path >> req.version)){
        return std::nullopt;
    }

    std::string extra;

    if (line_stream >> extra) { // Checks for extra fields in the request line
        return std::nullopt;
    }

    if(req.method != "GET") {
        return std::nullopt;
    }

    if(req.path.empty() || req.path[0] != '/') {
        return std::nullopt;
    }

    if(req.version != "HTTP/1.1") {
        return std::nullopt;
    }

    return req;
}