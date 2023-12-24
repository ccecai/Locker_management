//
// Created by 1 on 2023-11-02.
//
#include "Mymain.h"

int8_t Judge = 0;

void Mymain_Init(void)
{
    can1_filter_init();
    can2_filter_init();
    RetargetInit(&huart3);
    RetargetInit(&huart6);
    RetargetInit(&huart7);
    RetargetInit(&huart8);
    HAL_TIM_PWM_Start(&htim12,TIM_CHANNEL_1);

//    do
//    {
//        Judge = ESP_Init();
////        printf3("error code:%d\r\n",Judge);
//        osDelay(20);
//    }while(Judge);  //连接华为云直到成功
}