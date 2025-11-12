#include <iostream>
#include <filesystem>
#include <unistd.h>
#include <arpa/inet.h>

#include "defaults.hpp"
#include "http.hpp"
#include "request.hpp"
#include "response.hpp"
#include "lib.hpp"
#include "logger.hpp"

namespace server
{
	http::http(std::string host_, std::size_t port_) :
		_host{ host_ },
		_port{ port_ },
		_opt{ 1 },
		_addrlen{ sizeof(_address) },
		_server_fd{ 0 },
		_new_socket{ 0 },
		_buffer(BUFFER_SIZE, '\0'),
		_address{},
		_root_dir{ std::filesystem::current_path() },
		_error_dir{ std::filesystem::current_path() / "errors" }
	{
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
		if (bind(_server_fd, (struct sockaddr*)&_address, sizeof(_address)) < 0)
		{
			logger().error("bind failed");
			return (EXIT_FAILURE);
		}
		return 0;
	}

	std::string http::get_client_ip() const {
		char client_ip[INET_ADDRSTRLEN];
		inet_ntop(AF_INET, &_address.sin_addr, client_ip, INET_ADDRSTRLEN);
		return std::string(client_ip);
	}

	int http::listen()
	{
		if (::listen(_server_fd, MAX_CONNECTION) < 0)
		{
			logger().info("listen");
			return (EXIT_FAILURE);
		}

		if ((_new_socket = accept(_server_fd, (struct sockaddr*)&_address, (socklen_t*)&_addrlen)) < 0)
		{
			logger().info("accept");
			return (EXIT_FAILURE);
		}
		int valread = read(_new_socket, _buffer.data(), BUFFER_SIZE);
		return 0;
	}

	int http::response()
	{
		server::request request{ _buffer };

		std::string content = "";
		status_code status_code = status_code::ok;
		std::string content_type = "text/plain";

		logger().info(std::string("<request>") +
			std::string("<from>") + this->get_client_ip() + "</from>" +
			std::string("<method>") + request.method() + "</method>" +
			std::string("<path>") + request.path() + "</path>" +
			std::string("<query>") + request.query() + "</query>" +
			std::string("</request>"));

		std::filesystem::path file_name(this->root_dir() + request.path());

		if (file_name.string().back() == '/')
		{
			file_name += "index.html";
		}
		// Check if file exists
		if (!std::filesystem::exists(file_name))
		{
			logger().warn("file not found: " + file_name.string());
			file_name = this->errors_dir() + "/404.html";
			status_code = status_code::not_found;
			content_type = "text/html";

			content = file_get_contents(file_name);

			return send_response(content, status_code, content_type);
		}

		file_name = std::filesystem::canonical(file_name);

		// prevent directory traversal attack
		if (is_not_traversal(file_name, this->_root_dir) == false)
		{
			logger().warn("directory traversal attack detected: " + file_name.string());
			file_name = this->errors_dir() + "/403.html";
			status_code = status_code::access_denied;
			content_type = "text/html";

			content = file_get_contents(file_name);

			return send_response(content, status_code, content_type);
		}

		std::string ext = extension(file_name);

		try {
			content = file_get_contents(file_name);
			status_code = content.size() > 0 ? status_code::ok : status_code::not_found;
		}
		catch (std::runtime_error& e) {
			logger().warn("file not found: " + file_name.string());
			content = "<h1>404 Not Found</h1>";
			status_code = status_code::not_found;
			return send_response(content, status_code, content_type);
		}
		catch (...) {
			logger().error("internal server error reading file: " + file_name.string());
			content = "<h1>500 Internal Server Error</h1>";
			status_code = status_code::internal_server_error;
			return send_response(content, status_code, content_type);
		}

		if (mimetype::from_extension.find(ext) != mimetype::from_extension.end())
		{
			content_type = mimetype::from_extension.at(ext);
		}
		return send_response(content, status_code, content_type);
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
		return _root_dir.string();
	}

	std::string http::errors_dir() const
	{
		return _error_dir.string();
	}

	void http::set_root_dir(const std::string& root_dir_)
	{
		std::filesystem::path path = std::filesystem::canonical(root_dir_);
		if (!std::filesystem::exists(path))
		{
			throw std::runtime_error("root directory not found: " + root_dir_);
		}
		_root_dir = path;
	}

	int http::close()
	{
		return 0;
	}

	int http::send_response(const std::string& content, status_code status_code, const std::string& content_type) {
		server::response response{ status_code, content_type, content };

		logger().info(std::string("Response: ") +
			std::to_string((uint16_t)response.get_status_code()) +
			std::string(" ") +
			response.status_message());

		send(_new_socket, response.to_string().c_str(), response.to_string().size(), 0);
		::close(_new_socket);

		return static_cast<int>(status_code);
	}
}