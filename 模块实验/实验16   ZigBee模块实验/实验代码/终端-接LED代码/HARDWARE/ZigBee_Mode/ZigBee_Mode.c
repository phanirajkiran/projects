#include "ZigBee_Mode.h"
#include "stm32f1xx.h"
#include "delay.h"
#include "usart.h"
#include "timer.h"

#define ZBM_RESET_GPIO_PIN   GPIO_PIN_14
#define ZBM_RESET_GPIO_PORT  GPIOB
#define ZBM_IO_RCC_ENABLE()  __HAL_RCC_GPIOB_CLK_ENABLE() 
uint8_t RspLenght = 0;
ZBM_Info_TypeDef ZBM_Info;
uint8_t ZBM_RecvDataBuffer[ZBM_RECVDATA_LEN],ZBM_RecvDataIdx = 0;
uint8_t ZBM_RecvNwkStatePrompt[10],ZBM_RecvNwkStatePromptIdx = 0;
//==========================================================
//	�������ƣ�	ZBM_RecvHandler
//
//	�������ܣ�	����Ƿ������ݷ���
//
//	��ڲ�����	uint16_t waittime,�ȴ���ʱ��
//              uint32_t *pcheckobj,������
//              uint8_t expected_threshold�����������ֵ��
//
//	���ز�����	��
//
//	˵����		
//==========================================================
void ZBM_RecvHandler(uint8_t *precvbuf,uint8_t buflen)
{
    RspLenght = buflen;
//****************����ģ�鷵�ص�����״̬******************************************<<<
    if((precvbuf[0] == 0xFF)&&(precvbuf[1] == 0xAA)&&(buflen == 2))
    {//ֻ���ն��豸�Ż��յ��������
      ZBM_Info.nwk_state = ZBM_NETWORK_STATE_JOINED;
    }
    else if(((precvbuf[0] == 0xFF)&&(precvbuf[1] == 0x00))&&(buflen == 2))
    {//ֻ���ն��豸�Ż��յ��������
      ZBM_Info.nwk_state = ZBM_NETWORK_STATE_NO_NETWORK;
    }
    else if(((precvbuf[0] == 0xFF)&&(precvbuf[1] == 0xFF))&&(buflen == 2))
    {//ֻЭ�����ڵ�Ż��յ��������
      ZBM_Info.nwk_state = ZBM_NETWORK_STATE_BUILD_NETWORK;
    }
//****************����ģ�鷵�ص�����״̬******************************************>>> 

//****************��ȡ�����ò����Ļ���********************************************<<<
    if((precvbuf[0] == 0xFA)&&(buflen >= 2))
    {//���ò����ķ���
      ZBM_Info.get_writersp = 1;
    }
    else if((precvbuf[0] == 0xFB)&&(buflen >= 2))
    {//��ȡ�����ķ���
      ZBM_Info.get_readrsp = 1;
    }      
//****************��ȡ�����ò����Ļ���********************************************>>>  
    
//****************���յ�����******************************************************<<<
    //֡��ʽ��C0 C1 C2 + ���ݳ���+�û�����+���͵ĸ���Ϣ��ZigBeeģ��short addr(��ģ���Լ�д)
    if((precvbuf[0] == 0xC0)&&((precvbuf[1] == 0xC1)&&(precvbuf[2] == 0xC2)))
    {//�յ�����
      ZBM_Info.get_data = 1;
    }    
//****************���յ�����******************************************************>>>     
}
//==========================================================
//	�������ƣ�	ZBM_CheckRsp
//
//	�������ܣ�	����Ƿ������ݷ���
//
//	��ڲ�����	uint16_t waittime,�ȴ���ʱ��
//              uint32_t *pcheckobj,������
//              uint8_t expected_threshold�����������ֵ��
//
//	���ز�����	��
//
//	˵����		
//==========================================================
void ZBM_CheckRsp(uint16_t waittime,uint32_t *pcheckobj,uint8_t expected_threshold)
{
    RspLenght = 0;
    while(waittime)
    {
        if(ZBM_Info.get_readrsp || ZBM_Info.get_writersp)
        {
            break;
        }
        delay_ms(1);
        waittime--;
    }
    ZBM_Info.get_readrsp  = 0;
    ZBM_Info.get_writersp = 0;
}
//==========================================================
//	�������ƣ�	swaps
//
//	�������ܣ�	��һ�����ֽڵ����ݣ��ߵ��ֽڽ���
//
//	��ڲ�����	uint16_t i
//
//	���ز�����	��������uint16_t������ת����Ľ��
//
//	˵����		
//==========================================================
uint16_t swaps(uint16_t i)
{
    uint16_t ret=0;
    ret = (i & 0xFF) << 8;
    ret |= ((i >> 8)& 0xFF);
    return ret;	
}
//==========================================================
//	�������ƣ�	ZBM_SendData
//
//	�������ܣ�	��ZigBeeģ�鷢������
//
//	��ڲ�����	uint8_t *pdata,ָ���������͵�����
//               uint16_t len ,�����͵����ݳ���
//	���ز�����	��
//
//	˵����		ʹ�ô���2���з��� ������115200
//==========================================================
uint8_t gtemp[9],ii;
void ZBM_SendData(uint8_t *pdata,uint16_t len)
{
    ii = 0;
    while(len)
    {
        while((USART2->SR&0X40)==0)
        {;} //ѭ������,ֱ��������� 
        USART2->DR = *pdata; 
        len--;
        pdata++;
    }      
}
//==========================================================
//	�������ƣ�	ZBM_SetNetworkPAN
//
//	�������ܣ�	���������PAN
//
//	��ڲ�����	uint16_t panid,PAN id
//
//	���ز�����	��������ZBM_ErrorCode��
//
//	˵����	���� //FD 03 03 pan_id FF  ���� FA 03	
//==========================================================
enum ZBM_ErrorCode ZBM_SetNetworkPAN(uint16_t panid)
{
    uint8_t zbm_cmd[20],index=0;
    enum ZBM_ErrorCode error;
    
