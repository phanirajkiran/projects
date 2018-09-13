#include "stm32f1xx.h"
#include "delay.h"
#include "string.h"
#include "M5310.h"
#include "nbiot.h"
#include "coap.h"
#include "Usart.h"
//==========================================================
//	�������ƣ�	SendCmd
//
//	�������ܣ�	��ʼ������2��������������ڲ���9600
//
//	��ڲ�����	uint8_t  *cmd,     ��Ҫ���͵�����ͨ���Ǹ��ַ���
//              uint8_t  *result���ڴ����ص�һ�������
//              uint8_t  retry,   �ط�������
//              uint16_t waittime, �ȴ���Ӧʱ�䣬ʱ�䵥λ(����ms)
//	���ز�����	����1������ͳɹ���
//              ����0�������ʧ�ܡ�
//	˵����		
//==========================================================
 char AT_SendCmd(char* cmd, char *expected_result,uint8_t retry,uint16_t waittime)
 {
     uint8_t  ret = 0;
     uint16_t wt=0;
     do
     {
        USART2_RecvIndex = 0;
        memset((void*)USART2_RecvBuffer,0,USART2_RECV_BUFFER_LENGTH);
         
        USART2_SendBytes(cmd,strlen((char*)cmd));
        wt = waittime;
        while(wt--)
        {        
            if(strstr((void*)USART2_RecvBuffer,(const char*)expected_result))
            {//�յ����ڴ��ķ���
                retry = 0;
                ret = 1;
                break;//����while(waittime--)
            }
            delay_ms(1);
        }
     }while(retry--);
     
     return ret;//�������е��ˣ�ret��������յ�����ȷ�ظ�������֮��
 }
  //==========================================================
//	�������ƣ�	Msg_Handler
//
//	�������ܣ�	����USART2_RecvBuffer[]�Ƿ�����������Ϣ��ʽ����Բ�ͬ����Ϣ��ʽ������Ӧ�Ĳ���
//
//	��ڲ�����	��
//
//	���ز�����	��
// 
//	˵����		
//==========================================================
 uint8_t Msg_Handler(void)
 {
    uint8_t code = 0;
	char *read=NULL,*write=NULL,*excute=NULL;
	char *ack=NULL,*observe=NULL,*reg_rsp=NULL,*close_rsp=NULL,*update_rsp=NULL;
     
	read       = strstr((const char *)USART2_RecvBuffer, "+MIPLREAD");    
	write      = strstr((const char *)USART2_RecvBuffer, "+MIPLWRITE");
	excute     = strstr((const char *)USART2_RecvBuffer, "+MIPLEXECUTE");
	ack        = strstr((const char *)USART2_RecvBuffer, "+MIPLNOTIFY");
	observe    = strstr((const char *)USART2_RecvBuffer, "+MIPLOBSERVE");
	reg_rsp    = strstr((const char *)USART2_RecvBuffer, "+MIPLOPEN");
	close_rsp  = strstr((const char *)USART2_RecvBuffer, "+MIPLCLOSE");
	update_rsp = strstr((const char *)USART2_RecvBuffer, "+MIPLUPDATE");    

    if(read != NULL)
    {
       code = COAP_READ;
    }
    else if(write != NULL)
    {
       code = COAP_WRITE;
    }
    else if(excute != NULL)
    {
       code = COAP_EXECUTE;
    }
    else if(ack != NULL)
    {
       code = COAP_ACK;
    }
    else if(observe != NULL)
    {
       code = COAP_OBSERVE;
    }
    else if(reg_rsp!=NULL)
    {
       code = COAP_REG_RSP;
    }
    else if(close_rsp != NULL)
    {
       code = COAP_CLOSE_RSP;
    }
    else if(update_rsp != NULL)
    {
       code = UPDATE_RSP;  
    }    
    if((write != NULL) ||(read != NULL)||(excute != NULL))
    {
        delay_ms(100);
       // m5310_write_rsp(1, ackid);
        handle_request((nbiot_device_t *)0,code,USART2_RecvBuffer,strlen((char*)USART2_RecvBuffer),USART2_RECV_BUFFER_LENGTH);
    }
    
    return code;
 }



 