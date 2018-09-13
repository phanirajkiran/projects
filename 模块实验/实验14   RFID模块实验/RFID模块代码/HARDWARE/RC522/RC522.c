#include "stm32f1xx.h"
#include "RC522.h"
#include "delay.h"
#include "stdio.h"
#include "stdlib.h"
#include "string.h"
#include "Rs485.h"	
static void RC522_SPI_Config( void );




//==========================================================
//	�������ƣ�	RC522_Init
//
//	�������ܣ�	RC522��ʼ������
//
//	��ڲ�����	��
//
//	���ز�����	��
//
//	˵����		
//==========================================================
void RC522_Init ( void )
{
	RC522_SPI_Config ();
	
	macRC522_Reset_Disable();
	
	macRC522_CS_Disable();
	
	PcdReset ();
	
	M500PcdConfigISOType ( 'A' );//���ù���ģʽ
	
}
//==========================================================
//	�������ƣ�	IC_test
//
//	�������ܣ�	��IC��
//
//	��ڲ�����	��
//
//	���ز�����	��
//
//	˵����		
//==========================================================
int icd  = 0;
unsigned char tests[300];
uint8_t IC_Card_Exist = 0;
unsigned char pk[6] ={0xff,0xff,0xff,0xff,0xff,0xff};     
unsigned char ucArray_ID [ 10 ] = {0,0,0,0};//�Ⱥ���IC�������ͺ�UID(IC�����к�)
extern uint8_t SendBuf[ ];
void IC_Card_Search ( void )
{
    char cStr [ 30 ];
    uint8_t i=0;
    unsigned char ucStatusReturn;  //����״̬
    
    unsigned char date1[16] = {0x00};
    unsigned char res[16]  ="WANGYUNJIANG";

    if ((ucStatusReturn = PcdRequest ( PICC_REQALL, ucArray_ID ))!= MI_OK )//Ѱ��
    {
        ucStatusReturn = PcdRequest ( PICC_REQALL, ucArray_ID );//��ʧ���ٴ�Ѱ��
    }

    if ((ucStatusReturn == MI_OK )&&(IC_Card_Exist == 0))
    {
        if (PcdAnticoll(ucArray_ID) == MI_OK)  //����ײ�����ж��ſ������д��������Χʱ������ͻ���ƻ������ѡ��һ�Ž��в�����
            {               
                if (PcdSelect(ucArray_ID) == MI_OK)//ѡ��ucArray_ID�Ŀ�
                {
                    IC_Card_Exist = 1;
                    if (PcdAuthState(0x61,0x5,pk,ucArray_ID) == MI_OK)//����Կ�����Ȩ  
                    {
                        if (PcdRead(0x5,date1) == MI_OK )
                        {
                            memset((void*)SendBuf,0,16);
                            for(i = 0;i < 16;i ++)
                            {
                                SendBuf[i] = date1[i] + 0x30;
                            }
                            Rs485_Config(1);
                            printf("rfid->lcd,N,%s\r\n",SendBuf);
                            delay_ms(10);
                            Rs485_Config(0);
                        }
                    }
                }
            }
    }
    
    if(ucStatusReturn != MI_OK)//�޿�
    {
        IC_Card_Exist = 0;
    }
}
//==========================================================
//	�������ƣ�	IC_Card_Write
//
//	�������ܣ�	��IC����д����
//
//	��ڲ�����	��
//
//	���ز�����	��
//
//	˵����		
//==========================================================
uint8_t cStatus;
uint8_t IC_Card_Write(uint8_t *p)
{
    if (PcdAnticoll(ucArray_ID) == MI_OK)  //����ײ�����ж��ſ������д��������Χʱ������ͻ���ƻ������ѡ��һ�Ž��в�����
    {               
        if (PcdSelect(ucArray_ID) == MI_OK)//ѡ��ucArray_ID�Ŀ�
        {
            if (PcdAuthState(0x61,0x5,pk,ucArray_ID) == MI_OK)//����Կ�����Ȩ  
            {
                cStatus = PcdWrite(0x5,p);
                if(cStatus == MI_ERR)
                {//���дʧ����дһ��
                    cStatus = PcdWrite(0x5,p);
                }
            }
        }
    }
    return cStatus;
}
//==========================================================
//	�������ƣ�	IC_Card_Read
//
//	�������ܣ�	��IC����Ƴ�����
//
//	��ڲ�����	��
//
//	���ز�����	��
//
//	˵����		
//==========================================================
void IC_Card_Read(uint8_t *p)
{
     PcdRead(0X5,p);
}
//==========================================================
//	�������ƣ�	RC522_SPI_Config
//
//	�������ܣ�	RC522 SPI��ʼ��
//
//	��ڲ�����	��
//
//	���ز�����	��
//
//	˵����		
//==========================================================
static void RC522_SPI_Config ( void )
{     
    
     GPIO_InitTypeDef GPIO_Initure;

    __HAL_RCC_GPIOA_CLK_ENABLE();           	//����GPIOAʱ��
	
    GPIO_Initure.Pin=GPIO_PIN_0|GPIO_PIN_4|GPIO_PIN_5|GPIO_PIN_7; 	//PA0,PA4,PA5,PA7
    GPIO_Initure.Mode=GPIO_MODE_OUTPUT_PP;  	//�������
    GPIO_Initure.Speed=GPIO_SPEED_HIGH;    	 	//����
    HAL_GPIO_Init(GPIOA,&GPIO_Initure);
    
    GPIO_Initure.Pin=GPIO_PIN_6; 	            //PA6
    GPIO_Initure.Mode=GPIO_MODE_INPUT;  	    //����ģʽ
    GPIO_Initure.Speed=GPIO_SPEED_HIGH;    	 	//����
    HAL_GPIO_Init(GPIOA,&GPIO_Initure);      
	
}

