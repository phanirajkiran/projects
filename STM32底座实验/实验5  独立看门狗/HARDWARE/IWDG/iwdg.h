#ifndef __IWDG_H
#define __IWDG_H
#include "stm32f1xx.h"


void IWDG_Init(unsigned char prer,unsigned int rlr);//��ʼ��IWDG����ʹ��IWDG
void IWDG_Feed(void);//ι��


#endif
