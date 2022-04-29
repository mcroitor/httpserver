# httpserver
Simple HTTP server.

## Build
Create folders for output and make:

```bash
$ mkdir obj
$ mkdir build
$ make
```

## Start

Create a folder for HTML site and place your site in this folder, run server:

```bash
$ cd build
$ mkdir html
$ echo "<h2>Hello World</h2>" > html/index.html
$ ./server
```

And access http://localhost from your browser.

## TODO

 * config file
 * check config
 * start arguments
 * definitions to config file
