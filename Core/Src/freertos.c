/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * File Name          : freertos.c
  * Description        : Code for freertos applications
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2023 STMicroelectronics.
  * All rights reserved.
  *
  * This software is licensed under terms that can be found in the LICENSE file
  * in the root directory of this software component.
  * If no LICENSE file comes with this software, it is provided AS-IS.
  *
  ******************************************************************************
  */
/* USER CODE END Header */

/* Includes ------------------------------------------------------------------*/
#include "FreeRTOS.h"
#include "task.h"
#include "main.h"
#include "cmsis_os.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */

/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN PTD */

/* USER CODE END PTD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */

/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */
int Charge_count = 0;
extern int feed;
/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/
/* USER CODE BEGIN Variables */

/* USER CODE END Variables */
osThreadId StartDebugHandle;
osThreadId PID_OutputTaskHandle;
osThreadId KeyTaskHandle;
osThreadId WhileHandle;
osThreadId PrintfHandle;
osThreadId BlueTeethHandle;

/* Private function prototypes -----------------------------------------------*/
/* USER CODE BEGIN FunctionPrototypes */

/* USER CODE END FunctionPrototypes */

void StartDebugTask(void const * argument);
void PID_Output(void const * argument);
void Key(void const * argument);
void WhileTask(void const * argument);
void PrintfTask(void const * argument);
void BlueTeethTask(void const * argument);

void MX_FREERTOS_Init(void); /* (MISRA C 2004 rule 8.1) */

/* GetIdleTaskMemory prototype (linked to static allocation support) */
void vApplicationGetIdleTaskMemory( StaticTask_t **ppxIdleTaskTCBBuffer, StackType_t **ppxIdleTaskStackBuffer, uint32_t *pulIdleTaskStackSize );

/* USER CODE BEGIN GET_IDLE_TASK_MEMORY */
static StaticTask_t xIdleTaskTCBBuffer;
static StackType_t xIdleStack[configMINIMAL_STACK_SIZE];

void vApplicationGetIdleTaskMemory( StaticTask_t **ppxIdleTaskTCBBuffer, StackType_t **ppxIdleTaskStackBuffer, uint32_t *pulIdleTaskStackSize )
{
  *ppxIdleTaskTCBBuffer = &xIdleTaskTCBBuffer;
  *ppxIdleTaskStackBuffer = &xIdleStack[0];
  *pulIdleTaskStackSize = configMINIMAL_STACK_SIZE;
  /* place for user code */
}
/* USER CODE END GET_IDLE_TASK_MEMORY */

/**
  * @brief  FreeRTOS initialization
  * @param  None
  * @retval None
  */
void MX_FREERTOS_Init(void) {
  /* USER CODE BEGIN Init */

  /* USER CODE END Init */

  /* USER CODE BEGIN RTOS_MUTEX */
  /* add mutexes, ... */
  /* USER CODE END RTOS_MUTEX */

  /* USER CODE BEGIN RTOS_SEMAPHORES */
  /* add semaphores, ... */
  /* USER CODE END RTOS_SEMAPHORES */

  /* USER CODE BEGIN RTOS_TIMERS */
  /* start timers, add new ones, ... */
  /* USER CODE END RTOS_TIMERS */

  /* USER CODE BEGIN RTOS_QUEUES */
  /* add queues, ... */
  /* USER CODE END RTOS_QUEUES */

  /* Create the thread(s) */
  /* definition and creation of StartDebug */
  osThreadDef(StartDebug, StartDebugTask, osPriorityLow, 0, 128);
  StartDebugHandle = osThreadCreate(osThread(StartDebug), NULL);

  /* definition and creation of PID_OutputTask */
  osThreadDef(PID_OutputTask, PID_Output, osPriorityNormal, 0, 256);
  PID_OutputTaskHandle = osThreadCreate(osThread(PID_OutputTask), NULL);

  /* definition and creation of KeyTask */
  osThreadDef(KeyTask, Key, osPriorityNormal, 0, 256);
  KeyTaskHandle = osThreadCreate(osThread(KeyTask), NULL);

  /* definition and creation of While */
  osThreadDef(While, WhileTask, osPriorityAboveNormal, 0, 256);
  WhileHandle = osThreadCreate(osThread(While), NULL);

  /* definition and creation of Printf */
  osThreadDef(Printf, PrintfTask, osPriorityIdle, 0, 256);
  PrintfHandle = osThreadCreate(osThread(Printf), NULL);

  /* definition and creation of BlueTeeth */
  osThreadDef(BlueTeeth, BlueTeethTask, osPriorityNormal, 0, 256);
  BlueTeethHandle = osThreadCreate(osThread(BlueTeeth), NULL);

  /* USER CODE BEGIN RTOS_THREADS */
  /* add threads, ... */
    vTaskResume(StartDebugHandle);
    vTaskSuspend(PID_OutputTaskHandle);
    vTaskSuspend(PrintfHandle);
    vTaskSuspend(KeyTaskHandle);
    vTaskSuspend(WhileHandle);
    vTaskSuspend(BlueTeethHandle);
  /* USER CODE END RTOS_THREADS */

}

