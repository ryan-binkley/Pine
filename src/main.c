#include <stdio.h>
#include "logger.h"

int main() 
{
    printf("Hello World!\n");

    log_message(INFO, "This is an info message", OK);
    log_message(WARNING, "This is a warning message", NONE);
    log_message(ERROR, "This is an error message", INTERNAL_SERVER_ERROR);

    return 0;
}