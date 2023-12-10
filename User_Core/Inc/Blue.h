//
// Created by 1 on 2023-11-26.
//

#ifndef ROBOMASTER_A_BLUE_H
#define ROBOMASTER_A_BLUE_H

#include "motor_task.h"
#include "printf.h"
#include "Password_judge.h"

void Blue_Judge(void);
void Blue_Init(void);
int8_t Blue_Cmd ( char * cmd1,char * reply1,uint32_t waittime );

extern int8_t BlueTooth_data[20];
extern char cmd_1[20],cmd_2[20],cmd_3[20];

#endif //ROBOMASTER_A_BLUE_H
