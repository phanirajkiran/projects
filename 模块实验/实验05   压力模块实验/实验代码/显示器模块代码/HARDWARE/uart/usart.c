#include "stm32f1xx.h"
#include "usart.h"	
#include "Rs485.h"	
#include "TFT.h"

uint8_t weight[7] = "Weight:";		//����
uint8_t Company[1] = "g";					//��λ

#if UART1   //ʹ�ܽ���

//����1�жϷ������
//ע��,��ȡUSARTx->SR�ܱ���Ī������Ĵ���   	
unsigned char  USART1_RX_BUF[USART1_REC_LEN];     //���ջ���,���USART_REC_LEN���ֽ�.

unsigned int USART1_RX_STA=0;       							//����״̬���	  

unsigned char UART1_RxBuffer[UART1_RXBUFFERSIZE];	//HAL��ʹ�õĴ��ڽ��ջ���

UART_HandleTypeDef UART1_Handler; 								//UART���
  

//==========================================================
//	�������ƣ�	UART1_Init
//
//	�������ܣ�	����1��ʼ��
//
//	��ڲ�����	bound:������
//              
//	���ز�����	��
//
//	˵����		
//==========================================================
void UART1_Init(int bound)
{	
	//UART ��ʼ������
	UART1_Handler.Instance=USART1;					    			//USART1
	UART1_Handler.Init.BaudRate=bound;				    		//������
	UART1_Handler.Init.WordLength=UART_WORDLENGTH_8B; //�ֳ�Ϊ8λ���ݸ�ʽ
	UART1_Handler.Init.StopBits=UART_STOPBITS_1;	    //һ��ֹͣλ
	UART1_Handler.Init.Parity=UART_PARITY_NONE;		    //����żУ��λ
	UART1_Handler.Init.HwFlowCtl=UART_HWCONTROL_NONE; //��Ӳ������
	UART1_Handler.Init.Mode=UART_MODE_TX_RX;		    	//�շ�ģʽ
	HAL_UART_Init(&UART1_Handler);					    			//HAL_UART_Init()��ʹ��UART1
	
	HAL_UART_Receive_IT(&UART1_Handler, (unsigned char *)UART1_RxBuffer, UART1_RXBUFFERSIZE);//�ú����Ὺ�������жϣ���־λUART_IT_RXNE���������ý��ջ����Լ����ջ���������������
  
}


//==========================================================
//	�������ƣ�	USART1_IRQHandler
//
//	�������ܣ�	����1�жϷ������
//
//	��ڲ�����	��
//              
//	���ز�����	��
//
//	˵����		
//==========================================================
void USART1_IRQHandler(void)                	
{ 
	unsigned char Res;
	//HAL_StatusTypeDef err;

	if((__HAL_UART_GET_FLAG(&UART1_Handler,UART_FLAG_RXNE)!=RESET))  //�����ж�(���յ������ݱ�����0x0d 0x0a��β)
	{
		Res=USART1->DR; 
		if((USART1_RX_STA&0x8000)==0)			//����δ���
		{
			if(USART1_RX_STA&0x4000)				//���յ���0x0d
			{
				if(Res!=0x0a)USART1_RX_STA=0;	//���մ���,���¿�ʼ
				else USART1_RX_STA|=0x8000;		//��������� 
			}
			else //��û�յ�0X0D
			{	
				if(Res==0x0d)USART1_RX_STA|=0x4000;
				else
				{
					USART1_RX_BUF[USART1_RX_STA&0X3FFF]=Res ;
					USART1_RX_STA++;
					if(USART1_RX_STA>(USART1_REC_LEN-1))USART1_RX_STA=0;//�������ݴ���,���¿�ʼ����	  
				}		 
			}
		}   		 
	}
	HAL_UART_IRQHandler(&UART1_Handler);	
} 

#endif

#if UART2

//����2�жϷ������
//ע��,��ȡUSARTx->SR�ܱ���Ī������Ĵ���   	
unsigned char  USART2_RX_BUF[USART2_REC_LEN];     //���ջ���,���USART_REC_LEN���ֽ�.

unsigned int USART2_RX_STA=0;       							//����״̬���	  

unsigned char UART2_RxBuffer[UART2_RXBUFFERSIZE];	//HAL��ʹ�õĴ��ڽ��ջ���

