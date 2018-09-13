#ifndef _KEY_H
#define _KEY_H

#include "stm32f1xx.h"



#define S1        HAL_GPIO_ReadPin(GPIOA,GPIO_PIN_4)  //KEY0����PA4
#define S2        HAL_GPIO_ReadPin(GPIOA,GPIO_PIN_5)  //KEY1����PA5
#define S3        HAL_GPIO_ReadPin(GPIOA,GPIO_PIN_6)  //WKUP����PA6
#define S4        HAL_GPIO_ReadPin(GPIOA,GPIO_PIN_7)  //WKUP����PA7


#define S1_PRES   1
#define S2_PRES	  2
#define S3_PRES   3
#define S4_PRES   4

void KEY_Init(void);
unsigned char KEY_Scan(void);

#endif
