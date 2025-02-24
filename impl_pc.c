//
// Created by danan on 2/24/2025.
//
#include "impl.h"

void app_uart_put(char c) {
    printf("%c", c);  // Simulate UART transmit via console
}

int app_uart_get(uint8_t *c) {
    *c = getchar();  // Use getchar to read a character
    return (*c != EOF) ? SUCCESS : FAILURE;
}
