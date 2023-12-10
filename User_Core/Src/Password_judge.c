//
// Created by 1 on 2023-11-18.
//
#include "Password_judge.h"
int feed = 5;

int Book_Judge(int i)
{

        if(member[i] == 1 && Booking[i] == 1)
        {
            BookFail_flag = 1;
        }
        else if(Booking[i] == 0)
        {
            Booking[i] = 1;
            BookSuccess_flag = 1;
        }

    member[i] = 0;
}

void UR_Init(void)
{
    SCREEN[0].Username[0] = 0x32;
    SCREEN[0].Username[1] = 0x30;
    SCREEN[0].Username[2] = 0x32;
    SCREEN[0].Username[3] = 0x31;
    SCREEN[0].Username[4] = 0x31;
    SCREEN[0].Username[5] = 0x34;
    SCREEN[0].Username[6] = 0x31;
    SCREEN[0].Username[7] = 0x34;
    SCREEN[0].Username[8] = 0x35;
    SCREEN[0].Username[9] = 0x30;
    SCREEN[0].Username[10] = 0x30;
    SCREEN[0].Username[11] = 0x32;
    SCREEN[0].Username[12] = 0x37;


    SCREEN[0].Password[0] = 0x31;
    SCREEN[0].Password[1] = 0x32;
    SCREEN[0].Password[2] = 0x33;
    SCREEN[0].Password[3] = 0x34;
    SCREEN[0].Password[4] = 0x35;
    SCREEN[0].Password[5] = 0x36;
}

void Printf_Judge(void)
{
    if(Judge_flag == 1)
    {
        if(RegisterFail_flag == 1)
        {
            RegisterFail_flag = 0;
            usart_printf("page fail\xff\xff\xff");
        }
        else if(RegisterSuccess_flag == 1)
        {
            RegisterSuccess_flag = 0;
            usart_printf("page success\xff\xff\xff");
//            usart_printf("1\r\n");
        }
        else if(PasswordChange_flag == 1)
        {
            PasswordChange_flag = 0;
            usart_printf("page changesuccess\xff\xff\xff");
        }
        else if(PasswordInput_flag == 1)
        {
            PasswordInput_flag = 0;
            usart_printf("page inputsuccess\xff\xff\xff");
        }
        else if(PasswordInputfail_flag == 1)
        {
            PasswordInputfail_flag = 0;
            usart_printf("page inputfail\xff\xff\xff");
        }
        else if(BookFail_flag == 1)
        {
            BookFail_flag = 0;
            usart_printf("page bookfail\xff\xff\xff");
        }
        else if(BookSuccess_flag == 1)
        {
            BookSuccess_flag = 0;
            usart_printf("page booksuccess\xff\xff\xff");
        }
        else if(PasswordChangeFail_flag == 1)
        {
            PasswordChangeFail_flag = 0;
            usart_printf("page changefail\xff\xff\xff");
        }

        if(flag == 1)
        {
            usart_printf("erweima.t1.txt=\"%d\"\xff\xff\xff",Charge_flag * feed);

            Charge_flag = 0;

            flag = 0;

        }

        Judge_flag = 0;
    }

}

void member_judge(uint8_t data)
{
    switch(data) {
        case 0x01:
            member[0] = 1;
            break;
        case 0x02:
            member[1] = 1;
            break;
        case 0x03:
            member[2] = 1;
            break;
        case 0x04:
            member[3] = 1;
            break;
        case 0x05:
            member[4] = 1;
            break;
        case 0x06:
            member[5] = 1;
            break;
        case 0x07:
            member[6] = 1;
            break;
        case 0x08:
            member[7] = 1;
            break;
        case 0x09:
            member[8] = 1;
            break;
        case 0x10:
            member[9] = 1;
            break;
        case 0x11:
            member[10] = 1;
            break;
        case 0x12:
            member[11] = 1;
            break;
        case 0x13:
            member[12] = 1;
            break;
        case 0x14:
            member[13] = 1;
            break;
        case 0x15:
            member[14] = 1;
            break;
        case 0x16:
            member[15] = 1;
            break;
        case 0xa1:
            member[0] = 0;
            break;
        case 0xa2:
            member[1] = 0;
            break;
        case 0xa3:
            member[2] = 0;
            break;
        case 0xa4:
            member[3] = 0;
            break;
        case 0xa5:
            member[4] = 0;
            break;
        case 0xa6:
            member[5] = 0;
            break;
        case 0xa7:
            member[6] = 0;
            break;
        case 0xa8:
            member[7] = 0;
            break;
        case 0xa9:
            member[8] = 0;
            break;
        case 0xb0:
            member[9] = 0;
            break;
        case 0xb1:
            member[10] = 0;
            break;
        case 0xb2:
            member[11] = 0;
            break;
        case 0xb3:
            member[12] = 0;
            break;
        case 0xb4:
            member[13] = 0;
            break;
        case 0xb5:
            member[14] = 0;
            break;
        case 0xb6:
            member[15] = 0;
            break;
        default:
            break;
    }
}