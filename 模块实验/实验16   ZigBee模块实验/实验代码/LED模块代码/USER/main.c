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
            if(strstr((const char*)USART1_RX_BUF,(const char*)"led1,toggle"))
            {
                HAL_GPIO_TogglePin(GPIOB,GPIO_PIN_0); 	//LED1��Ӧ����PB0ȡ������/��	            
            }
            else if(strstr((const char*)USART1_RX_BUF,(const char*)"led2,toggle"))
            {	
                HAL_GPIO_TogglePin(GPIOB,GPIO_PIN_1);   //LED2��Ӧ����PB1ȡ������/��	           
            }
            else if(strstr((const char*)USART1_RX_BUF,(const char*)"led3,toggle"))
            {	
                HAL_GPIO_TogglePin(GPIOB,GPIO_PIN_13); 	//LED3��Ӧ����PB13ȡ������/��           
            }
            else if(strstr((const char*)USART1_RX_BUF,(const char*)"led4,toggle"))
            {
                 HAL_GPIO_TogglePin(GPIOB,GPIO_PIN_14);  //LED4��Ӧ����PB14ȡ������/��             
            }            
            GetMsg        = 0;
            USART1_RX_STA = 0;
        }
	 }
}

