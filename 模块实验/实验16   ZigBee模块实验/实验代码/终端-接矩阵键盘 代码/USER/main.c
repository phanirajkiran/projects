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
*	˵���� 		�⺯������ʵ��-HAL��汾
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
//��LEDģ��������ӵ�ZigBeeģ��MAC��ַ��ͨ��MAC��ַȡ����short addr,��short addrΪ���������ݡ�
const uint8_t RemoteZBM_MAC[8] = {0x6e,0x4B,0xF5,0x19,0x00,0x4B,0x12,0x00};
      uint16_t RemoteZBM_ShortAddr;

#define MSG_HEAD_LEN  8
const uint8_t MSG_HEAD[]="mrk->zbm";
#define READ_LOCAL_MAC 0
/*
����������Ϊ��ɫ���˽ڵ�Ϊ��ɫ�����Ӿ������ģ�����
*/
int main(void)
{ 
    uint8_t i = 0,pos = 0;
    HAL_Init();             					//��ʼ��HAL��
	UART1_Init(115200);						    //��ʼ������1
	Rs485_Init();   						    //��ʼ��485
    Rs485_Config(0);                            //Rs485 ����    
#if READ_LOCAL_MAC //���ڶ����豸��MAC��ַ
     ZBM_ResetIO_Init();
     ZBM_Reset();
    
    //�ж�Ƶ��5kz(200us)�����޸�ZigBeeģ���ͨ�Ų����ʣ�
    //��ʱ���ж�Ƶ��ҲҪ�޸ģ��ж�����Ӧ��Ϊ�����ֽڴ���ʱ��,
    TIM2_Init(64-1,200) ; //���ڼ����Ƿ������ɣ��������յ���һ���ֽڣ�ʹ�ܶ�ʱ��������ÿ�յ�һ���ֽ����㶨ʱ���������������ݷ���ʱ������ɡ�    
     delay_ms(3000);                           //ģ�鸴λ����ʱ3��
     UART2_Init(115200); 
     ZBM_GetLocalMAC(&ZBM_Info.MAC_ADDR[0]);    //��ȡ����MAC
     while(1);
#else
    ZigBee_Mode_Init();       
#endif  
    ZBM_Info.nwk_state = ZBM_NETWORK_STATE_JOINED; 
    while(ZBM_IsJoinedNetwork() != ZBM_NETWORK_STATE_JOINED);
    delay_ms(200);   
    while(!RemoteZBM_ShortAddr)
    {
        delay_ms(1000); 
        ZBM_GetShortaddr_throung_MAC(&RemoteZBM_MAC[0],&RemoteZBM_ShortAddr);
    }
	while(1)
    {
        if((GetMsg == 1) && (ZBM_Info.nwk_state == ZBM_NETWORK_STATE_JOINED))
        {
                for(i=0;i < MSG_HEAD_LEN;i++)
            {//�������ݵ�ͷ�Ƿ�ΪMSG_HEADָ����
                if(USART1_RX_BUF[i] != MSG_HEAD[i])
                {
                    break;
                }
            }
            
            pos = i;
            if(i == MSG_HEAD_LEN)//���i����MSG_HEAD_LEN�������յ�������ͷ��MSG_HEADָ�����ͬ����������ݷ���									
            {	
                switch(USART1_RX_BUF[pos+1])
                {
                    case '1':
                             ZBM_Send_P2P(RemoteZBM_ShortAddr,"led1,toggle",strlen("led1,toggle"));
                    break;
                    case '2':
                             ZBM_Send_P2P(RemoteZBM_ShortAddr,"led2,toggle",strlen("led2,toggle"));
                    break;
                    case '3':
                             ZBM_Send_P2P(RemoteZBM_ShortAddr,"led3,toggle",strlen("led3,toggle"));
                    break;
                    case '4':
                             ZBM_Send_P2P(RemoteZBM_ShortAddr,"led4,toggle",strlen("led4,toggle"));
                    break;                             
                    default:break;
                }//switch(USART1_RX_BUF[pos+2])
            }//if(i == MSG_HEAD_LEN)            
            GetMsg = 0;
            USART1_RX_STA = 0;
        }//if(GetMsg == 1) 
        
    }
}