//==========================================================
//	�������ƣ�	SPI_RC522_SendByte
//
//	�������ܣ�	��RC522����1 Byte ����
//
//	��ڲ�����	byte��Ҫ���͵�����
//
//	���ز�����	RC522���ص�����
//
//	˵����		
//==========================================================
void SPI_RC522_SendByte ( unsigned char byte )
{
    unsigned char counter;
	
	
    for(counter=0;counter<8;counter++)
    {     
			if ( byte & 0x80 )
					macRC522_MOSI_1 ();
			else 
					macRC522_MOSI_0 ();

//			Delay_us ( 3 );
			macRC522_DELAY();
		
			macRC522_SCK_0 ();

//			Delay_us ( 1 );
//			Delay_us ( 3 );
			macRC522_DELAY();
			 
			macRC522_SCK_1();

//			Delay_us ( 3 );
			macRC522_DELAY();
			 
			byte <<= 1; 
			
    } 
	
}

//==========================================================
//	�������ƣ�	SPI_RC522_ReadByte
//
//	�������ܣ�	��RC522����1 Byte ����
//
//	��ڲ�����	��
//
//	���ز�����	RC522���ص�����
//
//	˵����		
//==========================================================
unsigned char SPI_RC522_ReadByte ( void )
{
	unsigned char counter;
	unsigned char SPI_Data;


	for(counter=0;counter<8;counter++)
	{
			SPI_Data <<= 1;
	 
			macRC522_SCK_0 ();

//			Delay_us ( 3 );
		macRC522_DELAY();
		
			if ( macRC522_MISO_GET() == 1)
					SPI_Data |= 0x01;

//			Delay_us ( 2 );
//			Delay_us ( 3 );
			macRC522_DELAY();

			macRC522_SCK_1 ();
	
//			Delay_us ( 3 );
			macRC522_DELAY();
			
	}
	
	return SPI_Data;
	
}

