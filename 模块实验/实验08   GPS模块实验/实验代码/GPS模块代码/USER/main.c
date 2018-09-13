#include "stm32f1xx_hal.h"
#include "stm32f1xx.h"
#include "delay.h"
#include "Usart.h"
#include "Rs485.h"	
#include "main.h"
#include "GPS.h"
#include "string.h"
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
*	˵���� 		GPS�⺯������ʵ��-HAL��汾
*
*	�޸ļ�¼��	
************************************************************
************************************************************
************************************************************
**/

GPS_MsgTypeDef GPS_GGA_Msg;
uint8_t GGA_MsgBuffer[200];
int main(void) 
{ 
  HAL_Init();             			//��ʼ��HAL��  
	Rs485_Init();   							//��ʼ��485
	UART1_Init(115200);						//��ʼ������1,��������������ͨ��
	UART2_Init(9600);							//��ʼ������2������GPS����
	
	while(1)
	{	
        if(GetGGA_Msg == 1)
        {//���յ�GGA����
           memcpy((void*)GGA_MsgBuffer,(const void*)USART2_RX_BUF,USART2_RX_STA);
            
            if(GPS_GGA_Analysis(&GPS_GGA_Msg,GGA_MsgBuffer))
            {
								delay_ms(10);
							
								Rs485_Config(1);
                printf("nsh->lcd%c\r\n",GPS_GGA_Msg.nshemi);			//�ϱ�γ	
                delay_ms(10);
                Rs485_Config(0);
							
								Rs485_Config(1);
                printf("ewh->lcd%c\r\n",GPS_GGA_Msg.ewhemi);			//������
                delay_ms(10);
                Rs485_Config(0);
							
                Rs485_Config(1);
								printf("lat->lcd%f\r\n",GPS_GGA_Msg.latitude);		//γ��  
                delay_ms(10);
                Rs485_Config(0);
							
							  Rs485_Config(1);
                printf("lon->lcd%f\r\n",GPS_GGA_Msg.longitude);		//����
                delay_ms(10);
                Rs485_Config(0);
							
            }
            
            __HAL_UART_ENABLE(&UART2_Handler);//�򿪴���2������2���ܵĹر���Usart.c->
            USART2_RX_STA = 0;
            GetGGA_Msg    = 0;								//���㣬׼���´ν���
        }
	}
}



