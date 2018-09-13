#ifndef __Relay_H
#define __Relay_H

#include "stm32f1xx_hal.h"

#define  RELAY1_OPEN  	HAL_GPIO_WritePin(GPIOB, GPIO_PIN_14, GPIO_PIN_SET); 			//RL1����
#define  RELAY1_CLOSE   HAL_GPIO_WritePin(GPIOB, GPIO_PIN_14, GPIO_PIN_RESET);	  //RL1�ر�
#define  RELAY2_OPEN  	HAL_GPIO_WritePin(GPIOB, GPIO_PIN_13, GPIO_PIN_SET);  		//RL2����
#define  RELAY2_CLOSE   HAL_GPIO_WritePin(GPIOB, GPIO_PIN_13, GPIO_PIN_RESET);  	//RL2�ر�

void Relay_Config(uint8_t fag);  //���Ƽ̵�������

void Relay_Init(void);  //�̵�����ʼ��

#endif /*__Bsp_Relay_H */