//==========================================================
//	�������ƣ�	ReadRawRC
//
//	�������ܣ�	��RC522�Ĵ���
//
//	��ڲ�����	ucAddress���Ĵ�����ַ
//
//	���ز�����	�Ĵ����ĵ�ǰֵ
//
//	˵����		
//==========================================================
unsigned char ReadRawRC ( unsigned char ucAddress )
{
	unsigned char ucAddr, ucReturn;
	
	
	ucAddr = ( ( ucAddress << 1 ) & 0x7E ) | 0x80;
	
	macRC522_CS_Enable();
	
	SPI_RC522_SendByte ( ucAddr );
	
	ucReturn = SPI_RC522_ReadByte ();
	
	macRC522_CS_Disable();
	
	
	return ucReturn;
	
	
}
//==========================================================
//	�������ƣ�	WriteRawRC
//
//	�������ܣ�	дRC522�Ĵ���
//
//	��ڲ�����	ucAddress���Ĵ�����ַ
//              ucValue��д��Ĵ�����ֵ
//
//	���ز�����	��
//
//	˵����		
//==========================================================
void WriteRawRC ( unsigned char ucAddress, unsigned char ucValue )
{  
	unsigned char ucAddr;
	
	
	ucAddr = ( ucAddress << 1 ) & 0x7E;
	
	macRC522_CS_Enable();
	
	SPI_RC522_SendByte ( ucAddr );
	
	SPI_RC522_SendByte ( ucValue );
	
	macRC522_CS_Disable();	

	
}
//==========================================================
//	�������ƣ�	SetBitMask
//
//	�������ܣ�	��RC522�Ĵ�����λ
//
//	��ڲ�����	ucReg���Ĵ�����ַ
//              ucMask����λֵ
//
//	���ز�����	��
//
//	˵����		
//==========================================================
void SetBitMask ( unsigned char ucReg, unsigned char ucMask )  
{
    unsigned char ucTemp;
	
	
    ucTemp = ReadRawRC ( ucReg );
	
    WriteRawRC ( ucReg, ucTemp | ucMask );         // set bit mask
	
	
}

//==========================================================
//	�������ƣ�	ClearBitMask
//
//	�������ܣ�	��RC522�Ĵ�����λ
//
//	��ڲ�����	ucReg���Ĵ�����ַ
//              ucMask����λֵ
//
//	���ز�����	��
//
//	˵����		
//==========================================================
void ClearBitMask ( unsigned char ucReg, unsigned char ucMask )  
{
    unsigned char ucTemp;
	
	
    ucTemp = ReadRawRC ( ucReg );
	
    WriteRawRC ( ucReg, ucTemp & ( ~ ucMask) );  // clear bit mask
	
	
}

//==========================================================
//	�������ƣ�	PcdAntennaOn
//
//	�������ܣ�	�������� 
//
//	��ڲ�����	��
//
//	���ز�����	��
//
//	˵����		
//==========================================================
void PcdAntennaOn ( void )
{
    unsigned char uc;
	
	
    uc = ReadRawRC ( TxControlReg );
	
    if ( ! ( uc & 0x03 ) )
			SetBitMask(TxControlReg, 0x03);

		
}

//==========================================================
//	�������ƣ�	PcdAntennaOff
//
//	�������ܣ�	�ر�����
//
//	��ڲ�����	��
//
//	���ز�����	��
//
//	˵����		
//==========================================================
void PcdAntennaOff ( void )
{
  ClearBitMask ( TxControlReg, 0x03 );
}

//==========================================================
//	�������ƣ�	PcdReset
//
//	�������ܣ�	��λRC522 
//
//	��ڲ�����	��
//
//	���ز�����	��
//
//	˵����		
//==========================================================
void PcdReset ( void )
{
	macRC522_Reset_Disable();
	
	delay_us ( 1 );
	
	macRC522_Reset_Enable();
	
	delay_us ( 1 );
	
	macRC522_Reset_Disable();
	
	delay_us ( 1 );
	
	WriteRawRC ( CommandReg, 0x0f );
	
	while ( ReadRawRC ( CommandReg ) & 0x10 );
	
	delay_us ( 1 );
	
  WriteRawRC ( ModeReg, 0x3D );            //���巢�ͺͽ��ճ���ģʽ ��Mifare��ͨѶ��CRC��ʼֵ0x6363
	
  WriteRawRC ( TReloadRegL, 30 );          //16λ��ʱ����λ    
	WriteRawRC ( TReloadRegH, 0 );			     //16λ��ʱ����λ
	
  WriteRawRC ( TModeReg, 0x8D );				   //�����ڲ���ʱ��������
	
  WriteRawRC ( TPrescalerReg, 0x3E );			 //���ö�ʱ����Ƶϵ��
	
	WriteRawRC ( TxAutoReg, 0x40 );				   //���Ʒ����ź�Ϊ100%ASK	
	

}

