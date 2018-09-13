#include "pwm.h"

TIM_HandleTypeDef 	TIM4_Handler;      	//��ʱ����� 
TIM_OC_InitTypeDef 	TIM4_CH1Handler;	//��ʱ��1ͨ��1���


//==========================================================
//	�������ƣ�	TIM4_PWM_Init
//
//	�������ܣ�	TIM4 PWM���ֳ�ʼ�� 
//
//	��ڲ�����	arr���Զ���װֵ��
//							psc��ʱ��Ԥ��Ƶ��
//							��ʱ�����ʱ����㷽��:Tout=((arr+1)*(psc+1))/Ft(��λS).
//							Ft=��ʱ������Ƶ��,��λ:Mhz
//							
//	���ز�����	��
//
//	˵����		
//==========================================================
void TIM4_PWM_Init(uint16_t psc,uint16_t arr)
{  
    TIM4_Handler.Instance=TIM4;         								//��ʱ��4
    TIM4_Handler.Init.Prescaler=psc;       							//��ʱ����Ƶ
    TIM4_Handler.Init.CounterMode=TIM_COUNTERMODE_UP;		//���ϼ���ģʽ
    TIM4_Handler.Init.Period=arr;          							//�Զ���װ��ֵ
    TIM4_Handler.Init.ClockDivision=TIM_CLOCKDIVISION_DIV1;
    HAL_TIM_PWM_Init(&TIM4_Handler);       							//��ʼ��PWM
    
    TIM4_CH1Handler.OCMode=TIM_OCMODE_PWM1; 						//ģʽѡ��PWM1
    TIM4_CH1Handler.Pulse=0;           	 								//���ñȽ�ֵ,��ֵ����ȷ��ռ�ձȣ�Ĭ�ϱȽ�ֵΪ�Զ���װ��ֵ��һ��,��ռ�ձ�Ϊ50%
    TIM4_CH1Handler.OCPolarity=TIM_OCPOLARITY_LOW; 			//����Ƚϼ���Ϊ�� 
    HAL_TIM_PWM_ConfigChannel(&TIM4_Handler,&TIM4_CH1Handler,TIM_CHANNEL_1);//����TIM4ͨ��1
	
    HAL_TIM_PWM_Start(&TIM4_Handler,TIM_CHANNEL_1);			//����PWMͨ��1
	 	   
}

//==========================================================
//	�������ƣ�	HAL_TIM_PWM_MspInit
//
//	�������ܣ�	��ʱ���ײ�������ʱ��ʹ�ܣ���������
//							�˺����ᱻHAL_TIM_PWM_Init()����
//
//	��ڲ�����	htim:��ʱ�����
//							
//	���ز�����	��
//
//	˵����		
//==========================================================
void HAL_TIM_PWM_MspInit(TIM_HandleTypeDef *htim)
{
	GPIO_InitTypeDef GPIO_Initure;
	
    if(htim->Instance==TIM4)
	{
		__HAL_RCC_TIM4_CLK_ENABLE();					//ʹ�ܶ�ʱ��4
		__HAL_RCC_GPIOB_CLK_ENABLE();					//����GPIOBʱ��
		
		GPIO_Initure.Pin=GPIO_PIN_6;          //PB6
		GPIO_Initure.Mode=GPIO_MODE_AF_PP;  	//�����������
		GPIO_Initure.Pull=GPIO_PULLUP;        //����
		GPIO_Initure.Speed=GPIO_SPEED_HIGH;   //����
		
		HAL_GPIO_Init(GPIOB,&GPIO_Initure); 	
	}
}

uint8_t dir=1;
uint16_t led0pwmval=0; 

//==========================================================
//	�������ƣ�	TIM_SetTIM4Compare2
//
//	�������ܣ�	����TIM4ͨ��1��ռ�ձ�
//
//	��ڲ�����	compare:�Ƚ�ֵ
//							
//	���ز�����	��
//
//	˵����		
//==========================================================
void TIM_SetTIM4Compare2(uint32_t compare)
{
	TIM4->CCR1=compare; 
}


//==========================================================
//	�������ƣ�	PWM_SetTIM4Compare2
//
//	�������ܣ�	PWM����ռ�ձ�  ����LED3������Ƶ���Լ����ȵ�ת��Ƶ��
//
//	��ڲ�����	compare:�Ƚ�ֵ
//							
//	���ز�����	��
//
//	˵����		
//==========================================================
void PWM_SetTIM4Compare2(uint32_t compare)
{
	TIM_SetTIM4Compare2(compare);	//�޸ıȽ�ֵ���޸�ռ�ձ�
}












































