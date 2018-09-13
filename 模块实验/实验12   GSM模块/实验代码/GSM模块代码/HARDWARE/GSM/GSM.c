#include "GSM.h"

uint8_t ffiigg = 1;
/**
  * @brief  WIFI����ONE.NETƽ̨ATָ��
  * @param  void
  * @retval void
  **/
void GSM_Init()
{
	if(ffiigg)
	{
		ffiigg = 0;
		HAL_Delay(5000);
	
		gsm_send_cmd(AT,"OK",2000); 					/*����AT����ģʽ*/
		
		gsm_send_cmd(IPR,"OK",2000); 					/*���ò�����*/
	
		gsm_send_cmd(QIFGCNT,"OK",3000);			/*����Ϊǰ̨Context*/
	
		gsm_send_cmd(CSQ,"OK",3000);					/*�����ź�������ֵԽ���ź�Խ��*/
		
		gsm_send_cmd(CREG,"OK",5000);					/*����ֵΪ1��Ŀ��Ѿ���ͨGPRS����*/
	
		gsm_send_cmd(CGATT,"OK",5000);				/*����OK  ��������*/
	
		gsm_send_cmd(CGACT,"OK",5000);				/*�������磬֮�����ʹ��TCPIP  ATָ��*/
	
		gsm_send_cmd(QIOPEN,"OK",6000);				/*����TCP����*/
		
		gsm_send_cmd(QIOSEND,"0",3000);				/*��ʼ����*/
	
		printf("%s",CIPSTATUS);		                   /*ONE.NETƽ̨�����˺�ʶ����*/

		USART_AT_STA = 1;           					/*ATָ�����ɱ�־λ*/
	}
		
}




