#ifndef SOCKET_H
#define SOCKET_H

#include <sys/socket.h>
#include <netinet/in.h>
#include <stddef.h>

typedef struct {
    int domain;
    int type;
    int protocol;
} SocketCreateParams;

typedef struct {
    int sockfd;
    struct sockaddr* addr;
    socklen_t addrlen;
} SocketBindParams;

typedef struct {
    int sockfd;
    int backlog;
} SocketListenParams;

int socket_create(void* context);
int socket_bind(void* context);
int socket_listen(void* context);

#endif