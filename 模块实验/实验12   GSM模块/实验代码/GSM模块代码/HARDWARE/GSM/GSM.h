#ifndef __GSM_H__
#define __GSM_H__

#include "stm32f1xx_hal.h"
#include "Usart.h"

#define AT         	 	"AT\r\n"
#define IPR         	"AT+IPR=9600\r\n"																		//���ò�����
#define QIFGCNT       "AT+QIFGCNT=0\r\n"																	//����Ϊǰ̨Context
#define CSQ         	"AT+CSQ\r\n"																				//�����ź�������ֵԽ���ź�Խ��
#define CREG         	"AT+CREG=1\r\n"																			//����ֵΪ1��Ŀ��Ѿ���ͨGPRS����
#define CGATT         "AT+CGATT=1\r\n"																		//����OK  ��������
#define CGACT         "AT+CGACT=1,1\r\n"																	//�������磬֮�����ʹ��TCPIP  ATָ��
#define QIOPEN      	"AT+QIOPEN=\"TCP\",\"183.230.40.40\",\"1811\"\r\n"	//����TCP����
#define QIOSEND       "AT+QISEND=20\r\n"																	//��ʼ����
#define CIPSTATUS    "*134679#0001#sample*"													                //ONE.NETƽ̨�����˺�ʶ����


/*

*/

/**
  * @brief  ��ʼ��ESP8266,������·�ɺ�����ƽ̨
  * @param  server:����ATָ�����÷�������ַ�Ͷ˿��ַ���
    * @param  ssid_pwd: ����ATָ������·������SSID��PWD
  * @retval NONE
  **/
void GSM_Init(void);

#endif


