#ifndef SERVER_LIB_HPP
#define SERVER_LIB_HPP

#include <string>
#include <vector>
#include <map>
#include <cstdint>

namespace server
{
	/**
	 * @brief
	 *
	 */
	struct config
	{
		std::string host;
		std::size_t port;
		std::string root_dir;
	};

	typedef std::map<std::string, std::string> keymap;

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

	const std::vector<std::string> keys = {
		"host", "port", "root_dir"};

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

	// common functions

	/**
	 * @brief remove white spaces from left side of string
	 *
	 * @param str
	 * @param whitespace
	 * @return std::string
	 */
	std::string ltrim(const std::string &str, const std::string &whitespace = " \t\n\r\v\f");

	/**
	 * @brief remove whitespace from right side of string
	 * 
	 * @param str 
	 * @param whitespace 
	 * @return std::string 
	 */
	std::string rtrim(const std::string &str, const std::string &whitespace = " \t\n\r\v\f");
	
	/**
	 * @brief remove white spaces
	 *
	 * @param str
	 * @param whitespace
	 * @return std::string
	 */
	std::string trim(const std::string &str, const std::string &whitespace = " \t\n\r\v\f");
	/**
	 * @brief explode a string in chunks by delimiter.
	 *
	 * @param str
	 * @param delimiter
	 * @return std::vector<std::string>
	 */
	std::vector<std::string> explode(const std::string &str, const std::string &delimiter = " ");
	/**
	 * @brief load data from file
	 *
	 * @param file_name
	 * @return std::string
	 */
	std::string file_get_contents(const std::string &file_name);
	/**
	 * @brief extract extention from file name
	 *
	 * @param file_name
	 * @return std::string
	 */
	std::string extension(const std::string &file_name);

	// project specific functions
	/**
	 * @brief read server configuration
	 *
	 * @param cfg
	 * @param config_file
	 * @return config
	 */
	config read_config(config &cfg, const std::string &config_file);

	/**
	 * @brief server usage
	 *
	 */
	void usage();

	/**
	 * @brief generate default configuration file
	 *
	 */
	void default_config();

	/**
	 * @brief current time to string
	 *
	 * @return std::string
	 */
	std::string timestamp();

	std::string to_string(const config &cfg);

}

#endif