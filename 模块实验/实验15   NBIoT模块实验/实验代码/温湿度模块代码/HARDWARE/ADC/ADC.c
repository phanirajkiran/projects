#include "ADC.h"
#include "delay.h"
#include "stm32f1xx.h"

ADC_HandleTypeDef hadc1;		//ADC���


//==========================================================
//	�������ƣ�	MY_ADC_Init
//
//	�������ܣ�	��ʼ��ADC
//
//	��ڲ�����	��
//
//	���ز�����	��
//
//	˵����		
//==========================================================
void MY_ADC_Init(void)
{ 
		RCC_PeriphCLKInitTypeDef ADC_CLKInit;
		
		ADC_CLKInit.PeriphClockSelection=RCC_PERIPHCLK_ADC;			//ADC����ʱ��
		ADC_CLKInit.AdcClockSelection=RCC_ADCPCLK2_DIV6;				//��Ƶ����6ʱ��
		HAL_RCCEx_PeriphCLKConfig(&ADC_CLKInit);								//����ADCʱ��
	
    hadc1.Instance=ADC1;
    hadc1.Init.DataAlign=ADC_DATAALIGN_RIGHT;             	//�Ҷ���
    hadc1.Init.ScanConvMode=DISABLE;                      	//��ɨ��ģʽ
    hadc1.Init.ContinuousConvMode=DISABLE;                	//�ر�����ת��
    hadc1.Init.NbrOfConversion=1;                         	//1��ת���ڹ��������� Ҳ����ֻת����������1 
    hadc1.Init.DiscontinuousConvMode=DISABLE;             	//��ֹ����������ģʽ
    hadc1.Init.NbrOfDiscConversion=0;                     	//����������ͨ����Ϊ0
    hadc1.Init.ExternalTrigConv=ADC_SOFTWARE_START;       	//�������
    HAL_ADC_Init(&hadc1);                                 	//��ʼ�� 
	
	HAL_ADCEx_Calibration_Start(&hadc1);					 						//У׼ADC
}


//==========================================================
//	�������ƣ�	HAL_ADC_MspInit
//
//	�������ܣ�	ADC�ײ��������������ã�ʱ��ʹ��
//							�˺����ᱻHAL_ADC_Init()����
//
//	��ڲ�����	hadc:ADC���
//
//	���ز�����	��
//
//	˵����		
//==========================================================
void HAL_ADC_MspInit(ADC_HandleTypeDef* hadc)
{
    GPIO_InitTypeDef GPIO_Initure;
    __HAL_RCC_ADC1_CLK_ENABLE();            //ʹ��ADC1ʱ��
    __HAL_RCC_GPIOA_CLK_ENABLE();						//����GPIOAʱ��
	
    GPIO_Initure.Pin=GPIO_PIN_0;            //PA0
    GPIO_Initure.Mode=GPIO_MODE_ANALOG;     //ģ��
    GPIO_Initure.Pull=GPIO_NOPULL;          //����������
    HAL_GPIO_Init(GPIOA,&GPIO_Initure);
}


//==========================================================
//	�������ƣ�	Get_Adc
//
//	�������ܣ�	���ADCֵ
//
//	��ڲ�����	ch: ͨ��ֵ 0~16��ȡֵ��ΧΪ��ADC_CHANNEL_0~ADC_CHANNEL_16
//
//	���ز�����	ת�����
//
//	˵����			
//==========================================================
uint16_t Get_Adc(uint32_t ch)   
{
    ADC_ChannelConfTypeDef ADC1_ChanConf;
    
    ADC1_ChanConf.Channel=ch;                                   //ͨ��
    ADC1_ChanConf.Rank=1;                                       //��1�����У�����1
    ADC1_ChanConf.SamplingTime=ADC_SAMPLETIME_239CYCLES_5;      //����ʱ��               
    HAL_ADC_ConfigChannel(&hadc1,&ADC1_ChanConf);        				//ͨ������
	
    HAL_ADC_Start(&hadc1);                               				//����ADC
	
    HAL_ADC_PollForConversion(&hadc1,10);                				//��ѯת��
 
	return (uint16_t)HAL_ADC_GetValue(&hadc1);	         					//�������һ��ADC1�������ת�����
}

//==========================================================
//	�������ƣ�	Get_Adc_Average
//
//	�������ܣ�	��ȡָ��ͨ����ת��ֵ��ȡtimes��,Ȼ��ƽ�� 
//
//	��ڲ�����	times:��ȡ����
//
//	���ز�����	ͨ��ch��times��ת�����ƽ��ֵ
//
//	˵����			
//==========================================================
	double temp_val=0;   //��Ż�ȡ����ADֵ
	uint32_t lux=0;   		 //����ǿ��ֵ
	uint8_t t;

uint16_t Get_Adc_Average(uint32_t ch,uint8_t times)
{
	temp_val=0;
	
	for(t=0;t<times;t++)
	{
		temp_val+=Get_Adc(ch);
		HAL_Delay(5);
	}
	temp_val = (temp_val/times); 	//ʵ��ADֵ
	
//	temp_val = temp_val/4095*3.3;	//ʵ�ʵ�ѹֵ
//	
//	temp_val = temp_val/47000;		//ʵ�ʵ���ֵ
//	
//	temp_val = 3.3/temp_val;			//ʵ���ܵ���
//	
//	temp_val = temp_val - 47000;  //��������ֵ
	
	return (temp_val);
	
} 

