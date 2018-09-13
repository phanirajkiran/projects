#ifndef __TOUCH_H
#define __TOUCH_H	
#include "stm32f1xx_hal.h"
#include "stm32f1xx.h"
/* touch panel interface define */
#define  CMD_RDX  0xD0	 //����IC�����������
#define  CMD_RDY  0x90
//IO����
//sbit DCLK	   =    P1^6;   
//sbit CS        =    P1^4;
//sbit DIN       =    P3^0;	
//sbit DOUT      =    P3^1;																						   
//sbit Penirq    =    P3^4;   //��ⴥ������Ӧ�ź�

struct tp_pix_
{
	unsigned int x;
	unsigned int y;
};
struct tp_pixu32_
{
	int x;
	int y;
};
extern struct tp_pix_  tp_pixad,tp_pixlcd;	 //��ǰ���������ADֵ,ǰ�������������ֵ   
extern unsigned int vx,vy;  //�������ӣ���ֵ����1000֮���ʾ���ٸ�ADֵ����һ�����ص�
extern unsigned int chx,chy;//Ĭ�����ص�����Ϊ0ʱ��AD��ʼֵ
unsigned char tpstate(void);
void spistar(void);  
void Touch_Adjust(void);
void point(void); //��ͼ����
unsigned int ReadFromCharFrom7843();         //SPI ������
#endif  
	 
	 



