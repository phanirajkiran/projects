#include "WiFi.h"

/**
  * @brief  WIFI����ONE.NETƽ̨ATָ��
  * @param  void
  * @retval void
  **/
void ESP8266_Init()
{
		atk_8266_send_cmd(AT,"OK",2000); 					/*����AT����ģʽ*/
	
		atk_8266_send_cmd(CWMODE,"OK",3000);			/*����ΪAPģʽ*/
	
		atk_8266_send_cmd(RST,"ready",3000);			/*����ģ��*/
	
		atk_8266_send_cmd(CWSAP,"OK",3000);				/*���ø�ģ���SID��PWD*/
	
		atk_8266_send_cmd(CIFSR,"OK",3000);				/*��ѯIP */
	
		atk_8266_send_cmd(CIPMUX,"OK",3000);			/*ʹ�ܶ�����*/
	
		atk_8266_send_cmd(CIPSERVER,"OK",3000);		/*����Ϊ������-���ö˿�*/
	
		atk_8266_send_cmd(CIPAPMAC,"OK",2000);		/*����MAC��ַ*/
		
		atk_8266_send_cmd(CIPAP,"OK",3000);				/*����IP��ַ*/
	
		USART_AT_STA = 1;           							/*ATָ�����ɱ�־λ*/
}




