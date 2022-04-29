#include "response.hpp"

server_response::server_response(::status_code status_code_, std::string content_type_, std::string content_){
    _status_code = status_code_;
    _content_type = content_type_;
    _body = content_;

}

std::string server_response::body() const{
    return _body;
}

::status_code server_response::status_code() const{
    return _status_code;
}

std::string server_response::status_message() const{
    return ::status_message.at(_status_code);
}

std::string server_response::content_type() const{
    return _content_type;
}

std::string server_response::to_string() const{
    std::string response = "HTTP/1.1 " + std::to_string((uint16_t)_status_code) + " " + ::status_message.at(_status_code) + "\r\n";
    response += "Content-Type: " + _content_type + "\r\n";
    response += "Content-Length: " + std::to_string(_body.size()) + "\r\n";
    response += "\r\n";
    response += _body;
    return response;
}