/* USER CODE BEGIN Header_StartDebugTask */
/**
  * @brief  Function implementing the StartDebug thread.
  * @param  argument: Not used
  * @retval None
  */
/* USER CODE END Header_StartDebugTask */
void StartDebugTask(void const * argument)
{
  /* USER CODE BEGIN StartDebugTask */
    Mymain_Init();

    vTaskResume(PID_OutputTaskHandle);
    vTaskResume(PrintfHandle);
    vTaskResume(WhileHandle);
    vTaskResume(KeyTaskHandle);
    vTaskResume(BlueTeethHandle);
    
    BUZZER_OFF;

//    printf7("1 free\n");
  /* Infinite loop */
  for(;;)
  {
      LED1_Flash;
      LED2_Flash;
      WaterLED();
//      printf3("%d,%d,%d,%d,%d,%d,%d\r\n",SCREEN[1].Username[0],SCREEN[1].Username[1],SCREEN[1].Username[2],SCREEN[1].Username[3],SCREEN[1].Username[4],SCREEN[1].Username[5],SCREEN[1].Username[6]);
//      osDelay(10);
//      printf3("%d,%d,%d,%d,%d,%d,%d\r\n",SCREEN[2].Username[0],SCREEN[2].Username[1],SCREEN[2].Username[2],SCREEN[2].Username[3],SCREEN[2].Username[4],SCREEN[2].Username[5],SCREEN[2].Username[6]);

//      printf7("1\r\n");
      osDelay(70);
  }
  /* USER CODE END StartDebugTask */
}

