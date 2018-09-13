#include "led.h"
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