//==========================================================
//	�������ƣ�	M500PcdConfigISOType
//
//	�������ܣ�	����RC522�Ĺ�����ʽ
//
//	��ڲ�����	ucType��������ʽ
//
//	���ز�����	��
//
//	˵����		
//==========================================================
void M500PcdConfigISOType ( unsigned char ucType )
{
	if ( ucType == 'A')                     //ISO14443_A
  {
        ClearBitMask ( Status2Reg, 0x08 );

        WriteRawRC ( ModeReg, 0x3D );//3F

        WriteRawRC ( RxSelReg, 0x86 );//84

        WriteRawRC( RFCfgReg, 0x7F );   //4F

        WriteRawRC( TReloadRegL, 30 );//tmoLength);// TReloadVal = 'h6a =tmoLength(dec) 

        WriteRawRC ( TReloadRegH, 0 );

        WriteRawRC ( TModeReg, 0x8D );

        WriteRawRC ( TPrescalerReg, 0x3E );

        delay_us ( 2 );

        PcdAntennaOn ();//������
		
   }

	 
}

//==========================================================
//	�������ƣ�	PcdComMF522
//
//	�������ܣ�	ͨ��RC522��ISO14443��ͨѶ
//
//	��ڲ�����	ucCommand��RC522������
//              pInData��ͨ��RC522���͵���Ƭ������
//              ucInLenByte���������ݵ��ֽڳ���
//              pOutData�����յ��Ŀ�Ƭ��������
//              pOutLenBit���������ݵ�λ����
//
//	���ز�����	״ֵ̬ = MI_OK���ɹ�
//
//	˵����		
//==========================================================
char PcdComMF522 ( unsigned char ucCommand, unsigned char * pInData, unsigned char ucInLenByte, unsigned char * pOutData, int * pOutLenBit )		
{
    char cStatus = MI_ERR;
    unsigned char ucIrqEn   = 0x00;
    unsigned char ucWaitFor = 0x00;
    unsigned char ucLastBits;
    unsigned char ucN;
    int ul;
	
	
    switch ( ucCommand )
    {
       case PCD_AUTHENT:		//Mifare��֤
          ucIrqEn   = 0x12;		//��������ж�����ErrIEn  ��������ж�IdleIEn
          ucWaitFor = 0x10;		//��֤Ѱ���ȴ�ʱ�� ��ѯ�����жϱ�־λ
          break;
			 
       case PCD_TRANSCEIVE:		//���շ��� ���ͽ���
          ucIrqEn   = 0x77;		//����TxIEn RxIEn IdleIEn LoAlertIEn ErrIEn TimerIEn
          ucWaitFor = 0x30;		//Ѱ���ȴ�ʱ�� ��ѯ�����жϱ�־λ�� �����жϱ�־λ
          break;
			 
       default:
         break;
			 
    }
   
    WriteRawRC ( ComIEnReg, ucIrqEn | 0x80 );		//IRqInv��λ�ܽ�IRQ��Status1Reg��IRqλ��ֵ�෴ 
    ClearBitMask ( ComIrqReg, 0x80 );			//Set1��λ����ʱ��CommIRqReg������λ����
    WriteRawRC ( CommandReg, PCD_IDLE );		//д��������
    SetBitMask ( FIFOLevelReg, 0x80 );			//��λFlushBuffer����ڲ�FIFO�Ķ���дָ���Լ�ErrReg��BufferOvfl��־λ�����
    
    for ( ul = 0; ul < ucInLenByte; ul ++ )
		  WriteRawRC ( FIFODataReg, pInData [ ul ] );    		//д���ݽ�FIFOdata
			
    WriteRawRC ( CommandReg, ucCommand );					//д����
   
    
    if ( ucCommand == PCD_TRANSCEIVE )
			SetBitMask(BitFramingReg,0x80);  				//StartSend��λ�������ݷ��� ��λ���շ�����ʹ��ʱ����Ч
    
    ul = 1000;//����ʱ��Ƶ�ʵ���������M1�����ȴ�ʱ��25ms
		
    do 														//��֤ ��Ѱ���ȴ�ʱ��	
    {
         ucN = ReadRawRC ( ComIrqReg );							//��ѯ�¼��ж�
         ul --;
    } while ( ( ul != 0 ) && ( ! ( ucN & 0x01 ) ) && ( ! ( ucN & ucWaitFor ) ) );		//�˳�����i=0,��ʱ���жϣ���д��������
		
    ClearBitMask ( BitFramingReg, 0x80 );					//��������StartSendλ
		
    if ( ul != 0 )
    {
			if ( ! ( ReadRawRC ( ErrorReg ) & 0x1B ) )			//�������־�Ĵ���BufferOfI CollErr ParityErr ProtocolErr
			{
				cStatus = MI_OK;
				
				if ( ucN & ucIrqEn & 0x01 )					//�Ƿ�����ʱ���ж�
				  cStatus = MI_NOTAGERR;   
					
				if ( ucCommand == PCD_TRANSCEIVE )
				{
					ucN = ReadRawRC ( FIFOLevelReg );			//��FIFO�б�����ֽ���
					
					ucLastBits = ReadRawRC ( ControlReg ) & 0x07;	//�����յ����ֽڵ���Чλ��
					
					if ( ucLastBits )
						* pOutLenBit = ( ucN - 1 ) * 8 + ucLastBits;   	//N���ֽ�����ȥ1�����һ���ֽڣ�+���һλ��λ�� ��ȡ����������λ��
					else
						* pOutLenBit = ucN * 8;   					//�����յ����ֽ������ֽ���Ч
					
					if ( ucN == 0 )		
            ucN = 1;    
					
					if ( ucN > MAXRLEN )
						ucN = MAXRLEN;   
					
					for ( ul = 0; ul < ucN; ul ++ )
					  pOutData [ ul ] = ReadRawRC ( FIFODataReg );   
					
					}
					
      }
			
			else
				cStatus = MI_ERR;   
			
    }
   
   SetBitMask ( ControlReg, 0x80 );           // stop timer now
   WriteRawRC ( CommandReg, PCD_IDLE ); 
		 
		
   return cStatus;
		
		
}

