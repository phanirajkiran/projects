#include "SHT20.h"	

SHT2x_PARAM g_sht2x_param;

//==========================================================
//	�������ƣ�	SHT2x_Delay
//
//	�������ܣ�	��ʱ����
//
//	��ڲ�����	ʱ��
//
//	���ز�����	��
//
//	˵����		
//==========================================================
void SHT2x_Delay(u32 n)
{
    u8 i;
    
    while(n--)
    {
        for(i = 0; i < 100; i++)
        {
            __NOP();
        }
    }
}


//==========================================================
//	�������ƣ�	SHT2x_Init
//
//	�������ܣ�	��ʼ��IIC
//
//	��ڲ�����	ʱ��
//
//	���ز�����	��
//
//	˵����		
//==========================================================
void SHT2x_Init(void)
{
    GPIO_InitTypeDef GPIO_InitStructure;

    GPIO_InitStructure.Pin =  SHT2x_SCL_PIN | SHT2x_SDA_PIN;
    GPIO_InitStructure.Mode = GPIO_MODE_OUTPUT_OD;
    GPIO_InitStructure.Speed = GPIO_SPEED_FREQ_LOW;
    HAL_GPIO_Init(SHT2x_I2C_PORT, &GPIO_InitStructure);

    SHT2x_SCL_HIGH();
    SHT2x_SDA_HIGH();

    SHT2x_Delay(80);

    SHT2x_SoftReset();
}

//==========================================================
//	�������ƣ�	SHT2x_SCL_OUTPUT
//
//	�������ܣ�	IICʱ�������ģʽ
//
//	��ڲ�����	ʱ��
//
//	���ز�����	��
//
//	˵����		
//==========================================================
void SHT2x_SCL_OUTPUT(void)
{
    GPIO_InitTypeDef GPIO_InitStructure;


    GPIO_InitStructure.Pin =  SHT2x_SCL_PIN;
    GPIO_InitStructure.Mode = GPIO_MODE_OUTPUT_OD;
    GPIO_InitStructure.Speed = GPIO_SPEED_FREQ_LOW;
    HAL_GPIO_Init(SHT2x_I2C_PORT, &GPIO_InitStructure);
}

//==========================================================
//	�������ƣ�	SHT2x_SCL_INPUT
//
//	�������ܣ�	IICʱ��������ģʽ
//
//	��ڲ�����	ʱ��
//
//	���ز�����	��
//
//	˵����		
//==========================================================
void SHT2x_SCL_INPUT(void)
{
    GPIO_InitTypeDef GPIO_InitStructure;


    GPIO_InitStructure.Pin =  SHT2x_SCL_PIN;
    GPIO_InitStructure.Mode = GPIO_MODE_INPUT;
    HAL_GPIO_Init(SHT2x_I2C_PORT, &GPIO_InitStructure);
}

//==========================================================
//	�������ƣ�	SHT2x_SDA_OUTPUT
//
//	�������ܣ�	IIC���������ģʽ 
//
//	��ڲ�����	ʱ��
//
//	���ز�����	��
//
//	˵����		
//==========================================================
void SHT2x_SDA_OUTPUT(void)
{
    GPIO_InitTypeDef GPIO_InitStructure;

    GPIO_InitStructure.Pin =  SHT2x_SDA_PIN;
    GPIO_InitStructure.Mode = GPIO_MODE_OUTPUT_OD;				//���
    GPIO_InitStructure.Speed = GPIO_SPEED_FREQ_LOW;				//����
    HAL_GPIO_Init(SHT2x_I2C_PORT, &GPIO_InitStructure);
}

//==========================================================
//	�������ƣ�	SHT2x_SDA_INPUT
//
//	�������ܣ�	IIC����������ģʽ
//
//	��ڲ�����	ʱ��
//
//	���ز�����	��
//
//	˵����		
//==========================================================
void SHT2x_SDA_INPUT(void)
{
    GPIO_InitTypeDef GPIO_InitStructure;

    GPIO_InitStructure.Pin =  SHT2x_SDA_PIN;
    GPIO_InitStructure.Mode = GPIO_MODE_INPUT;			//����ģʽ
    HAL_GPIO_Init(SHT2x_I2C_PORT, &GPIO_InitStructure);
}

