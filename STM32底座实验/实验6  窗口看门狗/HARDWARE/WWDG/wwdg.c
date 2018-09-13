#include "wwdg.h"
#include "led.h"

WWDG_HandleTypeDef WWDG_Handler;     //���ڿ��Ź����

//����WWDG������������ֵ��Ĭ��Ϊ���
unsigned char WWDG_CNT=0X7F;

unsigned char  led_flag = 0;  //LED��״̬��־

//==========================================================
//	�������ƣ�	WWDG_Init
//
//	�������ܣ�	��ʼ�����ڿ��Ź� 	
//
//	��ڲ�����	
//              tr   :T[6:0],������ֵ 
//              wr   :W[6:0],����ֵ 
//              fprer:��Ƶϵ����WDGTB��,�����2λ��Ч 
//
//	���ز�����	��
//
//	˵����		Fwwdg=PCLK1/(4096*2^fprer). һ��PCLK1=42Mhz
//==========================================================
void WWDG_Init(unsigned char tr,unsigned char wr,unsigned int fprer)
{
    WWDG_Handler.Instance=WWDG;
    WWDG_Handler.Init.Prescaler=fprer; 		//���÷�Ƶϵ��
    WWDG_Handler.Init.Window=wr;       		//���ô���ֵ
    WWDG_Handler.Init.Counter=tr;     		//���ü�����ֵ
    HAL_WWDG_Init(&WWDG_Handler);        	//��ʼ��WWDG
    HAL_WWDG_Start_IT(&WWDG_Handler);    	//�������ڿ��Ź�  
}

//==========================================================
//	�������ƣ�	HAL_WWDG_MspInit
//
//	�������ܣ�	WWDG�ײ�������ʱ�����ã��ж�����
//
//	��ڲ�����	hwwdg:���ڿ��Ź����
//
//	���ز�����	��
//
//	˵����		
//==========================================================
void HAL_WWDG_MspInit(WWDG_HandleTypeDef *hwwdg)
{   
    __HAL_RCC_WWDG_CLK_ENABLE();    //ʹ�ܴ��ڿ��Ź�ʱ��
        
    HAL_NVIC_SetPriority(WWDG_IRQn,2,3);    //��ռ���ȼ�2�������ȼ�Ϊ3
    HAL_NVIC_EnableIRQ(WWDG_IRQn);          //ʹ�ܴ��ڿ��Ź��ж�
}

//==========================================================
//	�������ƣ�	WWDG_IRQHandler
//
//	�������ܣ�	���ڿ��Ź��жϷ�����
//
//	��ڲ�����	��
//
//	���ز�����	��
//
//	˵����		
//==========================================================
void WWDG_IRQHandler(void)
{
    HAL_WWDG_IRQHandler(&WWDG_Handler);//����WWDG�����жϴ�����
}


//==========================================================
//	�������ƣ�	HAL_WWDG_WakeupCallback
//
//	�������ܣ�	�жϷ������������
//
//	��ڲ�����	��
//
//	���ز�����	��
//
//	˵����		
//==========================================================
void HAL_WWDG_WakeupCallback(WWDG_HandleTypeDef* hwwdg)
{
    HAL_WWDG_Refresh(&WWDG_Handler,WWDG_CNT);//���´��ڿ��Ź�ֵ
    
    led_flag = !led_flag; //��־ȡ��
    
    
    if(led_flag)
    {
        HAL_GPIO_WritePin(GPIOB,GPIO_PIN_14,GPIO_PIN_RESET); 	//LED4��Ӧ����PB0���ͣ���
    }
    else
    {
        HAL_GPIO_WritePin(GPIOB,GPIO_PIN_14,GPIO_PIN_SET); 	    //LED4��Ӧ����PB0���ߣ���	
    } 
}
