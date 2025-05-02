#include "retry.h"
#include "logger.h"

int retry_operation (Operation op, void* context, int count) 
{
    for (int i = 0; i < count; ++i) 
    {
        int result = op(context);
        if (result >= 0) return result;
    }

    log_debug_error("Operation failed\n");
    return -1;
}