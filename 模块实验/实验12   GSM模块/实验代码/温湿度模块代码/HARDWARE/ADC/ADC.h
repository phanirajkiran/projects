#ifndef _ADC_H
#define _ADC_H

#include "stm32f1xx_hal.h"

void MY_ADC_Init(void); 				//ADCͨ����ʼ��
uint16_t  Get_Adc(uint32_t ch); 		        //���ĳ��ͨ��ֵ 
uint16_t Get_Adc_Average(uint32_t ch,uint8_t times);//�õ�ĳ��ͨ����������������ƽ��ֵ

#endif

