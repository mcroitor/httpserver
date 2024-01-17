#ifndef SERVE_LOGGER_HPP
#define SERVE_LOGGER_HPP

#include <string>

namespace server
{
    class logger
    {
    public:
        bool debugEnabled = false;
        
        void write_message(const std::string& type, const std::string& message);
        void info(const std::string& message);
        void debug(const std::string& message);
        void warn(const std::string& message);
        void error(const std::string& message);
    };
}

#endif