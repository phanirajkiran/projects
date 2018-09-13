#include "WiFi.h"

/**
  * @brief  WIFI����ONE.NETƽ̨ATָ��
  * @param  void
  * @retval void
  **/
void ESP8266_Init()
{
		atk_8266_send_cmd(AT,"OK",2000); 					/*����AT����ģʽ*/
	
		atk_8266_send_cmd(CWMODE,"OK",3000);			/*����ģ��Ӧ��ģʽ*/
	
		atk_8266_send_cmd(RST,"0",3000);					/*����ģ��*/
	
		atk_8266_send_cmd(CIFSR,"OK",3000);				/*��ѯ�豸IP�ɷ�����Ҫ��λ��*/
	
		atk_8266_send_cmd(CWJAP,"OK",12000);			/*����Ҫ���ӵ�·������SSID������*/
	
		atk_8266_send_cmd(TCP_CIPSTART,"OK",3000);/*�����������TCP����*/
	
		atk_8266_send_cmd(CIPMODE,"OK",3000);			/*͸��ģʽ*/
	
		atk_8266_send_cmd(CIPSEND,"OK",2000);			/*��ʼ����*/
	
		printf("22\r\n");
	
		USART_AT_STA = 1;           							/*ATָ�����ɱ�־λ*/
}




