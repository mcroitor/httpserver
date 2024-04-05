# compile application
FROM gcc:12 AS build

RUN apt-get update && apt-get install -y cmake

WORKDIR /app

COPY . .

RUN mkdir -p build && cd build && cmake .. && make

# run unit tests
FROM build AS test

RUN apt-get update && apt-get install -y catch2

WORKDIR /app/tests

COPY tests .

RUN mkdir -p build && cd build && cmake .. && make && ./unittests

# copy application to scratch image
FROM scratch

LABEL maintainer="Mihail Croitor <mcroitor@gmail.com>"
LABEL appname="httpserver"
LABEL version="1.0.0"

COPY --from=test /app/build/httpserver /httpserver
COPY --from=test /app/html /html
COPY --from=test /app/config.ini /config.ini

EXPOSE 8080

CMD ["/httpserver"]