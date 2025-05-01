// server_setup.c
#include <stdio.h>
#include "logs/logger.h"
#include "socket_handling/socket.h"
#include "server/server.h"


int setup_server_socket(socket_ops_t *ops) 
{
    int fd = ops->socket_create_fn(AF_INET, SOCK_STREAM, 0);
    
    if (fd == -1) 
    {
        log_debug_error("socket create failed\n");
        return -1;
    }

    struct sockaddr_in server_addr;
    server_addr.sin_family = AF_INET;
    server_addr.sin_addr.s_addr = INADDR_ANY;
    server_addr.sin_port = htons(8080);

    int bind_result = ops->bind_create_fn(fd, (struct sockaddr *)&server_addr, sizeof(server_addr));

    if (bind_result == -1) 
    {
        log_debug_error("socket bind failed\n");
        return -1;
    }
    
    int listen_result = ops->listen_create_fn(fd, 5);
    if (listen_result == -1) 
    {
        log_debug_error("socket listen failed\n");
        return -1;
    }
    log_debug("socket setup successful\n");
    
    return fd;
}