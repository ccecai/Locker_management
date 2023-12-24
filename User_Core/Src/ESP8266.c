//
// Created by 1 on 2023-12-03.
//
#include "ESP8266.h"

uint8_t ESPS[200] = {0};
int8_t back = 1,cmd = 0;
char str_esp[16][30] = {0};
char final_str[200] = {0};

const char* WIFI ="ssid";
const char* WIFIASSWORD="password";
const char* ClintID="65794b9f585c81787ad6f4c5_stm32_esp_0_0_2023121306";
const char* username="65794b9f585c81787ad6f4c5_stm32_esp";
const char* passwd="c426b1b23f34a506f803b261cf80555e51817e9fe8ab65a7657cb448c9f48b8e";
const char* Url="1186471610.st1.iotda-device.cn-north-4.myhuaweicloud.com";
//设备上报数据
const char* pubtopic="$oc/devices/65794b9f585c81787ad6f4c5_stm32_esp/sys/properties/report";
//订阅主题: 平台下发消息给设备
const char* subtopic="$oc/devices/65794b9f585c81787ad6f4c5_stm32_esp/sys/properties/report";
//const char* subtopic="$oc/devices/65794b9f585c81787ad6f4c5_stm32_esp/sys/messages/down";
const char* func1="stm32_to_yun_cmd";
// 上报的属性消息 (一次可以上报多个属性,在json里增加就行了)
// {"services": [{"service_id": "stm32","properties":{"stm32_to_yun_cmd":50}}]}

int8_t ESP_Init(void)
{
    memset(ESPS,0,sizeof ESPS);
    printf7("AT+RST\r\n");
    osDelay(2000);
    printf3("RST OK\r\n");

    memset(ESPS,0,sizeof ESPS);
    printf7("ATE0\r\n");
    osDelay(1000);
    if(strcmp(ESPS,"OK") != 0)
        return 1;
    printf3("ATE0 OK\r\n");

    memset(ESPS,0,sizeof ESPS);
    printf7("AT+CWMODE=1\r\n");
    osDelay(1000);
    if(strcmp(ESPS,"OK") != 0)
        return 2;
    printf3("STA OK\r\n");

    memset(ESPS,0,sizeof ESPS);
    printf7("AT+CWJAP=\"%s\",\"%s\"\r\n",WIFI,WIFIASSWORD); //连接热点
    osDelay(2000);
    if(strcmp(ESPS,"OK") != 0)
        return 3;
    printf3("CWJAP OK\r\n");

    memset(ESPS,0,sizeof ESPS);
    printf7("AT+MQTTUSERCFG=0,1,\"%s\",\"%s\",\"%s\",0,0,\"\"\r\n",ClintID,username,passwd);//用户信息配置
    osDelay(1000);
    if(strcmp(ESPS,"OK") != 0)
        return 4;
    printf3("MQTTUSER OK\r\n");

    memset(ESPS,0,sizeof ESPS);
    printf7("AT+MQTTCONN=0,\"%s\",1883,1\r\n",Url);//连接服务器
    osDelay(1000);
    printf3("MQTTCONN OK\r\n");

    memset(ESPS,0,sizeof ESPS);
    printf7("AT+MQTTSUB=0,\"%s\",1\r\n",subtopic);//订阅消息
    osDelay(1000);
    if(strcmp(ESPS,"OK") != 0)
        return 5;
    printf3("MQTTSUB OK\r\n");

    return 0;
}

int8_t ESP_Send(void)
{
    memset(ESPS,0,sizeof ESPS);
    printf7("AT+MQTTPUB=0,\"%s\",\"{\\\"services\\\":[{\\\"service_id\\\":\\\"stm32\\\"\\,\\\"properties\\\":{\\\"%s\\\":%d}}]}\",0,0\r\n",pubtopic,func1,cmd);
    osDelay(200);
    if(strcmp(ESPS,"OK") != 0)
        return 1;

    return 0;
}

void esp8266_send(void)
{
    for(int i = 0;i < 16;i++)
    {
        if(Booking[i] == 1 && i+1 >= 10)
            sprintf(str_esp[i],"%d booked",i+1);
        else if(Used[i] == 1 && i+1 >= 10)
            sprintf(str_esp[i],"%d used",i+1);
        else if(Used[i] == 0 && i+1 >= 10)
            sprintf(str_esp[i],"%d free",i+1);
        else if(Booking[i] == 1 && i+1 < 10)
            sprintf(str_esp[i],"0%d booked",i+1);
        else if(Used[i] == 1 && i+1 < 10)
            sprintf(str_esp[i],"0%d used",i+1);
        else if(Used[i] == 0 && i+1 < 10)
            sprintf(str_esp[i],"0%d free",i+1);
    }
    sprintf(final_str,"%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s",str_esp[0],str_esp[1],str_esp[2],str_esp[3],str_esp[4],str_esp[5],str_esp[6],str_esp[7],str_esp[8],str_esp[9],str_esp[10],str_esp[11],str_esp[12],str_esp[13],str_esp[14],str_esp[15]);
    printf7("%s",final_str);
}

void Esp_Judge(void)
{
    int number = 0;

    number = (ESPS[0] - 48) * 10 + ESPS[1] - 48;

    if(ESPS[0] == 'a')
        Motor_Slove(locker_count);

    if(ESPS[2] == 111 && ESPS[3] == 110)
    {
        locker_count++;//用来计数有几个柜子
        current_locker = number;//记录当前打开柜子的柜号
        Used[number - 1] = 1;//记录当前登录用户
        open_locker[number - 1] = 1;//记录当前打开柜号的标志量
        Booking[number - 1] = 0;//预约与选择标志量清零
        member[number - 1] = 0;
        SCREEN[current_user].judge_count[number - 1]++;//二维码收费所用
        printf3("%d\r\n",number);
//        Motor_Output(1,0,0,number);
    }
    else if(ESPS[2] == 111 && ESPS[3] == 102)
    {
//        AllMotor_Give(current_angle[0] + ((current_angle[1] - current_angle[0]) / 2),current_angle[1] - ((current_angle[1] - current_angle[0]) / 2),current_angle[2] - ((current_angle[2] - current_angle[3]) / 2),current_angle[3] + ((current_angle[2] - current_angle[3]) / 2));
//        osDelay(5000);
        AllMotor_Give(0,0,0,0);
    }

    memset(&ESPS,0,sizeof ESPS);
}