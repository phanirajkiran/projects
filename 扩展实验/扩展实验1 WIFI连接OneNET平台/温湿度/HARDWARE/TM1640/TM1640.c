#include "TM1640.h"	

void TM1640_Init(void)
{
	  GPIO_InitTypeDef GPIO_Initure;
    __HAL_RCC_GPIOA_CLK_ENABLE();								//����GPIOAʱ��
	
		GPIO_Initure.Pin = GPIO_PIN_4|GPIO_PIN_5;		//PA0
		GPIO_Initure.Mode = GPIO_MODE_OUTPUT_PP;		//���
		GPIO_Initure.Speed = GPIO_SPEED_FREQ_LOW;		//����
		HAL_GPIO_Init(GPIOA, &GPIO_Initure);
	
		HAL_GPIO_WritePin(GPIOA,GPIO_PIN_4|GPIO_PIN_5, GPIO_PIN_RESET);
}


/******									TM1640									******/

unsigned char TM164_DATA[14] = {0x3f,0x06,0x5b,0x4f,0x66,0x6d,0x7d,0x07,0x7f,0x6f,0x00,0X39,0X76,0X80};//0~9,�հף�C,H,��;
unsigned char TM164_SIG[4] = {0x01,0x02,0x04,0x08};

//==========================================================
//	�������ƣ�	start
//
//	�������ܣ�	TM1640��ʼ
//
//	��ڲ�����	��
//
//	���ز�����	��
//
//	˵����		
//==========================================================
void start(void)
{
		sda_H;
		scl_H;
		HAL_Delay(2);
		sda_L;
		HAL_Delay(2);
		scl_L;
		HAL_Delay(2);
}

//==========================================================
//	�������ƣ�	stop
//
//	�������ܣ�	TM1640ֹͣ
//
//	��ڲ�����	��
//
//	���ز�����	��
//
//	˵����		
//==========================================================
void stop(void)
{
		sda_L;
		scl_H;
		HAL_Delay(2);
		sda_H;
		HAL_Delay(2);
		scl_L;
		HAL_Delay(2);
}


//==========================================================
//	�������ƣ�	write
//
//	�������ܣ�	��������
//
//	��ڲ�����	��
//
//	���ز�����	��
//
//	˵����		
//==========================================================
void write(unsigned char date)
{
		unsigned char i,aa;
		aa=date;
		sda_L;
		scl_L;
		for(i=0;i<8;i++)
		{
				scl_L;
				if(aa&0x01)
				{
					sda_H;
					HAL_Delay(2);
				}
				else
				{
					sda_L
					HAL_Delay(2);
				}
				scl_H;
				aa=aa>>1;
		}
		scl_L;

		sda_L;

}

//==========================================================
//	�������ƣ�	init_tm1640
//
//	�������ܣ�	��ʼ��TM1640
//
//	��ڲ�����	��
//
//	���ز�����	��
//
//	˵����		
//==========================================================
void init_tm1640(void)

{
		sda_H;
		scl_H;
		start();
		write(SET_DATA_ORDER);		//�������ݣ�0x40,0x44�ֱ��Ӧ��ַ�Զ���һ�͹̶���ַģʽ
		stop();
		start();
		write(SET_DISPLAY);				//������ʾ������ʾ0x88, 0x89, 0x8a, 0x8b, 0x8c, 0x8d, 0x8e, 0x8f�ֱ��Ӧ������
															//------------------1/16, 2/16, 4/16, 10/16, 11/16, 12/16, 13/16, 14/16

		//0x80����ʾ
		stop();

}

//==========================================================
//	�������ƣ�	init_tm1640_NEW
//
//	�������ܣ�	����TM1640
//
//	��ڲ�����	��
//
//	���ز�����	��
//
//	˵����		
//==========================================================
void init_tm1640_NEW(void)
{
	unsigned char i;
		sda_H;
		scl_H;
	
		start();
		write(SET_DATA_ORDER);	//�������ݣ�0x40,0x44�ֱ��Ӧ��ַ�Զ���һ�͹̶���ַģʽ
		stop();
	
		start();
		write(0x00);					//���õ�ַ
		for(i=0;i<4;i++)
			{
				write(TM164_DATA[i]);
			}
		stop();
	
		start();
		write(SET_DISPLAY);	//������ʾ������ʾ0x88, 0x89, 0x8a, 0x8b, 0x8c, 0x8d, 0x8e, 0x8f�ֱ��Ӧ������
												//------------------1/16, 2/16, 4/16, 10/16, 11/16, 12/16, 13/16, 14/16
		//0x80����ʾ
		stop();

}

//==========================================================
//	�������ƣ�	send_LED_Display
//
//	�������ܣ�	��ʾ
//
//	��ڲ�����	��
//
//	���ز�����	��
//
//	˵����		
//==========================================================
void send_LED_Display(unsigned char address,uint16_t data,unsigned char type)  
{
		unsigned char SEG_1,SEG_2,SEG_3,SEG_4;
		if(type == 1)//��ʾ�¶ȵ�����
		{
			SEG_4 = 11;
		}
		else if(type == 2)//��ʾʪ�ȵ�����
		{
			SEG_4 = 12;
		}
		else if(type == 3)//��ʾ��ǿ������
		{
			SEG_4 = data%10;
		}
		else if(type == 4)//�������ģ����ʾ
		{
			SEG_1 =  data/1000;
			SEG_2 = (data/100)%10;
			SEG_3 = (data/10)%10;
			SEG_4 = data%10;
		}
		if(data > 1000)
		{          
			SEG_1 = data/1000;
			SEG_2 = (data/100)%10;
			SEG_3 = (data/10)%10;
		}
		else if(data > 9)
		{
			SEG_1 = data/10; 
			SEG_2 = data%10;
			SEG_3 = 10;
		}
		else
		{
			SEG_1 = 0x00;
			SEG_2 = data;
			SEG_3 = 10;
		}
		
		sda_H;
		scl_H;
	
		start();
		write(SET_DATA_ORDER);	//�������ݣ�0x40,0x44�ֱ��Ӧ��ַ�Զ���һ�͹̶���ַģʽ
		stop();
		
		start();
		write(address);	//������ʼ��ַ
		write(TM164_DATA[SEG_1]);
		write(TM164_DATA[SEG_2]);
		write(TM164_DATA[SEG_3]);
		write(TM164_DATA[SEG_4]);
		
		stop();
		
				start();
		write(SET_DISPLAY);	//������ʾ������ʾ0x88, 0x89, 0x8a, 0x8b, 0x8c, 0x8d, 0x8e, 0x8f�ֱ��Ӧ������
		//------------------1/16, 2/16, 4/16, 10/16, 11/16, 12/16, 13/16, 14/16
		//0x80����ʾ
		stop();
}

/******�Զ���һģʽ*****/

void send_z(uint8_t address,uint8_t date)
{
		unsigned char i;
		start();
		write(address);	//������ʼ��ַ
		for(i=0;i<4;i++)
		{
			write(TM164_DATA[i]);
		}
		stop();
}

/******�̶���ַģʽ*****/

void send(uint8_t address, uint8_t date)

{
	start();
	write(address);	//����ʾ���ݶ�Ӧ��ַ
	write(date);	//��BYTE��ʾ����
	stop();
}



/*   								TM1604����   								*/

