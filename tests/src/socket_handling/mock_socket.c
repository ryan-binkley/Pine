#include "mock_socket.h"

// SUCCESS
int mock_success_socket_create(int domain, int type, int protocol) 
{
    (void)domain;
    (void)type;
    (void)protocol;
    return 1;
}

int mock_success_socket_bind(int sockfd, const struct sockaddr *addr, socklen_t addrlen) 
{
    (void)sockfd;
    (void)addr;
    (void)addrlen;
    return 0;
}

int mock_success_socket_listen(int sockfd, int backlog) 
{
    (void)sockfd;
    (void)backlog;
    return 0;
}

// FAIL
int mock_fail_socket_create(int domain, int type, int protocol) 
{
    (void)domain;
    (void)type;
    (void)protocol;
    return -1;
}

int mock_fail_socket_bind(int sockfd, const struct sockaddr *addr, socklen_t addrlen) 
{
    (void)sockfd;
    (void)addr;
    (void)addrlen;
    return -1;
}

int mock_fail_socket_listen(int sockfd, int backlog) 
{
    (void)sockfd;
    (void)backlog;
    return -1;
}