#define CATCH_CONFIG_MAIN

#include <catch2/catch.hpp>

// unit tests, cover all functions from include/lib.hpp

#include <fstream>
#include "lib.hpp"

TEST_CASE("server::config", "[server::config]")
{
    server::config cfg;
    cfg.host = "localhost";
    cfg.port = 8080;
    cfg.root_dir = "/var/www/html";

    REQUIRE(cfg.host == "localhost");
    REQUIRE(cfg.port == 8080);
    REQUIRE(cfg.root_dir == "/var/www/html");
}

TEST_CASE("server::status_code", "[server::status_code]")
{
    REQUIRE(static_cast<uint16_t>(server::status_code::ok) == 200);
    REQUIRE(static_cast<uint16_t>(server::status_code::bad_request) == 400);
    REQUIRE(static_cast<uint16_t>(server::status_code::not_found) == 404);
    REQUIRE(static_cast<uint16_t>(server::status_code::internal_server_error) == 500);
}

TEST_CASE("server::status_message", "[server::status_message]")
{
    REQUIRE(server::status_message.at(server::status_code::ok) == "OK");
    REQUIRE(server::status_message.at(server::status_code::bad_request) == "Bad Request");
    REQUIRE(server::status_message.at(server::status_code::not_found) == "Not Found");
    REQUIRE(server::status_message.at(server::status_code::internal_server_error) == "Internal Server Error");
}

TEST_CASE("server::keys", "[server::keys]")
{
    REQUIRE(server::keys.at(0) == "host");
    REQUIRE(server::keys.at(1) == "port");
    REQUIRE(server::keys.at(2) == "root_dir");
}

TEST_CASE("server::mimetype", "[server::mimetype]")
{
    REQUIRE(server::mimetype::from_extension.at("html") == "text/html");
    REQUIRE(server::mimetype::from_extension.at("css") == "text/css");
    REQUIRE(server::mimetype::from_extension.at("js") == "text/javascript");
    REQUIRE(server::mimetype::from_extension.at("txt") == "text/plain");
    REQUIRE(server::mimetype::from_extension.at("jpg") == "image/jpeg");
    REQUIRE(server::mimetype::from_extension.at("png") == "image/png");
    REQUIRE(server::mimetype::from_extension.at("gif") == "image/gif");
    REQUIRE(server::mimetype::from_extension.at("ico") == "image/x-icon");
    REQUIRE(server::mimetype::from_extension.at("svg") == "image/svg+xml");
    REQUIRE(server::mimetype::from_extension.at("json") == "application/json");
    REQUIRE(server::mimetype::from_extension.at("xml") == "application/xml");
    REQUIRE(server::mimetype::from_extension.at("pdf") == "application/pdf");
    REQUIRE(server::mimetype::from_extension.at("zip") == "application/zip");
}

TEST_CASE("server::mimetype::html", "[server::mimetype::html]")
{
    REQUIRE(server::mimetype::html == "text/html");
}

TEST_CASE("server::mimetype::css", "[server::mimetype::css]")
{
    REQUIRE(server::mimetype::css == "text/css");
}

TEST_CASE("server::mimetype::js", "[server::mimetype::js]")
{
    REQUIRE(server::mimetype::js == "text/javascript");
}

TEST_CASE("server::mimetype::txt", "[server::mimetype::txt]")
{
    REQUIRE(server::mimetype::txt == "text/plain");
}

TEST_CASE("server::mimetype::jpg", "[server::mimetype::jpg]")
{
    REQUIRE(server::mimetype::jpg == "image/jpeg");
}

TEST_CASE("server::mimetype::png", "[server::mimetype::png]")
{
    REQUIRE(server::mimetype::png == "image/png");
}

TEST_CASE("server::mimetype::gif", "[server::mimetype::gif]")
{
    REQUIRE(server::mimetype::gif == "image/gif");
}

TEST_CASE("server::mimetype::ico", "[server::mimetype::ico]")
{
    REQUIRE(server::mimetype::ico == "image/x-icon");
}

TEST_CASE("server::mimetype::svg", "[server::mimetype::svg]")
{
    REQUIRE(server::mimetype::svg == "image/svg+xml");
}

