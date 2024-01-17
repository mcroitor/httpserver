// Server side C/C++ program to demonstrate Socket programming 

#include <string>
#include <iostream>

#include "defaults.hpp"
#include "http.hpp"
#include "lib.hpp"
#include "logger.hpp"

int main(int argc, char const *argv[]) 
{
	// read properties from config.ini file if exists
	// otherwise use default values
	server::config cfg = {
		server::DEFAULT_HOST, 
		server::DEFAULT_PORT, 
		server::DEFAULT_ROOT_DIR
	};

	server::logger logger;

	logger.info(std::string("initial config: ") + server::to_string(cfg));

	read_config(cfg, server::CONFIG_FILE);
	logger.info(std::string("updated config: ") + server::to_string(cfg));

	// create server
	server::http srv(cfg.host, cfg.port);
	srv.set_root_dir(cfg.root_dir);
	// start server
	int result = srv.start();
	if(result != 0){
		logger.info("Error starting server");
		return EXIT_FAILURE;
	}
	logger.info("Server started");
	// wait for client
	while(srv.listen() == 0){
		srv.response();
	}
	return 0; 
}