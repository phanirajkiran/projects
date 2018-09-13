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
uint8_t tets[17] = "www.stepiot.com\r\n";

uint8_t Message[22] = "The Message you sent :";

uint8_t Enter[2] = "\r\n";

int main(void)
{
	unsigned char len = 0;
    
    HAL_Init();             //��ʼ��HAL��

    LED_Init();				//��ʼ��LED
    KEY_Init();				//��ʼ������
    UART2_Init(9600);		//��ʼ������
    delay_ms(200);	

	while(1)
	{

		if(KEY_Scan())  //���ⰴ�����£����ʹ�������
		{
            while(1)
            {
                if(S1&S2&S3&S4) break;  //�ȴ������ſ�
            }
             HAL_UART_Transmit(&UART2_Handler,tets,17,1000);	                //���ͽ��յ�������
                while(__HAL_UART_GET_FLAG(&UART2_Handler,UART_FLAG_TC)!=SET);	//�ȴ����ͽ���
        }
         if(USART2_RX_STA&0x8000)
		{					   
			len=USART2_RX_STA&0x3fff;//�õ��˴ν��յ������ݳ���
            
			HAL_UART_Transmit(&UART2_Handler,Message,22,1000);
            
			HAL_UART_Transmit(&UART2_Handler,(uint8_t*)USART2_RX_BUF,len,1000);	//���ͽ��յ�������
            
			while(__HAL_UART_GET_FLAG(&UART2_Handler,UART_FLAG_TC)!=SET);		//�ȴ����ͽ���
            
			HAL_UART_Transmit(&UART2_Handler,Enter,2,1000);//���뻻��
            
			USART2_RX_STA=0;
		}

	 }
}

