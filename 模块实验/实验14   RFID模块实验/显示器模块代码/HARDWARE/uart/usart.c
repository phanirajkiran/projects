#include "stm32f1xx.h"
#include "usart.h"	
#include "Rs485.h"
#include "delay.h"
#include "TFT.h"

uint8_t pitch[6] = 		"pitch:";					//pitch
uint8_t roll[6] = 		"roll :";					//roll
uint8_t yaw[6] = 			"y a w:";					//yaw

uint8_t ffhh[2] = 			" -";					//yaw
uint8_t ffhh2[2] = 			"  ";					//yaw


int number1 = 0,number2 = 0,number3 = 0;					//��Ž��յ�������

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
	UART1_Handler.Instance=USART1;					    //USART1
	UART1_Handler.Init.BaudRate=bound;				    //������
	UART1_Handler.Init.WordLength=UART_WORDLENGTH_8B;   //�ֳ�Ϊ8λ���ݸ�ʽ
	UART1_Handler.Init.StopBits=UART_STOPBITS_1;	    //һ��ֹͣλ
	UART1_Handler.Init.Parity=UART_PARITY_NONE;		    //����żУ��λ
	UART1_Handler.Init.HwFlowCtl=UART_HWCONTROL_NONE;   //��Ӳ������
	UART1_Handler.Init.Mode=UART_MODE_TX_RX;		    //�շ�ģʽ
	HAL_UART_Init(&UART1_Handler);					    //HAL_UART_Init()��ʹ��UART1
	
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
uint8_t GetMsg = 0;
void USART1_IRQHandler(void)                	
{ 
	unsigned char Res;
	//HAL_StatusTypeDef err;

	if((__HAL_UART_GET_FLAG(&UART1_Handler,UART_FLAG_RXNE)!=RESET))  //�����ж�(���յ������ݱ�����0x0d 0x0a��β)
	{
		Res=USART1->DR; 
        __HAL_UART_CLEAR_FLAG(&UART1_Handler,UART_FLAG_RXNE);
        USART1_RX_BUF[USART1_RX_STA] = Res;
        USART1_RX_STA++;
#if 1  //���շ���1      
        if((USART1_RX_STA>2)&&(USART1_RX_BUF[USART1_RX_STA-2] == '\r')&&(USART1_RX_BUF[USART1_RX_STA-1] == '\n'))
        {//�յ���\r\n������һ������һ���������
            GetMsg        = 1;
            //Rs485_Config(1);
        }  
#else  //���շ��� 2      
        switch(USART1_RX_STA)
        {
            case 0:
                 USART1_RX_STA = (USART1_RX_BUF[USART1_RX_STA] == 'r')?1:0;
                 break;
            case 1:
                  USART1_RX_STA = (USART1_RX_BUF[USART1_RX_STA] == 'f')?2:0;
                  break;
            case 2:
                 USART1_RX_STA = (USART1_RX_BUF[USART1_RX_STA] == 'i')?3:0;
                break;
            case 3:
                 USART1_RX_STA = (USART1_RX_BUF[USART1_RX_STA] == 'd')?4:0;
                break;
            case 4:
                 USART1_RX_STA = (USART1_RX_BUF[USART1_RX_STA] == '-')?5:0;
                break;
            case 5:
                 USART1_RX_STA = (USART1_RX_BUF[USART1_RX_STA] == '>')?6:0;
                break;            
            default:
                 USART1_RX_STA++;
                if((USART1_RX_STA>2)&&(USART1_RX_BUF[USART1_RX_STA-2] == '\r')&&(USART1_RX_BUF[USART1_RX_STA-1] == '\n'))
                {
                    GetMsg        = 1;
                    Rs485_Config(1);
                }  
                break;
        }	
#endif
	}	
} 

#endif

#if UART2

