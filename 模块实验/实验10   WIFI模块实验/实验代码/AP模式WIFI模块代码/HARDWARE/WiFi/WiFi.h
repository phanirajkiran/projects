#ifndef __WiFi_H__
#define __WiFi_H__

#include "stm32f1xx_hal.h"
#include "Usart.h"

#define AT         	 "AT\r\n"
#define CWMODE     	 "AT+CWMODE=2\r\n"												//����ΪAPģʽ
#define RST        	 "AT+RST\r\n"															//��λ
#define CWSAP        "AT+CWSAP=\"BBCC\",\"12345678\",1,4\r\n"	//ssid: BBCC  pwd:123456
#define CIFSR        "AT+CIFSR\r\n"														//��ѯIP 
#define CIPMUX       "AT+CIPMUX=1\r\n"												//ʹ�ܶ�����
#define CIPSERVER    "AT+CIPSERVER=1,8080\r\n"								//����Ϊ������-���ö˿�
#define CIPAPMAC 		 "AT+CIPAPMAC=\"18:fe:35:98:d3:7b\"\r\n"	//����MAC��ַ
#define CIPAP      	 "AT+CIPAP=\"192.168.4.3\"\r\n"						//����IP��ַ


/**
  * @brief  ��ʼ��ESP8266,������·�ɺ�����ƽ̨
  * @param  server:����ATָ�����÷�������ַ�Ͷ˿��ַ���
    * @param  ssid_pwd: ����ATָ������·������SSID��PWD
  * @retval NONE
  **/
void ESP8266_Init(void);

#endif