//==========================================================
//	�������ƣ�	PcdRequest
//
//	�������ܣ�	Ѱ��
//
//	��ڲ�����	ucReq_code��Ѱ����ʽ
//                     = 0x52��Ѱ��Ӧ�������з���14443A��׼�Ŀ�
//                     = 0x26��Ѱδ��������״̬�Ŀ�
//              pTagType����Ƭ���ʹ���
//                   = 0x4400��Mifare_UltraLight
//                   = 0x0400��Mifare_One(S50)
//                   = 0x0200��Mifare_One(S70)
//                   = 0x0800��Mifare_Pro(X))
//                   = 0x4403��Mifare_DESFire
//
//	���ز�����	״ֵ̬ = MI_OK���ɹ�
//
//	˵����		
//==========================================================
char PcdRequest ( unsigned char ucReq_code, unsigned char * pTagType )
{
   char cStatus;  
   unsigned char ucComMF522Buf [ MAXRLEN ]; 
   int ulLen;
	

   ClearBitMask ( Status2Reg, 0x08 );	//����ָʾMIFARECyptol��Ԫ��ͨ�Լ����п�������ͨ�ű����ܵ����
   WriteRawRC ( BitFramingReg, 0x07 );	//	���͵����һ���ֽڵ� ��λ
   SetBitMask ( TxControlReg, 0x03 );	//TX1,TX2�ܽŵ�����źŴ��ݾ����͵��Ƶ�13.56�������ز��ź�

   ucComMF522Buf [ 0 ] = ucReq_code;		//���� ��Ƭ������

   cStatus = PcdComMF522 ( PCD_TRANSCEIVE,	ucComMF522Buf, 1, ucComMF522Buf, & ulLen );	//Ѱ��  
    //	��ڲ�����	ucCommand��RC522������
//              pInData��ͨ��RC522���͵���Ƭ������
//              ucInLenByte���������ݵ��ֽڳ���
//              pOutData�����յ��Ŀ�Ƭ��������
//              pOutLenBit���������ݵ�λ����
  
   if ( ( cStatus == MI_OK ) && ( ulLen == 0x10 ) )	//Ѱ���ɹ����ؿ����� 
   {    
       * pTagType = ucComMF522Buf [ 0 ];
       * ( pTagType + 1 ) = ucComMF522Buf [ 1 ];
   }
	 
   else
     cStatus = MI_ERR;

   
   return cStatus;
	 
	 
}

