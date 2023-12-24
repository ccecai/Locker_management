//
// Created by 1 on 2023-11-18.
//
#include "motor_task.h"

float Angle_Output[4] = {0};
float current_angle[4] = {0};
int8_t locker_count = 0;
int8_t fang_flag = 0;
int8_t hen_count = 1;
int8_t shu_count = 1;

void Motor_Slove(uint8_t count)
{
    int8_t Open[count];
    int8_t current = 0,temp = 0;
    int8_t hen_flag = 0,shu_flag = 0;

//得到要打开的柜号
    for(int i = 0;i<16;i++)
    {
        if(open_locker[i] == 1)
        {
            Open[current++] = i + 1;
            open_locker[i] = 0;
        }
    }
//判断是否相邻
    if(count > 1)
    {

        //冒泡排序
        for(int i = 0;i<count-1;i++)
        {
            for(int j=0;j<count-i-1;j++)
            {
                if(Open[j] > Open[j+1])
                {
                    temp = Open[j];
                    Open[j] = Open[j+1];
                    Open[j+1] = temp;
                }
            }
        }
        for(int i = count; i > 1;i--)
        {
            if(Open[i-1] - Open[i-2] == 1 && Open[i - 1] != 5 &&  Open[i - 1] !=9)
            {
                hen_count++;
                hen_flag = 1;
            }
            else if(Open[i-1] - Open[i-2] == 1 && (Open[i - 1] == 5 || Open[i - 1] == 9))
            {
                shu_count = count / hen_count;
                fang_flag = 1;
                hen_flag = 0;
                shu_flag = 0;
                break;
            }
            else
            {
                shu_count = count / hen_count;
                fang_flag = 1;
                hen_flag = 0;
                shu_flag = 0;
                printf3("%d,%d\r\n",hen_count,shu_count);
                break;
            }
//            else
//            {
//                hen_flag = 0;
//            }

        }
        for(int i = count; i > 1;i--)
        {
            if(Open[i-1] - Open[i-2] == 4)
                shu_flag = 1;
            else
            {
                shu_flag = 0;
            }

        }
        //定义每个电机的角度值
        if(hen_flag == 1 || shu_flag == 1)
            Motor_Output(count,hen_flag,shu_flag,Open[0]);
        else if(fang_flag == 1)
        {
            Motor_Output(count,hen_flag,shu_flag,Open[0]);
        }

    }
    else
        Motor_Output(1,0,0,Open[0]);

    memset(Open,0,sizeof Open);

    locker_count = 0;
}

