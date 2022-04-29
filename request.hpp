#ifndef SERVER_REQUEST_HPP
#define SERVER_REQUEST_HPP

#include <string>

class server_request {
    std::string raw;
    std::string _method;
    std::string _path;
    std::string _query;

public:
    server_request(const std::string& request_);
    void parse();
    std::string method() const;
    std::string path() const;
    std::string query() const;

};

#endif