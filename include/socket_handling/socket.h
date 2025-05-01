#ifndef SOCKET_H
#define SOCKET_H

#include <sys/socket.h>
#include <netinet/in.h>
#include <stddef.h>

int socket_create(int domain, int type, int protocol);
int socket_bind(int sockfd, const struct sockaddr *addr, socklen_t addrlen);
int socket_listen(int sockfd, int backlog);

#endif