    zbm_cmd[index++] = 0xFD;
    zbm_cmd[index++] = 0x03;
    zbm_cmd[index++] = 0x03; 
    zbm_cmd[index++] = (uint8_t)(panid>>8); 
    zbm_cmd[index++] = (uint8_t)panid;  
    zbm_cmd[index++] = 0xFF;    
    
    USART2_RX_STA = 0;
    memset((void*)USART2_RX_BUF,0,20);
    ZBM_SendData(zbm_cmd,index);
    ZBM_CheckRsp(3000,&USART2_RX_STA,1);
    if((USART2_RX_BUF[0] == 0xFA)&&(USART2_RX_BUF[1] == 0x03))
    {
        error = ZBM_SUCCESS;
    }
    else
    {
        error = ZBM_FAILED;
    }
    
    return error; 
}
//==========================================================
//	�������ƣ�	ZBM_SetDevType
//
//	�������ܣ�	���ýڵ����ͣ�·�ɣ�Э�������ն�
//
//	��ڲ�����	enum ZBM_DevType type,�ڵ������
//
//	���ز�����	��������ZBM_ErrorCode��
//
//	˵����	���� //FD 02 01 type FF  ���� FA 01	
//==========================================================
enum ZBM_ErrorCode ZBM_SetDevType(enum ZBM_DevType type)
{
    static uint8_t  zbm_cmd[10],index=0;
    enum ZBM_ErrorCode error;
    
    zbm_cmd[index++] = 0xFD;
    zbm_cmd[index++] = 0x02;
    zbm_cmd[index++] = 0x01; 
    zbm_cmd[index++] = type; 
    zbm_cmd[index++] = 0xFF;    

    USART2_RX_STA = 0;
    memset((void*)USART2_RX_BUF,0,20);
    ZBM_SendData(zbm_cmd,index);
    ZBM_CheckRsp(2000,&USART2_RX_STA,1);
    if((USART2_RX_BUF[0] == 0xFA)&&(USART2_RX_BUF[1] == 0x01))
    {
        error = ZBM_SUCCESS;
    }
    else
    {
        error = ZBM_FAILED;
    }
    
    return error; 
}
//==========================================================
//	�������ƣ�	ZBM_SetNetworkKey
//
//	�������ܣ�	����������Կ
//
//	��ڲ�����	uint8_t *pkey,������Կ��
//              uint8_t len����Կ����
//	���ز�����	��������ZBM_ErrorCode��
//
//	˵����	���� //FD 11 04 key(16λ) FF  ���� FA 04	
//==========================================================
enum ZBM_ErrorCode ZBM_SetNetworkKey(uint8_t *pkey,uint8_t len)
{
    uint8_t zbm_cmd[20],index=0,i=0;
    enum ZBM_ErrorCode error;
    
    zbm_cmd[index++] = 0xFD;
    zbm_cmd[index++] = 0x11;
    zbm_cmd[index++] = 0x04; 
    for(i=0;i<len;i++)
    {
        zbm_cmd[index++] = *(pkey++); 
    }
    zbm_cmd[index++] = 0xFF;    

    USART2_RX_STA = 0;
    memset((void*)USART2_RX_BUF,0,20);
    ZBM_SendData(zbm_cmd,index);
    ZBM_CheckRsp(2000,&USART2_RX_STA,1);
    if((USART2_RX_BUF[0] == 0xFA)&&(USART2_RX_BUF[1] == 0x04))
    {
        error = ZBM_SUCCESS;
    }
    else
    {
        error = ZBM_FAILED;
    }
    
    return error; 
}
//==========================================================
//	�������ƣ�	ZBM_SetNetworkGrounp
//
//	�������ܣ�	����������
//
//	��ڲ�����	uint8_t grounp,�������(1~99)
//
//	���ز�����	��������ZBM_ErrorCode��
//
//	˵����	���� //FD 11 04 key(16λ) FF  ���� FA 04	
//==========================================================
enum ZBM_ErrorCode ZBM_SetNetworkGrounp(uint8_t grounp)
{
    uint8_t zbm_cmd[20],index=0;
    enum ZBM_ErrorCode error;
    
    zbm_cmd[index++] = 0xFD;
    zbm_cmd[index++] = 0x02;
    zbm_cmd[index++] = 0x09; 
    zbm_cmd[index++] = grounp; 
    zbm_cmd[index++] = 0xFF;    

