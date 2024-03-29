FROM gcc:12 AS build

RUN apt-get update && apt-get install -y cmake

WORKDIR /app

COPY . .

RUN mkdir -p build && cd build && cmake .. && make

FROM scratch

LABEL maintainer="Mihail Croitor <mcroitor@gmail.com>"
LABEL appname="httpserver"
LABEL version="1.0.0"

COPY --from=build /app/build/httpserver /httpserver
COPY --from=build /app/html /html
COPY --from=build /app/config.ini /config.ini

EXPOSE 8080

CMD ["/httpserver"]