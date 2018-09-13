#include "key.h"
#include "delay.h"
#include "stm32f1xx.h"

//������ʼ������
void KEY_Init(void)
{
    GPIO_InitTypeDef GPIO_Initure;
    
    __HAL_RCC_GPIOA_CLK_ENABLE();           //����GPIOAʱ��
    
    GPIO_Initure.Pin=GPIO_PIN_7;    //PA7
    GPIO_Initure.Mode=GPIO_MODE_INPUT;      //����
    GPIO_Initure.Pull=GPIO_PULLUP;        //����
    GPIO_Initure.Speed=GPIO_SPEED_HIGH;     //����
    HAL_GPIO_Init(GPIOA,&GPIO_Initure);
    
}
//�������
unsigned char KEY_Scan(void)
{
    if(S1==0||S2==0||S3==0||S4==0)  //��⵽���ⰴ������
    {
        delay_ms(10);    // ��ʱȥ��

        if(S1==0)       return S1_PRES;
        else if(S2==0)  return S2_PRES;
        else if(S3==0)  return S3_PRES; 
				else if(S4==0)  return S4_PRES;  			
    }
    return 0;   //�ް�������
}




