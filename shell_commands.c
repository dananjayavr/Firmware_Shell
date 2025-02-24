//
// Created by danan on 2/21/2025.
//
#include <stdio.h>
#include <stdbool.h>
#include "shell/shell.h"

#define ARRAY_SIZE(arr) (sizeof(arr) / sizeof(arr[0]))

void shell_result_success(void) {
    shell_put_line("> OK");
}

void shell_result_fail(int code) {
    char buf[32];
    snprintf(buf, sizeof(buf), "> FAIL,%d", code);
    shell_put_line(buf);
}


// A simple Hello World command which prints "Hello World!"
int cli_cmd_hello(int argc, char *argv[]) {
    shell_put_line("Hello World!");
    return 0;
}

int cli_cmd_kv_write(int argc, char *argv[]) {
    // We expect 3 arguments:
    // 1. Command name
    // 2. Key
    // 3. Value
    if (argc != 3) {
        shell_put_line("> FAIL,1");
        return -1;
    }

    const char *key = argv[1];
    const char *value = argv[2];

    //bool result = kv_store_write(key, value, strlen(value));
    bool result = true;
    if (!result) {
        shell_result_fail(2);
        return -1;
    }
    shell_result_success();
    return 0;
}


static const sShellCommand s_shell_commands[] = {
    {"hello", cli_cmd_hello, "Say hello"},
    {"kv_write", cli_cmd_kv_write, "Write a Key/Value pair"},
    {"help", shell_help_handler, "Lists all commands"},
  };

const sShellCommand *const g_shell_commands = s_shell_commands;
const size_t g_num_shell_commands = ARRAY_SIZE(s_shell_commands);