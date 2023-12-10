//
// Created by 1 on 2023-11-04.
//

#ifndef ROBOMASTER_A_LED_H
#define ROBOMASTER_A_LED_H

#include "gpio.h"

#define BUZZER_ON __HAL_TIM_SetCompare(&htim12,TIM_CHANNEL_1,1000)
#define BUZZER_OFF __HAL_TIM_SetCompare(&htim12,TIM_CHANNEL_1,0)
#define LED1_Flash HAL_GPIO_TogglePin(GPIOF,GPIO_PIN_14);
#define LED2_Flash HAL_GPIO_TogglePin(GPIOE,GPIO_PIN_11);

void WaterLED(void);
void LEDALL(void);

#endif //ROBOMASTER_A_LED_H
