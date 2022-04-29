#include "request.hpp"
#include "lib.hpp"

server_request::server_request(const std::string& request_): raw(request_) {
    parse();
}

void server_request::parse() {
    std::vector<std::string> lines = explode(raw, "\n");
    std::string line = lines[0];
    std::vector<std::string> tokens = explode(line, " ");
    _method = tokens[0];
    _path = tokens[1];
    _query = tokens[2];
}

std::string server_request::method() const {
    return _method;
}

std::string server_request::path() const {
    return _path;
}

std::string server_request::query() const {
    return _query;
}