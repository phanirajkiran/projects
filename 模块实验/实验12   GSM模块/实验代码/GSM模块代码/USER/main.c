#include "stm32f1xx_hal.h"
#include "stm32f1xx.h"
#include "timer.h"
#include "delay.h"
#include "Usart.h"
#include "Rs485.h"	
#include "GSM.h"

/**
************************************************************
************************************************************
************************************************************
*
*	作者： 		重庆八城科技
*
*	日期： 		2018-01-01
*
*	版本： 		V1.0
*
*	说明： 		GSM库函数操作实验-HAL库版本
*
*	修改记录：	
************************************************************
************************************************************
************************************************************
**/


int main(void)
{ 
  HAL_Init();             					//初始化HAL库  
	UART1_Init(115200);								//初始化串口1
	UART2_Init(9600);									//初始化串口2
	Rs485_Init();   									//初始化485
	TIM3_Init(1000-1,64-1);						//初始化定时器3
	GSM_Init();												//初始化GSM

	while(1)
	{
		USART1_IRQHand(); 							//接收485中的数据并发送到串口二中
	}
}