//����2�жϷ������
//ע��,��ȡUSARTx->SR�ܱ���Ī������Ĵ���   	
unsigned char  USART2_RX_BUF[USART2_REC_LEN];     //���ջ���,���USART_REC_LEN���ֽ�.

unsigned int USART2_RX_STA=0;       //����״̬���	  

unsigned char UART2_RxBuffer[UART2_RXBUFFERSIZE];//HAL��ʹ�õĴ��ڽ��ջ���

UART_HandleTypeDef UART2_Handler; //UART���

  
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
	UART2_Handler.Instance=USART2;					    //USART1
	UART2_Handler.Init.BaudRate=bound;				    //������
	UART2_Handler.Init.WordLength=UART_WORDLENGTH_8B;   //�ֳ�Ϊ8λ���ݸ�ʽ
	UART2_Handler.Init.StopBits=UART_STOPBITS_1;	    //һ��ֹͣλ
	UART2_Handler.Init.Parity=UART_PARITY_NONE;		    //����żУ��λ
	UART2_Handler.Init.HwFlowCtl=UART_HWCONTROL_NONE;   //��Ӳ������
	UART2_Handler.Init.Mode=UART_MODE_TX_RX;		    //�շ�ģʽ
    UART2_Handler.Init.OverSampling = UART_OVERSAMPLING_16;
	HAL_UART_Init(&UART2_Handler);					    //HAL_UART_Init()��ʹ��UART1
	
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
		if((USART2_RX_STA&0x8000)==0)//����δ���
		{
			if(USART2_RX_STA&0x4000)//���յ���0x0d
			{
				if(Res!=0x0a)USART2_RX_STA=0;//���մ���,���¿�ʼ
				else USART2_RX_STA|=0x8000;	//��������� 
			}
			else //��û�յ�0X0D
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
    
    if (huart->Instance==USART1)   //����Ǵ���1�����д���1 MSP��ʼ��
    {
        __HAL_RCC_GPIOA_CLK_ENABLE();			//ʹ��GPIOAʱ��
        __HAL_RCC_USART1_CLK_ENABLE();			//ʹ��USART1ʱ��
        __HAL_RCC_AFIO_CLK_ENABLE();

        GPIO_Initure.Pin=GPIO_PIN_9;			//PA9
        GPIO_Initure.Mode=GPIO_MODE_AF_PP;		//�����������
        GPIO_Initure.Pull=GPIO_PULLUP;			//����
        GPIO_Initure.Speed=GPIO_SPEED_FREQ_HIGH;//����
        HAL_GPIO_Init(GPIOA,&GPIO_Initure);	   	//��ʼ��PA9

        GPIO_Initure.Pin=GPIO_PIN_10;			//PA10
        GPIO_Initure.Mode=GPIO_MODE_AF_INPUT;	//ģʽҪ����Ϊ��������ģʽ��	
        HAL_GPIO_Init(GPIOA,&GPIO_Initure);	   	//��ʼ��PA10
        
    #if EN_USART1_RX
        HAL_NVIC_EnableIRQ(USART1_IRQn);				//ʹ��USART1�ж�ͨ��
        HAL_NVIC_SetPriority(USART1_IRQn,3,3);			//��ռ���ȼ�3�������ȼ�3
    #endif	
    }
    else if(huart->Instance==USART2)//����Ǵ���2�����д���2 MSP��ʼ��
	{

            __HAL_RCC_GPIOA_CLK_ENABLE();			//ʹ��GPIOAʱ��
            __HAL_RCC_USART2_CLK_ENABLE();			//ʹ��USART2ʱ��
            
           // __HAL_RCC_AFIO_CLK_ENABLE();

            GPIO_Initure.Pin=GPIO_PIN_2;			//PA2
            GPIO_Initure.Mode=GPIO_MODE_AF_PP;		//�����������
            GPIO_Initure.Pull=GPIO_PULLUP;			//����
            GPIO_Initure.Speed=GPIO_SPEED_FREQ_HIGH;//����
            HAL_GPIO_Init(GPIOA,&GPIO_Initure);	   	//��ʼ��PA2

            GPIO_Initure.Pin=GPIO_PIN_3;			//PA3
            GPIO_Initure.Mode=GPIO_MODE_AF_INPUT;	//ģʽҪ����Ϊ��������ģʽ��	
            HAL_GPIO_Init(GPIOA,&GPIO_Initure);	   	//��ʼ��PA3
            
        #if EN_USART2_RX
            HAL_NVIC_EnableIRQ(USART2_IRQn);				//ʹ��USART2�ж�ͨ��
            HAL_NVIC_SetPriority(USART2_IRQn,3,3);			//��ռ���ȼ�3�������ȼ�3
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
#define MSG_HEAD_LEN   9
const uint8_t MSG_HEAD[MSG_HEAD_LEN]="rfid->lcd";
uint8_t IC_Card_Data[17]  = {0};
uint8_t UserInputData[17] = {0};
uint8_t UserInputLenght = 0;
uint8_t UpdataGUI = 1;
void USART1_IRQHand(void)
{
    uint8_t i=0,pos;
	uint8_t len = 0;  								//��Ž��յ������ݳ���
	Rs485_Config(0);  								//����485����

    if(GetMsg == 1)
    {
        GetMsg = 0;

        for(i=0;i < MSG_HEAD_LEN;i++)
        {//�������ݵ�ͷ�Ƿ�ΪMSG_HEADָ����
            if(USART1_RX_BUF[i] != MSG_HEAD[i])
            {
                break;
            }
        }
        
        pos = i;
        if(i == MSG_HEAD_LEN)//���i����MSG_HEAD_LEN�������յ�������ͷ��MSG_HEADָ�����ͬ����������ݷ���									
        {	
            UpdataGUI = 1;
            if(USART1_RX_BUF[pos+1] == 'I')
            {
                memset((void*)UserInputData,'*',16);
                for(i=0;i<16;i++)
                {
                    if(USART1_RX_BUF[pos+3+i] != '\r')
                    {
                        UserInputData[i]=USART1_RX_BUF[pos+3+i];  
                        
                    }
                    else
                    {
                        break;
                    }
                }
                UserInputLenght = i;                
            }
            if(USART1_RX_BUF[pos+1] == 'N')
            {
                for(i=0;i<16;i++)
                {
                    IC_Card_Data[i]=USART1_RX_BUF[pos+3+i];  
                }                
            }            
        }
        USART1_RX_STA = 0;
        GetMsg = 0;
        Rs485_Config(0);
    }
}


//==========================================================
//	�������ƣ�	TFT_Update
//
//	�������ܣ�	������ʾ������
//
//	��ڲ�����	��
//              
//	���ز�����	��
//
//	˵����	UpdataGUI ����0����������Ҫ�������ݣ�
//          UpdataGUI ����1��������Ҫ�������ݣ�	
//����LCD_ShowString()�������ʾ��Ϣ�ǰ��ַ�������ʽ����Ҫ��֤����ʾ��Ϣ�洢����������
//���һλΪ�㡣��������Ҫ��ʾ abc,
//UserInputData[0]='a',UserInputData[1]='b',UserInputData[3]='c',UserInputData[4]=0;
//==========================================================
void TFT_Update(void)
{			
    if(UpdataGUI == 0)														
    {
        return;
    }

    UpdataGUI = 0;                            //����

    LCD_ShowString(75,50,UserInputData); 	 //����Ļ������(75,50)����ʾUserInputData(�û����������)	 		

    if(strlen((char*)IC_Card_Data))
    {
            LCD_ShowString(75,100,(const uint8_t*)"                 "); //������Ļ��				
            LCD_ShowString(75,100,(const uint8_t*)IC_Card_Data); 	    //��ʾ������IC�������š�			
    }	
}

