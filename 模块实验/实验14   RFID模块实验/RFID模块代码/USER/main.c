#include "stm32f1xx.h"
#include "delay.h"
#include "led.h"
#include "key.h"
#include "usart.h"	
#include "RC522.h"
#include "Rs485.h"	
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
*	˵���� 		������������ʵ��-HAL��汾
*
*	�޸ļ�¼��	
************************************************************
************************************************************
************************************************************
**/
uint8_t DataToIC_Card[16]={1,2,3,5,6,7,8,9,0,1,2,3,4,5,6};//����д��IC������Ϣ
uint8_t index;    
uint8_t kv;
uint8_t count = 0;
uint8_t SendBuf[16];
int main(void)
{
    uint8_t i;
    HAL_Init();             //��ʼ��HAL��

    Rs485_Init();
    UART1_Init(115200);		//��ʼ������
    UART2_Init(9600);		//��ʼ������
    
    RC522_Init ();     //RC522ģ���ʼ��
    
    delay_ms(200);	

    
    Rs485_Config(0);
	while(1)
	{
        IC_Card_Search();//IC�����
        
        if(GetKeyMsg)
        {
            GetKeyMsg = 0;
                   kv = GetTheKey(USART1_RX_BUF);
            switch(kv)
            {
                case KEY_0:
                case KEY_1:
                case KEY_2:
                case KEY_3:
                case KEY_4:
                case KEY_5:
                case KEY_6:   
                case KEY_7:   
                case KEY_8:   
                case KEY_9: 
                     if(index <= 15)//������д��16���ֽ�
                     {
                        DataToIC_Card[index++] = kv;
                        
                        memset((void*)SendBuf,0,16);
                        for(i=0;i<index;i++)
                        {
                            SendBuf[i] = DataToIC_Card[i] + 0x30;
                        }
                        Rs485_Config(1);
                        
                        printf("rfid->lcd,I,%s\r\n",SendBuf);
                        delay_ms(10);
                        Rs485_Config(0);                         
                     }
                     break;                    
                case KEY_Enter:
                     if((IC_Card_Exist == 1)&&(index == 16))//��⵽IC������,����д��16λ
                     {
                         IC_Card_Write(DataToIC_Card);
                         index = 0;
                         memset((void*)DataToIC_Card,0,16);//�������
                     }
                     else if((IC_Card_Exist == 1)&&(index)&&(index != 16))
                     {
                        Rs485_Config(1);
                        printf("rfid->lcd,I,%s\r\n","need 16 bytes");
                        delay_ms(1000);
                        printf("rfid->lcd,I,%s\r\n",SendBuf);
                        delay_ms(10);
                        Rs485_Config(0);
                     }
                     break;                    
                case KEY_Canncle: 
                     if(index)//����ɾ��
                     {
                        index--;
                        DataToIC_Card[index] = 0;
                        memset((void*)SendBuf,0,16);
                        for(i=0;i<index;i++)
                        {
                            SendBuf[i] = DataToIC_Card[i] + 0x30;
                        }
                        Rs485_Config(1);
                        if(index)
                        {
                            printf("rfid->lcd,I,%s\r\n",SendBuf); 
                        }
                        else
                        {
                            printf("rfid->lcd,I,\r\n");
                        }
                        delay_ms(10);
                        Rs485_Config(0);                         
                     }
                        
                     break;                    
                default:break;
            }                    
        }

	}
}