    USART2_RX_STA = 0;
    memset((void*)USART2_RX_BUF,0,20);
    ZBM_SendData(zbm_cmd,index);
    ZBM_CheckRsp(2000,&USART2_RX_STA,1);
    if((USART2_RX_BUF[0] == 0xFA)&&(USART2_RX_BUF[1] == 0x09))
    {
        error = ZBM_SUCCESS;
    }
    else
    {
        error = ZBM_FAILED;
    }
    
    return error; 
}
//==========================================================
//	�������ƣ�	ZBM_SetChannel
//
//	�������ܣ�	����������
//
//	��ڲ�����	uint8_t ch,ͨ���ŵ� (11~26)
//
//	���ز�����	��������ZBM_ErrorCode��
//
//	˵����	���� //FD 02 0A ch FF  ���� FA 0A	
//==========================================================
enum ZBM_ErrorCode ZBM_SetChannel(uint8_t ch)
{
    uint8_t zbm_cmd[20],index=0;
    enum ZBM_ErrorCode error;
    
    if((ch<11)||(ch>26))
    {
        error = ZBM_FAILED;
    }
    
    zbm_cmd[index++] = 0xFD;
    zbm_cmd[index++] = 0x02;
    zbm_cmd[index++] = 0x0A; 
    zbm_cmd[index++] = ch; 
    zbm_cmd[index++] = 0xFF;    

    USART2_RX_STA = 0;
    memset((void*)USART2_RX_BUF,0,20);
    ZBM_SendData(zbm_cmd,index);
    ZBM_CheckRsp(2000,&USART2_RX_STA,1);
    if((USART2_RX_BUF[0] == 0xFA)&&(USART2_RX_BUF[1] == 0x0A))
    {
        error = ZBM_SUCCESS;
    }
    else
    {
        error = ZBM_FAILED;
    }
    
    return error; 
}
//==========================================================
//	�������ƣ�	ZBM_SetTxPower
//
//	�������ܣ�	���÷��͹���
//
//	��ڲ�����	uint8_t pow,����ֵ (00~05)
//
//	���ز�����	��������ZBM_ErrorCode��
//
//	˵����	���� //FD 02 0B pow FF  ���� FA 0B	
//==========================================================
enum ZBM_ErrorCode ZBM_SetTxPower(uint8_t pow)
{
    uint8_t zbm_cmd[20],index=0;
    enum ZBM_ErrorCode error;
    
    zbm_cmd[index++] = 0xFD;
    zbm_cmd[index++] = 0x02;
    zbm_cmd[index++] = 0x0B; 
    zbm_cmd[index++] = pow; 
    zbm_cmd[index++] = 0xFF;    

    USART2_RX_STA = 0;
    memset((void*)USART2_RX_BUF,0,20);
    ZBM_SendData(zbm_cmd,index);
    ZBM_CheckRsp(2000,&USART2_RX_STA,1);
    if((USART2_RX_BUF[0] == 0xFA)&&(USART2_RX_BUF[1] == 0x0B))
    {
        error = ZBM_SUCCESS;
    }
    else
    {
        error = ZBM_FAILED;
    }
    
    return error; 
}
//==========================================================
//	�������ƣ�	ZBM_SetSerialBaud
//
//	�������ܣ�	���ô��ڲ�����
//
//	��ڲ�����	uint8_t baud_index,����ֵ (00~0F)
//
//	���ز�����	��������ZBM_ErrorCode��
//
//	˵����	���� //FD 02 0C baud FF  ���� FA 0C	
//==========================================================
enum ZBM_ErrorCode ZBM_SetSerialBaud(uint8_t baud_index)
{
    uint8_t zbm_cmd[20],index=0;
    enum ZBM_ErrorCode error;
    
    zbm_cmd[index++] = 0xFD;
    zbm_cmd[index++] = 0x02;
    zbm_cmd[index++] = 0x0C; 
    zbm_cmd[index++] = baud_index; 
    zbm_cmd[index++] = 0xFF;    

    USART2_RX_STA = 0;
    memset((void*)USART2_RX_BUF,0,20);    
    ZBM_SendData(zbm_cmd,index);
    ZBM_CheckRsp(2000,&USART2_RX_STA,1);
    if((USART2_RX_BUF[0] == 0xFA)&&(USART2_RX_BUF[1] == 0x0C))
    {
        error = ZBM_SUCCESS;
    }
    else
    {
        error = ZBM_FAILED;
    }
    
    return error; 
}
//==========================================================
//	�������ƣ�	ZBM_SetSleepMode
//
//	�������ܣ�	�����ն˵�����ģʽ
//
//	��ڲ�����	uint8_t mode
//
//	���ز�����	��������ZBM_ErrorCode��
//
//	˵����	���� //FD 02 0D sleepmode FF  ���� FA 0D	
//==========================================================
enum ZBM_ErrorCode ZBM_SetSleepMode(uint8_t mode)
{
    uint8_t zbm_cmd[20],index=0;
    enum ZBM_ErrorCode error;
    
    zbm_cmd[index++] = 0xFD;
    zbm_cmd[index++] = 0x02;
    zbm_cmd[index++] = 0x0D; 
    zbm_cmd[index++] = mode; 
    zbm_cmd[index++] = 0xFF;    

    USART2_RX_STA = 0;
    memset((void*)USART2_RX_BUF,0,20);    
    ZBM_SendData(zbm_cmd,index);
    ZBM_CheckRsp(2000,&USART2_RX_STA,1);
    if((USART2_RX_BUF[0] == 0xFA)&&(USART2_RX_BUF[1] == 0x0D))
    {
        error = ZBM_SUCCESS;
    }
    else
    {
        error = ZBM_FAILED;
    }
    
