//
// Created by 1 on 2023-12-03.
//
#include "ESP8266.h"

char ESPS[200] = {0};
int8_t back = 1;
float longit = 1.0f,latit = 1.0f;

const char* WIFI ="OnePlus 9";
const char* WIFIASSWORD="88888888";
const char* ClintID="public";
const char* username="admin";
const char* passwd="123456";
const char* Url="47.109.133.87";
const char* pubtopic="cattest";
const char* func1="Longitude";
//double Latitude = 104.123456;
const char* func2="Latitude";
const char* ntp = "ntp1.aliyun.com";

int8_t ESP_Init(void)
{
    memset(ESPS,0,sizeof ESPS);
    printf7("AT+RST\r\n");
    osDelay(2000);

    memset(ESPS,0,sizeof ESPS);
    printf7("AT+CWMODE=1\r\n");
    osDelay(1000);
    if(strcmp(ESPS,"OK") != 0)
        return 1;

    memset(ESPS,0,sizeof ESPS);
    printf("AT+CWJAP=\"%s\",\"%s\"\r\n",WIFI,WIFIASSWORD); //连接热点
    osDelay(2000);
    if(strcmp(ESPS,"OK") != 0)
        return 2;

    memset(ESPS,0,sizeof ESPS);
    printf("AT+MQTTUSERCFG=0,1,\"%s\",\"%s\",\"%s\",0,0,\"\"\r\n",ClintID,username,passwd);//用户信息配置
    osDelay(1000);
    if(strcmp(ESPS,"OK") != 0)
        return 3;

    while(back)
    {
        memset(ESPS,0,sizeof ESPS);
        printf("AT+MQTTCONN=0,\"%s\",1883,0\r\n",Url); //连接服务器
        osDelay(2000);
        if(strcmp(ESPS,"OK") != 0)
            back = 1;
        else
            back = 0;
    }

    return 0;
}

int8_t ESP_Send(void)
{
    memset(ESPS,0,sizeof ESPS);
    printf("AT+MQTTPUB=0,\"%s\",\"{\\\"%s\\\":\\\"%0.4f\\\"\\,\\\"%s\\\":\\\"%0.4f\\\"}\",0,0\r\n",pubtopic,func1,longit,func2,latit);
    osDelay(200);
    if(strcmp(ESPS,"OK") != 0)
        return 1;

    return 0;
}