//==========================================================
//	�������ƣ�	PcdAnticoll
//
//	�������ܣ�	����ײ
//
//	��ڲ�����	pSnr����Ƭ���кţ�4�ֽ�
//
//	���ز�����	״ֵ̬ = MI_OK���ɹ�
//
//	˵����		
//==========================================================
char PcdAnticoll ( unsigned char * pSnr )
{
    char cStatus;
    unsigned char uc, ucSnr_check = 0;
    unsigned char ucComMF522Buf [ MAXRLEN ]; 
	int ulLen;
    

    ClearBitMask ( Status2Reg, 0x08 );		//��MFCryptol Onλ ֻ�гɹ�ִ��MFAuthent����󣬸�λ������λ
    WriteRawRC ( BitFramingReg, 0x00);		//����Ĵ��� ֹͣ�շ�
    ClearBitMask ( CollReg, 0x80 );			//��ValuesAfterColl���н��յ�λ�ڳ�ͻ�����
   
    ucComMF522Buf [ 0 ] = 0x93;	//��Ƭ����ͻ����
    ucComMF522Buf [ 1 ] = 0x20;
   
    cStatus = PcdComMF522 ( PCD_TRANSCEIVE, ucComMF522Buf, 2, ucComMF522Buf, & ulLen);//�뿨Ƭͨ��
	
    if ( cStatus == MI_OK)		//ͨ�ųɹ�
    {
			for ( uc = 0; uc < 4; uc ++ )
			{
                 * ( pSnr + uc )  = ucComMF522Buf [ uc ];			//����UID
                 ucSnr_check ^= ucComMF522Buf [ uc ];
            }
			
      if ( ucSnr_check != ucComMF522Buf [ uc ] )
				cStatus = MI_ERR;    
				 
    }
    
    SetBitMask ( CollReg, 0x80 );
		
		
    return cStatus;
		
		
}

//==========================================================
//	�������ƣ�	CalulateCRC
//
//	�������ܣ�	��RC522����CRC16
//
//	��ڲ�����	pIndata������CRC16������
//              ucLen������CRC16�������ֽڳ���
//              pOutData����ż�������ŵ��׵�ַ
//
//	���ز�����	��
//
//	˵����		
//==========================================================
void CalulateCRC ( unsigned char * pIndata, unsigned char ucLen, unsigned char * pOutData )
{
    unsigned char uc, ucN;
	
	
    ClearBitMask(DivIrqReg,0x04);
	
    WriteRawRC(CommandReg,PCD_IDLE);
	
    SetBitMask(FIFOLevelReg,0x80);
	
    for ( uc = 0; uc < ucLen; uc ++)
	    WriteRawRC ( FIFODataReg, * ( pIndata + uc ) );   

    WriteRawRC ( CommandReg, PCD_CALCCRC );
	
    uc = 0xFF;
	
    do 
    {
        ucN = ReadRawRC ( DivIrqReg );
        uc --;
    } while ( ( uc != 0 ) && ! ( ucN & 0x04 ) );
		
    pOutData [ 0 ] = ReadRawRC ( CRCResultRegL );
    pOutData [ 1 ] = ReadRawRC ( CRCResultRegM );
		
		
}