TEST_CASE("server::mimetype::json", "[server::mimetype::json]")
{
    REQUIRE(server::mimetype::json == "application/json");
}

TEST_CASE("server::mimetype::xml", "[server::mimetype::xml]")
{
    REQUIRE(server::mimetype::xml == "application/xml");
}

TEST_CASE("server::mimetype::pdf", "[server::mimetype::pdf]")
{
    REQUIRE(server::mimetype::pdf == "application/pdf");
}

TEST_CASE("server::mimetype::zip", "[server::mimetype::zip]")
{
    REQUIRE(server::mimetype::zip == "application/zip");
}

TEST_CASE("server::ltrim", "[server::ltrim]")
{
    REQUIRE(server::ltrim("  test") == "test");
    REQUIRE(server::ltrim("  test  ") == "test  ");
    REQUIRE(server::ltrim("test") == "test");
}

TEST_CASE("server::rtrim", "[server::rtrim]")
{
    REQUIRE(server::rtrim("test  ") == "test");
    REQUIRE(server::rtrim("  test  ") == "  test");
    REQUIRE(server::rtrim("test") == "test");
}

TEST_CASE("server::trim", "[server::trim]")
{
    REQUIRE(server::trim("  test  ") == "test");
    REQUIRE(server::trim("  test  ") == "test");
    REQUIRE(server::trim("test") == "test");
}

TEST_CASE("server::explode", "[server::explode]")
{
    std::vector<std::string> result = server::explode("test test test");
    REQUIRE(result.size() == 3);
    REQUIRE(result.at(0) == "test");
    REQUIRE(result.at(1) == "test");
    REQUIRE(result.at(2) == "test");
}

TEST_CASE("server::file_get_contents", "[server::file_get_contents]")
{
    // prepare test file
    std::ofstream file("/app/tests/test.txt");
    file << "test\n";
    file.close();

    // test
    std::string result = server::file_get_contents("/app/tests/test.txt");
    REQUIRE(result == "test\n");
}

TEST_CASE("server::extension", "[server::extension]")
{
    REQUIRE(server::extension("path/to/test.txt") == "txt");
    REQUIRE(server::extension("path/to/test.html") == "html");
    REQUIRE(server::extension("path/to/test.css") == "css");
    REQUIRE(server::extension("path/to/test.js") == "js");
    REQUIRE(server::extension("path/to/test.jpg") == "jpg");
    REQUIRE(server::extension("path/to/test.png") == "png");
    REQUIRE(server::extension("path/to/test.gif") == "gif");
    REQUIRE(server::extension("path/to/test.ico") == "ico");
    REQUIRE(server::extension("path/to/test.svg") == "svg");
    REQUIRE(server::extension("path/to/test.json") == "json");
    REQUIRE(server::extension("path/to/test.xml") == "xml");
    REQUIRE(server::extension("path/to/test.pdf") == "pdf");
    REQUIRE(server::extension("path/to/test.zip") == "zip");
}

/* TEST_CASE("server::read_config", "[server::read_config]")
{
    // prepare test file
    std::ofstream file("/app/tests/config.json");
    file << "{\n";
    file << "    \"host\": \"localhost\",\n";
    file << "    \"port\": 8080,\n";
    file << "    \"root_dir\": \"/var/www/html\"\n";
    file << "}\n";
    file.close();

    // test
    server::config default_config;
    server::config cfg = server::read_config(default_config, "/app/tests/config.json");
    REQUIRE(cfg.host == "localhost");
    REQUIRE(cfg.port == 8080);
    REQUIRE(cfg.root_dir == "/var/www/html");
} */

/* TEST_CASE("server::default_config", "[server::default_config]")
{
    server::config cfg = server::default_config();
    REQUIRE(cfg.host == "localhost");
    REQUIRE(cfg.port == 8080);
    REQUIRE(cfg.root_dir == "/var/www/html");
} */

TEST_CASE("server::to_string server::config", "[server::to_string server::config]")
{
    server::config cfg;
    cfg.host = "localhost";
    cfg.port = 8080;
    cfg.root_dir = "/var/www/html";

    REQUIRE(server::to_string(cfg) == "{ host: localhost, port: 8080, root_dir: /var/www/html }");
}