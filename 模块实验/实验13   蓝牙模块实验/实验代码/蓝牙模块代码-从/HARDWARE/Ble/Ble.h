#ifndef __Ble_H
#define __Ble_H
#include "stm32f1xx_hal.h"

#define AT         	 	"AT"											/*��⴮���Ƿ���������*/
#define ROLE        	"AT+ROLE=S"								/*�������ӽ�ɫ  M(��)    S(��) Ĭ��ΪS*/
#define NAME        	"AT+NAME=BaCheng"					/*�޸���������*/
#define ADDR 					"AT+ADDR=FFFFFDFAFDAF"		/*�޸�������ַ*/
#define BAUD      		"AT+BAUD=9600"						/*�޸Ĳ�����*/
#define CONT      		"AT+CONT=0"								/*����ģ���Ƿ������   0(������)  1(��������)   Ĭ�Ͽ�����*/
#define LUUID      		"AT+LUUID=1211"						/*����UUID*/

/*
*		��ʼ������HC-08����ģ��
*
*/
void HC_08_Init(void);


#endif