//==========================================================
//	�������ƣ�	SHT2x_I2cStartCondition
//
//	�������ܣ�	IIC����ʱ��
//
//	��ڲ�����	ʱ��
//
//	���ز�����	��
//
//	˵����		
//==========================================================
void SHT2x_I2cStartCondition(void)
{
    SHT2x_SCL_OUTPUT();			//ʱ�������ģʽ
    SHT2x_SDA_OUTPUT();			//���������ģʽ
    
    SHT2x_SDA_HIGH();				//����������
    SHT2x_SCL_HIGH();				//����ʱ����
    SHT2x_SDA_LOW();				//����������
    SHT2x_Delay(30);
    SHT2x_SCL_LOW();				//����ʱ����
    SHT2x_Delay(30);
}

//==========================================================
//	�������ƣ�	SHT2x_I2cStopCondition
//
//	�������ܣ�	IICֹͣʱ�� 
//
//	��ڲ�����	ʱ��
//
//	���ز�����	��
//
//	˵����		
//==========================================================
void SHT2x_I2cStopCondition(void)
{
    SHT2x_SCL_OUTPUT();
    SHT2x_SDA_OUTPUT();
    
    SHT2x_SDA_LOW();
    SHT2x_SCL_LOW();
    SHT2x_SCL_HIGH();
    SHT2x_Delay(30);
    SHT2x_SDA_HIGH();
    SHT2x_Delay(30);
}

//==========================================================
//	�������ƣ�	SHT2x_I2cAcknowledge
//
//	�������ܣ�	IIC ACKӦ��
//
//	��ڲ�����	ʱ��
//
//	���ز�����	��
//
//	˵����		
//==========================================================
void SHT2x_I2cAcknowledge(void)
{
    SHT2x_SCL_OUTPUT();
    SHT2x_SDA_OUTPUT();

    SHT2x_SDA_LOW();
    
    SHT2x_SCL_HIGH();
    SHT2x_Delay(80);
    SHT2x_SCL_LOW();   
    SHT2x_Delay(80);
}

//==========================================================
//	�������ƣ�	SHT2x_I2cNoAcknowledge
//
//	�������ܣ�	IIC ��ACKӦ��
//
//	��ڲ�����	ʱ��
//
//	���ز�����	��
//
//	˵����		
//==========================================================
void SHT2x_I2cNoAcknowledge(void)
{
    SHT2x_SCL_OUTPUT();
    SHT2x_SDA_OUTPUT();

    SHT2x_SDA_HIGH();
    
    SHT2x_SCL_HIGH();
    SHT2x_Delay(80);
    SHT2x_SCL_LOW();   
    SHT2x_Delay(80);
}

//==========================================================
//	�������ƣ�	SHT2x_I2cReadByte
//
//	�������ܣ�	IIC ��ȡ����
//
//	��ڲ�����	ʱ��
//
//	���ز�����	��
//
//	˵����		
//==========================================================
u8 SHT2x_I2cReadByte(void)
{
    u8 i, val = 0;


    SHT2x_SCL_OUTPUT();  //����Ϊ���ģʽ
    SHT2x_SDA_OUTPUT();

    SHT2x_SDA_HIGH();					//����������
    
    SHT2x_SDA_INPUT();				//����������Ϊ����ģʽ
        
    for(i = 0; i < 8; i++)
    {
        val <<= 1; 
        
        SHT2x_SCL_HIGH();  	 	//����ʱ����
        
        if(Bit_SET == SHT2x_SDA_STATE())   //��������߱�����   ���Ӽ����׷� ���Ͷ���˿�׷�  ��ĭѿ�˳���   ���ݳ���
        {
            val |= 0x01;			//��ȡ�������е�����
        }
        
        SHT2x_SCL_LOW();      //����ʱ����
    }

    SHT2x_SDA_OUTPUT();  			//���������ģʽ

    SHT2x_SDA_HIGH();					//����������
    
    return (val);							//���ض�ȡ��������
}

