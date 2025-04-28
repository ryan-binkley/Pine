FROM alpine:latest

RUN apk add --no-cache build-base git curl-dev curl libcurl

WORKDIR /app
COPY ./include ./include
COPY ./src ./src
COPY ./vendor ./vendor
COPY ./Makefile ./

RUN make

CMD ["./build/bin/pine"]

EXPOSE 8080