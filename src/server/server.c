// server_setup.c
#include <stdio.h>
#include <stdlib.h>
#include "logs/logger.h"
#include "socket_handling/socket.h"
#include "server/server.h"
#include "utils/retry.h"
#include "string.h"
#include "config.h"

int setup_server_socket() 
{
    SocketCreateParams params = {AF_INET, SOCK_STREAM, 0};
    int fd = retry_operation(socket_create, &params, 3);
    if (fd == -1) 
    {
        log_debug_error("socket create failed\n");
        return -1;
    }

    // Allow port to be reused
    int opt = 1;
    setsockopt(fd, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(opt));

    struct sockaddr_in server_addr;
    server_addr.sin_family = AF_INET;
    server_addr.sin_addr.s_addr = INADDR_ANY;
    if (strcmp(getenv(APP_ENV), "local") == 0)
    {
        server_addr.sin_port = htons(8080);
    }
    else if (strcmp(getenv(APP_ENV), "development") == 0 || strcmp(getenv(APP_ENV), "production") == 0)
    {
        server_addr.sin_port = htons(80);
    }

    SocketBindParams bind_params = {fd, (struct sockaddr *)&server_addr, sizeof(server_addr)};
    int bind_result = retry_operation(socket_bind, &bind_params, 3);

    if (bind_result == -1) 
    {
        log_debug_error("socket bind failed\n");
        return -1;
    }
    
    SocketListenParams listen_params = {fd, 256};
    int listen_result = retry_operation(socket_listen, &listen_params, 3);
    if (listen_result == -1) 
    {
        log_debug_error("socket listen failed\n");
        return -1;
    }

    log_debug("socket setup successful\n");
    
    return fd;
}