#include <sys/socket.h>
#include "socket_handling/socket.h"

int socket_create(int domain, int type, int protocol) 
{
    return socket(domain, type, protocol);
}

int socket_bind(int sockfd, const struct sockaddr *addr, socklen_t addrlen) {
    return bind(sockfd, addr, addrlen);
}

int socket_listen(int sockfd, int backlog) 
{
    return listen(sockfd, backlog);
}