//==========================================================
//	�������ƣ�	PcdSelect
//
//	�������ܣ�	ѡ����Ƭ
//
//	��ڲ�����	pSnr����Ƭ���кţ�4�ֽ�
//
//	���ز�����	״ֵ̬ = MI_OK���ɹ�
//
//	˵����		
//==========================================================
char PcdSelect ( unsigned char * pSnr )
{
    char ucN;
    unsigned char uc;
	  unsigned char ucComMF522Buf [ MAXRLEN ]; 
    int  ulLen;
    
    
    ucComMF522Buf [ 0 ] = PICC_ANTICOLL1;
    ucComMF522Buf [ 1 ] = 0x70;
    ucComMF522Buf [ 6 ] = 0;
	
    for ( uc = 0; uc < 4; uc ++ )
    {
    	ucComMF522Buf [ uc + 2 ] = * ( pSnr + uc );
    	ucComMF522Buf [ 6 ] ^= * ( pSnr + uc );
    }
		
    CalulateCRC ( ucComMF522Buf, 7, & ucComMF522Buf [ 7 ] );
  
    ClearBitMask ( Status2Reg, 0x08 );

    ucN = PcdComMF522 ( PCD_TRANSCEIVE, ucComMF522Buf, 9, ucComMF522Buf, & ulLen );
    
    if ( ( ucN == MI_OK ) && ( ulLen == 0x18 ) )
      ucN = MI_OK;  
    else
      ucN = MI_ERR;    

		
    return ucN;
		
		
}

//==========================================================
//	�������ƣ�	PcdAuthState
//
//	�������ܣ�	��֤��Ƭ����
//
//	��ڲ�����	ucAuth_mode��������֤ģʽ
//                     = 0x60����֤A��Կ
//                     = 0x61����֤B��Կ
//         unsigned char ucAddr�����ַ
//         pKey������
//         pSnr����Ƭ���кţ�4�ֽ�
//
//	���ز�����	 ״ֵ̬ = MI_OK���ɹ�
//
//	˵����		
//==========================================================
char PcdAuthState ( unsigned char ucAuth_mode, unsigned char ucAddr, unsigned char * pKey, unsigned char * pSnr )
{
    char cStatus;
	  unsigned char uc, ucComMF522Buf [ MAXRLEN ];
    int ulLen;
    
	
    ucComMF522Buf [ 0 ] = ucAuth_mode;
    ucComMF522Buf [ 1 ] = ucAddr;
	
    for ( uc = 0; uc < 6; uc ++ )
	    ucComMF522Buf [ uc + 2 ] = * ( pKey + uc );   
	
    for ( uc = 0; uc < 6; uc ++ )
	    ucComMF522Buf [ uc + 8 ] = * ( pSnr + uc );   

    cStatus = PcdComMF522 ( PCD_AUTHENT, ucComMF522Buf, 12, ucComMF522Buf, & ulLen );
	
    if ( ( cStatus != MI_OK ) || ( ! ( ReadRawRC ( Status2Reg ) & 0x08 ) ) )
      cStatus = MI_ERR;   
    
		
    return cStatus;
		
		
}

