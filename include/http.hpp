#ifndef SERVER_HTTP_HPP
#define SERVER_HTTP_HPP

#include <sys/socket.h>
#include <netinet/in.h>
#include <string>
#include <filesystem>

#include "defaults.hpp"
#include "lib.hpp"

#ifndef SO_REUSEPORT
  #define SO_REUSEPORT 0
#endif

namespace server
{
	class http
	{
		int _server_fd;
		int _new_socket;
		std::string _buffer;
		sockaddr_in _address;
		int _opt;
		int _addrlen;

		std::string _host;
		std::size_t _port;
		std::filesystem::path _root_dir;
		std::filesystem::path _error_dir;

		int send_response(const std::string& content, status_code status_code, const std::string& content_type);
		std::string get_client_ip() const;
	public:
		http(std::string host_, std::size_t port_);

		/**
		 * Starts the HTTP server by creating a socket, setting options, and binding to the specified address and port.
		 * @return int Returns 0 on success, or EXIT_FAILURE on failure.
		 */
		int start();
		/**
		 * Listens for incoming connections and accepts them.
		 * @return int Returns 0 on success, or EXIT_FAILURE on failure.
		 */
		int listen();
		/**
		 * Processes the HTTP request and sends an appropriate response.
		 * @return int Returns 0 on success.
		 */
		int response();
		std::string data() const;
		std::string host() const;
		std::string port() const;
		std::string root_dir() const;
		std::string errors_dir() const;
		void set_root_dir(const std::string& root_dir_);
		/**
		 * Closes the HTTP server.
		 * @return int Returns 0 on success.
		 */
		int close();
	};

}

#endif