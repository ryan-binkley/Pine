#define MUNIT_ENABLE_ASSERT_ALIASES

#include "munit.h"
#include "mock_socket.h"
#include "test_server.h"
#include "server.h"


MunitResult test_setup_server_socket_happy_path(const MunitParameter params[], void* user_data_or_fixture) {
    (void) params;
    (void) user_data_or_fixture;

    socket_ops_t ops;
    ops.socket_create_fn = mock_success_socket_create;
    ops.bind_create_fn = mock_success_socket_bind;
    ops.listen_create_fn = mock_success_socket_listen;

    int fd = setup_server_socket(&ops);
    assert_int(fd, !=, -1);

    return MUNIT_OK;
}

MunitResult test_setup_server_socket_create_fails(const MunitParameter params[], void* user_data_or_fixture) {
    (void) params;
    (void) user_data_or_fixture;

    socket_ops_t ops;
    ops.socket_create_fn = mock_fail_socket_create;
    ops.bind_create_fn = mock_success_socket_bind;
    ops.listen_create_fn = mock_success_socket_listen;

    int fd = setup_server_socket(&ops);
    assert_int(fd, ==, -1);

    return MUNIT_OK;
}

MunitResult test_setup_server_socket_bind_fails(const MunitParameter params[], void* user_data_or_fixture) {
    (void) params;
    (void) user_data_or_fixture;

    socket_ops_t ops;
    ops.socket_create_fn = mock_success_socket_create;
    ops.bind_create_fn = mock_fail_socket_bind;
    ops.listen_create_fn = mock_success_socket_listen;

    int fd = setup_server_socket(&ops);
    assert_int(fd, ==, -1);

    return MUNIT_OK;
}

MunitResult test_setup_server_socket_listen_fails(const MunitParameter params[], void* user_data_or_fixture) {
    (void) params;
    (void) user_data_or_fixture;

    socket_ops_t ops;
    ops.socket_create_fn = mock_success_socket_create;
    ops.bind_create_fn = mock_success_socket_bind;
    ops.listen_create_fn = mock_fail_socket_listen;

    int fd = setup_server_socket(&ops);
    assert_int(fd, ==, -1);

    return MUNIT_OK;
}

MunitTest tests[] = {
    {"/setup_server_socket_happy_path", test_setup_server_socket_happy_path, NULL, NULL, MUNIT_TEST_OPTION_NONE, NULL},
    {"/test_setup_server_socket_create_fails", test_setup_server_socket_create_fails, NULL, NULL, MUNIT_TEST_OPTION_NONE, NULL},
    {"/test_setup_server_socket_bind_fails", test_setup_server_socket_bind_fails, NULL, NULL, MUNIT_TEST_OPTION_NONE, NULL},
    {"/test_setup_server_socket_listen_fails", test_setup_server_socket_listen_fails, NULL, NULL, MUNIT_TEST_OPTION_NONE, NULL},

    {NULL, NULL, NULL, NULL, MUNIT_TEST_OPTION_NONE, NULL}
};

MunitSuite test_server_suite[] = {
    {"/server", tests, NULL, 1, MUNIT_SUITE_OPTION_NONE},

    {NULL, NULL, NULL, 0, MUNIT_SUITE_OPTION_NONE}
};