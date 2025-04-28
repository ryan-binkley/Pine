#ifndef LOGGER_H
#define LOGGER_H

typedef enum {
    INFO,
    WARNING,
    ERROR
} Severity;

typedef enum {
    OK = 200,
    BAD_REQUEST = 400,
    UNAUTHORIZED = 401,
    FORBIDDEN = 403,
    NOT_FOUND = 404,
    INTERNAL_SERVER_ERROR = 500,
    NONE = -1
} StatusCode;


void log_message(Severity severity, const char *message, StatusCode http_status_code);

#endif // LOGGER_H
