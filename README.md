# httpserver

Simple HTTP server.

## Build

You can use cmake tool to build.

I personal use custom makefile. Just make:

```bash
$ make -f Makefile.msys
```
The folder `build` will be created with `server` application.

## Configuration

Server uses simple configuration file `config.ini`:

```ini
# domain name, default value = localhost
host=localhost

# port number, default value = 80
port=8080

# site directory, default value = ./html
root_dir=./html
```

## Start

The project contains default site folder `html`, you can customize files in it. For running do:

```bash
$ make -f Makefile.msys start
```

And access http://localhost:8080 from your browser.

## TODO

 * ~~config file~~
 * ~~check config~~
 * start arguments
 * definitions to config file
