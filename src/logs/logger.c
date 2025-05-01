#include "logs/logger.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <curl/curl.h>

#define LOG_ENDPOINT "https://s1288156.eu-nbg-2.betterstackdata.com"
#define LOG_TOKEN "LOG_TOKEN"
#define APP_ENV "APP_ENV"

static const char* severity_to_string(Severity severity)
{
    switch (severity)
    {
    case INFO:
        return "info";
    case WARNING:
        return "warning";
    case ERROR:
        return "error";
    default:
        return "unknown";
    }
}

static void get_utc_timestamp(char* buffer, size_t size)
{
    time_t now = time(NULL);
    struct tm *utc_time = gmtime(&now);
    strftime(buffer, size, "%Y-%m-%d %H:%M:%S UTC", utc_time);
}

static int http_status_code_is_error(StatusCode http_status_code)
{
    if (http_status_code >= 400 && http_status_code < 600)
    {
        return 1;
    }
    return 0;
}

void log_message(Severity severity, const char* message, StatusCode http_status_code)
{
    CURL* curl;
    CURLcode res;
    struct curl_slist *headers = NULL;
    char timestamp[64];
    char json_payload[1024];
    char *log_token = getenv(LOG_TOKEN);

    if (!log_token)
    {
        fprintf(stderr, "Environment variable %s not set! Log message not sent.\n", LOG_TOKEN);
        return;
    }

    get_utc_timestamp(timestamp, sizeof(timestamp));

    if (http_status_code != -1)
    {
        snprintf(json_payload, sizeof(json_payload), "{\"dt\":\"%s\",\"severity\":\"%s\",\"message\":\"%s\",\"http_status\":%d}", timestamp, severity_to_string(severity), message, http_status_code);

        fprintf(stdout, "[%s] %s: %s (%d)\n", severity_to_string(severity), timestamp, message, http_status_code);
    }
    else if (http_status_code_is_error(http_status_code))
    {
        snprintf(json_payload, sizeof(json_payload), "{\"dt\":\"%s\",\"severity\":\"%s\",\"message\":\"%s\",\"http_status\":%d}", timestamp, severity_to_string(severity), message, http_status_code);

        fprintf(stderr, "[%s] %s: %s\n", severity_to_string(severity), timestamp, message);
    }
    else
    {
        snprintf(json_payload, sizeof(json_payload), "{\"dt\":\"%s\",\"severity\":\"%s\",\"message\":\"%s\"}", timestamp, severity_to_string(severity), message);

        fprintf(stdout, "[%s] %s: %s\n", severity_to_string(severity), timestamp, message);
    }

    curl = curl_easy_init();
    if (curl)
    {
        headers = curl_slist_append(headers, "Content-Type: application/json");

        char auth_header[256];
        snprintf(auth_header, sizeof(auth_header), "Authorization: Bearer %s", log_token);

        headers = curl_slist_append(headers, auth_header);

        curl_easy_setopt(curl, CURLOPT_URL, LOG_ENDPOINT);
        curl_easy_setopt(curl, CURLOPT_HTTPHEADER, headers);
        curl_easy_setopt(curl, CURLOPT_POSTFIELDS, json_payload);
        curl_easy_setopt(curl, CURLOPT_SSL_VERIFYPEER, 0L); // Skip SSL verification, like curl -k

        if (strcmp(getenv(APP_ENV), "development") == 0 || strcmp(getenv(APP_ENV), "production") == 0)
        {
            res = curl_easy_perform(curl);
            if (res != CURLE_OK)
            {
                fprintf(stderr, "log_message() failed: %s\n", curl_easy_strerror(res));
            }
        }

        curl_slist_free_all(headers);
        curl_easy_cleanup(curl);
    }
}

void log_debug(const char* message)
{
    fprintf(stdout, "[DEBUG] --- %s\n", message);
}

void log_debug_error(const char* message)
{
    fprintf(stderr, "[ERROR] --- %s\n", message);
    perror(message);
}