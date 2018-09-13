#ifndef __USART_H
#define __USART_H(null)

#include "stm32f1xx.h"
#include "stdlib.h"
#include "string.h"
#include "stdio.h"

#define UART1  0
#define UART2  1

#if UART1

#define USART1_REC_LEN  			200  										//�����������ֽ��� 200
#define EN_USART1_RX 			1														//ʹ�ܣ�1��/��ֹ��0������1����
	  	
extern unsigned char  USART1_RX_BUF[USART1_REC_LEN]; 	//���ջ���,���USART_REC_LEN���ֽ�.ĩ�ֽ�Ϊ���з� 
extern unsigned int USART1_RX_STA;         						//����״̬���	
extern UART_HandleTypeDef UART1_Handler; 							//UART���

#define UART1_RXBUFFERSIZE   1 												//�����С
extern unsigned char UART1_RxBuffer[UART1_RXBUFFERSIZE];			//HAL��USART����Buffer

void USART1_IRQHand(void); 												//����1�жϷ�����

//����봮���жϽ��գ��벻Ҫע�����º궨��
void UART1_Init(int bound);

#endif



#if UART2

#define USART2_REC_LEN  	600  												//�����������ֽ��� 200
#define EN_USART2_RX 			1														//ʹ�ܣ�1��/��ֹ��0������1����
extern uint8_t USART_AT_STA;         									//ATָ�����ɱ�־λ
	  	
extern unsigned char  USART2_RX_BUF[USART2_REC_LEN]; 	//���ջ���,���USART_REC_LEN���ֽ�.ĩ�ֽ�Ϊ���з� 
extern unsigned int USART2_RX_STA;         						//����״̬���	
extern UART_HandleTypeDef UART2_Handler; 							//UART���

#define UART2_RXBUFFERSIZE   1 												//�����С
extern unsigned char UART2_RxBuffer[UART2_RXBUFFERSIZE];//HAL��USART����Buffer
void USART2_IRQHand(void);														//���ڶ��жϴ�����

uint8_t* atk_8266_check_cmd(uint8_t *str);						//ATK-ESP8266���������,�����յ���Ӧ��
void atk_8266_send_cmd(uint8_t *cmd,uint8_t *ack,uint16_t waittime);	//��ATK-ESP8266��������

//����봮���жϽ��գ��벻Ҫע�����º궨��
void UART2_Init(int bound);

#endif


#endif



