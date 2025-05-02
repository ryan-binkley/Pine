#include <sys/socket.h>
#include "socket_handling/socket.h"

int socket_create(void* context) 
{
    SocketCreateParams* params = (SocketCreateParams*)context;
    return socket(params->domain, params->type, params->protocol);
}

int socket_bind(void* context) 
{
    SocketBindParams* params = (SocketBindParams*)context;
    return bind(params->sockfd, params->addr, params->addrlen);
}

int socket_listen(void* context) 
{
    SocketListenParams* params = (SocketListenParams*)context;
    return listen(params->sockfd, params->backlog);
}