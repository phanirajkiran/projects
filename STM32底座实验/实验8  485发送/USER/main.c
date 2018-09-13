#include "stm32f1xx.h"
#include "delay.h"
#include "led.h"
#include "key.h"
#include "usart.h"	

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

uint8_t Message[21] = "This is 485 Message\r\n";

int main(void)
{
    
    HAL_Init();             //��ʼ��HAL��

    LED_Init();				//��ʼ��LED
    IO_Init();
    KEY_Init();				//��ʼ������
    UART2_Init(9600);		//��ʼ������
    UART1_Init(115200);		//��ʼ������
    delay_ms(200);	
    
    HAL_GPIO_WritePin(GPIOA,GPIO_PIN_8,GPIO_PIN_SET);	//PA8����
    HAL_GPIO_WritePin(GPIOA,GPIO_PIN_8,GPIO_PIN_RESET);	//PA8����

	while(1)
	{
              
            HAL_GPIO_WritePin(GPIOA,GPIO_PIN_8,GPIO_PIN_SET);	//PA8����  ʹ��485����
            delay_ms(10);
            
            HAL_UART_Transmit(&UART1_Handler,Message,21,1000);	//���ͽ��յ�������
            
            delay_ms(10);
            
            HAL_GPIO_WritePin(GPIOA,GPIO_PIN_8,GPIO_PIN_RESET);	//PA8����   ʹ��485���ڽ���״̫
              
            delay_ms(1000);

	 }
}

