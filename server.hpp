#ifndef _MYSERVER_H_
#define _MYSERVER_H_

#include <sys/socket.h> 
#include <netinet/in.h>
#include <string>

class server{
	int _server_fd;
	int _new_socket;
	char _buffer[BUFFER_SIZE];
	sockaddr_in _address; 
	int _opt; 
	int _addrlen;

	std::string _host;
	std::size_t _port;
	std::string _root_dir;
public:
	server(std::string host_, std::size_t port_);

	int start();
	int listen();
	int response();
	std::string data() const;
	std::string host() const;
	std::string port() const;
	std::string root_dir() const;
	void set_root_dir(std::string root_dir_);
	int close();
};

#endif