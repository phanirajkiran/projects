#include "stm32f1xx.h"
#include "delay.h"
#include "led.h"


/**
************************************************************
************************************************************
************************************************************
*
*	���ߣ� 		����˳ǿƼ�
*
*	���ڣ� 		2018-01-01
*
*	�汾�� 		V1.0
*
*	˵���� 		����ƿ⺯������ʵ��-HAL��汾
*
*	�޸ļ�¼��	
************************************************************
************************************************************
************************************************************
**/


int main(void)
{ 
    HAL_Init();             //��ʼ��HAL��    

    LED_Init();				//��ʼ��LED	

	while(1)
	{
        HAL_GPIO_WritePin(GPIOB,GPIO_PIN_0,GPIO_PIN_RESET); 	//LED1��Ӧ����PB0���ͣ�������ͬ��LED1(0)	
        delay_ms(1000);		
        HAL_GPIO_WritePin(GPIOB,GPIO_PIN_1,GPIO_PIN_RESET);   //LED2��Ӧ����PB1���ͣ�������ͬ��LED2(0)
        delay_ms(1000);			
        HAL_GPIO_WritePin(GPIOB,GPIO_PIN_13,GPIO_PIN_RESET); 	//LED3��Ӧ����PB13���ͣ�������ͬ��LED3(0)	
        delay_ms(1000);	    
        HAL_GPIO_WritePin(GPIOB,GPIO_PIN_14,GPIO_PIN_RESET);  //LED4��Ӧ����PB14���ͣ�������ͬ��LED04(0)	

        delay_ms(1000);											//��ʱ500ms

        HAL_GPIO_WritePin(GPIOB,GPIO_PIN_0,GPIO_PIN_SET); 	//LED1��Ӧ����PB0���ߣ��𣬵�ͬ��LED1(1)
        delay_ms(1000);			
        HAL_GPIO_WritePin(GPIOB,GPIO_PIN_1,GPIO_PIN_SET);   //LED2��Ӧ����PB1���ߣ��𣬵�ͬ��LED2(1)
        delay_ms(1000);	
        HAL_GPIO_WritePin(GPIOB,GPIO_PIN_13,GPIO_PIN_SET); 	//LED3��Ӧ����PB2���ߣ��𣬵�ͬ��LED3(1)
        delay_ms(1000);	
        HAL_GPIO_WritePin(GPIOB,GPIO_PIN_14,GPIO_PIN_SET);  //LED4��Ӧ����PB3���ߣ��𣬵�ͬ��LED4(1)
        delay_ms(1000); 
	 }
}

