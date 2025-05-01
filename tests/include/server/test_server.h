#ifndef TEST_SERVER_H
#define TEST_SERVER_H

#include "munit.h"

extern MunitSuite test_server_suite[];

MunitResult test_setup_server_socket(const MunitParameter params[], void* user_data_or_fixture);

#endif