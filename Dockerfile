FROM alpine:latest

RUN apk add --no-cache build-base git

WORKDIR /app
COPY ./include ./include
COPY ./src ./src
COPY ./vendor ./vendor
COPY ./Makefile ./

RUN make

CMD ["tail", "-f", "/dev/null"]

EXPOSE 8080