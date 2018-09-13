#include "Martix_Key.h"	
#include "Rs485.h"
#include "delay.h"

//==========================================================
//	�������ƣ�	KEY_Init
//
//	�������ܣ�	��ʼ������
//
//	��ڲ�����	��
//
//	���ز�����	��
//
//	˵����		
//==========================================================
void KEY_Init(void)
{
	  GPIO_InitTypeDef GPIO_Initure;
	
			/* GPIO Ports Clock Enable */
		__HAL_RCC_GPIOA_CLK_ENABLE();			//����GPIOAʱ��
		__HAL_RCC_GPIOB_CLK_ENABLE();			//����GPIOBʱ��
	
		GPIO_Initure.Pin = GPIO_PIN_4|GPIO_PIN_5|GPIO_PIN_6|GPIO_PIN_7;		//PA4��PA5��PA6��PA7
		GPIO_Initure.Mode = GPIO_MODE_OUTPUT_PP;//�������
		GPIO_Initure.Speed = GPIO_SPEED_FREQ_LOW; //����
		HAL_GPIO_Init(GPIOA, &GPIO_Initure);
	
	  /*Configure GPIO pins : PB0 PB1 PB13 PB14 */
		GPIO_Initure.Pin = GPIO_PIN_0|GPIO_PIN_1|GPIO_PIN_13|GPIO_PIN_14;
		GPIO_Initure.Mode = GPIO_MODE_INPUT;   //��������
		GPIO_Initure.Pull = GPIO_PULLUP;			//����
		HAL_GPIO_Init(GPIOB, &GPIO_Initure);
	
		HAL_GPIO_WritePin(GPIOA,GPIO_PIN_4|GPIO_PIN_5|GPIO_PIN_6|GPIO_PIN_7,GPIO_PIN_RESET);	//PA4��5��6��7��0

}


