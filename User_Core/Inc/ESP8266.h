//
// Created by 1 on 2023-12-03.
//

#ifndef ROBOMASTER_A_ESP8266_H
#define ROBOMASTER_A_ESP8266_H

#include "printf.h"
#include <string.h>
#include "uart_slove.h"

extern uint8_t ESPS[200];

int8_t ESP_Init(void);
int8_t ESP_Send(void);
void esp8266_send(void);
void Esp_Judge(void);

#endif //ROBOMASTER_A_ESP8266_H
