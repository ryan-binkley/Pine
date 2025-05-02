#ifndef RETRY_H
#define RETRY_H

typedef int (*Operation)(void* context);

int retry_operation (Operation op, void* context, int count);

#endif