#include <stdio.h>
#include "logger.h"
#include "server.h"

int main() 
{
    int socket_fd = setup_server_socket();

    printf("Socket FD: %d\n", socket_fd);

    return 0;
}