void Motor_Output(int count,int8_t hen,int8_t shu,int8_t min)
{
    switch (min) {
        case 1:
            if(count == 1)
                AllMotor_Give(-OneLocker_Angle,2 * OneLocker_Angle,-OneLocker_Angle,2 * OneLocker_Angle);
            else if(count > 1 && hen == 1)
            {
                printf3("%d,%d\r\n",hen_count,shu_count);
                AllMotor_Give(-OneLocker_Angle + OneLocker_Angle * (count - 1),2 * OneLocker_Angle,-OneLocker_Angle,2 * OneLocker_Angle);
            }
            else if(count > 1 && shu == 1)
                AllMotor_Give(-OneLocker_Angle,2 * OneLocker_Angle,(float)(-OneLocker_Angle + OneLocker_Angle * (count - 1)),2 * OneLocker_Angle);
            else if(fang_flag == 1)
            {
                AllMotor_Give(-OneLocker_Angle + OneLocker_Angle * (hen_count - 1),2 * OneLocker_Angle,(float)(-OneLocker_Angle + OneLocker_Angle * (shu_count - 1)),2 * OneLocker_Angle);
                printf3("%d,%d\r\n",hen_count,shu_count);
            }

            break;
        case 2:
            if(count == 1)
                AllMotor_Give(0,OneLocker_Angle,-OneLocker_Angle,2 * OneLocker_Angle);
            else if(count > 1 && hen == 1)
                AllMotor_Give( (float)(OneLocker_Angle * (count - 1)),OneLocker_Angle,-OneLocker_Angle,2 * OneLocker_Angle);
            else if(count > 1 && shu == 1)
                AllMotor_Give(0,OneLocker_Angle,(float )(-OneLocker_Angle + OneLocker_Angle * (count - 1)),2 * OneLocker_Angle);
            else if(fang_flag == 1)
                AllMotor_Give((float)(OneLocker_Angle * (hen_count - 1)),OneLocker_Angle,(float )(-OneLocker_Angle + OneLocker_Angle * (shu_count - 1)),2 * OneLocker_Angle);
            break;
        case 3:
            if(count == 1)
                AllMotor_Give(OneLocker_Angle,0,-OneLocker_Angle,2 * OneLocker_Angle);
            else if(count > 1 && hen == 1)
                AllMotor_Give((float )(OneLocker_Angle + OneLocker_Angle * (count - 1)),0,-OneLocker_Angle,2 * OneLocker_Angle);
            else if(count > 1 && shu == 1)
                AllMotor_Give(OneLocker_Angle,0,(float )(-OneLocker_Angle + OneLocker_Angle * (count - 1)),2 * OneLocker_Angle);
            else if(fang_flag == 1)
                AllMotor_Give((float )(OneLocker_Angle + OneLocker_Angle * (hen_count - 1)),0,(float )(-OneLocker_Angle + OneLocker_Angle * (shu_count - 1)),2 * OneLocker_Angle);
            break;
        case 4:
            if(count == 1)
                AllMotor_Give(2 * OneLocker_Angle,-OneLocker_Angle,-OneLocker_Angle,2 * OneLocker_Angle);
            else if(count > 1 && shu == 1)
                AllMotor_Give(2 * OneLocker_Angle,-OneLocker_Angle,(float )(-OneLocker_Angle + OneLocker_Angle * (count - 1)),2 * OneLocker_Angle);
            break;
        case 5:
            if(count == 1)
                AllMotor_Give(-OneLocker_Angle,2 * OneLocker_Angle,0,OneLocker_Angle);
            else if(count > 1 && hen == 1)
                AllMotor_Give(-OneLocker_Angle + OneLocker_Angle * (count - 1),2 * OneLocker_Angle,0,OneLocker_Angle);
            else if(count > 1 && shu == 1)
                AllMotor_Give(-OneLocker_Angle,2 * OneLocker_Angle, OneLocker_Angle * (count - 1),OneLocker_Angle);
            else if(fang_flag == 1)
                AllMotor_Give(-OneLocker_Angle + OneLocker_Angle * (hen_count - 1),2 * OneLocker_Angle,OneLocker_Angle * (shu_count - 1),OneLocker_Angle);
            break;
        case 6:
            if(count == 1)
                AllMotor_Give(0,OneLocker_Angle,0,OneLocker_Angle);
            else if(count > 1 && hen == 1)
                AllMotor_Give( (float)(OneLocker_Angle * (count - 1)),OneLocker_Angle,0,OneLocker_Angle);
            else if(count > 1 && shu == 1)
                AllMotor_Give(0,OneLocker_Angle,  OneLocker_Angle * (count - 1),OneLocker_Angle);
            else if(fang_flag == 1)
                AllMotor_Give((float)(OneLocker_Angle * (hen_count - 1)),OneLocker_Angle,OneLocker_Angle * (shu_count - 1),OneLocker_Angle);
            break;
        case 7:
            if(count == 1)
                AllMotor_Give(OneLocker_Angle,0,0,OneLocker_Angle);
            else if(count > 1 && hen == 1)
                AllMotor_Give((float )(OneLocker_Angle + OneLocker_Angle * (count - 1)),0,0,OneLocker_Angle);
            else if(count > 1 && shu == 1)
                AllMotor_Give(OneLocker_Angle,0,  OneLocker_Angle * (count - 1), OneLocker_Angle);
            else if(fang_flag == 1)
                AllMotor_Give((float )(OneLocker_Angle + OneLocker_Angle * (hen_count - 1)),0,OneLocker_Angle * (shu_count - 1),OneLocker_Angle);
            break;
        case 8:
            if(count == 1)
                AllMotor_Give(2 * OneLocker_Angle,-OneLocker_Angle,0,OneLocker_Angle);
            else if(count > 1 && shu == 1)
                AllMotor_Give(2 * OneLocker_Angle,-OneLocker_Angle, OneLocker_Angle * (count - 1),OneLocker_Angle);
            break;
        case 9:
            if(count == 1)
                AllMotor_Give(-OneLocker_Angle,2 * OneLocker_Angle,OneLocker_Angle,0);
            else if(count > 1 && hen == 1)
                AllMotor_Give(-OneLocker_Angle + OneLocker_Angle * (count - 1),2 * OneLocker_Angle,OneLocker_Angle,0);
            else if(count > 1 && shu == 1)
                AllMotor_Give(-OneLocker_Angle,2 * OneLocker_Angle, OneLocker_Angle + OneLocker_Angle * (count - 1),0);
            else if(fang_flag == 1)
                AllMotor_Give(-OneLocker_Angle + OneLocker_Angle * (hen_count - 1),2 * OneLocker_Angle,OneLocker_Angle + OneLocker_Angle * (shu_count - 1),0);
            break;
        case 10:
            if(count == 1)
                AllMotor_Give(0,OneLocker_Angle,OneLocker_Angle,0);
            else if(count > 1 && hen == 1)
                AllMotor_Give( (float )(OneLocker_Angle * (count - 1)),OneLocker_Angle,OneLocker_Angle,0);
            else if(count > 1 && shu == 1)
                AllMotor_Give(0,OneLocker_Angle,  OneLocker_Angle + OneLocker_Angle * (count - 1),0);
            else if(fang_flag == 1)
                AllMotor_Give((float )(OneLocker_Angle * (hen_count - 1)),OneLocker_Angle,OneLocker_Angle + OneLocker_Angle * (shu_count - 1),0);
            break;
        case 11:
            if(count == 1)
                AllMotor_Give(OneLocker_Angle,0,OneLocker_Angle,0);
            else if(count > 1 && hen == 1)
                AllMotor_Give((float )(OneLocker_Angle + OneLocker_Angle * (count - 1)),0,OneLocker_Angle,0);
            else if(count > 1 && shu == 1)
                AllMotor_Give(OneLocker_Angle,0,  OneLocker_Angle + OneLocker_Angle * (count - 1), 0);
            else if(fang_flag == 1)
                AllMotor_Give((float )(OneLocker_Angle + OneLocker_Angle * (hen_count - 1)),0,OneLocker_Angle + OneLocker_Angle * (shu_count- 1),0);
            break;
        case 12:
            if(count == 1)
                AllMotor_Give(2 * OneLocker_Angle,-OneLocker_Angle,OneLocker_Angle,0);
            else if(count > 1 && shu == 1)
                AllMotor_Give(2 * OneLocker_Angle,-OneLocker_Angle, OneLocker_Angle + OneLocker_Angle * (count - 1),0);
            break;
        case 13:
            if(count == 1)
                AllMotor_Give(-OneLocker_Angle,2 * OneLocker_Angle, 2 * OneLocker_Angle,-OneLocker_Angle);
            else if(count > 1 && hen == 1)
                AllMotor_Give(-OneLocker_Angle + OneLocker_Angle * (count - 1),2 * OneLocker_Angle,2 * OneLocker_Angle,-OneLocker_Angle);
            break;
        case 14:
            if(count == 1)
                AllMotor_Give(0,OneLocker_Angle,2 * OneLocker_Angle, -OneLocker_Angle);
            else if(count > 1 && hen == 1)
                AllMotor_Give( (float )(OneLocker_Angle * (count - 1)),OneLocker_Angle,2 * OneLocker_Angle,-OneLocker_Angle);
            break;
        case 15:
            if(count == 1)
                AllMotor_Give(OneLocker_Angle,0,2 * OneLocker_Angle,-OneLocker_Angle);
            else if(count > 1 && hen == 1)
                AllMotor_Give((float )(OneLocker_Angle + OneLocker_Angle * (count - 1)),0,2 * OneLocker_Angle,-OneLocker_Angle);
            break;
        case 16:
                AllMotor_Give(2 * OneLocker_Angle,-OneLocker_Angle,2 * OneLocker_Angle,-OneLocker_Angle);
            break;
        default:
            break;

    }
    fang_flag = 0;
    hen_count = 1;
    shu_count = 1;
}

void AllMotor_Give(float angle1,float angle2,float angle3,float angle4)
{
    Angle_Output[0] = Motor_Change(angle1);
    Angle_Output[1] = Motor_Change(angle2);
    Angle_Output[2] = Motor_Change(angle3);
    Angle_Output[3] = Motor_Change(angle4);

    current_angle[0] = angle1;
    current_angle[1] = angle2;
    current_angle[2] = angle3;
    current_angle[3] = angle4;

//    printf3("%f,%f,%f,%f\r\n",Angle_Output[0],Angle_Output[1],Angle_Output[2],Angle_Output[3]);
}

float Motor_Change(float MotorAngle)
{
    return MotorAngle / 360 * 8192 * 36;
}
