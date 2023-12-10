//
// Created by 1 on 2023-11-18.
//

#ifndef ROBOMASTER_A_MOTOR_TASK_H
#define ROBOMASTER_A_MOTOR_TASK_H

#include "main.h"

extern float Angle_Output[4];
extern int8_t locker_count;

#define OneLocker_Angle 126.5

void Motor_Slove(uint8_t count);
float Motor_Change(float MotorAngle);
void AllMotor_Change(void);
void Motor_Output(int count,int8_t hen,int8_t shu,int8_t min);
void AllMotor_Give(float angle1,float angle2,float angle3,float angle4);

#endif //ROBOMASTER_A_MOTOR_TASK_H
