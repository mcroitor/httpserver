// Server side C/C++ program to demonstrate Socket programming 

#include <string>
#include <iostream>

#include "defaults.hpp"
#include "server.hpp"
#include "lib.hpp"

int main(int argc, char const *argv[]) 
{
	// read properties from config.ini file if exists
	// otherwise use default values
	server_config cfg = {DEFAULT_HOST, DEFAULT_PORT, DEFAULT_ROOT_DIR};

	cfg = read_config(cfg, CONFIG_FILE);

	// create server
	server srv(cfg.host, cfg.port);
	srv.set_root_dir(cfg.root_dir);
	// start server
	int result = srv.start();
	if(result != 0){
		std::cerr << "Error starting server" << std::endl;
		return EXIT_FAILURE;
	}
	std::cout << "Server started" << std::endl;
	// wait for client
	while(srv.listen() == 0){
		srv.response();
	}
	return 0; 
}