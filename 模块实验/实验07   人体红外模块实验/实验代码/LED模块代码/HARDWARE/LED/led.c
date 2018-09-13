#include "led.h"
#include "delay.h"
#include "stm32f1xx.h"

//==========================================================
//	�������ƣ�	LED_Init
//
//	�������ܣ�	LED�Ƴ�ʼ��
//
//	��ڲ�����	��
//
//	���ز�����	��
//
//	˵����		
//==========================================================

uint8_t number0 = 1;  //��ʼ��

void LED_Init(void)
{
	
    GPIO_InitTypeDef GPIO_Initure;

    __HAL_RCC_GPIOB_CLK_ENABLE();           	//����GPIOBʱ��
	
    GPIO_Initure.Pin=GPIO_PIN_0|GPIO_PIN_1|GPIO_PIN_13|GPIO_PIN_14; 	//PB0,PB1,PB13,PB14
    GPIO_Initure.Mode=GPIO_MODE_OUTPUT_PP;  	//�������
    GPIO_Initure.Pull=GPIO_PULLUP;          	//����
    GPIO_Initure.Speed=GPIO_SPEED_HIGH;    	 	//����
    HAL_GPIO_Init(GPIOB,&GPIO_Initure);
	
    HAL_GPIO_WritePin(GPIOB,GPIO_PIN_0|GPIO_PIN_1|GPIO_PIN_13|GPIO_PIN_14,GPIO_PIN_SET);	//PB0,PB1,PB13,PB14��1��Ĭ�ϳ�ʼ�������

}

//==========================================================
//	�������ƣ�	LED_Config
//
//	�������ܣ�	LED����
//
//	��ڲ�����	��
//
//	���ز�����	��
//
//	˵����		
//==========================================================
void LED_Config(uint32_t num)
{
	switch(num)
		{
			case 1:
			{
				//��תLED1״̬
				HAL_GPIO_TogglePin(LED_GPIO_PORT,LED1_GPIO_PIN);
				delay_ms(200); 
				HAL_GPIO_TogglePin(LED_GPIO_PORT,LED1_GPIO_PIN);  		
				break;
			}				
			case 2:
			{
				//��תLED2״̬
				HAL_GPIO_TogglePin(LED_GPIO_PORT,LED1_GPIO_PIN);
				HAL_GPIO_TogglePin(LED_GPIO_PORT,LED2_GPIO_PIN);
				delay_ms(200); 
				HAL_GPIO_TogglePin(LED_GPIO_PORT,LED1_GPIO_PIN);  
				HAL_GPIO_TogglePin(LED_GPIO_PORT,LED2_GPIO_PIN);  
				delay_ms(200); 				
				break;
			}	
			case 3:
			{
				//��תLED3״̬
				HAL_GPIO_TogglePin(LED_GPIO_PORT,LED1_GPIO_PIN);
				HAL_GPIO_TogglePin(LED_GPIO_PORT,LED2_GPIO_PIN);
				HAL_GPIO_TogglePin(LED_GPIO_PORT,LED3_GPIO_PIN);
				delay_ms(200); 
				HAL_GPIO_TogglePin(LED_GPIO_PORT,LED1_GPIO_PIN);  
				HAL_GPIO_TogglePin(LED_GPIO_PORT,LED2_GPIO_PIN); 
				HAL_GPIO_TogglePin(LED_GPIO_PORT,LED3_GPIO_PIN);   				
				delay_ms(200); 	
				
				break;
			}		
			case 4: 
			{
				//��תLED4״̬
				HAL_GPIO_TogglePin(LED_GPIO_PORT,LED1_GPIO_PIN);
				HAL_GPIO_TogglePin(LED_GPIO_PORT,LED2_GPIO_PIN);
				HAL_GPIO_TogglePin(LED_GPIO_PORT,LED3_GPIO_PIN);
				HAL_GPIO_TogglePin(LED_GPIO_PORT,LED4_GPIO_PIN);
				delay_ms(200); 
				HAL_GPIO_TogglePin(LED_GPIO_PORT,LED1_GPIO_PIN);  
				HAL_GPIO_TogglePin(LED_GPIO_PORT,LED2_GPIO_PIN); 
				HAL_GPIO_TogglePin(LED_GPIO_PORT,LED3_GPIO_PIN);  
				HAL_GPIO_TogglePin(LED_GPIO_PORT,LED4_GPIO_PIN);  				
				delay_ms(200); 
				  
				break;
			}	
			
			default: break;
		}
}

