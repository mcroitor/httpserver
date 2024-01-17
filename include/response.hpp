#ifndef SERVER_RESPONSE_HPP
#define SERVER_RESPONSE_HPP

#include <string>
#include "lib.hpp"

namespace server
{
    class response
    {

    protected:
        std::string _body;
        status_code _status_code;
        std::string _content_type;

    public:
        response(server::status_code status_code_, std::string content_type_, std::string content_);

        std::string body() const;
        server::status_code status_code() const;
        std::string status_message() const;
        std::string content_type() const;

        std::string to_string() const;
    };
}
#endif