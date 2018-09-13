#include "stm32f1xx.h"
#include "delay.h"
#include "led.h"
#include "key.h"
#include "exti.h"
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
*	说明： 		外部中断函数操作实验-HAL库版本
*
*	修改记录：	
************************************************************
************************************************************
************************************************************
**/

int main(void)
{ 
    HAL_Init();             //初始化HAL库    
    LED_Init();				//初始化LED	
    KEY_Init();				//初始化按键
    EXTI_Init();			//初始化外部中断

	while(1)
	{
		HAL_GPIO_WritePin(GPIOB,GPIO_PIN_14,GPIO_PIN_RESET); 	//LED4对应引脚PB0拉低，亮，等同于LED1(0)	
		delay_ms(500);		

		HAL_GPIO_WritePin(GPIOB,GPIO_PIN_14,GPIO_PIN_SET); 	//LED4对应引脚PB0拉高，灭，等同于LED1(1)		

		delay_ms(500);		
        
  }
}
