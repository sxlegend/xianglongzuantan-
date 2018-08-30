

#include <msp430x14x.h>
#include "Flash.h"

extern int Sav1_D,Sav1_F,Sav2_D,Sav2_F,Sav3_D,Sav3_F;
extern int Sav4_D,Sav4_F,Sav5_D,Sav5_F,Sav6_D,Sav6_F;
extern int Sav7_D,Sav7_F,Sav8_D,Sav8_F,Sav9_D,Sav9_F;

unsigned char FlashSR;
/*=======================�궨��==========================*/
#define DINT    FlashSR=__get_SR_register();_DINT() // ���жϣ�������״̬�Ĵ���
#define EINT    if(FlashSR & GIE)           _EINT() //���ݱ���Ľ���ж� ���ж�
/*=======================================================*/

/************************************************************
* �������ƣ�FlashInit
* ��    �ܣ�Flash��ؼĴ�������Դ��ʼ��
* ��    ������
* �� �� ֵ����
* ˵    ����ʹ�ó����֮ǰӦ�ȵ��ô˺�����
*************************************************************/
void FlashInit()
{
    FCTL2 = FWKEY + FSSEL_2 + FN1;          // Ĭ�� SMCLK/3 =333KHz 
}

/****************************************************************************
* ��    �ƣ�WaitForEnable
* ��    �ܣ�Flashæ�ȴ�
* ��ڲ������� 
* ���ڲ�������
* ˵    ��: ��Flashæ��ȴ���ֱ��Flash�������(����)�ŷ��ء�
****************************************************************************/
void WaitForEnable()
{
    while((FCTL3 & BUSY) == BUSY);      //Busy
}

/****************************************************************************
* ��    �ƣ�FlashErase
* ��    �ܣ�����Flash��һ�����ݶ�
* ��ڲ�����Addr:���������ݶε��׵�ַ 
* ���ڲ�������
****************************************************************************/
void FlashErase(unsigned int Addr)  
{ 
    char *FlashPtr;
    FlashPtr = (char *)Addr;
    FCTL1 = FWKEY + ERASE;                      // Set Erase bit
    FCTL3 = FWKEY;                              // Clear Lock bit
    DINT;
    *FlashPtr = 0;                              // Dummy write to erase Flash segment B
    WaitForEnable();                            //Busy
    EINT;
    FCTL1 = FWKEY;                              // Lock
    FCTL3 = FWKEY + LOCK;                       // Set Lock bit  
}

/****************************************************************************
* ��    �ƣ�FlashWriteChar
* ��    �ܣ���Flash��д��һ���ֽ�(Char�ͱ���)
* ��ڲ�����Addr:������ݵĵ�ַ
            Data:��д�������
* ���ڲ�������
* ˵    ������ַֻ����ż������������������Զ�ǰ��һλ
* ��    ����FlashWriteChar(0x1000,123);������123д��0x1000��Ԫ
            FlashWriteChar(0x1002,a);�����ͱ���aд��0x1002��Ԫ 
****************************************************************************/
void FlashWriteChar(unsigned int addr,char Data)
{
    char *FlashPtr = (char *)addr;              // Segment A pointer
    FCTL1 = FWKEY + WRT;                        // Set WRT bit for write operation
    FCTL3 = FWKEY;                              // Clear Lock bit
    DINT;
    *FlashPtr = Data;                           // Save Data
    WaitForEnable();                            //Busy
    EINT;
    FCTL1 = FWKEY;                              // Clear WRT bit
    FCTL3 = FWKEY + LOCK;                       // Set LOCK bit
}  

/****************************************************************************
* ��    �ƣ�FlashWriteWord
* ��    �ܣ���Flash��д��һ����(�޷������ͱ���)
* ��ڲ�����Addr:������ݵĵ�ַ
            Data:��д�������
* ���ڲ�������
* ��    ����FlashWriteChar(0x1000,123);������123д��0x1000��Ԫ
            FlashWriteChar(0x1002,a);�����ͱ���aд��0x1002��Ԫ 
****************************************************************************/
void FlashWriteWord(unsigned int addr,unsigned int Data)
{
    unsigned int *FlashPtr = (unsigned int *)addr;
    FCTL1 = FWKEY + WRT;                        // Set WRT bit for write operation
    FCTL3 = FWKEY;                              // Clear Lock bit
    DINT;
    *FlashPtr = Data;                           // Save Data
    WaitForEnable();                            //Busy
    EINT;
    FCTL1 = FWKEY;                              // Clear WRT bit
    FCTL3 = FWKEY + LOCK;                       // Set LOCK bit
}  

/****************************************************************************
* ��    �ƣ�FlashReadChar
* ��    �ܣ���Flash�ж�ȡһ���ֽ�
* ��ڲ�����Addr:������ݵĵ�ַ
* ���ڲ��������ص�����
****************************************************************************/
char FlashReadChar(unsigned int Addr)
{ 
    char Data;
    char *FlashPtr = (char *) Addr; 
    Data = *FlashPtr;
    return(Data);
}

/****************************************************************************
* ��    �ƣ�FlashReadWord
* ��    �ܣ���Flash�ж�ȡһ����
* ��ڲ�����Addr:������ݵĵ�ַ
* ���ڲ��������ص����ݣ��޷������ͣ�
****************************************************************************/
unsigned int FlashReadWord(unsigned int Addr)
{ 
    unsigned int Data;
    unsigned int *FlashPtr = (unsigned int *)Addr; 
    Data = *FlashPtr;
    return(Data);
}


void Yaw_SAV()
{
   FlashErase(InfoA);
   FlashWriteWord(InfoA,Sav1_D);
   FlashWriteWord(InfoA+2,Sav1_F);
   FlashWriteWord(InfoA+4,Sav2_D);
   FlashWriteWord(InfoA+6,Sav2_F);
   FlashWriteWord(InfoA+8,Sav3_D);
   FlashWriteWord(InfoA+10,Sav3_F);
   FlashWriteWord(InfoA+12,Sav4_D);
   FlashWriteWord(InfoA+14,Sav4_F);
   FlashWriteWord(InfoA+16,Sav5_D);
   FlashWriteWord(InfoA+18,Sav5_F);
   FlashWriteWord(InfoA+20,Sav6_D);
   FlashWriteWord(InfoA+22,Sav6_F);
   FlashWriteWord(InfoA+24,Sav7_D);
   FlashWriteWord(InfoA+26,Sav7_F);
   FlashWriteWord(InfoA+28,Sav8_D);
   FlashWriteWord(InfoA+30,Sav8_F);
   FlashWriteWord(InfoA+32,Sav9_D);
   FlashWriteWord(InfoA+34,Sav9_F);
  
}
