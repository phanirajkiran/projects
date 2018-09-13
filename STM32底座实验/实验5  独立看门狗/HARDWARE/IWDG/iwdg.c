#include "iwdg.h"


IWDG_HandleTypeDef IWDG_Handler; //�������Ź����


//==========================================================
//	�������ƣ�	IWDG_Init
//
//	�������ܣ�	��ʼ���������Ź�
//
//	��ڲ�����	
//              prer:��Ƶ��:IWDG_PRESCALER_4~IWDG_PRESCALER_256
//              rlr:�Զ���װ��ֵ,0~0XFFF.
//
//	���ز�����	��
//
//	˵����		ʱ�����(���):Tout=((4*2^prer)*rlr)/32 (ms).
//==========================================================
void IWDG_Init(unsigned char prer,unsigned int rlr)
{
    IWDG_Handler.Instance=IWDG;
    IWDG_Handler.Init.Prescaler=prer;	//����IWDG��Ƶϵ��
    IWDG_Handler.Init.Reload=rlr;		//��װ��ֵ
    HAL_IWDG_Init(&IWDG_Handler);		//��ʼ��IWDG,Ĭ�ϻῪ���������Ź�	

	HAL_IWDG_Start(&IWDG_Handler);		//�����������Ź�
}
   
//==========================================================
//	�������ƣ�	IWDG_Feed
//
//	�������ܣ�	ι�������Ź�
//
//	��ڲ�����	��
//
//	���ز�����	��
//
//	˵����		
//==========================================================
void IWDG_Feed(void)
{   
    HAL_IWDG_Refresh(&IWDG_Handler); 	//ι��
}
