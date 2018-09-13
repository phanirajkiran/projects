#include "stm32f1xx_hal.h"  
#include "Usart.h"					   
#include "stdio.h"	 
#include "stdarg.h"	 
#include "string.h"	 
#include "delay.h"
#include "math.h"
#include "GPS.h"

//==========================================================
//	�������ƣ�	NMEA_Pow
//
//	�������ܣ�	bufָ��������У����ҵ�cx����,�����Ų����شˡ�,�����ŵ����buf��ַƫ��λ��
//
//	��ڲ�����	u8 *buf�����룬������
//              u8 cx �� ���룬ָ��
//	���ز�����	�������buf��ַƫ��λ��
//
//	˵����		
//==========================================================						  
u8 NMEA_Comma_Pos(u8 *buf,u8 cx)
{	 		    
	u8 *p=buf;
	while(cx)
	{		 
		if(*buf=='*'||*buf<' '||*buf>'z')return 0XFF;//����'*'���߷Ƿ��ַ�,�򲻴��ڵ�cx������
		if(*buf==',')cx--;
		buf++;
	}
	return buf-p;	 
}
//==========================================================
//	�������ƣ�	NMEA_Pow
//
//	�������ܣ�	��m^n�η���mΪunsigned char
//
//	��ڲ�����	u8 m�����룬������
//              u8    n �����룬ָ��
//	���ز�����	����ת����Ľ��
//
//	˵����		
//==========================================================
u32 NMEA_Pow(u8 m,u8 n)
{
	u32 result=1;	 
	while(n--)result*=m;    
	return result;
}
//==========================================================
//	�������ƣ�	pow_f
//
//	�������ܣ�	��m^n�η���mΪ����������
//
//	��ڲ�����	float m�����룬������
//              u8    n �����룬ָ��
//	���ز�����	����ת����Ľ��
//
//	˵����		
//==========================================================
float pow_f(float m,u8 n)
{
	float result = 1;	 
	while(n--)
    {
        result*=m; 
    }        
	return result;
}
//==========================================================
//	�������ƣ�	NMEA_Str2num
//
//	�������ܣ�	���ַ��������ݣ�ת����int�͡�����������(����)����*��(����)
//
//	��ڲ�����	u8 *buf�����룬��ת�����ַ�����ָ�롣
//              u8 *dx �����������С����֮���λ��
//	���ز�����	����ת����Ľ��
//
//	˵����		
//==========================================================
int NMEA_Str2num(u8 *buf,u8*dx)
{
	u8 *p=buf;
	u32 ires=0,fres=0;
	u8 ilen=0,flen=0,i;
	u8 mask=0;
	int res;
	while(1) //�õ�������С���ĳ���
	{
		if(*p=='-'){mask|=0X02;p++;}//�Ǹ���
		if(*p==','||(*p=='*'))break;//����������
		if(*p=='.'){mask|=0X01;p++;}//����С������
		else if(*p>'9'||(*p<'0'))		//�зǷ��ַ�
		{	
			ilen=0;
			flen=0;
			break;
		}	
		if(mask&0X01)flen++;
		else ilen++;
		p++;
	}
	if(mask&0X02)buf++;	//ȥ������
	for(i=0;i<ilen;i++)	//�õ�������������
	{  
		ires+=NMEA_Pow(10,ilen-1-i)*(buf[i]-'0');
	}
	if(flen>5)flen=5;		//���ȡ5λС��
	*dx=flen;	 					//С����λ��
	for(i=0;i<flen;i++)	//�õ�С����������
	{  
		fres+=NMEA_Pow(10,flen-1-i)*(buf[ilen+1+i]-'0');
	} 
	res=ires*NMEA_Pow(10,flen)+fres;
	if(mask&0X02)res=-res;		   
	return res;
}
//==========================================================
//	�������ƣ�	GPS_PosInfoConvert
//
//	�������ܣ�	��GPS������γ�ȡ����ȵĸ�ʽ,ת�ɵ�λΪ�ȵĸ�ʽ
//
//	��ڲ���    double pos �����룬λ����Ϣ��
//	���ز�����	����0��������Ч������1��������Ч
//
//	GPS�����ݸ�ʽ��DDMM.MMMMMM
//��ȡ����GPS֡���ݱ����ǣ�$GNRMC,112317.000,A,3438.1633,N,11224.4992,E,0.19,186.95,240916,,,A*7D
//˵��
//����112��24.4992��
//γ��34��38.1633��
//תΪ�Զ�Ϊ��λDD.DDDDD,�����Ҫת��
//����Ϊ 112+24.4992/60 = 112.40832
//γ��Ϊ 34+38.1633/60 = 34.636055
//==========================================================
double GPS_PosInfoConvert(double pos)
{//pos=12345,78901234
  
    double temp1,temp2;
    uint32_t    i,j;
    
    temp1  = pos;            //temp1 = 12345.78901234
    j     = (uint32_t)temp1; //j     = 12345
    temp1 = temp1/100;       //temp1 = 123.4578901234
    i    = (uint32_t)temp1;  //i     = 123
    i    = i*100;            //i     = 12300;
    temp2 = pos - i;         //temp2 = 12345.78901234 - 12300 = 45.78901234
    
    //j/100    = 123
    //temp2/60 = 45.78901234/60
    //123 + (45.78901234)/60
    return (j/100 + temp2/60);
    
}
//==========================================================
//	�������ƣ�	GPS_GGA_Analysis
//
//	�������ܣ�	����GGA��ʽ���ݣ����������gpsx�ṹ���С�
//
//	��ڲ�����	GPS_MsgTypeDef *gpsx��������������������ݡ�
//              u8 *buf             �����룬���յ���GGA��ʽ�����ݡ�
//	���ز�����	����0��������Ч������1��������Ч
//
//	˵����		���������Ч��ԭ���豸���ڿ���֮���1�����ڣ����������޷����յ��ź�
//==========================================================
uint8_t GPS_GGA_Analysis(GPS_MsgTypeDef *gpsx,u8 *buf)
{
    uint8_t ret = 0;
    
	u8 *p1,dx,i=0,j=0;			 
	u8 posx;     
	p1 = buf;
    
	posx=NMEA_Comma_Pos(p1,6);								
    GPS_GGA_Msg.MsgSta = NMEA_Str2num(p1+posx,&dx);	//�õ������Ƿ���Ч
    
    if(GPS_GGA_Msg.MsgSta == 1)
    {//��λ��Ч,�����λ����Ϣ��ȡ
//******************��ȡγ����Ϣ*****************************************************<   
//��������Ϣ��ʽ�е��ַ�����12345.7890123��ת��double �������� 12345.7890123       
        posx            = NMEA_Comma_Pos(p1,2);	
        j = 1;
        GPS_GGA_Msg.latitude = 0;        
        while(buf[posx + i] != '.')//��ȡ.��ǰ��12345
        {
            GPS_GGA_Msg.latitude = GPS_GGA_Msg.latitude*10;
            GPS_GGA_Msg.latitude = GPS_GGA_Msg.latitude + buf[posx + i] - 0x30;
            i++;
        }
        i++;
        while(buf[posx + i] != ',')//��ȡ.�ź��7890123
        {
            GPS_GGA_Msg.latitude = GPS_GGA_Msg.latitude + (buf[posx + i] - 0x30)*pow_f(0.1,j);
            i++;
            j++;
        }        
        GPS_GGA_Msg.latitude = GPS_PosInfoConvert(GPS_GGA_Msg.latitude);//���е�λת��
        
        posx=NMEA_Comma_Pos(p1,3);	
        GPS_GGA_Msg.nshemi    = buf[posx];                //��/�����ʶ N/S
//******************��ȡγ����Ϣ*****************************************************>

//******************��ȡ������Ϣ*****************************************************< 
////��������Ϣ��ʽ�е��ַ�����12345.7890123��ת��double �������� 12345.7890123            
        posx=NMEA_Comma_Pos(p1,4);	
        i = 0;
        j = 1;
        GPS_GGA_Msg.longitude = 0;
        while(buf[posx + i] != '.')//��ȡ.��ǰ��12345
        {
            GPS_GGA_Msg.longitude = GPS_GGA_Msg.longitude*10;
            GPS_GGA_Msg.longitude = GPS_GGA_Msg.longitude + buf[posx + i] - 0x30;
            i++;
        }
        i++;
        while(buf[posx + i] != ',')//��ȡ.�ź��7890123
        {
            GPS_GGA_Msg.longitude = GPS_GGA_Msg.longitude + (buf[posx + i] - 0x30)*pow_f(0.1,j);
            i++;
            j++;
        }  
        
        GPS_GGA_Msg.longitude = GPS_PosInfoConvert(GPS_GGA_Msg.longitude);//���е�λת��
        
        posx=NMEA_Comma_Pos(p1,5);	
         GPS_GGA_Msg.ewhemi    = buf[posx];                //��/�����ʶ   E/S
//******************��ȡ������Ϣ*****************************************************>
        
        posx=NMEA_Comma_Pos(p1,7);								
        GPS_GGA_Msg.PossLocationNum  = NMEA_Str2num(p1+posx,&dx); //�õ����ڶ�λ��������   
        ret  = 1;
    }
    return ret;    
}






