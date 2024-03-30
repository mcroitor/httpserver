# httpserver

Simple HTTP server.

## Build

You can use cmake tool to build.

```bash
mkdir build
cd build
cmake ..
make
```

I use custom makefile. Just make:

```bash
make -f Makefile.msys
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
make -f Makefile.msys start
```

And access `http://localhost:8080` from your browser.

## Docker version

You also can try to use docker version. Just build image and run container:

```bash
docker build -t httpserver .
docker run -d -p 8080:8080 --name httpserver httpserver
```

The site is placed int the `/html` directory by default, you can mount your own site directory:

```bash
docker run -d -p 8080:8080 -v /path/to/your/site:/html --name httpserver httpserver
```

Docker Compose is also supported:

```bash
docker-compose up -d
```

## TODO

- ~~config file~~
- ~~check config~~
- start arguments
- definitions to config file
- proxy
- logging
