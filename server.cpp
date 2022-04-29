#include <iostream>
#include <unistd.h>

#include "server.hpp"
#include "request.hpp"
#include "response.hpp"
#include "lib.hpp"

server::server(std::string host_, std::size_t port_)
{
	_host = host_;
	_port = port_;
	_opt = 1;
	_addrlen = sizeof(_address);
}

int server::start()
{
	// Creating socket file descriptor
	if ((_server_fd = socket(AF_INET, SOCK_STREAM, 0)) == 0)
	{
		std::cerr << "socket failed" << std::endl;
		return (EXIT_FAILURE);
	}

	// Setting socket options
	const size_t SO_REUSEPORT = 0;
	if (setsockopt(_server_fd, SOL_SOCKET, SO_REUSEADDR | SO_REUSEPORT, &_opt, sizeof(_opt)))
	{
		std::cerr << "setsockopt" << std::endl;
		return (EXIT_FAILURE);
	}
	_address.sin_family = AF_INET;
	_address.sin_addr.s_addr = INADDR_ANY;
	_address.sin_port = htons(_port);

	// Bind socket to address
	if (bind(_server_fd, (struct sockaddr *)&_address, sizeof(_address)) < 0)
	{
		std::cerr << "bind failed" << std::endl;
		return (EXIT_FAILURE);
	}
	return 0;
}

int server::listen()
{
	if (::listen(_server_fd, MAX_CONNECTION) < 0)
	{
		std::cerr << "listen" << std::endl;
		return (EXIT_FAILURE);
	}

	if ((_new_socket = accept(_server_fd, (struct sockaddr *)&_address, (socklen_t *)&_addrlen)) < 0)
	{
		std::cerr << "accept" << std::endl;
		return (EXIT_FAILURE);
	}
	int valread = read(_new_socket, _buffer, BUFFER_SIZE);
	return 0;
}

int server::response()
{
	server_request request = server_request(_buffer);
	std::cout << "Request: " << request.method() << " " << request.path() << " " << request.query() << std::endl;
	std::string file_name = this->root_dir() + request.path();
	if (file_name.back() == '/')
	{
		file_name += "index.html";
	}
	std::string ext = extension(file_name);

	std::cout << "file: " << file_name << ", extension: " << ext << std::endl;

	std::string page = file_get_contents(file_name);

	status_code status_code = page.size() > 0 ? status_code::ok : status_code::not_found;
	std::string content_type = "text/plain";
	
	if(mimetype::from_extension.find(ext) != mimetype::from_extension.end())
	{
		content_type = mimetype::from_extension.at(ext);
	}
	std::cout << "content_type: " << content_type << std::endl;

	server_response response = server_response(status_code, content_type, page);

	std::cout << "Response: " << (uint16_t)response.status_code() << " " << response.status_message() << std::endl;

	send(_new_socket, response.to_string().c_str(), response.to_string().size(), 0);
	::close(_new_socket);
	return 0;
}

std::string server::data() const
{
	return std::string(_buffer);
}

std::string server::host() const
{
	return _host;
}

std::string server::port() const
{
	return std::to_string(_port);
}

std::string server::root_dir() const
{
	return _root_dir;
}

void server::set_root_dir(std::string root_dir_)
{
	_root_dir = root_dir_;
}

int server::close()
{
	return 0;
}