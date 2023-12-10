//
// Created by 1 on 2023-11-18.
//

#ifndef ROBOMASTER_A_PASSWORD_JUDGE_H
#define ROBOMASTER_A_PASSWORD_JUDGE_H

#include "uart_slove.h"
#include "printf.h"
#include "string.h"

int8_t UR_JUDEG(uint8_t UserID,Screen *Sc);

int8_t R_JUDEG(uint8_t UserID,Screen *Sc);
void UR_Init(void);
int Book_Judge(int i);
void Open_Judge(uint8_t UserID,Screen *Sc);
int8_t U_JUDEG(uint8_t UserID,Screen *Sc);
void Printf_Judge(void);
void member_judge(uint8_t data);

#endif //ROBOMASTER_A_PASSWORD_JUDGE_H
