#include "Pressure_Sensor.h"
#include "delay.h"


char  i;  						//forѭ��ʹ��
long  val;						//���صĳ���ֵ
float Newval = 0.0; 	//�����0�µ����
int a = 0; 						//���ڼ���  ��¼�������  ���ڳ�ʼ��У׼
	
//==========================================================
//	�������ƣ�	ReadCount_Init
//
//	�������ܣ�	��ʼ��ѹ��������
//
//	��ڲ�����	��
//
//	���ز�����	��
//
//	˵����		
//==========================================================	
void Pressure_Sensor_Init(void)
{
    GPIO_InitTypeDef GPIO_Initure;

    __HAL_RCC_GPIOB_CLK_ENABLE();           	//����GPIOBʱ��
	
		GPIO_Initure.Pin = GPIO_PIN_0;						//PB0
		GPIO_Initure.Mode = GPIO_MODE_OUTPUT_PP;	//�������
		GPIO_Initure.Speed = GPIO_SPEED_FREQ_LOW; //����
		HAL_GPIO_Init(GPIOB, &GPIO_Initure);
	
	  GPIO_Initure.Pin = GPIO_PIN_1;						//PB1
		GPIO_Initure.Mode = GPIO_MODE_INPUT;			//����
		GPIO_Initure.Pull = GPIO_NOPULL;					//����
		HAL_GPIO_Init(GPIOB, &GPIO_Initure);
	
		HAL_GPIO_WritePin(GPIOB,GPIO_PIN_0,GPIO_PIN_RESET);	//PA0��0   ��ʼ���ȴ�ģʽ

}

//==========================================================
//	�������ƣ�	Calibration
//
//	�������ܣ�	У׼ѹ��ֵ
//
//	��ڲ�����	����ֵ
//
//	���ز�����	��
//
//	˵����		
//==========================================================	
void Calibration(void)
{
	if((val<0 || val>0) && a<=5) 
	{
		Newval = 0-val;																					//���п���У׼
		val = 0;   																					
	}
	else val += Newval;      																	//У׼
	
	if(a>5)  a = 10;																					//����У׼��̶�a��ֵ
}

	
//==========================================================
//	�������ƣ�	ReadCount
//
//	�������ܣ�	��ȡѹ��ֵ
//
//	��ڲ�����	��
//
//	���ز�����	�������ݣ���λ g��
//
//	˵����		
//==========================================================	
unsigned long ReadCount(void)  
{ 
	a++; //�����ۼ�
	HAL_GPIO_WritePin(GPIOB, GPIO_PIN_1, GPIO_PIN_SET);	   		//DOUT=1 
	HAL_GPIO_WritePin(GPIOB, GPIO_PIN_0, GPIO_PIN_RESET);	   	//SCK=0 
	val = 0;
	
	while( HAL_GPIO_ReadPin(GPIOB,GPIO_PIN_1));  							//�ȴ�DOUT=0  
	__NOP(); 
	for(i=0;i<24;i++) 
	{ 
		HAL_GPIO_WritePin(GPIOB, GPIO_PIN_0, GPIO_PIN_SET);	   	//SCK=1 
		__NOP(); 
		if( HAL_GPIO_ReadPin(GPIOB,GPIO_PIN_1))   							//DOUT=1 
			val++; 
		val=val<<1;   
		HAL_GPIO_WritePin(GPIOB, GPIO_PIN_0, GPIO_PIN_RESET);	  //SCK=0 
		__NOP(); 

	} 
	
	HAL_GPIO_WritePin(GPIOB, GPIO_PIN_0, GPIO_PIN_SET); 			//SCK=1 
	__NOP();  
	
	HAL_GPIO_WritePin(GPIOB, GPIO_PIN_0, GPIO_PIN_RESET);			//SCK=0 
	__NOP();
	
	val = val^0x800000; 
	
	val = (val/429.4967296-19610)/1.701; 											//����ʵ���ʵ������
	
	Calibration();																						//У׼
	
	delay_ms(10);
	
	return (val);																							//����ѹ��ֵ����λg��
}  

