#ifndef __Esp8266_H__
#define __Esp8266_H__

#include "stm32f1xx_hal.h"
#include "Usart.h"

#define AT         	 "AT\r\n"
#define CWMODE     	 "AT+CWMODE=3\r\n"																//����ģʽΪAP+STA
#define RST        	 "AT+RST\r\n"																			//������ģ��
#define CIFSR        "AT+CIFSR\r\n"																		//��ѯIP��ַ
#define CWJAP        "AT+CWJAP=\"BC\",\"f0f0f0f0f0\"\r\n"				//����SID��PWD��������
#define TCP_CIPSTART "AT+CIPSTART=\"TCP\",\"183.230.40.40\",1811\r\n"	//����ΪTCPЭ�鴫�䲢ָ��IP�Ͷ˿ں�
#define CIPMODE      "AT+CIPMODE=1\r\n"																//͸��
#define CIPSEND      "AT+CIPSEND\r\n"																	//��ʼ����
#define CIPSTATUS    "*152342#0001#sample*\r\n"												//ONE.NETƽ̨�����˺�ʶ����

/**
  * @brief  ��ʼ��ESP8266,������·�ɺ�����ƽ̨
  * @param  server:����ATָ�����÷�������ַ�Ͷ˿��ַ���
    * @param  ssid_pwd: ����ATָ������·������SSID��PWD
  * @retval NONE
  **/
void ESP8266_Init(void);

#endif


