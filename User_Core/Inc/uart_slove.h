//
// Created by 1 on 2023-11-18.
//

#ifndef ROBOMASTER_A_UART_SLOVE_H
#define ROBOMASTER_A_UART_SLOVE_H

#include "stdint.h"
#include <string.h>
#include <stdio.h>

#define RECEIVE_DATA_SIZE 1000
#define MAX_SIZE 900

typedef struct {

    uint8_t Username[50];
    uint8_t Password[50];
    int judge_count[16];
}Screen;


extern uint8_t Booking[16],Used[16];
extern uint8_t Judge_flag;
extern uint8_t receive_data[RECEIVE_DATA_SIZE];
extern Screen SCREEN[MAX_SIZE];
extern int8_t Receive_Start;
extern Screen InputMessage;
extern int8_t member[16];
extern int8_t open_locker[16];
extern int8_t Back_flag;
extern uint8_t RegisterFail_flag,RegisterSuccess_flag;
extern uint8_t PasswordChange_flag,PasswordInput_flag;
extern uint8_t BookFail_flag,BookSuccess_flag,PasswordChangeFail_flag,PasswordInputfail_flag;
extern uint8_t Buzzer_flag,Charge_flag,flag,close_flag;
extern uint8_t init_flag;
extern int current_locker,current_user;

int8_t Ignore(uint8_t *data);
int8_t Screen_slove(uint8_t *data, Screen *Sc);
void Clean(uint8_t *data);
void While(uint8_t *data, Screen *Sc);

#endif //ROBOMASTER_A_UART_SLOVE_H