    return error; 
}
//==========================================================
//	�������ƣ�	ZBM_SetDataSaveTime
//
//	�������ܣ�	����·�������ն˵����ݱ���ʱ��
//
//	��ڲ�����	uint8_t time
//
//	���ز�����	��������ZBM_ErrorCode��
//
//	˵����	���� //FD 02 0E baud FF  ���� FA 0E	
//==========================================================
enum ZBM_ErrorCode ZBM_SetDataSaveTime(uint8_t time)
{
    uint8_t zbm_cmd[20],index=0;
    enum ZBM_ErrorCode error;
    
    zbm_cmd[index++] = 0xFD;
    zbm_cmd[index++] = 0x02;
    zbm_cmd[index++] = 0x0E; 
    zbm_cmd[index++] = time; 
    zbm_cmd[index++] = 0xFF;    

    USART2_RX_STA = 0;
    memset((void*)USART2_RX_BUF,0,20);    
    ZBM_SendData(zbm_cmd,index);
    ZBM_CheckRsp(2000,&USART2_RX_STA,1);
    if((USART2_RX_BUF[0] == 0xFA)&&(USART2_RX_BUF[1] == 0x0E))
    {
        error = ZBM_SUCCESS;
    }
    else
    {
        error = ZBM_FAILED;
    }
    
    return error; 
}
//==========================================================
//	�������ƣ�	ZBM_GetDevType
//
//	�������ܣ�	��ȡ�ڵ�����
//
//	��ڲ�����	uint8_t *ptype
//
//	���ز�����	��������ZBM_ErrorCode��
//
//	˵����	���� //FE 01 01 FF  ���� FB type	
//==========================================================
enum ZBM_ErrorCode ZBM_GetDevType(uint8_t *ptype)
{
    uint8_t zbm_cmd[20],index=0;
    enum ZBM_ErrorCode error;
    
    zbm_cmd[index++] = 0xFE;
    zbm_cmd[index++] = 0x01;
    zbm_cmd[index++] = 0x01; 
    zbm_cmd[index++] = 0xFF;    

    USART2_RX_STA = 0;
    memset((void*)USART2_RX_BUF,0,20);
    ZBM_SendData(zbm_cmd,4);
    ZBM_CheckRsp(2000,&USART2_RX_STA,1);
    if(USART2_RX_BUF[0] == 0xFB)
    {
       *ptype = USART2_RX_BUF[1];
        error = ZBM_SUCCESS;
    }
    else
    {
        error = ZBM_FAILED;
    }
    return error; 
}
//==========================================================
//	�������ƣ�	ZBM_GetNwkState
//
//	�������ܣ�	��ȡ����״̬
//
//	��ڲ�����	uint8_t *pstate
//
//	���ز�����	��������ZBM_ErrorCode��
//
//	˵����	���� //FE 01 02 FF  ���� FB state	
//==========================================================
enum ZBM_ErrorCode ZBM_GetNwkState(uint8_t *pstate)
{
    uint8_t zbm_cmd[20],index=0;
    enum ZBM_ErrorCode error;
    
    zbm_cmd[index++] = 0xFE;
    zbm_cmd[index++] = 0x01;
    zbm_cmd[index++] = 0x02; 
    zbm_cmd[index++] = 0xFF;    

    USART2_RX_STA = 0;
    memset((void*)USART2_RX_BUF,0,20);
    ZBM_SendData(zbm_cmd,index);
    ZBM_CheckRsp(2000,&USART2_RX_STA,1);
    if(USART2_RX_BUF[0] == 0xFB)
    {
       *pstate = USART2_RX_BUF[1];
        error = ZBM_SUCCESS;
    }
    else
    {
        error = ZBM_FAILED;
    }
    return error; 
}
//==========================================================
//	�������ƣ�	ZBM_GetPAN
//
//	�������ܣ�	��ȡ����PAN
//
//	��ڲ�����	uint16_t *ppan
//
//	���ز�����	��������ZBM_ErrorCode��
//
//	˵����	���� //FE 01 03 FF  ���� FB pan	
//==========================================================
enum ZBM_ErrorCode ZBM_GetPAN(uint16_t *ppan)
{
    uint8_t zbm_cmd[20],index=0;
    enum ZBM_ErrorCode error;
    
    zbm_cmd[index++] = 0xFE;
    zbm_cmd[index++] = 0x01;
    zbm_cmd[index++] = 0x03; 
    zbm_cmd[index++] = 0xFF;    

    USART2_RX_STA = 0;
    memset((void*)USART2_RX_BUF,0,20);
    ZBM_SendData(zbm_cmd,index);
    ZBM_CheckRsp(2000,&USART2_RX_STA,1);
    if(USART2_RX_BUF[0] == 0xFB)
    {
        *ppan = (USART2_RX_BUF[1]<<8) + USART2_RX_BUF[2];
        error = ZBM_SUCCESS;
    }
    else
    {
        error = ZBM_FAILED;
    }
    return error; 
}
//==========================================================
//	�������ƣ�	ZBM_GetNwkPAN
//
//	�������ܣ�	��ȡ������Կ
//
//	��ڲ�����	uint8_t *ppan
//
//	���ز�����	��������ZBM_ErrorCode��
//
//	˵����	���� //FE 01 04 FF  ���� FB key	
//==========================================================
enum ZBM_ErrorCode ZBM_GetNwkKey(uint8_t *pkey)
{
    uint8_t zbm_cmd[20],index=0,i;
    enum ZBM_ErrorCode error;
    
