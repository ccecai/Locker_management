//
// Created by 1 on 2023-11-18.
//
#include "uart_slove.h"
#include "Password_judge.h"

int8_t Back_flag = 0;
uint8_t receive_data[RECEIVE_DATA_SIZE]={0};
int8_t member[16] = {0};
int8_t open_locker[16] = {0};
Screen SCREEN[MAX_SIZE];
Screen InputMessage;
int8_t Receive_Start = 1;
uint8_t Booking[16] = {0},Used[16] = {0};
int input = 1;
uint8_t Judge_flag;
int count = 0;
int current_user;
int current_locker;
uint8_t init_flag = 1;
uint8_t success_flag = 0,fail_flag = 0;

uint8_t RegisterFail_flag = 0,RegisterSuccess_flag = 0;
uint8_t PasswordChange_flag = 0,PasswordInput_flag = 0,PasswordChangeFail_flag = 0,PasswordInputfail_flag = 0;
uint8_t BookFail_flag = 0,BookSuccess_flag = 0,Charge_flag = 0,flag = 0,close_flag = 0;
uint8_t Buzzer_flag = 0;

int8_t Screen_slove(uint8_t *data, Screen *Sc)
{
        uint8_t username_count = 1,password_count = 1;

        if(data[0] == 0xaa && data[1] == 0xab && data[2] == 0xac) //��������λ
        {
            AllMotor_Give(0,0,0,0);
        }

        else if(data[0] == 0x3a) //��¼�����ж������Ƿ�������ȷ
        {

            if(++count == 4)
            {
                while(data[username_count] != 0xff)
                {
                    InputMessage.Username[username_count-1] = data[username_count];
                    username_count++;
                }

                username_count++;

                while(data[username_count] != 0xfd)
                {
                    InputMessage.Password[password_count-1] = data[username_count];
                    username_count++;
                    password_count++;
                }

                for(int8_t i = 0;i < Receive_Start;i++)
                {
                    if(strcmp((char *)SCREEN[i].Username,(char *)InputMessage.Username) == 0 && strcmp((char *)SCREEN[i].Password,(char *)InputMessage.Password) == 0)
                    {
                        RegisterSuccess_flag = 1;
                        RegisterFail_flag = 0;
                        current_user = i;
                        break;
                    }
                    else
                    {
                        RegisterFail_flag = 1;
                    }


                }
//                printf7("%d,%d\r\n",RegisterSuccess_flag,RegisterFail_flag);
                count = 0;
            }
//            printf7("%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d\r\n",SCREEN[1].Username[0],SCREEN[1].Username[1],SCREEN[1].Username[2],SCREEN[1].Username[3],SCREEN[1].Username[4],SCREEN[1].Username[5],SCREEN[1].Username[6],SCREEN[1].Password[0],SCREEN[1].Password[1],SCREEN[1].Password[2],SCREEN[1].Password[3],SCREEN[1].Password[4],SCREEN[1].Username[5],SCREEN[1].Username[6]);

            memset(InputMessage.Username,0,sizeof InputMessage.Username);
            memset(InputMessage.Password,0,sizeof InputMessage.Password);

        }
        else if(data[0] == 0x2a) //¼���µ��û���Ϣ
        {

//            printf7("%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d\r\n",SCREEN[1].Username[0],SCREEN[1].Username[1],SCREEN[1].Username[2],SCREEN[1].Username[3],SCREEN[1].Username[4],SCREEN[1].Username[5],SCREEN[1].Username[6],SCREEN[1].Password[0],SCREEN[1].Password[1],SCREEN[1].Password[2],SCREEN[1].Password[3],SCREEN[1].Password[4],SCREEN[1].Username[5],SCREEN[1].Username[6]);

            if(++count == 4)
            {
                while(data[username_count] != 0xff)
                {
                    SCREEN[Receive_Start].Username[username_count-1] = data[username_count];
                    username_count++;
                }
                username_count++;
                while(data[username_count] != 0xfd)
                {
                    SCREEN[Receive_Start].Password[password_count-1] = data[username_count];
                    username_count++;
                    password_count++;
                }

                for(int8_t i = 0;i < Receive_Start;i++)
                {
                    if(strcmp((char *)SCREEN[i].Username,(char *)Sc->Username) < 0 || strcmp((char *)SCREEN[i].Username,(char *)Sc->Username) > 0)
                    {
                        PasswordInput_flag = 1;

                    }
                    else
                    {
                        PasswordInput_flag = 0;
                        PasswordInputfail_flag = 1;
                        break;
                    }
//
                }
//                printf7("%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d\r\n",SCREEN[1].Username[0],SCREEN[1].Username[1],SCREEN[1].Username[2],SCREEN[1].Username[3],SCREEN[1].Username[4],SCREEN[1].Username[5],SCREEN[1].Username[6],SCREEN[1].Password[0],SCREEN[1].Password[1],SCREEN[1].Password[2],SCREEN[1].Password[3],SCREEN[1].Password[4],SCREEN[1].Username[5],SCREEN[1].Username[6]);

                count = 0;
                Receive_Start++;
            }


        }
        else if(data[0] == 0x77) //�޸������û�������
        {
            if(++count == 4)
            {
                while(data[username_count] != 0xff)
                {
                    SCREEN[Receive_Start].Username[username_count-1] = data[username_count];
                    username_count++;
                }
                username_count++;
                while(data[username_count] != 0xfd)
                {
                    SCREEN[Receive_Start].Password[password_count-1] = data[username_count];
                    username_count++;
                    password_count++;
                }

                for(int8_t i = 0;i < Receive_Start;i++)
                {
                    if(strcmp((char *)SCREEN[i].Username,(char *)SCREEN[Receive_Start].Username) == 0)
                    {
                        PasswordChange_flag = 1;
                        memset(SCREEN[i].Password,0,sizeof SCREEN[i].Password);
                        memset(SCREEN[i].Username,0,sizeof SCREEN[i].Username);
                        Receive_Start++;
                        break;
                    }
                    else if(strcmp((char *)SCREEN[i].Username,(char *)SCREEN[Receive_Start].Username) > 0 || strcmp((char *)SCREEN[i].Username,(char *)SCREEN[Receive_Start].Username) < 0)
                    {
                        PasswordChangeFail_flag = 1;
                        memset(SCREEN[Receive_Start].Password,0,sizeof SCREEN[Receive_Start].Password);
                        memset(SCREEN[Receive_Start].Username,0,sizeof SCREEN[Receive_Start].Username);
                    }

                }
                count = 0;
            }


        }
        else if(data[0] == 0x0a && data[2] == 0xfe) //ԤԼ�Լ����򿪵Ĺ��ź�
        {
            if(++count == 3)
            {
                member_judge(data[1]); //��member�������1 0 ��ֵ
                count = 0;
            }

        }
        else if(data[0] == 0x1a && data[1] == 0xee && data[2] == 0xfe)//�����µĹ�Ž���ԤԼ��ͬʱ�ж���û�������˶���ͬ��Ž���ԤԼ
        {
            if(++count == 3)
            {
                for(int i = 0;i < 16;i++)
                {
                    if(member[i] == 1)
                        Book_Judge(i); //��ԤԼ�����ж�
                }
                count = 0;
            }

        }
        else if(data[0] == 0x1a && data[1] == 0xef && data[2] == 0xfe)//�򿪶�Ӧ�Ĺ��
        {
            if(++count == 3)
            {
                for(int i = 0;i < 16;i++)
                {
                    if(member[i] == 1)
                    {
                        locker_count++;//���������м�������
                        current_locker = i+1;//��¼��ǰ�򿪹��ӵĹ��
                        Used[i] = 1;//��¼��ǰ��¼�û�
                        open_locker[i] = 1;//��¼��ǰ�򿪹�ŵı�־��
                        Booking[i] = 0;//ԤԼ��ѡ���־������
                        member[i] = 0;
                        SCREEN[current_user].judge_count[i]++;//��ά���շ�����
                    }
                }
                for(int i = 0;i < 16;i++)
                {
                    if(SCREEN[current_user].judge_count[i] % 2 == 0 && SCREEN[current_user].judge_count[i] != 0) //����ͬ���Ӵ����Σ���Ĭ��Ϊ�Ѿ�ʹ�ò��ҹر�
                    {
                        Charge_flag++;
                        Used[i] = 0;
                        SCREEN[current_user].judge_count[i] = 0;
//                    printf7("erweima\r\n");
                        flag = 1;
                    }
                }
                Motor_Slove(locker_count);
                count = 0;
            }


//            printf7("%d%d%d%d\r\n",SCREEN[current_user].judge_count[0],SCREEN[current_user].judge_count[1],SCREEN[current_user].judge_count[2],SCREEN[current_user].judge_count[3]);
        }
        else if(data[0] == 0x1a && data[1] == 0xff && data[2] == 0xfe)//�رյ�ǰ�򿪵Ĺ���
        {
            AllMotor_Give(0,0,0,0);
        }
//        else if(data[0] == 0xdd && data[1] == 0xdd && data[2] == 0xdd && data[3] == 0xdf) //ԭ�н����ά���տ������жϴ�����Ϣ
//        {
//
//
//            Judge_flag = 1;
//        }
        else if(data[0] == 0xaa && data[2] == 0xfe)//�Թ��ӵĴ򿪽��з������
        {
            if(++count == 3)
            {
                switch (data[1])
                {
                    case 0x0a:
                        if(current_locker >= 1 && current_locker <= 4)
                            current_locker += 12;
                        else
                            current_locker -= 4;
                        Motor_Output(1,0,0,current_locker);
                        break;
                    case 0x1a:
                        if(current_locker >= 13 && current_locker <= 16)
                            current_locker -= 12;
                        else
                            current_locker += 4;
                        Motor_Output(1,0,0,current_locker);
                        break;
                    case 0x2a:
                        if(current_locker == 1 || current_locker == 5 || current_locker == 9 || current_locker == 13)
                            current_locker += 3;
                        else
                            current_locker -= 1;
                        Motor_Output(1,0,0,current_locker);
                        break;
                    case 0x3a:
                        if(current_locker == 4 || current_locker == 8 || current_locker == 12 || current_locker == 16)
                            current_locker -= 3;
                        else
                            current_locker += 1;
                        Motor_Output(1,0,0,current_locker);
                        break;
                    default:
                        break;
                }
                count = 0;
            }

        }

        Judge_flag = 1;

        if(data[0] == 0x04 && data[1] == 0xFF && data[2] == 0xFF && data[3] == 0xFF)
            Judge_flag = 0;

        memset(data,0,sizeof &data);
}

