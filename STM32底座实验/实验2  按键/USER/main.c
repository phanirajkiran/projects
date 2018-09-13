#include "stm32f1xx.h"
#include "delay.h"
#include "led.h"
#include "key.h"


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
*	˵���� 		������������ʵ��-HAL��汾
*
*	�޸ļ�¼��	
************************************************************
************************************************************
************************************************************
**/


int main(void)
{ 
	unsigned char key = 0;
    
    HAL_Init();             //��ʼ��HAL��    

    LED_Init();				//��ʼ��LED	
    KEY_Init();				//��ʼ������

	while(1)
	{
		
		key = KEY_Scan();  //����ֵ��ȡ
		
		switch(key)
		{
			case 1:HAL_GPIO_WritePin(GPIOB,GPIO_PIN_0,GPIO_PIN_RESET); break;  //LED1��Ӧ����PB0���ͣ���
			case 2:HAL_GPIO_WritePin(GPIOB,GPIO_PIN_0,GPIO_PIN_SET);  break;   //LED1��Ӧ����PB0���ߣ���
			case 3:
				{
					HAL_GPIO_WritePin(GPIOB,GPIO_PIN_0,GPIO_PIN_RESET); 	//LED1��Ӧ����PB0���ͣ���
					delay_ms(200);		
					HAL_GPIO_WritePin(GPIOB,GPIO_PIN_1,GPIO_PIN_RESET);     //LED2��Ӧ����PB1���ͣ���
					delay_ms(200);			
					HAL_GPIO_WritePin(GPIOB,GPIO_PIN_13,GPIO_PIN_RESET); 	//LED3��Ӧ����PB13���ͣ���
					delay_ms(200);	    
					HAL_GPIO_WritePin(GPIOB,GPIO_PIN_14,GPIO_PIN_RESET);    //LED4��Ӧ����PB14���ͣ���
				}
				break;
			case 4:
				{
					HAL_GPIO_WritePin(GPIOB,GPIO_PIN_0,GPIO_PIN_SET); 	//LED1��Ӧ����PB0���ߣ���	
					HAL_GPIO_WritePin(GPIOB,GPIO_PIN_1,GPIO_PIN_SET);   //LED2��Ӧ����PB1���ߣ���
					HAL_GPIO_WritePin(GPIOB,GPIO_PIN_13,GPIO_PIN_SET); 	//LED3��Ӧ����PB2���ߣ���
					HAL_GPIO_WritePin(GPIOB,GPIO_PIN_14,GPIO_PIN_SET);  //LED4��Ӧ����PB3���ߣ���
				}
				break;
			default :
				break;
		}

	 }
}

