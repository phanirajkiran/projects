#include "stm32f1xx_hal.h"  
#include "delay.h"

//==========================================================
//	�������ƣ�	delay_ms
//
//	�������ܣ�	������ʱ����
//
//	��ڲ�����	��
//
//	���ز�����	��
//
//	˵����		
//==========================================================
void delay_ms(unsigned int nms)
{		
	unsigned int i = 0,j = 0;
	for(i = 0;i<nms;i++)
	{
		for(j = 0;j<6400;j++)
		{;}
	}
}


void delay_us(unsigned int nus)
{		
	unsigned int i = 0,j = 0;
	for(i = 0;i<nus;i++)
	{
		for(j = 0;j<1142;j++)
		{;}
	}
}

