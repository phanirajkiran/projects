#ifndef __DELAY_H
#define __DELAY_H 			   

#include "stm32f1xx_hal.h"  

void delay_ms(unsigned int nms);

extern void Stm32_Clock_Init(uint32_t PLL);					//ʱ��ϵͳ����

#endif





























