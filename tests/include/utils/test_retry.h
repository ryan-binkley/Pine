#ifndef TEST_RETRY_H
#define TEST_RETRY_H

#include "munit.h"

extern MunitSuite test_retry_suite[];
MunitResult test_retry_happy_path(const MunitParameter params[], void* user_data_or_fixture);
MunitResult test_retry_failure(const MunitParameter params[], void* user_data_or_fixture);

#endif