//==========================================================
//	�������ƣ�	PcdWrite
//
//	�������ܣ�	д���ݵ�M1��һ��
//
//	��ڲ�����	unsigned char ucAddr�����ַ
//              pData��д������ݣ�16�ֽ�
//
//	���ز�����	״ֵ̬ = MI_OK���ɹ�
//
//	˵����		
//==========================================================
char PcdWrite ( unsigned char ucAddr, unsigned char * pData )
{
    char cStatus;
	  unsigned char uc, ucComMF522Buf [ MAXRLEN ];
    int ulLen;
     
    
    ucComMF522Buf [ 0 ] = PICC_WRITE;
    ucComMF522Buf [ 1 ] = ucAddr;
	
    CalulateCRC ( ucComMF522Buf, 2, & ucComMF522Buf [ 2 ] );
 
    cStatus = PcdComMF522 ( PCD_TRANSCEIVE, ucComMF522Buf, 4, ucComMF522Buf, & ulLen );

    if ( ( cStatus != MI_OK ) || ( ulLen != 4 ) || ( ( ucComMF522Buf [ 0 ] & 0x0F ) != 0x0A ) )
      cStatus = MI_ERR;   
        
    if ( cStatus == MI_OK )
    {
			//memcpy(ucComMF522Buf, pData, 16);
      for ( uc = 0; uc < 16; uc ++ )
			  ucComMF522Buf [ uc ] = * ( pData + uc );  
			
      CalulateCRC ( ucComMF522Buf, 16, & ucComMF522Buf [ 16 ] );

      cStatus = PcdComMF522 ( PCD_TRANSCEIVE, ucComMF522Buf, 18, ucComMF522Buf, & ulLen );
			
			if ( ( cStatus != MI_OK ) || ( ulLen != 4 ) || ( ( ucComMF522Buf [ 0 ] & 0x0F ) != 0x0A ) )
        cStatus = MI_ERR;   
			
    } 
		
		
    return cStatus;
			
}

//==========================================================
//	�������ƣ�	PcdRead
//
//	�������ܣ�	��ȡM1��һ������
//
//	��ڲ�����	unsigned char ucAddr�����ַ
//               pData�����������ݣ�16�ֽ�
//
//	���ز�����	״ֵ̬ = MI_OK���ɹ�
//
//	˵����		
//==========================================================
char PcdRead ( unsigned char ucAddr, unsigned char * pData )
{
    char cStatus;
	  unsigned char uc, ucComMF522Buf [ MAXRLEN ]; 
    int ulLen;
    

    ucComMF522Buf [ 0 ] = PICC_READ;
    ucComMF522Buf [ 1 ] = ucAddr;
	
    CalulateCRC ( ucComMF522Buf, 2, & ucComMF522Buf [ 2 ] );
   
    cStatus = PcdComMF522 ( PCD_TRANSCEIVE, ucComMF522Buf, 4, ucComMF522Buf, & ulLen );
	
    if ( ( cStatus == MI_OK ) && ( ulLen == 0x90 ) )
    {
			for ( uc = 0; uc < 16; uc ++ )
        * ( pData + uc ) = ucComMF522Buf [ uc ];   
    }
		
    else
      cStatus = MI_ERR;   
    
		
    return cStatus;
		
		
}

//==========================================================
//	�������ƣ�	PcdHalt
//
//	�������ܣ�	���Ƭ��������״̬
//
//	��ڲ�����	��
//
//	���ز�����	״ֵ̬ = MI_OK���ɹ�
//
//	˵����		
//==========================================================
char PcdHalt( void )
{
	unsigned char ucComMF522Buf [ MAXRLEN ]; 
	int  ulLen;
  

  ucComMF522Buf [ 0 ] = PICC_HALT;
  ucComMF522Buf [ 1 ] = 0;
	
  CalulateCRC ( ucComMF522Buf, 2, & ucComMF522Buf [ 2 ] );
 	PcdComMF522 ( PCD_TRANSCEIVE, ucComMF522Buf, 4, ucComMF522Buf, & ulLen );

  return MI_OK;
	
}


void IC_CMT ( unsigned char * UID, unsigned char * KEY, unsigned char RW, unsigned char * Dat )
{
  unsigned char ucArray_ID [ 4 ] = { 0 };//�Ⱥ���IC�������ͺ�UID(IC�����к�)
  
	
  PcdRequest ( 0x52, ucArray_ID );//Ѱ��

  PcdAnticoll ( ucArray_ID );//����ײ
  
  PcdSelect ( UID );//ѡ����
  
  PcdAuthState ( 0x60, 0x10, KEY, UID );//У��
	

	if ( RW )//��дѡ��1�Ƕ���0��д
    PcdRead ( 0x10, Dat );
   
   else 
     PcdWrite ( 0x10, Dat );
   
	 
   PcdHalt ();
	 
	 
}


