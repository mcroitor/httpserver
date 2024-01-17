#include <iostream>
#include "logger.hpp"

namespace server
{
    std::string timestamp();

    void logger::write_message(const std::string &type, const std::string &message){
        std::cout << timestamp() << " " << type << " " << message << std::endl;
    }
    void logger::info(const std::string &message){
        write_message("[info]", message);
    }
    void logger::debug(const std::string &message){
        if(debugEnabled){
            write_message("[debug]", message);
        }
    }
    void logger::warn(const std::string &message){
        write_message("[warn]", message);
    }
    void logger::error(const std::string &message){
        write_message("[error]", message);
    }
}