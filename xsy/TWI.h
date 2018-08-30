
#ifndef _TWI_H_
#define _TWI_H_

#define unsigned  int  u32;
#define unsigned  short int  u16;
#define unsigned  char  u8;

//条件编译 1:使用软件模拟I2C
#define TWI_ENABLE 1

#define TWI_SCL_0      P3OUT &=~BIT0
#define TWI_SCL_1      P3OUT |= BIT0
#define TWI_SDA_0      P2OUT &=~BIT7
#define TWI_SDA_1      P2OUT |= BIT7

#define TWI_SDA_OUT    P2DIR |= BIT7
#define TWI_SDA_IN     P2OUT &=~BIT7
#define TWI_SDA_STATE  I2C_SDA_STATE() 


enum ENUM_TWI_REPLY
{
TWI_NACK=0,TWI_ACK=1
};


enum ENUM_TWI_BUS_STATE
{
TWI_READY=0
,TWI_BUS_BUSY=1
,TWI_BUS_ERROR=2
};





void TWI_Initialize(void);
u8 TWI_START(void);
void TWI_STOP(void);
u8  TWI_SendByte(u8 Data);
u8 TWI_ReceiveByte(void);
void TWI_SendACK(void);
void TWI_SendNACK(void);

void I2C_WriteData2(u8 DeveiceAdress, u8 RegiserAddress,u8 mdata1,u8 mdata2);
void I2C_WriteData(u8 DeveiceAdress, u8 RegiserAddress,u8 mdata);
u8  I2C_ReadData(u8 DeveiceAdress, u8 RegiserAddress);
void I2C_WriteComm(u8 DeveiceAdress, u8 RegiserAddress);

void I2C_WriteData(u8 DeveiceAdress, u8 RegiserAddress,u8 mdata);
u8 I2C_ReadData(u8 DeveiceAdress, u8 RegiserAddress);
void I2C_SpeedSet(u32 Speed2Set);

u8 I2C_WriteMultiData(u8 DeveiceAdress, u8 RegiserAddress,u8 mdata[],u8 cnt);
void I2C_ReadMultiData(u8 DeveiceAdress, u8 RegiserAddress , u8  Rx_Buff[], u8  cnt) ;


#endif