//==========================================================
//	�������ƣ�	SHT2x_I2cWriteByte
//
//	�������ܣ�	IIC д������
//
//	��ڲ�����	ʱ��
//
//	���ز�����	��
//
//	˵����		
//==========================================================
u8 SHT2x_I2cWriteByte(u8 byte)
{
    u8 i, ack;


    SHT2x_SCL_OUTPUT();
    SHT2x_SDA_OUTPUT();		//����Ϊ���ģʽ
    
    for(i = 0; i < 8; i++)
    {
        if(byte & 0x80)   //һ�ζ�ȡ���λ ��������
        {
            SHT2x_SDA_HIGH();
        }
        else 
        {
            SHT2x_SDA_LOW();
        }
        
        SHT2x_SCL_HIGH();  //ʱ��������
        SHT2x_Delay(80);
        SHT2x_SCL_LOW();   //ʱ��������
        SHT2x_Delay(80);
        
        byte <<= 1;
    }

    SHT2x_SDA_INPUT();  //����������ģʽ
    
    SHT2x_SCL_HIGH();		//ʱ��������
    
    if(Bit_SET == SHT2x_SDA_STATE())   //������ܵ������߸��ź�  ACK����
    {
        ack = ACK_ERROR;
    }
    else
    {
        ack = ACK_OK;
    }
    
    SHT2x_SCL_LOW();    //����ʱ����

    SHT2x_SDA_OUTPUT();	

    SHT2x_SDA_HIGH();		//����������
    
    return (ack);
}

//==========================================================
//	�������ƣ�	SHT2x_MeasureTempHM
//
//	�������ܣ�	����ģʽ�¶ȶ�ȡ
//
//	��ڲ�����	ʱ��
//
//	���ز�����	��
//
//	˵����		
//==========================================================
float SHT2x_MeasureTempHM(void)
{
    float TEMP;
    u8 tmp1, tmp2;
    u16 ST;
    

    SHT2x_SCL_OUTPUT();  													//ʱ��������Ϊ���ģʽ
     
    SHT2x_I2cStartCondition();    								//����IIC����״̬                       
    SHT2x_I2cWriteByte(I2C_ADR_W);								//д��0x80 ��ʾ��ʼд����
    SHT2x_I2cWriteByte(TRIG_TEMP_MEASUREMENT_HM); //����ģʽ����¶�

    SHT2x_I2cStartCondition();										//����IIC����״̬      
    SHT2x_I2cWriteByte(I2C_ADR_R);								//д��0x81 ��ʾ��ʼ������

    SHT2x_SCL_HIGH();   													//����ʱ����

    SHT2x_SCL_INPUT();														//����Ϊ����ģʽ

    while(Bit_RESET == SHT2x_SCL_STATE())  				//�����ʱ���߱��õ�
    {
        SHT2x_Delay(20);
    }
    
    tmp1 = SHT2x_I2cReadByte(); //��ȡ����
    SHT2x_I2cAcknowledge();			//ACKӦ��
    tmp2 = SHT2x_I2cReadByte();	//��ȡ����
    SHT2x_I2cNoAcknowledge();		//��Ӧ��
    SHT2x_I2cStopCondition();		//�ر�IIC
    
    ST = (tmp1 << 8) | (tmp2 << 0);
    ST &= ~0x0003;
    TEMP = ((float)ST * 0.00268127) - 46.85;  //ת�����õ�������

    SHT2x_SCL_OUTPUT();  	//ʱ�������

    return (TEMP);	    	//�����¶�ֵ
}

//==========================================================
//	�������ƣ�	SHT2x_MeasureHumiHM
//
//	�������ܣ�	����ģʽʪ�ȶ�ȡ
//
//	��ڲ�����	ʱ��
//
//	���ز�����	��
//
//	˵����		
//==========================================================
float SHT2x_MeasureHumiHM(void)
{
    float HUMI;
    u8 tmp1, tmp2;    
    u16 SRH;


    SHT2x_SCL_OUTPUT();
    
    SHT2x_I2cStartCondition();                               
    SHT2x_I2cWriteByte(I2C_ADR_W);
    SHT2x_I2cWriteByte(TRIG_HUMI_MEASUREMENT_HM);

    SHT2x_I2cStartCondition();
    SHT2x_I2cWriteByte(I2C_ADR_R);

    SHT2x_SCL_HIGH();

    SHT2x_SCL_INPUT();

    while(Bit_RESET == SHT2x_SCL_STATE())
    {
        SHT2x_Delay(20);
    }
    
    tmp1 = SHT2x_I2cReadByte();
    SHT2x_I2cAcknowledge();
    tmp2 = SHT2x_I2cReadByte();
    SHT2x_I2cNoAcknowledge();
    SHT2x_I2cStopCondition();
    
    SRH = (tmp1 << 8) | (tmp2 << 0);
    SRH &= ~0x0003;
    HUMI = ((float)SRH * 0.00190735) - 6;

    SHT2x_SCL_OUTPUT();

    return (HUMI);
}

