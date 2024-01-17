#ifndef SERVER_DEFAULTS_HPP
#define SERVER_DEFAULTS_HPP

#include <string>

namespace server
{

    /**
     * @brief Default port, == 80.
     * 
     */
    const size_t DEFAULT_PORT = 80;
    /**
     * @brief Default host name, == localhost.
     * 
     */
    const std::string DEFAULT_HOST = "localhost";
    /**
     * @brief Default site directory, `,/html/`.
     * 
     */
    const std::string DEFAULT_ROOT_DIR = "./html/";
    /**
     * @brief Buffer size (max size of request data read).
     * 
     */
    const std::size_t BUFFER_SIZE = 10240;
    /**
     * @brief Parallel connections number.
     * 
     */
    const int MAX_CONNECTION = 10;
    /**
     * @brief Default configuration file name.
     * 
     */
    const std::string CONFIG_FILE = "config.ini";
}

#endif