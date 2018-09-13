#include "stm32f1xx.h"
#include "delay.h"
#include "MPU6050.h"
#include "Usart.h"
#include "Rs485.h"
#include "math.h"
#include "inv_mpu.h"
#include "inv_mpu_dmp_motion_driver.h"
/**
************************************************************
************************************************************
************************************************************
*
*	���ߣ� 		����˳ǿƼ�
*
*	���ڣ� 		2018-01-01
*
*	�汾�� 		V1.0
*
*	˵���� 		�����ǿ⺯������ʵ��-HAL��汾
*
*	�޸ļ�¼��	
************************************************************
************************************************************
************************************************************
**/

int main(void)
{ 
	float pitch,roll,yaw; 		//ŷ����
	int number1 = 0,number2 = 0,number3 = 0;
	HAL_Init();             	//��ʼ��HAL��   
  Rs485_Init();  						//��ʼ��485
	UART1_Init(115200);				//��ʼ������1
	
	if(mpu_dmp_init()) 
	{
			delay_ms(1000);
      mpu_dmp_init();	
	}	
	while(1)
	{
		if(mpu_dmp_get_data(&pitch,&roll,&yaw)==0)
		{
				
			number1 = pitch/1;
			Rs485_Config(1); 									//485����ģʽ
			printf("pit->lcd%d\r\n",number1);	//�����ݷ��͵�485������
			delay_ms(2);
			Rs485_Config(0); 									//485�ȴ�ģʽ
			
			delay_ms(2);

			number2 = roll/1;
			Rs485_Config(1); 									//485����ģʽ
			printf("rol->lcd%d\r\n",number2);	//�����ݷ��͵�485������
			delay_ms(2);
			Rs485_Config(0); 									//485�ȴ�ģʽ
			
			delay_ms(2);
			
			number3 = yaw/1;
			Rs485_Config(1); 									//485����ģʽ
			printf("yaw->lcd%d\r\n",number3);	//�����ݷ��͵�485������
			delay_ms(2);
			Rs485_Config(0); 									//485�ȴ�ģʽ
			
			delay_ms(2);
		}            
	}

}


