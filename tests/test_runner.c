#include <stdio.h>
#include "munit.h"
#include "test_retry.h"

MunitSuite full_test_suite[] = {
    {"/tests", NULL, test_retry_suite, 1, MUNIT_SUITE_OPTION_NONE}
};

int main() {
    printf("\n\nRunning tests...\n\n");
    return munit_suite_main(full_test_suite, NULL, 0, NULL);
}