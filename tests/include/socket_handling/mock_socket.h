#ifndef MOCK_SOCKET_H
#define MOCK_SOCKET_H

#include "socket_handling/socket.h"

int mock_success_socket_create(int domain, int type, int protocol);
int mock_success_socket_bind(int sockfd, const struct sockaddr *addr, socklen_t addrlen);
int mock_success_socket_listen(int sockfd, int backlog);
int mock_fail_socket_create(int domain, int type, int protocol);
int mock_fail_socket_bind(int sockfd, const struct sockaddr *addr, socklen_t addrlen);
int mock_fail_socket_listen(int sockfd, int backlog);

#endif