#include "stm32f1xx_hal.h"
#include "stm32f1xx.h"
#include "TM1640.h"	
#include "SHT20.h"	
#include "delay.h"
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

uint32_t Light_AD = 0;

int main(void)
{ 
  HAL_Init();             					//��ʼ��HAL��  
	TM1640_Init();										//��ʼ��TM1640
	MY_ADC_Init();										//��ʼ��ADC
	MX_I2C1_Init();										//��ʼ��I2C

	while(1)
	{
		SHT2x_GetTempHumi(); 															//��ȡ��ʪ��ֵ
		Light_AD = Get_Adc_Average(ADC_CHANNEL_0,50);  		//��ȡ����ǿ��
		
		send_LED_Display(0xC0,Light_AD,3);								//��ʾ��ǿ
		HAL_Delay(1000);
			
		send_LED_Display(0xC0,g_sht2x_param.HUMI_HM ,2);  //��ʾʪ��
		HAL_Delay(1000);
		
		send_LED_Display(0xC0,g_sht2x_param.TEMP_HM,1);  	//��ʾ�¶�
		HAL_Delay(1000);
	}
}

