//
// Created by 1 on 2023-11-26.
//
#include "Blue.h"

char str[16][30] = {0};
char cmd_1[20] = {0},cmd_2[20] = {0},cmd_3[20] = {0};
int8_t BlueTooth_data[20] = {0};

void Blue_Judge(void)
{
        for(int i = 0;i < 16;i++)
        {
            if(Booking[i] == 1)
                sprintf(str[i],"%d booked           \n",i+1);
            else if(Used[i] == 1)
                sprintf(str[i],"%d used         \n",i+1);
            else if(Used[i] == 0)
                sprintf(str[i],"%d free         \n",i+1);
        }
    printf8("%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s",str[0],str[1],str[2],str[3],str[4],str[5],str[6],str[7],str[8],str[9],str[10],str[11],str[12],str[13],str[14],str[15]);
}