UART_HandleTypeDef UART2_Handler; 								//UART���

  
//==========================================================
//	�������ƣ�	UART2_Init
//
//	�������ܣ�	����2��ʼ��
//
//	��ڲ�����	bound:������
//              
//	���ز�����	��
//
//	˵����		
//==========================================================
void UART2_Init(int bound)
{	
	//UART ��ʼ������
	UART2_Handler.Instance=USART2;					    						//USART1
	UART2_Handler.Init.BaudRate=bound;				    					//������
	UART2_Handler.Init.WordLength=UART_WORDLENGTH_8B;   		//�ֳ�Ϊ8λ���ݸ�ʽ
	UART2_Handler.Init.StopBits=UART_STOPBITS_1;	    			//һ��ֹͣλ
	UART2_Handler.Init.Parity=UART_PARITY_NONE;		    			//����żУ��λ
	UART2_Handler.Init.HwFlowCtl=UART_HWCONTROL_NONE;   		//��Ӳ������
	UART2_Handler.Init.Mode=UART_MODE_TX_RX;		    				//�շ�ģʽ
    UART2_Handler.Init.OverSampling = UART_OVERSAMPLING_16;
	HAL_UART_Init(&UART2_Handler);					    						//HAL_UART_Init()��ʹ��UART1
	
	HAL_UART_Receive_IT(&UART2_Handler, (unsigned char *)UART2_RxBuffer, UART2_RXBUFFERSIZE);//�ú����Ὺ�������жϣ���־λUART_IT_RXNE���������ý��ջ����Լ����ջ���������������
  
}

//==========================================================
//	�������ƣ�	USART2_IRQHandler
//
//	�������ܣ�	����2�жϷ������
//
//	��ڲ�����	��
//              
//	���ز�����	��
//
//	˵����		
//==========================================================
void USART2_IRQHandler(void)                	
{ 
	unsigned char Res;
//	HAL_StatusTypeDef err;

	if((__HAL_UART_GET_FLAG(&UART2_Handler,UART_FLAG_RXNE)!=RESET))  //�����ж�(���յ������ݱ�����0x0d 0x0a��β)
	{
		Res=USART2->DR; 
		if((USART2_RX_STA&0x8000)==0)			//����δ���
		{
			if(USART2_RX_STA&0x4000)				//���յ���0x0d
			{
				if(Res!=0x0a)USART2_RX_STA=0;	//���մ���,���¿�ʼ
				else USART2_RX_STA|=0x8000;		//��������� 
			}
			else 														//��û�յ�0X0D
			{	
				if(Res==0x0d)USART2_RX_STA|=0x4000;
				else
				{
					USART2_RX_BUF[USART2_RX_STA&0X3FFF]=Res ;
					USART2_RX_STA++;
					if(USART2_RX_STA>(USART2_REC_LEN-1))USART2_RX_STA=0;//�������ݴ���,���¿�ʼ����	  
				}		 
			}
		}   		 
	}
	HAL_UART_IRQHandler(&UART2_Handler);	
} 

#endif


