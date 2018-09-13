#include "stm32f1xx_hal.h"
#include "stm32f1xx.h"
#include "timer.h"
#include "delay.h"
#include "Usart.h"
#include "Rs485.h"	
#include "ZigBee_Mode.h"
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
*	˵���� 		GSM�⺯������ʵ��-HAL��汾
*
*	�޸ļ�¼��	
************************************************************
************************************************************
************************************************************
**/

uint8_t KEY[16]={1,2,3,4,5,6,7,8,9,01,2,3,4,5,6};
const ZBM_Setting_TypeDef ZBM_Setting={
    ENDPOINT,         //�豸����
    0x1234,       //���� PAN_ID(0000~FFFE �̶����� PAN_ID,FFFF ������� PAN_ID) 
    &KEY[0],      //�����ܳ�(16λ)
    0x01,         //�������(1~99)
    0x0B,         //ͨ���ŵ�
    0x04,         //���͹���
    0x09,         //���ڲ�����
    0x00          //����״̬  0,����״ֹ̬ͣ ������1~250�� ����ģʽ����������ʱ��Ϊ sleep_time ��λ S���룩 
};

const uint8_t RemoteZBM_MAC[8] = {0x6e,0x4B,0xF5,0x19,0x00,0x4B,0x12,0x00};
      uint8_t RemoteZBM_ShortAddr;
#define READ_LOCAL_MAC 0
/*
����������Ϊ��ɫɫ���˽ڵ�Ϊ�նˣ�����LEDģ�����
*/
int main(void)
{ 
    HAL_Init();             					//��ʼ��HAL��
	UART1_Init(115200);						    //��ʼ������1
	Rs485_Init();   						    //��ʼ��485
    Rs485_Config(0);                            //Rs485 ����    
#if READ_LOCAL_MAC  //���ڶ����豸��MAC��ַ
     ZBM_ResetIO_Init();
     ZBM_Reset();
    
    //�ж�Ƶ��5kz(200us)�����޸�ZigBeeģ���ͨ�Ų����ʣ�
    //��ʱ���ж�Ƶ��ҲҪ�޸ģ��ж�����Ӧ��Ϊ�����ֽڴ���ʱ��
    TIM2_Init(64-1,200) ;//���ڼ����Ƿ������ɣ��������յ���һ���ֽڣ�ʹ�ܶ�ʱ��������ÿ�յ�һ���ֽ����㶨ʱ���������������ݷ���ʱ������ɡ�      
     delay_ms(3000);                           //ģ�鸴λ����ʱ3��
     UART2_Init(115200); 
     ZBM_GetLocalMAC(&ZBM_Info.MAC_ADDR[0]);    //��ȡ����MAC
     while(1);
#else
    ZigBee_Mode_Init();    
#endif    
    while(ZBM_IsJoinedNetwork() == ZBM_NETWORK_STATE_NO_NETWORK);
    
    ZBM_Info.nwk_state = ZBM_NETWORK_STATE_JOINED;
    USART2_RX_STA = 0;
    RecvSta = 0;
    Rs485_Config(0);
	while(1)
    {
        if(ZBM_Info.get_data == 1)
        {
            if(strstr((const char*)USART2_RX_BUF,"led1,toggle"))
            {
                memset((void*)USART2_RX_BUF,0,20);
                USART2_RX_STA = 0;
                RecvSta = 0;
                Rs485_Config(1);
                printf("led1,toggle\r\n");
                Rs485_Config(0);
                HAL_GPIO_TogglePin(GPIOB,GPIO_PIN_4);
            }
            else if(strstr((const char*)USART2_RX_BUF,"led2,toggle"))
            {
                memset((void*)USART2_RX_BUF,0,20);
                USART2_RX_STA = 0;
                RecvSta = 0;
                Rs485_Config(1);
                printf("led2,toggle\r\n");
                Rs485_Config(0);
            //            HAL_GPIO_TogglePin(GPIOB,GPIO_PIN_4);
            }
            else if(strstr((const char*)USART2_RX_BUF,"led3,toggle"))
            {
                memset((void*)USART2_RX_BUF,0,20);
                USART2_RX_STA = 0;
                RecvSta = 0;
                Rs485_Config(1);
                printf("led3,toggle\r\n");
            //            HAL_GPIO_TogglePin(GPIOB,GPIO_PIN_4);
            }
            else if(strstr((const char*)USART2_RX_BUF,"led4,toggle"))
            {
                memset((void*)USART2_RX_BUF,0,20);
                USART2_RX_STA = 0;
                RecvSta = 0;
                Rs485_Config(1);
                printf("led4,toggle\r\n");
                Rs485_Config(0);
            //            HAL_GPIO_TogglePin(GPIOB,GPIO_PIN_4);
            }
        }
    }
}