    zbm_cmd[index++] = 0xFE;
    zbm_cmd[index++] = 0x01;
    zbm_cmd[index++] = 0x04; 
    zbm_cmd[index++] = 0xFF;    

    USART2_RX_STA = 0;
    memset((void*)USART2_RX_BUF,0,20);
    ZBM_SendData(zbm_cmd,index);
    ZBM_CheckRsp(2000,&USART2_RX_STA,1);
    if(USART2_RX_BUF[0] == 0xFB)
    {
        for(i=1;i < RspLenght;i++)
        {
            *(pkey++) = USART2_RX_BUF[i];
        }
        error = ZBM_SUCCESS;
    }
    else
    {
        error = ZBM_FAILED;
    }
    return error; 
}
//==========================================================
//	�������ƣ�	ZBM_GetNwkShortAddr
//
//	�������ܣ�	��ȡ����short addr
//
//	��ڲ�����	uint8_t *pshortaddr
//
//	���ز�����	��������ZBM_ErrorCode��
//
//	˵����	���� //FE 01 05 FF  ���� FB short addr
//==========================================================
enum ZBM_ErrorCode ZBM_GetNwkShortAddr(uint16_t *pshortaddr)
{
    uint8_t zbm_cmd[20],index=0;
    enum ZBM_ErrorCode error;
    
    zbm_cmd[index++] = 0xFE;
    zbm_cmd[index++] = 0x01;
    zbm_cmd[index++] = 0x05; 
    zbm_cmd[index++] = 0xFF;    

    USART2_RX_STA = 0;
    memset((void*)USART2_RX_BUF,0,20);
    ZBM_SendData(zbm_cmd,index);
    ZBM_CheckRsp(2000,&USART2_RX_STA,1);
    if(USART2_RX_BUF[0] == 0xFB)
    {
        *pshortaddr = (USART2_RX_BUF[1]<<8) + USART2_RX_BUF[2];
        error = ZBM_SUCCESS;
    }
    else
    {
        error = ZBM_FAILED;
    }
    return error; 
}
//==========================================================
//	�������ƣ�	ZBM_GetLocalMAC
//
//	�������ܣ�	��ȡ������MAC��ַ
//
//	��ڲ�����	uint8_t *pmac
//
//	���ز�����	��������ZBM_ErrorCode��
//
//	˵����	���� //FE 01 06 FF  ���� FB mac addr	
//==========================================================
enum ZBM_ErrorCode ZBM_GetLocalMAC(uint8_t *pmac)
{
    uint8_t zbm_cmd[20],index=0,i;
    enum ZBM_ErrorCode error;
    
    zbm_cmd[index++] = 0xFE;
    zbm_cmd[index++] = 0x01;
    zbm_cmd[index++] = 0x06; 
    zbm_cmd[index++] = 0xFF;    

    USART2_RX_STA = 0;
    memset((void*)USART2_RX_BUF,0,20);
    ZBM_SendData(zbm_cmd,index);
    ZBM_CheckRsp(2000,&USART2_RX_STA,1);
    if(USART2_RX_BUF[0] == 0xFB)
    {
        for(i=1;i < RspLenght;i++)
        {
            *(pmac++) = USART2_RX_BUF[i];
        }
        error = ZBM_SUCCESS;
    }
    else
    {
        error = ZBM_FAILED;
    }
    return error; 
}
//==========================================================
//	�������ƣ�	ZBM_GetParentsShortAddr
//
//	�������ܣ�	��ȡ���ڵ��short addr
//
//	��ڲ�����	uint16_t *pshortaddr
//
//	���ز�����	��������ZBM_ErrorCode��
//
//	˵����	���� //FE 01 07 FF  ���� FB short addr	
//==========================================================
enum ZBM_ErrorCode ZBM_GetParentsShortAddr(uint16_t *pshortaddr)
{
    uint8_t zbm_cmd[20],index=0;
    enum ZBM_ErrorCode error;
    
    zbm_cmd[index++] = 0xFE;
    zbm_cmd[index++] = 0x01;
    zbm_cmd[index++] = 0x07; 
    zbm_cmd[index++] = 0xFF;    

    USART2_RX_STA = 0;
    memset((void*)USART2_RX_BUF,0,20);
    ZBM_SendData(zbm_cmd,index);
    ZBM_CheckRsp(2000,&USART2_RX_STA,1);
    if(USART2_RX_BUF[0] == 0xFB)
    {
        *pshortaddr = (USART2_RX_BUF[1]<<8) + USART2_RX_BUF[2];
        error = ZBM_SUCCESS;
    }
    else
    {
        error = ZBM_FAILED;
    }
    return error; 
}
//==========================================================
//	�������ƣ�	ZBM_GetParentsMACAddr
//
//	�������ܣ�	��ȡ���ڵ��MAC��ַ
//
//	��ڲ�����	uint8_t *pmacaddr
//
//	���ز�����	��������ZBM_ErrorCode��
//
//	˵����	���� //FE 01 08 FF  ���� FB mac addr	
//==========================================================
enum ZBM_ErrorCode ZBM_GetParentsMACAddr(uint8_t *pmacaddr)
{
    uint8_t zbm_cmd[20],index=0,i;
    enum ZBM_ErrorCode error;
    