//==========================================================
//	�������ƣ�	HAL_UART_MspInit
//
//	�������ܣ�	UART�ײ��ʼ����ʱ��ʹ�ܣ��������ã��ж�����
//
//	��ڲ�����	huart:���ھ��
//              
//	���ز�����	��
//
//	˵����		
//==========================================================
void HAL_UART_MspInit(UART_HandleTypeDef *huart)
{
    //GPIO�˿�����
	GPIO_InitTypeDef GPIO_Initure;
    
    if (huart->Instance==USART1)   									//����Ǵ���1�����д���1 MSP��ʼ��
    {
        __HAL_RCC_GPIOA_CLK_ENABLE();								//ʹ��GPIOAʱ��
        __HAL_RCC_USART1_CLK_ENABLE();							//ʹ��USART1ʱ��
        __HAL_RCC_AFIO_CLK_ENABLE();

        GPIO_Initure.Pin=GPIO_PIN_9;								//PA9
        GPIO_Initure.Mode=GPIO_MODE_AF_PP;					//�����������
        GPIO_Initure.Pull=GPIO_PULLUP;							//����
        GPIO_Initure.Speed=GPIO_SPEED_FREQ_HIGH;		//����
        HAL_GPIO_Init(GPIOA,&GPIO_Initure);	   			//��ʼ��PA9

        GPIO_Initure.Pin=GPIO_PIN_10;								//PA10
        GPIO_Initure.Mode=GPIO_MODE_AF_INPUT;				//ģʽҪ����Ϊ��������ģʽ��	
        HAL_GPIO_Init(GPIOA,&GPIO_Initure);	   			//��ʼ��PA10
        
    #if EN_USART1_RX
        HAL_NVIC_EnableIRQ(USART1_IRQn);						//ʹ��USART1�ж�ͨ��
        HAL_NVIC_SetPriority(USART1_IRQn,3,3);			//��ռ���ȼ�3�������ȼ�3
    #endif	
    }
    else if(huart->Instance==USART2)								//����Ǵ���2�����д���2 MSP��ʼ��
	{

            __HAL_RCC_GPIOA_CLK_ENABLE();						//ʹ��GPIOAʱ��
            __HAL_RCC_USART2_CLK_ENABLE();					//ʹ��USART2ʱ��
            
           // __HAL_RCC_AFIO_CLK_ENABLE();

            GPIO_Initure.Pin=GPIO_PIN_2;						//PA2
            GPIO_Initure.Mode=GPIO_MODE_AF_PP;			//�����������
            GPIO_Initure.Pull=GPIO_PULLUP;					//����
            GPIO_Initure.Speed=GPIO_SPEED_FREQ_HIGH;//����
            HAL_GPIO_Init(GPIOA,&GPIO_Initure);	   	//��ʼ��PA2

            GPIO_Initure.Pin=GPIO_PIN_3;						//PA3
            GPIO_Initure.Mode=GPIO_MODE_AF_INPUT;		//ģʽҪ����Ϊ��������ģʽ��	
            HAL_GPIO_Init(GPIOA,&GPIO_Initure);	   	//��ʼ��PA3
            
        #if EN_USART2_RX
            HAL_NVIC_EnableIRQ(USART2_IRQn);				//ʹ��USART2�ж�ͨ��
            HAL_NVIC_SetPriority(USART2_IRQn,3,3);	//��ռ���ȼ�3�������ȼ�3
        #endif	
    }
	
}



//////////////////////////////////////////////////////////////////
//�������´���,֧��printf����,������Ҫѡ��use MicroLIB	  
#if 1
#pragma import(__use_no_semihosting)             
//��׼����Ҫ��֧�ֺ���                 
struct __FILE 
{ 
	int handle; 

}; 

FILE __stdout;       
//����_sys_exit()�Ա���ʹ�ð�����ģʽ    
void _sys_exit(int x) 
{ 
	x = x; 
} 
//�ض���fputc���� 
int fputc(int ch, FILE *f)
{      
	while((USART1->SR&0X40)==0);//ѭ������,ֱ���������   
    USART1->DR = (unsigned char) ch;      
	return ch;
}
#endif 

//==========================================================
//	�������ƣ�	USART1_IRQHand
//
//	�������ܣ�	����һ485���ݴ�����
//
//	��ڲ�����	��
//              
//	���ز�����	��
//
//	˵����		
//==========================================================

void USART1_IRQHand(void)
{
	uint16_t i = 0;									//forѭ���������ʹ��
	char *strx=0;										//���նԱȽ��
	uint8_t len = 0;  							//��Ž��յ������ݳ���
	static int number = 0;					//��Ž��յ�������
	Rs485_Config(0);  							//����485����

  if(USART1_RX_STA&0x8000)
	{
		len=USART1_RX_STA&0x3fff;			//�õ��˴ν��յ������ݳ���

		strx=strstr((const char*)USART1_RX_BUF,(const char*)"->lcd");			//�ж����������Ƿ�Ϊ�����lcd������
		
		if(strx)											//�������Ϊ�����lcd��������ȡ��������ʾ
		{	
			switch(len)
			{
				case 9: 
						number = (USART1_RX_BUF[8]-0x30);
				break;
				case 10: 
						number = ((USART1_RX_BUF[9]-0x30)+(USART1_RX_BUF[8]-0x30)*10);
				break;
				case 11: 
						number = ((USART1_RX_BUF[10]-0x30) + (USART1_RX_BUF[9]-0x30)*10+(USART1_RX_BUF[8]-0x30)*100);
				break;
				case 12: 
						number = ((USART1_RX_BUF[11]-0x30)+ (USART1_RX_BUF[10]-0x30)*10 + (USART1_RX_BUF[9]-0x30)*100+(USART1_RX_BUF[8]-0x30)*1000);
				break;
			}
			LCD_ShowNum(80,50,number,4);  //������������
			
		}
		USART1_RX_STA=0;
		for(i = 0;i<200;i++){
			USART1_RX_BUF[i] = 0;						//�������
		}
	}
}

