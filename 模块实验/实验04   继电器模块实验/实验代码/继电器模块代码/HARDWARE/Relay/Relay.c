#include "Relay.h"

//==========================================================
//	�������ƣ�	Relay_Init
//
//	�������ܣ�	��ʼ��485
//
//	��ڲ�����	��
//
//	���ز�����	��
//
//	˵����		
//==========================================================
void Relay_Init(void)
{

    GPIO_InitTypeDef GPIO_Initure;

    __HAL_RCC_GPIOB_CLK_ENABLE();           				//����GPIOBʱ��
	
		GPIO_Initure.Pin = GPIO_PIN_13 | GPIO_PIN_14;		//PB14 PB13
		GPIO_Initure.Mode = GPIO_MODE_OUTPUT_PP;				//�������
		GPIO_Initure.Speed = GPIO_SPEED_FREQ_LOW; 			//����
		HAL_GPIO_Init(GPIOB, &GPIO_Initure);
	
		HAL_GPIO_WritePin(GPIOB,GPIO_PIN_13 | GPIO_PIN_14,GPIO_PIN_RESET);  //��ʼ���رռ̵���
 
}


//==========================================================
//	�������ƣ�	Relay_Config
//
//	�������ܣ�	���ؼ̵���
//
//	��ڲ�����	1(��)  0(��)
//
//	���ز�����	��
//
//	˵����		
//==========================================================
void Relay_Config(uint8_t fag)
{
	if(fag){
			RELAY1_OPEN;	 //�򿪼̵���1
			RELAY2_OPEN;	 //�򿪼̵���2
	}
	else{
			RELAY1_CLOSE;  //�رռ̵���1
			RELAY2_CLOSE;  //�رռ̵���2
	}
}



