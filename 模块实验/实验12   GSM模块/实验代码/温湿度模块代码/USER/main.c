#include "stm32f1xx_hal.h"
#include "stm32f1xx.h"
#include "TM1640.h"	
#include "SHT20.h"	
#include "delay.h"
#include "Rs485.h"
#include "Usart.h"
#include "ADC.h"
#include "I2C.h"


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
*	˵���� 		SHT20�⺯������ʵ��-HAL��汾
*
*	�޸ļ�¼��	
************************************************************
************************************************************
************************************************************
**/

uint32_t Light_AD = 0;							//����ǿ��
uint8_t temp = 0 , humi = 0;				//��ʪ��

int main(void)
{ 
  HAL_Init();             					//��ʼ��HAL��  
	TM1640_Init();										//��ʼ��TM1640
	MY_ADC_Init();										//��ʼ��ADC
	MX_I2C1_Init();										//��ʼ��I2C
	UART1_Init(115200);								//��ʼ������һ
	Rs485_Init();											//��ʼ��485

	while(1)
	{	
		SHT2x_GetTempHumi(); 															//��ȡ��ʪ��ֵ
		Light_AD = Get_Adc_Average(ADC_CHANNEL_0,50);  		//��ȡ����ǿ��
		temp = g_sht2x_param.TEMP_HM;											//��ȡ�¶�
		humi = g_sht2x_param.HUMI_HM;											//��ȡʪ��
		
		send_LED_Display(0xC0,Light_AD,3);								//��ʾ��ǿ
		HAL_Delay(1000);
			
		send_LED_Display(0xC0,humi,2);  									//��ʾʪ��
		HAL_Delay(1000);
		
		send_LED_Display(0xC0,temp,1);  									//��ʾ�¶�
		HAL_Delay(1000);
		
		Rs485_Config(1);																	//����485����
		printf("wsd->gsm%d%d%d\r\n",temp,humi,Light_AD);
		delay_ms(20);
		Rs485_Config(0);																	//�ر�485����
	}
}





