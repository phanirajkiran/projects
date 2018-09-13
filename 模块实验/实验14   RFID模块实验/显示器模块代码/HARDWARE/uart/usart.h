#ifndef __USART_H
#define __USART_H
#include "stdlib.h"
#include "string.h"
#include "stdio.h"
#include "stm32f1xx.h"


#define UART1  1
#define UART2  0



#if UART1

#define USART1_REC_LEN  			200  											//�����������ֽ��� 200
#define EN_USART1_RX 			1															//ʹ�ܣ�1��/��ֹ��0������1����

extern int number1,number2,number3;											//��Ž��յ�������
	  	
extern unsigned char  USART1_RX_BUF[USART1_REC_LEN]; 		//���ջ���,���USART_REC_LEN���ֽ�.ĩ�ֽ�Ϊ���з� 
extern unsigned int USART1_RX_STA;         							//����״̬���	
extern UART_HandleTypeDef UART1_Handler; 								//UART���

#define UART1_RXBUFFERSIZE   1 													//�����С
extern unsigned char UART1_RxBuffer[UART1_RXBUFFERSIZE];//HAL��USART����Buffer

extern uint8_t pitch[6];			//pitch
extern uint8_t roll[6];				//roll
extern uint8_t yaw[6];				//yaw

void USART1_IRQHand(void); 		//����1������
void TFT_Update(void); 				//TFT��ʾ���ݸ���

//����봮���жϽ��գ��벻Ҫע�����º궨��
void UART1_Init(int bound);

extern uint8_t IC_Card_Data[ ];
extern uint8_t UserInputData[ ] ;
extern uint8_t UserInputLenght;

#endif



#if UART2

#define USART2_REC_LEN  		200  		//�����������ֽ��� 200
#define EN_USART2_RX 			1			//ʹ�ܣ�1��/��ֹ��0������1����
	  	
extern unsigned char  USART2_RX_BUF[USART2_REC_LEN]; 	//���ջ���,���USART_REC_LEN���ֽ�.ĩ�ֽ�Ϊ���з� 
extern unsigned int USART2_RX_STA;         			//����״̬���	
extern UART_HandleTypeDef UART2_Handler; 	//UART���

#define UART2_RXBUFFERSIZE   1 					//�����С
extern unsigned char UART2_RxBuffer[UART2_RXBUFFERSIZE];			//HAL��USART����Buffer

//����봮���жϽ��գ��벻Ҫע�����º궨��
void UART2_Init(int bound);

#endif






#endif