//==========================================================
//	�������ƣ�	SHT2x_MeasureTempPoll
//
//	�������ܣ�	������ģʽ�¶ȶ�ȡ 
//
//	��ڲ�����	ʱ��
//
//	���ز�����	��
//
//	˵����		
//==========================================================
float SHT2x_MeasureTempPoll(void)
{
    float TEMP;
    u8 ack, tmp1, tmp2;
    u16 ST;
    
    SHT2x_I2cStartCondition();                            
    SHT2x_I2cWriteByte(I2C_ADR_W);
    SHT2x_I2cWriteByte(TRIG_TEMP_MEASUREMENT_POLL);

    do {
        SHT2x_Delay(20);               
        SHT2x_I2cStartCondition();
        ack = SHT2x_I2cWriteByte(I2C_ADR_R);
    } while(ACK_ERROR == ack);
    
    tmp1 = SHT2x_I2cReadByte();
    SHT2x_I2cAcknowledge();
    tmp2 = SHT2x_I2cReadByte();
    SHT2x_I2cNoAcknowledge();
    SHT2x_I2cStopCondition();
    
    ST = (tmp1 << 8) | (tmp2 << 0);
    ST &= ~0x0003;
    TEMP = ((float)ST * 0.00268127) - 46.85;

    return (TEMP);	  
}

//==========================================================
//	�������ƣ�	SHT2x_MeasureHumiPoll
//
//	�������ܣ�	������ģʽʪ�ȶ�ȡ 
//
//	��ڲ�����	ʱ��
//
//	���ز�����	��
//
//	˵����		
//==========================================================
float SHT2x_MeasureHumiPoll(void)
{
    float HUMI;
    u8 ack, tmp1, tmp2;    
    u16 SRH;
    
    SHT2x_I2cStartCondition();                               
    SHT2x_I2cWriteByte(I2C_ADR_W);
    SHT2x_I2cWriteByte(TRIG_HUMI_MEASUREMENT_POLL);
    
    do {
        SHT2x_Delay(20);
        SHT2x_I2cStartCondition();
        ack = SHT2x_I2cWriteByte(I2C_ADR_R);
    } while(ACK_ERROR == ack);
    
    tmp1 = SHT2x_I2cReadByte();
    SHT2x_I2cAcknowledge();
    tmp2 = SHT2x_I2cReadByte();
    SHT2x_I2cNoAcknowledge();
    SHT2x_I2cStopCondition();
    
    SRH = (tmp1 << 8) | (tmp2 << 0);
    SRH &= ~0x0003;
    HUMI = ((float)SRH * 0.00190735) - 6;

    return (HUMI);
}

//==========================================================
//	�������ƣ�	SHT2x_ReadUserReg
//
//	�������ܣ�	��ȡ����
//
//	��ڲ�����	ʱ��
//
//	���ز�����	��
//
//	˵����		
//==========================================================
u8 SHT2x_ReadUserReg(void)    
{
    u8 reg;
  
    SHT2x_I2cStartCondition();                 
    SHT2x_I2cWriteByte(I2C_ADR_W);
    SHT2x_I2cWriteByte(USER_REG_R);
    SHT2x_I2cStartCondition(); 
    SHT2x_I2cWriteByte(I2C_ADR_R);
    reg = SHT2x_I2cReadByte();
    SHT2x_I2cNoAcknowledge();
    SHT2x_I2cStopCondition();
    
    return (reg); 
}

//==========================================================
//	�������ƣ�	SHT2x_WriteUserReg
//
//	�������ܣ�	����ACK����
//
//	��ڲ�����	ʱ��
//
//	���ز�����	��
//
//	˵����		
//==========================================================
u8 SHT2x_WriteUserReg(u8 reg)
{
    u8 ack;
    
    SHT2x_I2cStartCondition();
    SHT2x_I2cWriteByte(I2C_ADR_W);
    SHT2x_I2cWriteByte(USER_REG_W);
    ack = SHT2x_I2cWriteByte(reg);
    SHT2x_I2cStopCondition();  
    
    return (ack);
}

//==========================================================
//	�������ƣ�	SHT2x_SoftReset
//
//	�������ܣ�	��λ
//
//	��ڲ�����	ʱ��
//
//	���ز�����	��
//
//	˵����		
//==========================================================
void SHT2x_SoftReset(void)
{
    SHT2x_I2cStartCondition();
    SHT2x_I2cWriteByte(I2C_ADR_W);
    SHT2x_I2cWriteByte(SOFT_RESET);
    SHT2x_I2cStopCondition();

    SHT2x_Delay(80);
}

