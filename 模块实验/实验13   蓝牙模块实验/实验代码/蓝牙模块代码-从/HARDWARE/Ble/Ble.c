#include "Ble.h"	
#include "delay.h"
#include "Usart.h"

void HC_08_Init()
{
	delay_ms(3000);															/*��ʱ�ȴ�*/		
	
	printf("blefig\r\n");												/*���ͼ������*/
	
	delay_ms(5000);															/*��ʱ�ȴ�*/	
	
	if(BLE_FIG)																	/*�������û������ִ��ATָ��*/
	{
		atk_8266_send_cmd(AT,"OK",3000); 					/*��⴮���Ƿ���������*/
	
		atk_8266_send_cmd(ROLE,"OK",3000);				/*�������ӽ�ɫ*/
	
		atk_8266_send_cmd(NAME,"OK",5000);				/*�޸���������*/
	
		atk_8266_send_cmd(ADDR,"OK",4000);				/*�޸�������ַ*/
	
		atk_8266_send_cmd(BAUD,"OK",2000);				/*�޸Ĳ�����*/
	
		atk_8266_send_cmd(CONT,"OK",2000);				/*����ģ���Ƿ������*/
	
		atk_8266_send_cmd(LUUID,"OK",2000);				/*����UUID*/
		
	}
	
	USART_AT_STA = 1;													//ATָ�����ɱ�־λ
}