//==========================================================
//	�������ƣ�	KEY_ConFig
//
//	�������ܣ�	���հ�������
//
//	��ڲ�����	��
//
//	���ز�����	��
//
//	˵����		
//==========================================================
void KEY_ConFig(void)
{
	static uint8_t cnt = 0;  	//��������
    static uint8_t fig1 = 0;  	//�������±�־λ
    static uint8_t fig2 = 0;  	//�������±�־λ	
    static uint8_t fig3 = 0;  	//�������±�־λ
    static uint8_t fig4 = 0;  	//�������±�־λ
	HAL_Delay(10);
	switch(cnt%4){
    case 0:
      {
        HAL_GPIO_WritePin(GPIOA,GPIO_PIN_4|GPIO_PIN_5|GPIO_PIN_6|GPIO_PIN_7,GPIO_PIN_SET);
        HAL_GPIO_WritePin(GPIOA,GPIO_PIN_4,GPIO_PIN_RESET);
				
/*
*				key 7 push down		
*/
        if(!HAL_GPIO_ReadPin(GPIOB, GPIO_PIN_0)){
					
					delay_ms(50);  						//��ʱ����
					
					if(!HAL_GPIO_ReadPin(GPIOB, GPIO_PIN_0) && fig1 == 0){
					//key 7 push down
							Rs485_Config(1);			//����485Ϊ����ģʽ
//							printf("mrk->zbm,%d\r\n",7);  	//��������7
							HAL_Delay(10);
							Rs485_Config(0);			//����485Ϊ�ȴ�����ģʽ
							fig1 = 1;							//�������±�־λ
					}
					
/*
*				key 4 push down
*/
        }else if(!HAL_GPIO_ReadPin(GPIOB, GPIO_PIN_1)){
          
					delay_ms(50);  						//��ʱ����
					
					if(!HAL_GPIO_ReadPin(GPIOB, GPIO_PIN_1) && fig1 == 0){
					//key 4 push down
							Rs485_Config(1);			//����485Ϊ����ģʽ
							printf("mrk->zbm,%d\r\n",4);  	//��������4
							HAL_Delay(10);
							Rs485_Config(0);			//����485Ϊ�ȴ�����ģʽ
							fig1 = 1;							//�������±�־λ
					}
					
/*
*				key 1 push down
*/					
        }else if(!HAL_GPIO_ReadPin(GPIOB, GPIO_PIN_13)){
          
					delay_ms(50);  						//��ʱ����
					
					if(!HAL_GPIO_ReadPin(GPIOB, GPIO_PIN_13) && fig1 == 0){
					//key 1 push down
							Rs485_Config(1);			//����485Ϊ����ģʽ
							printf("mrk->zbm,%d\r\n",1);  	//��������1
							HAL_Delay(10);
							Rs485_Config(0);			//����485Ϊ�ȴ�����ģʽ
							fig1 = 1;							//�������±�־λ
					}
					
/*
*				key Enter push down
*/		
        }else if(!HAL_GPIO_ReadPin(GPIOB, GPIO_PIN_14)){
          
					delay_ms(50);  						//��ʱ����
					
					if(!HAL_GPIO_ReadPin(GPIOB, GPIO_PIN_14) && fig1 == 0){
					//key Enter push down
							Rs485_Config(1);			//����485Ϊ����ģʽ
//							printf("mrk->zbm,%d\r\n",10);  	//��������10
							HAL_Delay(10);
							Rs485_Config(0);			//����485Ϊ�ȴ�����ģʽ
							fig1 = 1;							//�������±�־λ
					}
					
        }else{  
             fig1 = 0;
        }
        
        break;
      }
    case 1:
      {
        HAL_GPIO_WritePin(GPIOA,GPIO_PIN_4|GPIO_PIN_5|GPIO_PIN_6|GPIO_PIN_7,GPIO_PIN_SET);
        HAL_GPIO_WritePin(GPIOA,GPIO_PIN_5,GPIO_PIN_RESET);
				
/*
*				key 8 push down
*/	
        if(!HAL_GPIO_ReadPin(GPIOB, GPIO_PIN_0)){
          
					delay_ms(50);   						//��ʱ����
					
					if(!HAL_GPIO_ReadPin(GPIOB, GPIO_PIN_0) && fig2 == 0){
					//key 8 push down
							Rs485_Config(1);			//����485Ϊ����ģʽ
//							printf("mrk->zbm,%d\r\n",8);  	//��������8
							HAL_Delay(10);
							Rs485_Config(0);			//����485Ϊ�ȴ�����ģʽ
							fig2 = 1;							//�������±�־λ
					}
					
/*
*				key 5 push down
*/		
        }else if(!HAL_GPIO_ReadPin(GPIOB, GPIO_PIN_1)){
          
					delay_ms(50);  						//��ʱ����
					
					if(!HAL_GPIO_ReadPin(GPIOB, GPIO_PIN_1) && fig2 == 0){
					//key 5 push down
							Rs485_Config(1);			//����485Ϊ����ģʽ
//							printf("mrk->zbm,%d\r\n",5);  	//��������5
							HAL_Delay(10);
							Rs485_Config(0);			//����485Ϊ�ȴ�����ģʽ
							fig2 = 1;							//�������±�־λ
					}
					
/*
*				key 2 push down
*/		
        }else if(!HAL_GPIO_ReadPin(GPIOB, GPIO_PIN_13)){
          
					delay_ms(50);  						//��ʱ����
					
					if(!HAL_GPIO_ReadPin(GPIOB, GPIO_PIN_13) && fig2 == 0){
					//key 2 push down
							Rs485_Config(1);			//����485Ϊ����ģʽ
							printf("mrk->zbm,%d\r\n",2);  	//��������2
							HAL_Delay(10);
							Rs485_Config(0);			//����485Ϊ�ȴ�����ģʽ
							fig2 = 1;							//�������±�־λ
					}
					
 /*
*				key 0 push down
*/	         
        }else if(!HAL_GPIO_ReadPin(GPIOB, GPIO_PIN_14)){
          
					delay_ms(50);   						//��ʱ����
					
					if(!HAL_GPIO_ReadPin(GPIOB, GPIO_PIN_14) && fig2 == 0){
					//key 0 push down
							Rs485_Config(1);			//����485Ϊ����ģʽ
//								printf("mrk->zbm,%d\r\n",0);  	//��������0
							HAL_Delay(10);
							Rs485_Config(0);			//����485Ϊ�ȴ�����ģʽ
							fig2 = 1;							//�������±�־λ
					}
					
        }else{
                fig2 = 0;
        }
        break;
      }
    case 2:
      {
        HAL_GPIO_WritePin(GPIOA,GPIO_PIN_4|GPIO_PIN_5|GPIO_PIN_6|GPIO_PIN_7,GPIO_PIN_SET);
        HAL_GPIO_WritePin(GPIOA,GPIO_PIN_6,GPIO_PIN_RESET);
				
 /*
*				key 9 push down
*/	    
        if(!HAL_GPIO_ReadPin(GPIOB, GPIO_PIN_0)){
          
					delay_ms(50);   						//��ʱ����
					
					if(!HAL_GPIO_ReadPin(GPIOB, GPIO_PIN_0) && fig3 == 0){
					//key 9 push down
							Rs485_Config(1);			//����485Ϊ����ģʽ
//							printf("mrk->zbm,%d\r\n",9);  	//��������9
							HAL_Delay(10);
							Rs485_Config(0);			//����485Ϊ�ȴ�����ģʽ
							fig3 = 1;							//�������±�־λ
					}
					
 /*
*				key 6 push down
*/	          
        }else if(!HAL_GPIO_ReadPin(GPIOB, GPIO_PIN_1)){
          
					delay_ms(50);   						//��ʱ����
					
					if(!HAL_GPIO_ReadPin(GPIOB, GPIO_PIN_1) && fig3 == 0){
					//key 6 push down
							Rs485_Config(1);			//����485Ϊ����ģʽ
//							printf("mrk->zbm,%d\r\n",6);  	//��������6
							HAL_Delay(10);
							Rs485_Config(0);			//����485Ϊ�ȴ�����ģʽ
							fig3 = 1;							//�������±�־λ
					}
							
 /*
*				key 3 push down
*/	 	
        }else if(!HAL_GPIO_ReadPin(GPIOB, GPIO_PIN_13)){
          
					delay_ms(50);   						//��ʱ����
					
					if(!HAL_GPIO_ReadPin(GPIOB, GPIO_PIN_13) && fig3 == 0){
					//key 6 push down
							Rs485_Config(1);			//����485Ϊ����ģʽ
							printf("mrk->zbm,%d\r\n",3);  	//��������3
							HAL_Delay(10);
							Rs485_Config(0);			//����485Ϊ�ȴ�����ģʽ
							fig3 = 1;							//�������±�־λ
					}

 /*
*				key Canel push down
*/	           
        }else if(!HAL_GPIO_ReadPin(GPIOB, GPIO_PIN_14)){
          
					delay_ms(50);   						//��ʱ����
					
					if(!HAL_GPIO_ReadPin(GPIOB, GPIO_PIN_14) && fig3 == 0){
					//key Canel push down
							Rs485_Config(1);			//����485Ϊ����ģʽ
//							printf("mrk->zbm,%d\r\n",11);  	//��������11
							HAL_Delay(10);
							Rs485_Config(0);			//����485Ϊ�ȴ�����ģʽ
							fig3 = 1;							//�������±�־λ
					}

        }else{
              fig3 = 0;

        }
        
        break;
      }
    case 3:
      {
        HAL_GPIO_WritePin(GPIOA,GPIO_PIN_4|GPIO_PIN_5|GPIO_PIN_6|GPIO_PIN_7,GPIO_PIN_SET);
        HAL_GPIO_WritePin(GPIOA,GPIO_PIN_7,GPIO_PIN_RESET);
				
 /*
*				key up push down
*/	  
        if(!HAL_GPIO_ReadPin(GPIOB, GPIO_PIN_0)){
          //up push down

 /*
*				key down push down
*/	            
        }else if(!HAL_GPIO_ReadPin(GPIOB, GPIO_PIN_1)){
          //down push down
          HAL_GPIO_WritePin(GPIOA,GPIO_PIN_15,GPIO_PIN_RESET);
					
 /*
*				key left push down
*/	  
        }else if(!HAL_GPIO_ReadPin(GPIOB, GPIO_PIN_13)){
          //left push donw
 
 /*
*				key right push down
*/	  					
        }else if(!HAL_GPIO_ReadPin(GPIOB, GPIO_PIN_14)){
          //right 16 push down
        }else{
        }
        break;
      }
    }
    cnt++;   //�����ۼ�
}

    

