#include "stm32f1xx_hal.h"
#include "stm32f1xx.h"
#include "delay.h"
#include "Usart.h"
#include "Rs485.h"	
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
	uint8_t fag = 0;  								//��������
	
  HAL_Init();             					//��ʼ��HAL��  
	UART1_Init(115200);								//��ʼ������
	Rs485_Init();   									//��ʼ��485
  LED_Init();												//��ʼ��LED	

	while(1)
	{
		fag = USART1_IRQHand(); 				//�ȴ������������� ����һ����־λ
		
		if(fag == 1)
		{
			/*		������ȷ		*/
			LED_Config();  								//��ˮ��
		}
		if(fag == 2)
		{
			/*		�������		*/
			HAL_GPIO_WritePin(LED_GPIO_PORT,LED1_GPIO_PIN|LED2_GPIO_PIN|LED3_GPIO_PIN|LED4_GPIO_PIN,GPIO_PIN_SET);
			delay_ms(500);
			HAL_GPIO_WritePin(LED_GPIO_PORT,LED1_GPIO_PIN|LED2_GPIO_PIN|LED3_GPIO_PIN|LED4_GPIO_PIN,GPIO_PIN_RESET); 
			delay_ms(500);
		}  
	}
}

