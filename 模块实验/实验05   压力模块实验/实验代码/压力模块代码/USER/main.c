#include "Pressure_Sensor.h"	
#include "stm32f1xx_hal.h"
#include "stm32f1xx.h"
#include "delay.h"
#include "Usart.h"
#include "Rs485.h"	


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
*	说明： 		压力传感器库函数操作实验-HAL库版本
*
*	修改记录：	
************************************************************
************************************************************
************************************************************
**/


int main(void)
{ 
	int Weight_Shiwu = 0;							//存放获取到的重量信息
  HAL_Init();             					//初始化HAL库  
	UART1_Init(115200);								//初始化串口
	Rs485_Init();   									//初始化485
	Pressure_Sensor_Init();						//初始化压力传感器
	
	while(1)
	{
	  Weight_Shiwu = ReadCount();  		//接收重量数据
		
		Rs485_Config(1); 								//485发送模式
 		printf("pes->lcd%d\r\n",Weight_Shiwu);	//将数据发送到485总线中
		delay_ms(10);
		Rs485_Config(0); 								//485等待模式
		delay_ms(100);
	}
}




