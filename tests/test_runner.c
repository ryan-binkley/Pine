#include "minunit.h"

// Test functions
MU_TEST(test_example) {
    mu_check(1 == 1);
}

// Test suite
MU_TEST_SUITE(test_suite) {
    MU_RUN_TEST(test_example);
}

int main() {
    MU_RUN_SUITE(test_suite);
    MU_REPORT();
    return MU_EXIT_CODE;
}