    zbm_cmd[index++] = 0xFE;
    zbm_cmd[index++] = 0x01;
    zbm_cmd[index++] = 0x08; 
    zbm_cmd[index++] = 0xFF;    

    USART2_RX_STA = 0;
    memset((void*)USART2_RX_BUF,0,20);
    ZBM_SendData(zbm_cmd,index);
    ZBM_CheckRsp(2000,&USART2_RX_STA,1);
    if(USART2_RX_BUF[0] == 0xFB)
    {
        for(i=0;i<RspLenght;i++)
        {
            *pmacaddr = USART2_RX_BUF[i];
        }
        error = ZBM_SUCCESS;
    }
    else
    {
        error = ZBM_FAILED;
    }
    return error; 
}
//==========================================================
//	�������ƣ�	ZBM_GetNwkGrounNo
//
//	�������ܣ�	��ȡ�������
//
//	��ڲ�����	uint8_t *pgroundno
//
//	���ز�����	��������ZBM_ErrorCode��
//
//	˵����	���� //FE 01 09 FF  ���� FB groundno	
//==========================================================
enum ZBM_ErrorCode ZBM_GetNwkGrounNo(uint8_t *pgroundno)
{
    uint8_t zbm_cmd[20],index=0;
    enum ZBM_ErrorCode error;
    
    zbm_cmd[index++] = 0xFE;
    zbm_cmd[index++] = 0x01;
    zbm_cmd[index++] = 0x09; 
    zbm_cmd[index++] = 0xFF;    

    USART2_RX_STA = 0;
    memset((void*)USART2_RX_BUF,0,20);
    ZBM_SendData(zbm_cmd,index);
    ZBM_CheckRsp(2000,&USART2_RX_STA,1);
    if(USART2_RX_BUF[0] == 0xFB)
    {
        *pgroundno = USART2_RX_BUF[1];
        error = ZBM_SUCCESS;
    }
    else
    {
        error = ZBM_FAILED;
    }
    return error; 
}
//==========================================================
//	�������ƣ�	ZBM_GetChannel
//
//	�������ܣ�	��ȡͨ���ŵ�
//
//	��ڲ�����	uint8_t *pchannel
//
//	���ز�����	��������ZBM_ErrorCode��
//
//	˵����	���� //FE 01 0A FF  ���� FB channel	
//==========================================================
enum ZBM_ErrorCode ZBM_GetChannel(uint8_t *pchannel)
{
    uint8_t zbm_cmd[20],index=0;
    enum ZBM_ErrorCode error;
    
    zbm_cmd[index++] = 0xFE;
    zbm_cmd[index++] = 0x01;
    zbm_cmd[index++] = 0x0A; 
    zbm_cmd[index++] = 0xFF;    

    USART2_RX_STA = 0;
    memset((void*)USART2_RX_BUF,0,20);
    ZBM_SendData(zbm_cmd,index);
    ZBM_CheckRsp(2000,&USART2_RX_STA,1);
    if(USART2_RX_BUF[0] == 0xFB)
    {
        *pchannel = USART2_RX_BUF[1];
        error = ZBM_SUCCESS;
    }
    else
    {
        error = ZBM_FAILED;
    }
    return error; 
}
//==========================================================
//	�������ƣ�	ZBM_GetTxPower
//
//	�������ܣ�	��ȡ���书��
//
//	��ڲ�����	uint8_t *ptxpower
//
//	���ز�����	��������ZBM_ErrorCode��
//
//	˵����	���� //FE 01 0B FF  ���� FB power	
//==========================================================
enum ZBM_ErrorCode ZBM_GetTxPower(uint8_t *ptxpower)
{
    uint8_t zbm_cmd[20],index=0;
    enum ZBM_ErrorCode error;
    
    zbm_cmd[index++] = 0xFE;
    zbm_cmd[index++] = 0x01;
    zbm_cmd[index++] = 0x0B; 
    zbm_cmd[index++] = 0xFF;    

    USART2_RX_STA = 0;
    memset((void*)USART2_RX_BUF,0,20);
    ZBM_SendData(zbm_cmd,index);
    ZBM_CheckRsp(2000,&USART2_RX_STA,1);
    if(USART2_RX_BUF[0] == 0xFB)
    {
        *ptxpower = USART2_RX_BUF[1];
        error = ZBM_SUCCESS;
    }
    else
    {
        error = ZBM_FAILED;
    }
    return error; 
}
//==========================================================
//	�������ƣ�	ZBM_GetSerialBaud
//
//	�������ܣ�	��ȡ���ڲ�����
//
//	��ڲ�����	uint8_t *pbaud
//
//	���ز�����	��������ZBM_ErrorCode��
//
//	˵����	���� //FE 01 0C FF  ���� FB baud	
//==========================================================
enum ZBM_ErrorCode ZBM_GetSerialBaud(uint8_t *pbaud)
{
    uint8_t zbm_cmd[20],index=0;
    enum ZBM_ErrorCode error;
    
