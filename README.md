# httpserver
Simple HTTP server.

## Build
Just make:

```bash
$ make
```
The folder `build` will be created with `server` application.

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
