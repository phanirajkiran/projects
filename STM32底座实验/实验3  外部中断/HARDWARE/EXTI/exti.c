#include "exti.h"
#include "delay.h"
#include "led.h"
#include "key.h"
#include "stm32f1xx.h"

unsigned char  led_flag = 0;  //LED��״̬��־

//==========================================================
//	�������ƣ�	EXTI_Init
//
//	�������ܣ�	�ⲿ�жϳ�ʼ��
//
//	��ڲ�����	��
//
//	���ز�����	��
//
//	˵����		
//==========================================================
void EXTI_Init(void)
{
    GPIO_InitTypeDef GPIO_Initure;
    
    __HAL_RCC_GPIOA_CLK_ENABLE();               //����GPIOAʱ��

    GPIO_Initure.Pin=GPIO_PIN_7; 				//PA7
    GPIO_Initure.Mode=GPIO_MODE_IT_FALLING;     //�½��ش���
    GPIO_Initure.Pull=GPIO_PULLUP;
    HAL_GPIO_Init(GPIOA,&GPIO_Initure);
    
    HAL_NVIC_SetPriority(EXTI9_5_IRQn,2,2);       //��ռ���ȼ�Ϊ2�������ȼ�Ϊ2
    HAL_NVIC_EnableIRQ(EXTI9_5_IRQn);             //ʹ���ж���

}

//==========================================================
//	�������ƣ�	EXTI9_5_IRQHandler
//
//	�������ܣ�	�жϷ�����
//
//	��ڲ�����	��
//
//	���ز�����	��
//
//	˵����		
//==========================================================
void EXTI9_5_IRQHandler(void)
{
    HAL_GPIO_EXTI_IRQHandler(GPIO_PIN_7);		//�����жϴ����ú���
}

//==========================================================
//	�������ƣ�	HAL_GPIO_EXTI_Callback
//
//	�������ܣ�	�жϷ������
//
//	��ڲ�����	GPIO_Pin:�ж����ź�
//
//	���ز�����	��
//
//	˵����		
//==========================================================
void HAL_GPIO_EXTI_Callback(uint16_t GPIO_Pin)
{
    delay_ms(100);    
    
    led_flag = !led_flag; //��־ȡ��
    
    
    if(led_flag)
    {
        HAL_GPIO_WritePin(GPIOB,GPIO_PIN_0,GPIO_PIN_RESET); 	//LED1��Ӧ����PB0���ͣ�������ͬ��LED1(0)	
    }
    else
    {
        HAL_GPIO_WritePin(GPIOB,GPIO_PIN_0,GPIO_PIN_SET); 	    //LED1��Ӧ����PB0���ߣ��𣬵�ͬ��LED1(1)		
    }
		
}
