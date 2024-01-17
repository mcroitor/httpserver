#include "request.hpp"
#include "lib.hpp"

namespace server
{
    request::request(const std::string &request_) : raw(request_)
    {
        parse();
    }

    void request::parse()
    {
        std::vector<std::string> lines = explode(raw, "\n");
        std::string line = lines[0];
        std::vector<std::string> tokens = explode(line, " ");
        _method = tokens[0];
        _path = tokens[1];
        _query = tokens[2];
    }

    std::string request::method() const
    {
        return _method;
    }

    std::string request::path() const
    {
        return _path;
    }

    std::string request::query() const
    {
        return _query;
    }
}