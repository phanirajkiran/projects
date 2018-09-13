#include "Rs485.h"	
#include "delay.h"
//==========================================================
//	�������ƣ�	Rs485_Init
//
//	�������ܣ�	��ʼ��485
//
//	��ڲ�����	��
//
//	���ز�����	��
//
//	˵����		
//==========================================================
void Rs485_Init(void)
{
    GPIO_InitTypeDef GPIO_Initure;

    __HAL_RCC_GPIOA_CLK_ENABLE();           	//����GPIOAʱ��
	
    GPIO_Initure.Pin = GPIO_PIN_8;		//PA8
    GPIO_Initure.Mode = GPIO_MODE_OUTPUT_PP;//�������
    GPIO_Initure.Speed = GPIO_SPEED_FREQ_LOW; //����
    HAL_GPIO_Init(GPIOA, &GPIO_Initure);

    HAL_GPIO_WritePin(GPIOA,GPIO_PIN_8,GPIO_PIN_RESET);	//PA8��0   ��ʼ���ȴ�ģʽ
}

//==========================================================
//	�������ƣ�	Rs485_Config
//
//	�������ܣ�	����485�շ�ģʽ
//
//	��ڲ�����	1(485����)   0(485����)
//
//	���ز�����	��
//
//	˵����		
//==========================================================
void Rs485_Config(uint8_t fag)
{
	if(fag)
    {
		RS485_TX_EN; //����485����
        delay_ms(10);
	}
	else
    {
        delay_ms(10);
		RS485_RX_EN; //����485����
    }   
}