/* USER CODE BEGIN Header_PID_Output */
/**
* @brief Function implementing the PID_OutputTask thread.
* @param argument: Not used
* @retval None
*/
/* USER CODE END Header_PID_Output */
void PID_Output(void const * argument)
{
  /* USER CODE BEGIN PID_Output */
    int16_t Speed1,Speed2,Speed3,Speed4;
    int16_t Speed1_OUT,Speed2_OUT,Speed3_OUT,Speed4_OUT;

    //数组0-3对应电机id1-4
    PID_Change(&MOTOR2006_S[0],&MOTOR2006_P[0],5.5f,0.05f,0.0f,0.45f,1.5f);
    PID_Change(&MOTOR2006_S[1],&MOTOR2006_P[1],5.5f,0.05f,0.0f,0.45f,1.5f);
    PID_Change(&MOTOR2006_S[2],&MOTOR2006_P[2],5.5f,0.05f,0.0f,0.45f,1.5f);
    PID_Change(&MOTOR2006_S[3],&MOTOR2006_P[3],5.5f,0.05f,0.0f,0.45f,1.5f);

    //记录电机应该对开的正向电机角度正负
    /*
     *   如下图机构所示：
     *   上层：
     *      * * * *
     *      * * * *
     *   <- * * * *  ->
     *      * * * *
     *    id2       id1
     *
     *    下层：
     *          ^
     *          |
     *      * * * *  id4
     *      * * * *
     *      * * * *
     *      * * * *
     *              id3
     *           |
     *           \/
     *
     *
     */

//    AllMotor_Give(0,0,0,10);
  /* Infinite loop */
  for(;;)
  {
//      AllMotor_Give(OneLocker_Angle,2 * OneLocker_Angle,(float)(-OneLocker_Angle + OneLocker_Angle * (3 - 1)),-2 * OneLocker_Angle);

      Speed1 = (int16_t) PID_realise(&MOTOR2006_P[0],Angle_Output[0],motor_info[0].total_angle,M2006_CURRENT_MAX);
      Speed2 = (int16_t) PID_realise(&MOTOR2006_P[1],Angle_Output[1],motor_info[1].total_angle,M2006_CURRENT_MAX);
      Speed3 = (int16_t) PID_realise(&MOTOR2006_P[2],Angle_Output[2],motor_info[2].total_angle,M2006_CURRENT_MAX);
      Speed4 = (int16_t) PID_realise(&MOTOR2006_P[3],Angle_Output[3],motor_info[3].total_angle,M2006_CURRENT_MAX);

//      usart_printf("%f,%d,%f,%d\n",Angle_Output[0],motor_info[0].total_angle,Angle_Output[1],motor_info[0].total_angle);
      Speed1 = Output_Limit(Speed1);
      Speed2 = Output_Limit(Speed2);
      Speed3 = Output_Limit(Speed3);
      Speed4 = Output_Limit(Speed4);
//      printf3("1\n");
      Speed1_OUT = (int16_t) PID_realise(&MOTOR2006_S[0],Speed1,motor_info[0].speed,M2006_CURRENT_MAX);
      Speed2_OUT = (int16_t) PID_realise(&MOTOR2006_S[1],Speed2,motor_info[1].speed,M2006_CURRENT_MAX);
      Speed3_OUT = (int16_t) PID_realise(&MOTOR2006_S[2],Speed3,motor_info[2].speed,M2006_CURRENT_MAX);
      Speed4_OUT = (int16_t) PID_realise(&MOTOR2006_S[3],Speed4,motor_info[3].speed,M2006_CURRENT_MAX);

      set_current(&hcan1,0x200,Speed1_OUT,Speed2_OUT,Speed3_OUT,Speed4_OUT);

    osDelay(5);
  }
  /* USER CODE END PID_Output */
}

/* USER CODE BEGIN Header_Key */
/**
* @brief Function implementing the KeyTask thread.
* @param argument: Not used
* @retval None
*/
/* USER CODE END Header_Key */
void Key(void const * argument)
{
  /* USER CODE BEGIN Key */
  /* Infinite loop */
  for(;;)
  {
      Key_Scan();
    osDelay(1);
  }
  /* USER CODE END Key */
}

/* USER CODE BEGIN Header_WhileTask */
/**
* @brief Function implementing the While thread.
* @param argument: Not used
* @retval None
*/
/* USER CODE END Header_WhileTask */
void WhileTask(void const * argument)
{
  /* USER CODE BEGIN WhileTask */
  /* Infinite loop */
  for(;;)
  {
      if(init_flag == 1)
          UR_Init();

    osDelay(0);
  }
  /* USER CODE END WhileTask */
}

/* USER CODE BEGIN Header_PrintfTask */
/**
* @brief Function implementing the Printf thread.
* @param argument: Not used
* @retval None
*/
/* USER CODE END Header_PrintfTask */
void PrintfTask(void const * argument)
{
  /* USER CODE BEGIN PrintfTask */
  /* Infinite loop */
  for(;;)
  {
      Printf_Judge();
    osDelay(80);
  }
  /* USER CODE END PrintfTask */
}

/* USER CODE BEGIN Header_BlueTeethTask */
/**
* @brief Function implementing the BlueTeeth thread.
* @param argument: Not used
* @retval None
*/
/* USER CODE END Header_BlueTeethTask */
void BlueTeethTask(void const * argument)
{
  /* USER CODE BEGIN BlueTeethTask */

  /* Infinite loop */
  for(;;)
  {
      Blue_Judge();
      esp8266_send();
    osDelay(5000);
  }
  /* USER CODE END BlueTeethTask */
}

/* Private application code --------------------------------------------------*/
/* USER CODE BEGIN Application */

/* USER CODE END Application */
