#include "timer.h"
#include "stm32f1xx.h"
#include "timer.h"
#include "ZigBee_Mode.h"
#include "USART.h"

unsigned char  led_flag = 0;  //LED��״̬��־

TIM_HandleTypeDef TIM2_Handler;      //��ʱ����� 

//==========================================================
//	�������ƣ�	TIM2_Init
//
//	�������ܣ�	ͨ�ö�ʱ��3�жϳ�ʼ��
//
//	��ڲ�����	arr���Զ���װֵ��
//              psc��ʱ��Ԥ��Ƶ��
//
//	���ز�����	��
//
//	˵����		��ʱ�����ʱ����㷽��:Tout=((arr+1)*(psc+1))/Ft us.   Ft=��ʱ������Ƶ��,��λ:Mhz
//==========================================================

void TIM2_Init(unsigned int arr,unsigned int psc)
{  
    TIM2_Handler.Instance=TIM2;                          //ͨ�ö�ʱ��2
    TIM2_Handler.Init.Prescaler=psc;                     //��Ƶϵ��
    TIM2_Handler.Init.CounterMode=TIM_COUNTERMODE_UP;    //���ϼ�����
    TIM2_Handler.Init.Period=arr;                        //�Զ�װ��ֵ
    TIM2_Handler.Init.ClockDivision=TIM_CLOCKDIVISION_DIV1;//ʱ�ӷ�Ƶ����
    HAL_TIM_Base_Init(&TIM2_Handler);
    
    HAL_TIM_Base_Start_IT(&TIM2_Handler); //ʹ�ܶ�ʱ��2�Ͷ�ʱ��2�����жϣ�TIM_IT_UPDATE   
    __HAL_TIM_DISABLE(&TIM2_Handler);
}

//==========================================================
//	�������ƣ�	HAL_TIM_Base_MspInit
//
//	�������ܣ�	ʹ�ܶ�ʱ��
//
//	��ڲ�����	
//
//	���ز�����	��
//
//	˵����		
//==========================================================
void HAL_TIM_Base_MspInit(TIM_HandleTypeDef *htim)
{
    if(htim->Instance==TIM2)
	{
		__HAL_RCC_TIM2_CLK_ENABLE();            //ʹ��TIM3ʱ��
		HAL_NVIC_SetPriority(TIM2_IRQn,1,3);    //�����ж����ȼ�����ռ���ȼ�1�������ȼ�3
		HAL_NVIC_EnableIRQ(TIM2_IRQn);          //����ITM3�ж�   
	}
}

//==========================================================
//	�������ƣ�	TIM2_IRQHandler
//
//	�������ܣ�	��ʱ��2�жϷ�����
//
//	��ڲ�����	��
//
//	���ز�����	��
//
//	˵����		
//==========================================================
void TIM2_IRQHandler(void)
{
    __HAL_TIM_CLEAR_FLAG(&TIM2_Handler, TIM_IT_UPDATE);
    __HAL_TIM_DISABLE(&TIM2_Handler);
    ZBM_RecvHandler(USART2_RX_BUF,USART2_RX_STA);
    USART2_RX_STA = 0;
    
}
//==========================================================
//	�������ƣ�	HAL_TIM_PeriodElapsedCallback
//
//	�������ܣ�	�ص���������ʱ���жϷ���������
//
//	��ڲ�����	��
//
//	���ز�����	��
//
//	˵����		
//==========================================================
void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim)
{
     led_flag = !led_flag; //��־ȡ��
    
    
    if(led_flag)
    {
        HAL_GPIO_WritePin(GPIOB,GPIO_PIN_0,GPIO_PIN_RESET); 	//LED1��Ӧ����PB0���ͣ�������ͬ��LED1(0)	
    }
    else
    {
        HAL_GPIO_WritePin(GPIOB,GPIO_PIN_0,GPIO_PIN_SET); 	    //LED1��Ӧ����PB0���ߣ��𣬵�ͬ��LED1(1)		
    }
}
