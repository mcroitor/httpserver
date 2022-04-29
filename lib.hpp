#ifndef SERVER_LIB_HPP
#define SERVER_LIB_HPP

#include <string>
#include <vector>
#include <map>

struct server_config
{
	std::string host;
	std::size_t port;
	std::string root_dir;
};

enum class status_code : uint16_t
{
	ok = 200,
	bad_request = 400,
	not_found = 404,
	internal_server_error = 500
};

const std::map<status_code, std::string> status_message = {
	{status_code::ok, "OK"},
	{status_code::bad_request, "Bad Request"},
	{status_code::not_found, "Not Found"},
	{status_code::internal_server_error, "Internal Server Error"}};

struct mimetype
{
	const static std::string html;
	const static std::string css;
	const static std::string js;
	const static std::string txt;
	const static std::string jpg;
	const static std::string png;
	const static std::string gif;
	const static std::string ico;
	const static std::string svg;
	const static std::string json;
	const static std::string xml;
	const static std::string pdf;
	const static std::string zip;

	static const std::map<std::string, std::string> from_extension;
};

std::string trim(const std::string &str, const std::string &whitespace = " \t\n\r\v\f");
std::vector<std::string> explode(const std::string &str, const std::string &delimiter = " ");
std::string file_get_contents(const std::string &file_name);
std::string extension(const std::string &file_name);

server_config read_config(server_config &config, const std::string &config_file);

#endif