    zbm_cmd[index++] = 0xFE;
    zbm_cmd[index++] = 0x01;
    zbm_cmd[index++] = 0x0C; 
    zbm_cmd[index++] = 0xFF;    

    USART2_RX_STA = 0;
    memset((void*)USART2_RX_BUF,0,20);
    ZBM_SendData(zbm_cmd,index);
    ZBM_CheckRsp(2000,&USART2_RX_STA,1);
    if(USART2_RX_BUF[0] == 0xFB)
    {
        *pbaud = USART2_RX_BUF[1];
        error = ZBM_SUCCESS;
    }
    else
    {
        error = ZBM_FAILED;
    }
    return error; 
}
//==========================================================
//	�������ƣ�	ZBM_GetSerialBaud
//
//	�������ܣ�	��ȡ�ն��豸������״̬
//
//	��ڲ�����	uint8_t *pbaud
//
//	���ز�����	��������ZBM_ErrorCode��
//
//	˵����	���� //FE 01 0D FF  ���� FB dormant status	
//==========================================================
enum ZBM_ErrorCode ZBM_GetDormantStatus(uint8_t *psta)
{
    uint8_t zbm_cmd[20],index=0;
    enum ZBM_ErrorCode error;
    
    zbm_cmd[index++] = 0xFE;
    zbm_cmd[index++] = 0x01;
    zbm_cmd[index++] = 0x0D; 
    zbm_cmd[index++] = 0xFF;    

    USART2_RX_STA = 0;
    memset((void*)USART2_RX_BUF,0,20);
    ZBM_SendData(zbm_cmd,index);
    ZBM_CheckRsp(2000,&USART2_RX_STA,1);
    if(USART2_RX_BUF[0] == 0xFB)
    {
        *psta = USART2_RX_BUF[1];
        error = ZBM_SUCCESS;
    }
    else
    {
        error = ZBM_FAILED;
    }
    return error; 
}
//==========================================================
//	�������ƣ�	ZBM_GetShortaddr_throung_MAC
//
//	�������ܣ�	��ȡMAC��ַ�豸��Ӧ�Ķ̵�ַ
//
//	��ڲ�����	uint8_t *pmacaddr,
//              uint16_t *pshortaddr,�����豸�Ķ̵�ַ
//	���ز�����	��������ZBM_ErrorCode��
//
//	˵����	���� //FE 09 10 FF  ���� FB short addr
//==========================================================
enum ZBM_ErrorCode ZBM_GetShortaddr_throung_MAC(const uint8_t *pmacaddr,uint16_t *pshortaddr)
{
    uint8_t zbm_cmd[20],index=0,i,retry=3;
    enum ZBM_ErrorCode error;
    
    zbm_cmd[index++] = 0xFE;
    zbm_cmd[index++] = 0x09;
    zbm_cmd[index++] = 0x10;
    for(i=0;i < 8;i++)
    {
        zbm_cmd[index++] = *(pmacaddr++);   
    }
    
    zbm_cmd[index++] = 0xFF;    
    
    while(retry--)
    {
        USART2_RX_STA = 0;
        memset((void*)USART2_RX_BUF,0,20);
        ZBM_SendData(zbm_cmd,index);
        ZBM_CheckRsp(2000,&USART2_RX_STA,1);
        if(USART2_RX_BUF[0] == 0xFB)
        {
            *pshortaddr = (USART2_RX_BUF[1]<<8) + USART2_RX_BUF[2];
            error = ZBM_SUCCESS;
            break;
        }
        else
        {
            error = ZBM_FAILED;
        }
    }
    return error; 
}
//==========================================================
//	�������ƣ�	ZBM_GetShortaddr_throung_MAC
//
//	�������ܣ�	��ȡMAC��ַЭ������·���������ݱ���ʱ�䡣
//
//	��ڲ�����	uint8_t *ptime,
//              
//	���ز�����	��������ZBM_ErrorCode��
//
//	˵����	���� //FE 01 0E FF  ���� FB save time
//==========================================================
enum ZBM_ErrorCode ZBM_GetDataSaveTimeC(uint8_t *ptime)
{
    uint8_t zbm_cmd[20],index=0;
    enum ZBM_ErrorCode error;
    
    zbm_cmd[index++] = 0xFE;
    zbm_cmd[index++] = 0x09;
    zbm_cmd[index++] = 0x0E;
    zbm_cmd[index++] = 0xFF;    

