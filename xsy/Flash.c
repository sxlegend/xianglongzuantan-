

#include <msp430x14x.h>
#include "Flash.h"

extern int Sav1_D,Sav1_F,Sav2_D,Sav2_F,Sav3_D,Sav3_F;
extern int Sav4_D,Sav4_F,Sav5_D,Sav5_F,Sav6_D,Sav6_F;
extern int Sav7_D,Sav7_F,Sav8_D,Sav8_F,Sav9_D,Sav9_F;

unsigned char FlashSR;
/*=======================宏定义==========================*/
#define DINT    FlashSR=__get_SR_register();_DINT() // 关中断，并保存状态寄存器
#define EINT    if(FlashSR & GIE)           _EINT() //根据保存的结果判断 开中断
/*=======================================================*/

/************************************************************
* 函数名称：FlashInit
* 功    能：Flash相关寄存器等资源初始化
* 参    数：无
* 返 回 值：无
* 说    明：使用程序库之前应先调用此函数。
*************************************************************/
void FlashInit()
{
    FCTL2 = FWKEY + FSSEL_2 + FN1;          // 默认 SMCLK/3 =333KHz 
}

/****************************************************************************
* 名    称：WaitForEnable
* 功    能：Flash忙等待
* 入口参数：无 
* 出口参数：无
* 说    明: 若Flash忙则等待，直到Flash操作完成(空闲)才返回。
****************************************************************************/
void WaitForEnable()
{
    while((FCTL3 & BUSY) == BUSY);      //Busy
}

/****************************************************************************
* 名    称：FlashErase
* 功    能：擦除Flash的一个数据段
* 入口参数：Addr:被擦除数据段的首地址 
* 出口参数：无
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
* 名    称：FlashWriteChar
* 功    能：向Flash中写入一个字节(Char型变量)
* 入口参数：Addr:存放数据的地址
            Data:待写入的数据
* 出口参数：无
* 说    明：地址只能是偶数，如果是奇数，会自动前移一位
* 范    例：FlashWriteChar(0x1000,123);将常数123写入0x1000单元
            FlashWriteChar(0x1002,a);将整型变量a写入0x1002单元 
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
* 名    称：FlashWriteWord
* 功    能：向Flash中写入一个字(无符号整型变量)
* 入口参数：Addr:存放数据的地址
            Data:待写入的数据
* 出口参数：无
* 范    例：FlashWriteChar(0x1000,123);将常数123写入0x1000单元
            FlashWriteChar(0x1002,a);将整型变量a写入0x1002单元 
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
* 名    称：FlashReadChar
* 功    能：从Flash中读取一个字节
* 入口参数：Addr:存放数据的地址
* 出口参数：读回的数据
****************************************************************************/
char FlashReadChar(unsigned int Addr)
{ 
    char Data;
    char *FlashPtr = (char *) Addr; 
    Data = *FlashPtr;
    return(Data);
}

/****************************************************************************
* 名    称：FlashReadWord
* 功    能：从Flash中读取一个字
* 入口参数：Addr:存放数据的地址
* 出口参数：读回的数据（无符号整型）
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
