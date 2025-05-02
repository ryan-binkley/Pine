#define MUNIT_ENABLE_ASSERT_ALIASES

#include "munit.h"
#include "test_retry.h"
#include "retry.h"

int mock_success_operation(void* context) {
    (void) context;
    return 0; // Simulate a successful operation
}
int mock_failure_operation(void* context) {
    (void) context;
    return -1; // Simulate a failed operation
}

MunitResult test_retry_happy_path(const MunitParameter params[], void* user_data_or_fixture) {
    (void) params;
    (void) user_data_or_fixture;


    int result = retry_operation(mock_success_operation, NULL, 3);
    assert_int(result, ==, 0);

    return MUNIT_OK;
}

MunitResult test_retry_failure(const MunitParameter params[], void* user_data_or_fixture) {
    (void) params;
    (void) user_data_or_fixture;


    int result = retry_operation(mock_failure_operation, NULL, 3);
    assert_int(result, ==, -1);

    return MUNIT_OK;
}

MunitTest tests[] = {
    {"/test_retry_happy_path", test_retry_happy_path, NULL, NULL, MUNIT_TEST_OPTION_NONE, NULL},
    {"/test_retry_failure", test_retry_failure, NULL, NULL, MUNIT_TEST_OPTION_NONE, NULL},

    {NULL, NULL, NULL, NULL, MUNIT_TEST_OPTION_NONE, NULL}
};

MunitSuite test_retry_suite[] = {
    {"/utils", tests, NULL, 1, MUNIT_SUITE_OPTION_NONE},

    {NULL, NULL, NULL, 0, MUNIT_SUITE_OPTION_NONE}
};