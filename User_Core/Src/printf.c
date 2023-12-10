#include "stdarg.h"
#include "stdio.h"
#include "main.h"
#include "printf.h"

#define TX_BUF_SIZE 512

uint8_t send_buf3[TX_BUF_SIZE];
uint8_t send_buf6[TX_BUF_SIZE];
uint8_t send_buf7[TX_BUF_SIZE];
uint8_t send_buf8[TX_BUF_SIZE];

void usart_printf(const char *format, ...)
{
    va_list args;
    uint32_t length;

    va_start(args, format);
    length = vsnprintf((char *) send_buf6, TX_BUF_SIZE, (const char *) format, args);
    va_end(args);
//  HAL_UART_Transmit(&huart8, (uint8_t *)send_buf, length, 0xFFFF);
    HAL_UART_Transmit_DMA(&huart6, (uint8_t *) send_buf6, length);
}
void printf7(const char *format, ...)
{
    va_list args;
    uint32_t length;

    va_start(args, format);
    length = vsnprintf((char *) send_buf7, TX_BUF_SIZE, (const char *) format, args);
    va_end(args);
//  HAL_UART_Transmit(&huart8, (uint8_t *)send_buf, length, 0xFFFF);
    HAL_UART_Transmit_DMA(&huart7, (uint8_t *) send_buf7, length);
}
void printf8(const char *format, ...)
{
    va_list args;
    uint32_t length;

    va_start(args, format);
    length = vsnprintf((char *) send_buf8, TX_BUF_SIZE, (const char *) format, args);
    va_end(args);
//  HAL_UART_Transmit(&huart8, (uint8_t *)send_buf, length, 0xFFFF);
    HAL_UART_Transmit_DMA(&huart8, (uint8_t *) send_buf8, length);
}

void printf3(const char *format, ...)
{
    va_list args;
    uint32_t length;

    va_start(args, format);
    length = vsnprintf((char *) send_buf3, TX_BUF_SIZE, (const char *) format, args);
    va_end(args);
//  HAL_UART_Transmit(&huart8, (uint8_t *)send_buf, length, 0xFFFF);
    HAL_UART_Transmit_DMA(&huart3, (uint8_t *) send_buf3, length);
}
