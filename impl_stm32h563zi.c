//
// Created by danan on 2/24/2025.
//
#include "stm32h5xx_hal.h"
#include "impl.h"

extern UART_HandleTypeDef huart3;

void app_uart_put(char c) {
    HAL_UART_Transmit(&huart3, (uint8_t *)&c, 1, HAL_MAX_DELAY);
}

int app_uart_get(uint8_t *c) {
    HAL_StatusTypeDef status;
    status = HAL_UART_Receive(&huart3, c, 1, HAL_MAX_DELAY);
    return (status == HAL_OK) ? SUCCESS : FAILURE;
}
