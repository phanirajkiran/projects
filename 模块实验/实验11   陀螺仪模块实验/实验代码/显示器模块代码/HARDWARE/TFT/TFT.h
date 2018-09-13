#ifndef __TFT__H
#define __TFT__H
#include "stm32f1xx_hal.h"
#include "stm32f1xx.h"
#include "font.h"

#define u8 			uint8_t
#define u16 		uint16_t
#define u32 		uint32_t


#define LCD_REST_H 	HAL_GPIO_WritePin(GPIOA,GPIO_PIN_1,GPIO_PIN_SET);
#define LCD_SDI_H  	HAL_GPIO_WritePin(GPIOA,GPIO_PIN_7,GPIO_PIN_SET);
#define LCD_SCK_H  	HAL_GPIO_WritePin(GPIOA,GPIO_PIN_5,GPIO_PIN_SET);
#define LCD_CS_H   	HAL_GPIO_WritePin(GPIOA,GPIO_PIN_0,GPIO_PIN_SET);
#define LCD_DC_H   	HAL_GPIO_WritePin(GPIOB,GPIO_PIN_0,GPIO_PIN_SET);

#define LCD_REST_L 	HAL_GPIO_WritePin(GPIOA,GPIO_PIN_1,GPIO_PIN_RESET);
#define LCD_SDI_L  	HAL_GPIO_WritePin(GPIOA,GPIO_PIN_7,GPIO_PIN_RESET);
#define LCD_SCK_L  	HAL_GPIO_WritePin(GPIOA,GPIO_PIN_5,GPIO_PIN_RESET);
#define LCD_CS_L   	HAL_GPIO_WritePin(GPIOA,GPIO_PIN_0,GPIO_PIN_RESET);
#define LCD_DC_L   	HAL_GPIO_WritePin(GPIOB,GPIO_PIN_0,GPIO_PIN_RESET);

extern  u16 BACK_COLOR,POINT_COLOR;   	//����ɫ������ɫ

u16  LCD_ReadPoint(u16 x,u16 y); 				//����

void Lcd_Init(void); 
void LCD_Clear(u16 Color);
void Address_set(unsigned int x1,unsigned int y1,unsigned int x2,unsigned int y2);
void LCD_WR_DATA8(char da);
void LCD_WR_DATA(int da);
void LCD_WR_REG(char da);
void TFT_Init(void);

void LCD_DrawPoint(u16 x,u16 y);		//����
void LCD_DrawPoint_big(u16 x,u16 y);//��һ�����
void LCD_UI(void);									//UI����
void Draw_Circle(u16 x0,u16 y0,u8 r);
void LCD_DrawLine(u16 x1, u16 y1, u16 x2, u16 y2);
void LCD_DrawRectangle(u16 x1, u16 y1, u16 x2, u16 y2);		   
void LCD_Fill(u16 xsta,u16 ysta,u16 xend,u16 yend,u16 color);
void LCD_ShowChar(u16 x,u16 y,u8 num,u8 mode);			//��ʾһ���ַ�
void LCD_ShowNum(u16 x,u16 y,u32 num,u8 len);				//��ʾ����
void LCD_Show2Num(u16 x,u16 y,u16 num,u8 len);			//��ʾ2������
void LCD_ShowString(u16 x,u16 y,const u8 *p);		 		//��ʾһ���ַ���,16����
 
void showhanzi(unsigned int x,unsigned int y,unsigned char index);

 //����LCD�ĳߴ�	
#define LCD_W 240
#define LCD_H 320

//������ɫ
#define WHITE         	 	0xFFFF
#define BLACK         	 	0x0000	  
#define BLUE         	 		0x001F  
#define BRED             	0XF81F
#define GRED 			 				0XFFE0
#define GBLUE			 				0X07FF
#define RED           	 	0xF800
#define MAGENTA       	 	0xF81F
#define GREEN         	 	0x07E0
#define CYAN          	 	0x7FFF
#define YELLOW        	 	0xFFE0
#define BROWN 			 			0XBC40 	//��ɫ
#define BRRED 			 			0XFC07 	//�غ�ɫ
#define GRAY  			 			0X8430 	//��ɫ
//GUI��ɫ

#define DARKBLUE      	 	0X01CF	//����ɫ
#define LIGHTBLUE      	 	0X7D7C	//ǳ��ɫ  
#define GRAYBLUE       	 	0X5458 	//����ɫ
//������ɫΪPANEL����ɫ 
 
#define LIGHTGREEN     		0X841F 	//ǳ��ɫ
#define LGRAY 			 			0XC618 	//ǳ��ɫ(PANNEL),���屳��ɫ

#define LGRAYBLUE        	0XA651 	//ǳ����ɫ(�м����ɫ)
#define LBBLUE           	0X2B12 	//ǳ����ɫ(ѡ����Ŀ�ķ�ɫ)

#endif
