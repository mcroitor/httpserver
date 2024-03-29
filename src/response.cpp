#include "response.hpp"

namespace server
{
    response::response(server::status_code status_code_, std::string content_type_, std::string content_)
    {
        _status_code = status_code_;
        _content_type = content_type_;
        _body = content_;
    }

    std::string response::body() const
    {
        return _body;
    }

    server::status_code response::get_status_code() const
    {
        return _status_code;
    }

    std::string response::status_message() const
    {
        return server::status_message.at(_status_code);
    }

    std::string response::content_type() const
    {
        return _content_type;
    }

    std::string response::to_string() const
    {
        std::string response = "HTTP/1.1 " + 
            std::to_string((uint16_t)_status_code) + 
            " " + 
            server::status_message.at(_status_code) + "\r\n";
        response += "Content-Type: " + _content_type + "\r\n";
        response += "Content-Length: " + std::to_string(_body.size()) + "\r\n";
        response += "\r\n";
        response += _body;
        return response;
    }
}