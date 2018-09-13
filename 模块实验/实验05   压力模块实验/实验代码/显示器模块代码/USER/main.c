#include "stm32f1xx_hal.h"
#include "stm32f1xx.h"
#include "delay.h"
#include "usart.h"
#include "Rs485.h"	
#include "TFT.h"

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
*	说明： 		TFT操作实验-HAL库版本
*
*	修改记录：	
************************************************************

************************************************************
************************************************************
**/
	
int main(void)
{ 
    HAL_Init();             				//初始化HAL库
		TFT_Init();             				//TFT显示器端口初始化
		Rs485_Init();										//初始化485
    UART1_Init(115200);							//初始化串口
		Lcd_Init();											//初始化LCD
	
    LCD_Clear(GRAYBLUE); 						//清屏
		POINT_COLOR = WHITE;						//画笔颜色
		BACK_COLOR = GRAYBLUE;
	
		LCD_ShowString(20,50,weight); 	//重量
		LCD_ShowNum(75,50,0,4);					//重量数据（初始化为0 在485数据处理函数中更新）
		LCD_ShowString(120,50,Company);	//重量单位
	
		while(1)
		{
			USART1_IRQHand(); 						//串口一485数据处理函数	
		}
}