    USART2_RX_STA = 0;
    memset((void*)USART2_RX_BUF,0,20);
    ZBM_SendData(zbm_cmd,index);
    ZBM_CheckRsp(2000,&USART2_RX_STA,1);
    if(USART2_RX_BUF[0] == 0xFB)
    {
        *ptime = USART2_RX_BUF[1];
        error = ZBM_SUCCESS;
    }
    else
    {
        error = ZBM_FAILED;
    }
    return error; 
}
//==========================================================
//	�������ƣ�	ZBM_GetShortaddr_throung_MAC
//
//	�������ܣ�	��ȡMAC��ַЭ������·���������ݱ���ʱ�䡣
//
//	��ڲ�����	uint8_t *ptime,
//              
//	���ز�����	��������ZBM_ErrorCode��
//
//	˵����	ָ� 03+ type +addr+data
//==========================================================
#define ZBM_SEND_BUF_LEN 50
uint8_t ZBM_SendBuffer[ZBM_SEND_BUF_LEN];
void ZBM_Send_P2P(uint16_t shortaddr,uint8_t *pdata,uint8_t len)
{
    uint8_t index=0,i=0;
    
    ZBM_SendBuffer[index++] = 0xFC;
    ZBM_SendBuffer[index++] = len + 4;
    ZBM_SendBuffer[index++] = 0x03;
    ZBM_SendBuffer[index++] = 0x02;
    ZBM_SendBuffer[index++] = (uint8_t)(shortaddr>>8);
    ZBM_SendBuffer[index++] = (uint8_t)shortaddr;  
    for(i=0;i < len;i++)
    {
        ZBM_SendBuffer[index++] = *(pdata+i);
    }
    USART2_RX_STA = 0;
    memset((void*)USART2_RX_BUF,0,20);
    ZBM_SendData(ZBM_SendBuffer,index); 
    delay_ms(10);    
}
//==========================================================
//	�������ƣ�	ZBM_IsJoinedNetwork
//
//	�������ܣ�	����Ƿ��������ɹ�
//
//	��ڲ�����	��
//              
//	���ز�����	��������ZBM_ErrorCode��
//
//	˵����	ָ� 03+ type +addr+data
//==========================================================
enum ZBM_ErrorCode ZBM_IsJoinedNetwork(void)
{
    return ZBM_Info.nwk_state;
}
//==========================================================
//	�������ƣ�	ZBM_ResetIO_Init(void)
//
//	�������ܣ�	��λZigBeeģ��ܽų�ʼ��
//
//	��ڲ�����	��
//
//	���ز�����	��
//
//	˵����		
//==========================================================
void ZBM_ResetIO_Init(void)
{
    GPIO_InitTypeDef GPIO_Initure;

    ZBM_IO_RCC_ENABLE();                  	     //����GPIOBʱ��
	 
    GPIO_Initure.Pin   = ZBM_RESET_GPIO_PIN;     //PB14
    GPIO_Initure.Mode  = GPIO_MODE_OUTPUT_PP;    //�������
    GPIO_Initure.Pull  = GPIO_PULLUP;
    GPIO_Initure.Speed = GPIO_SPEED_FREQ_LOW;    //����
    HAL_GPIO_Init(ZBM_RESET_GPIO_PORT, &GPIO_Initure);
}
//==========================================================
//	�������ƣ�	ZBM_Reset
//
//	�������ܣ�	��λZigBee ģ��
//
//	��ڲ�����	��
//
//	���ز�����	��
//
//	˵����		
//==========================================================
void ZBM_Reset(void)
{
    HAL_GPIO_WritePin(ZBM_RESET_GPIO_PORT,ZBM_RESET_GPIO_PIN,GPIO_PIN_SET);	//PB14��1 �����  
    delay_ms(1);    
    HAL_GPIO_WritePin(ZBM_RESET_GPIO_PORT,ZBM_RESET_GPIO_PIN,GPIO_PIN_RESET);	//PB14��0 ����� 
    delay_ms(1); 
    HAL_GPIO_WritePin(ZBM_RESET_GPIO_PORT,ZBM_RESET_GPIO_PIN,GPIO_PIN_SET);	//PB14��1 �����    
    delay_ms(10);    
}
//==========================================================
//	�������ƣ�	ZigBee_Mode_Init
//
//	�������ܣ�	��ʼ��ZigBee ģ��
//
//	��ڲ�����	��
//
//	���ز�����	��
//
//	˵����		
//==========================================================
void ZigBee_Mode_Init(void)
{
    ZBM_ResetIO_Init();
    ZBM_Reset();
    UART2_Init(115200);                          //��ʼ������(��ZigBeeģ��ͨ��)
    
    //�ж�Ƶ��5kz(200us)�����޸�ZigBeeģ���ͨ�Ų����ʣ�
    //��ʱ���ж�Ƶ��ҲҪ�޸ģ��ж�����Ӧ��Ϊ�����ֽڴ���ʱ��
    TIM2_Init(64-1,200) ;                        
    delay_ms(3000);
    if(ZBM_SetDevType(ZBM_Setting.dev_type) == ZBM_FAILED)    //�豸����
    {
        
    }   
    if(ZBM_SetNetworkPAN(ZBM_Setting.pan_id) == ZBM_FAILED)   //���� PAN
    {
           
    }
    if(ZBM_SetNetworkKey(ZBM_Setting.pKey,16) == ZBM_FAILED)  //�����ܳ�
    {
 
    }
    if(ZBM_SetNetworkGrounp(ZBM_Setting.group) == ZBM_FAILED)//�������
    {
        
    }
    if(ZBM_SetChannel(ZBM_Setting.channel) == ZBM_FAILED)    //ͨ���ŵ�
    {
        
    }
    if(ZBM_SetTxPower(ZBM_Setting.txpower) == ZBM_FAILED)     //���͹���
    {

    }
    if(ZBM_SetSerialBaud(ZBM_Setting.baud) == ZBM_FAILED)      //ģ��Ĭ�ϵĲ�������115200����ĳ��������Ĳ��أ��ǵ�MCU�Ĳ�����Ҳ�����޸�
    {
   
    }
    if(ZBM_SetSleepMode(ZBM_Setting.sleepmode))
    {
    
    }
    
    ZBM_Reset();
}






















