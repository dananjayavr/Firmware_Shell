//
// Created by danan on 2/21/2025.
//
#include "CppUTest/TestHarness.h"
#include "CppUTestExt/MockSupport.h"

extern "C"
{
    //Any C .h files can go here
    #include "shell.h"
    extern int cli_cmd_hello(int argc, char *argv[]);
}

static char s_resp_buffer[1024];
static const size_t s_resp_buffer_len = sizeof(s_resp_buffer);

// Stub
int shell_help_handler(int argc, char *argv[]) {
    return 0;
}

// Poor man's mock
void shell_put_line(const char *str) {
    strncpy(s_resp_buffer, str, s_resp_buffer_len);
}

TEST_GROUP(TestShellCommands)
{
    void setup() {}
    void teardown() {}
};

TEST(TestShellCommands, hello)
{
    int argc = 1;
    char *argv[] = {
        (char *)"hello"
    };

    cli_cmd_hello(argc, argv);
    STRNCMP_EQUAL("Hello World!", s_resp_buffer, sizeof(s_resp_buffer));
}