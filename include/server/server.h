#ifndef SERVER_H
#define SERVER_H

#include "socket_handling/socket.h"

typedef struct {
    int (*socket_create_fn)(int, int, int);
    int (*bind_create_fn)(int, const struct sockaddr *, socklen_t);
    int (*listen_create_fn)(int, int);
} socket_ops_t;


int setup_server_socket(socket_ops_t *ops);

#endif