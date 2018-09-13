#include "stm32f1xx.h"
#include "delay.h"
#include "led.h"
#include "rs485.h"
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
    UART1_Init(115200);
    Rs485_Init();
    Rs485_Config(0);
    
	while(1)
	{
        if(GetMsg == 1)
        {
            if(strstr((const char*)USART1_RX_BUF,(const char*)"led3,on"))
            {
                HAL_GPIO_WritePin(GPIOB,GPIO_PIN_13,GPIO_PIN_RESET); 	//LED1��Ӧ����PB0ȡ������/��	            
            } 
            if(strstr((const char*)USART1_RX_BUF,(const char*)"led3,off"))
            {
                HAL_GPIO_WritePin(GPIOB,GPIO_PIN_13,GPIO_PIN_SET); 	//LED1��Ӧ����PB0ȡ������/��	            
            } 
            if(strstr((const char*)USART1_RX_BUF,(const char*)"led2,on"))
            {
                HAL_GPIO_WritePin(GPIOB,GPIO_PIN_1,GPIO_PIN_RESET); 	//LED1��Ӧ����PB0ȡ������/��	            
            }             
            GetMsg        = 0;
            USART1_RX_STA = 0;
        }
	 }
}