//==========================================================
//	�������ƣ�	SHT2x_GetSerialNumber
//
//	�������ܣ�	���к�
//
//	��ڲ�����	ʱ��
//
//	���ز�����	��
//
//	˵����		
//==========================================================
void SHT2x_GetSerialNumber(u8 *buf)
{
    /* Read from memory location 1 */
    SHT2x_I2cStartCondition();
    SHT2x_I2cWriteByte(I2C_ADR_W);//I2C address
    SHT2x_I2cWriteByte(0xFA); 		//Command for readout on-chip memory
    SHT2x_I2cWriteByte(0x0F); 		//on-chip memory address
    SHT2x_I2cStartCondition();
    SHT2x_I2cWriteByte(I2C_ADR_R);//I2C address
    buf[5] = SHT2x_I2cReadByte(); //Read SNB_3
    SHT2x_I2cAcknowledge();
    SHT2x_I2cReadByte(); 					//Read CRC SNB_3 (CRC is not analyzed)
    SHT2x_I2cAcknowledge();
    buf[4] = SHT2x_I2cReadByte(); //Read SNB_2
    SHT2x_I2cAcknowledge();
    SHT2x_I2cReadByte(); 					//Read CRC SNB_2 (CRC is not analyzed)
    SHT2x_I2cAcknowledge();
    buf[3] = SHT2x_I2cReadByte(); //Read SNB_1
    SHT2x_I2cAcknowledge();
    SHT2x_I2cReadByte(); 					//Read CRC SNB_1 (CRC is not analyzed)
    SHT2x_I2cAcknowledge();
    buf[2] = SHT2x_I2cReadByte(); //Read SNB_0
    SHT2x_I2cAcknowledge();
    SHT2x_I2cReadByte(); 					//Read CRC SNB_0 (CRC is not analyzed)
    SHT2x_I2cNoAcknowledge();
    SHT2x_I2cStopCondition();

    /* Read from memory location 2 */
    SHT2x_I2cStartCondition();
    SHT2x_I2cWriteByte(I2C_ADR_W); 	//I2C address
    SHT2x_I2cWriteByte(0xFC); 			//Command for readout on-chip memory
    SHT2x_I2cWriteByte(0xC9); 			//on-chip memory address
    SHT2x_I2cStartCondition();
    SHT2x_I2cWriteByte(I2C_ADR_R); 	//I2C address
    buf[1] = SHT2x_I2cReadByte(); 	//Read SNC_1
    SHT2x_I2cAcknowledge();
    buf[0] = SHT2x_I2cReadByte(); 	//Read SNC_0
    SHT2x_I2cAcknowledge();
    SHT2x_I2cReadByte(); 						//Read CRC SNC0/1 (CRC is not analyzed)
    SHT2x_I2cAcknowledge();
    buf[7] = SHT2x_I2cReadByte(); 	//Read SNA_1
    SHT2x_I2cAcknowledge();
    buf[6] = SHT2x_I2cReadByte(); 	//Read SNA_0
    SHT2x_I2cAcknowledge();
    SHT2x_I2cReadByte(); 						//Read CRC SNA0/1 (CRC is not analyzed)
    SHT2x_I2cNoAcknowledge();
    SHT2x_I2cStopCondition();
}

//==========================================================
//	�������ƣ�	SHT2x_GetTempHumi
//
//	�������ܣ�	�õ������� 
//
//	��ڲ�����	ʱ��
//
//	���ز�����	��
//
//	˵����		
//==========================================================
void SHT2x_GetTempHumi(void)
{   
    g_sht2x_param.TEMP_HM = SHT2x_MeasureTempHM();			//����ģʽ�µ��¶�����
    g_sht2x_param.HUMI_HM = SHT2x_MeasureHumiHM(); 			//����ģʽ�µ�ʪ������

    g_sht2x_param.TEMP_POLL = SHT2x_MeasureTempPoll();  //������ģʽ�µ��¶�����
    g_sht2x_param.HUMI_POLL = SHT2x_MeasureHumiPoll();	//������ģʽ�µ�ʪ������
    
    SHT2x_GetSerialNumber(g_sht2x_param.SerialNumber);	//���к�
}



