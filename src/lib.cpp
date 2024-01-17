#include <fstream>
#include <iomanip>
#include <ctime>

#include "lib.hpp"
#include "logger.hpp"

namespace server
{
    const std::string mimetype::html = "text/html";
    const std::string mimetype::css = "text/css";
    const std::string mimetype::js = "text/javascript";
    const std::string mimetype::txt = "text/plain";
    const std::string mimetype::jpg = "image/jpeg";
    const std::string mimetype::png = "image/png";
    const std::string mimetype::gif = "image/gif";
    const std::string mimetype::ico = "image/x-icon";
    const std::string mimetype::svg = "image/svg+xml";
    const std::string mimetype::json = "application/json";
    const std::string mimetype::xml = "application/xml";
    const std::string mimetype::pdf = "application/pdf";
    const std::string mimetype::zip = "application/zip";

    const std::map<std::string, std::string> mimetype::from_extension = {
        {"html", mimetype::html},
        {"css", mimetype::css},
        {"js", mimetype::js},
        {"txt", mimetype::txt},
        {"jpg", mimetype::jpg},
        {"png", mimetype::png},
        {"gif", mimetype::gif},
        {"ico", mimetype::ico},
        {"svg", mimetype::svg},
        {"json", mimetype::json},
        {"xml", mimetype::xml},
        {"pdf", mimetype::pdf},
        {"zip", mimetype::zip},
    };

    std::string ltrim(const std::string &str, const std::string &whitespace){
        if(str.empty()) {
            return str;
        }
        std::size_t str_begin = str.find_first_not_of(whitespace);
        return str.substr(str_begin);
    }

    std::string rtrim(const std::string &str, const std::string &whitespace){
        if(str.empty()) {
            return str;
        }
        std::size_t str_end = str.find_last_not_of(whitespace);
        return str.substr(0, str_end+1);
    }


    std::string trim(const std::string &str, const std::string &whitespace)
    {
        if(str.empty()) {
            return str;
        }

        return ltrim(rtrim(str, whitespace), whitespace);
    }

    std::vector<std::string> explode(const std::string &str, const std::string &delimiter)
    {
        std::vector<std::string> result;

        std::size_t pos = 0;
        std::size_t last_pos = 0;
        while (true)
        {
            pos = str.find(delimiter, last_pos);
            if (pos == std::string::npos)
            {
                break;
            }
            result.push_back(str.substr(last_pos, pos - last_pos));
            last_pos = pos + delimiter.length();
        }
        result.push_back(str.substr(last_pos));

        return result;
    }

    std::string file_get_contents(const std::string &file_name)
    {
        std::string str = "";

        std::ifstream file(file_name);

        if (file.is_open())
        {
            file.seekg(0, std::ios::end);
            str.resize(file.tellg());
            file.seekg(0, std::ios::beg);
            file.read(&str[0], str.size());
            file.close();
        }
        return str;
    }

    std::string extension(const std::string &file_name)
    {
        std::size_t pos = file_name.find_last_of('.');
        if (pos != std::string::npos)
        {
            return file_name.substr(pos + 1);
        }
        return "";
    }

    config read_config(config &cfg, const std::string &config_file)
    {
        // read config.ini file
        std::ifstream fin(config_file);
        if (!fin.is_open())
        {
            logger().warn("config not load, set defaults");
            return cfg;
        }
        std::string line;
        std::map<std::string, std::string> options;
        while (std::getline(fin, line))
        {
            // trim line
            line = trim(line);
            if (line.empty() || line[0] == '#')
            {
                continue;
            }

            std::vector<std::string> tokens = explode(line, "=");

            if (tokens.size() != 2)
            {
                continue;
            }
            tokens[0] = trim(tokens[0]);
            tokens[1] = trim(tokens[1]);

            options.insert({tokens[0], tokens[1]});
        }
        if (options.count("host"))
        {
            cfg.host = options.at("host");
        }
        if (options.count("port"))
        {
            cfg.port = std::stoi(options.at("port"));
        }
        if (options.count("root_dir"))
        {
            cfg.root_dir = options.at("root_dir");
        }
        return cfg;
    }

    std::string timestamp()
    {
        auto t = std::time(nullptr);
        auto tm = *std::localtime(&t);
        std::ostringstream oss;
        oss << std::put_time(&tm, "%d-%m-%Y %H:%M:%S");
        return oss.str();
    }

    std::string to_string(const config &cfg)
    {
        std::ostringstream oss;
        oss << "{ host: " << cfg.host << ", port: " << cfg.port << ", root_dir: " << cfg.root_dir << " }";
        return oss.str();
    }
}