//
// Created by danan on 2/24/2025.
//

#ifndef IMPL_H
#define IMPL_H

#include <stdio.h>
#include <stdint.h>

#define SUCCESS 0
#define FAILURE 1

void app_uart_put(char c);
int app_uart_get(uint8_t *c);

#endif //IMPL_H
