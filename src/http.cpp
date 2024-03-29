#include <iostream>
#include <unistd.h>

#include "defaults.hpp"
#include "http.hpp"
#include "request.hpp"
#include "response.hpp"
#include "lib.hpp"
#include "logger.hpp"

namespace server
{
	http::http(std::string host_, std::size_t port_)
	{
		_host = host_;
		_port = port_;
		_opt = 1;
		_addrlen = sizeof(_address);
	}

	int http::start()
	{
		// Creating socket file descriptor
		if ((_server_fd = socket(AF_INET, SOCK_STREAM, 0)) == 0)
		{
			logger().error("socket failed");
			return (EXIT_FAILURE);
		}

		// Setting socket options
		// const size_t SO_REUSEPORT = 0;
		if (setsockopt(_server_fd, SOL_SOCKET, SO_REUSEADDR | SO_REUSEPORT, &_opt, sizeof(_opt)))
		{
			logger().error("setsockopt");
			return (EXIT_FAILURE);
		}
		_address.sin_family = AF_INET;
		_address.sin_addr.s_addr = INADDR_ANY;
		_address.sin_port = htons(_port);

		// Bind socket to address
		if (bind(_server_fd, (struct sockaddr *)&_address, sizeof(_address)) < 0)
		{
			logger().error("bind failed");
			return (EXIT_FAILURE);
		}
		return 0;
	}

	int http::listen()
	{
		if (::listen(_server_fd, MAX_CONNECTION) < 0)
		{
			logger().info("listen");
			return (EXIT_FAILURE);
		}

		if ((_new_socket = accept(_server_fd, (struct sockaddr *)&_address, (socklen_t *)&_addrlen)) < 0)
		{
			logger().info("accept");
			return (EXIT_FAILURE);
		}
		int valread = read(_new_socket, _buffer, BUFFER_SIZE);
		return 0;
	}

	int http::response()
	{
		server::request request {_buffer};
		logger().info(std::string("Request: ") +
			request.method() +
			std::string(" ") +
			request.path() +
			std::string(" ") +
			request.query());
		std::string file_name = this->root_dir() + request.path();
		if (file_name.back() == '/')
		{
			file_name += "index.html";
		}
		std::string ext = extension(file_name);

		logger().info( std::string("file: ") +
			file_name +
			std::string(", extension: ") + 
			ext);

		std::string page = file_get_contents(file_name);

		status_code status_code = page.size() > 0 ? status_code::ok : status_code::not_found;
		std::string content_type = "text/plain";

		if (mimetype::from_extension.find(ext) != mimetype::from_extension.end())
		{
			content_type = mimetype::from_extension.at(ext);
		}
		logger().info(std::string("content_type: ") +
			content_type);

		server::response response {status_code, content_type, page};

		logger().info(std::string("Response: ") +
			std::to_string((uint16_t)response.get_status_code()) +
			std::string(" ") +
			response.status_message());

		send(_new_socket, response.to_string().c_str(), response.to_string().size(), 0);
		::close(_new_socket);
		return 0;
	}

	std::string http::data() const
	{
		return std::string(_buffer);
	}

	std::string http::host() const
	{
		return _host;
	}

	std::string http::port() const
	{
		return std::to_string(_port);
	}

	std::string http::root_dir() const
	{
		return _root_dir;
	}

	void http::set_root_dir(std::string root_dir_)
	{
		_root_dir = root_dir_;
	}

	int http::close()
	{
		return 0;
	}
}