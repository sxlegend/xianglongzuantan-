/*
本文件实现了一个模拟的I2C总线，因为STM32的 硬件I2C总线一直没有调通
*/
#include "TWI.h"

#define TWI_NOP TWI_Delay()

/*设定I2C速度，单位为Hz*/
u32 prv_I2C_Speed =400000; 

/*******************************************************************************
 * 函数名称:TWI_Delay
 * 描    述:延时函数
 *
 * 输    入:无
 * 输    出:无
 * 返    回:无
 * 作    者:梅川酷子
 * 修改日期:2010年6月8日
 *******************************************************************************/
void TWI_Delay(void)
{
 u32 i= (u32)(1008000 / prv_I2C_Speed);
 while(i--);
}

/*******************************************************************************
 * 函数名称:TWI_START
 * 描    述:发送启动
 *
 * 输    入:无
 * 输    出:无
 * 返    回:无
 * 作    者:梅川酷子
 * 修改日期:2010年6月8日
 *******************************************************************************/
u8 TWI_START(void)
{
 TWI_SDA_1;
 TWI_NOP;

 TWI_SCL_1;
 TWI_NOP;

 if(!TWI_SDA_STATE)
 {
  ////DebugPrint("TWI_START:BUSY\n");
  return TWI_BUS_BUSY;
 }
 TWI_SDA_0;
 TWI_NOP;

 TWI_SCL_0;
 TWI_NOP;

 if(TWI_SDA_STATE)
 {
  ////DebugPrint("TWI_START:BUS ERROR\n");
  return TWI_BUS_ERROR;
 }

 return TWI_READY;
}

/*******************************************************************************
 * 函数名称:TWI_STOP
 * 描    述:发送停止位
 *
 * 输    入:无
 * 输    出:无
 * 返    回:无
 * 作    者:梅川酷子
 * 修改日期:2010年6月8日
 *******************************************************************************/
void TWI_STOP(void)
{
 TWI_SDA_0;
 TWI_NOP;

 TWI_SCL_1;
 TWI_NOP;

 TWI_SDA_1;
 TWI_NOP;

// TWI_SCL_0;
// TWI_NOP;

 //////DebugPrint("TWI_STOP\n");
}

/*******************************************************************************
 * 函数名称:TWI_SendACK
 * 描    述:收到数据,发送ACK
 *
 * 输    入:无
 * 输    出:无
 * 返    回:无
 * 作    者:梅川酷子
 * 修改日期:2010年6月8日
 *******************************************************************************/
void TWI_SendACK(void)
{
 TWI_SDA_0;
 TWI_NOP;
 TWI_SCL_1;
 TWI_NOP;
 TWI_SCL_0;
 TWI_NOP;
 //////DebugPrint("TWI_SendACK\n");
}

/*******************************************************************************
 * 函数名称:TWI_SendNACK
 * 描    述:收到数据,发送NACK
 *
 * 输    入:无
 * 输    出:无
 * 返    回:无
 * 作    者:梅川酷子
 * 修改日期:2010年6月8日
 *******************************************************************************/
void TWI_SendNACK(void)
{
 TWI_SDA_1;
 TWI_NOP;
 TWI_SCL_1;
 TWI_NOP;
 TWI_SCL_0;
 TWI_NOP;
 //////DebugPrint("TWI_SendNACK\n");
}

/*******************************************************************************
 * 函数名称:TWI_SendByte
 * 描    述:发送一个字节
 *
 * 输    入:无
 * 输    出:无
 * 返    回:TWI_ACK/TWI_NACK
 * 作    者:梅川酷子
 * 修改日期:2010年6月8日
 *******************************************************************************/
u8 TWI_SendByte(u8 Data)
{
 u8 i;
 TWI_SCL_0;
 for(i=0;i<8;i++)
 {
  //---------数据建立----------
  if(Data&0x80)
  {
   TWI_SDA_1;
  }
  else
  {
   TWI_SDA_0;
  }
  Data<<=1;
  TWI_NOP;
  //---数据建立保持一定延时----

  //----产生一个上升沿[正脉冲]
  TWI_SCL_1;
  TWI_NOP;
  TWI_SCL_0;
  TWI_NOP;//延时,防止SCL还没变成低时改变SDA,从而产生START/STOP信号
  //---------------------------
 }
 //接收从机的应答
 TWI_SDA_1;
 TWI_NOP;
 TWI_SCL_1;
 TWI_NOP;
 if(TWI_SDA_STATE)
 {
  TWI_SCL_0;
  //////DebugPrint("TWI_NACK!\n");
  return TWI_NACK;
 }
 else
 {
  TWI_SCL_0;
  //////DebugPrint("TWI_ACK!\n");
  return TWI_ACK;
 }
}

/*******************************************************************************
 * 函数名称:TWI_ReceiveByte
 * 描    述:接收一个字节
 *
 * 输    入:无
 * 输    出:无
 * 返    回:返回接收到的数据
 * 作    者:梅川酷子
 * 修改日期:2010年6月8日
 *******************************************************************************/
u8 TWI_ReceiveByte(void)
{
 u8 i,Dat;
 TWI_SDA_1;
 TWI_SCL_0;
 Dat=0;
 for(i=0;i<8;i++)
 {
  TWI_SCL_1;//产生时钟上升沿[正脉冲],让从机准备好数据
  TWI_NOP;
  Dat<<=1;
  if(TWI_SDA_STATE) //读引脚状态
  {
   Dat|=0x01;
  }
  TWI_SCL_0;//准备好再次接收数据
  TWI_NOP;//等待数据准备好
 }
 //////DebugPrint("TWI_Dat:%x\n",Dat);
 return Dat;
}


/*-------------------------I2C_BUS------------------------*/

void I2C_SpeedSet(u32 Speed2Set)
{
    prv_I2C_Speed = Speed2Set; 
}


//=============================================
//输出数据to Device
//=============================================
void I2C_WriteData(u8 DeveiceAdress, u8 RegiserAddress,u8 mdata)
{
   TWI_START();
   TWI_SendByte(DeveiceAdress); /*写命令*/
   TWI_SendByte(RegiserAddress); /*写地址*/
   TWI_SendByte(mdata); /*写数据*/
   TWI_STOP(); 
}

//=============================================
//输出数据to Device
//=============================================
void I2C_WriteFMData(u8 DeveiceAdress, u8 RegiserAddress,u8 mdata1,u8 mdata2)
{
   TWI_START();
   TWI_SendByte(DeveiceAdress); /*写命令*/
   TWI_SendByte(RegiserAddress); /*写地址*/
   TWI_SendByte(mdata1); /*写数据*/
   
   TWI_SendByte(mdata2); /*写数据*/
   TWI_STOP();
}




void I2C_WriteComm(u8 DeveiceAdress, u8 RegiserAddress)
{
   TWI_START();
   TWI_SendByte(DeveiceAdress); /*写命令*/
   TWI_SendByte(RegiserAddress); /*写地址*/
//   TWI_SendByte(mdata); /*写数据*/
   TWI_STOP();
}
void I2C_WriteData2(u8 DeveiceAdress, u8 RegiserAddress,u8 mdata1,u8 mdata2)
{
   TWI_START();
   TWI_SendByte(DeveiceAdress); /*写命令*/
   TWI_SendByte(RegiserAddress); /*写地址*/
   TWI_SendByte(mdata1); /*写数据*/
   TWI_SendByte(mdata2); /*写数据*/
   TWI_STOP();
}

//==========================================
//输入数据from Device
//==========================================
u8 I2C_ReadData(u8 DeveiceAdress, u8 RegiserAddress) /*单字节*/
{  
   u8 rdata;

   TWI_START();
   TWI_SendByte(DeveiceAdress); /*写命令*/
   TWI_SendByte(RegiserAddress); /*写地址*/
   TWI_START();
   TWI_SendByte(DeveiceAdress | 0x01); /*读命令*/
   rdata=TWI_ReceiveByte();
   TWI_SendNACK();
   TWI_STOP();
   return(rdata);
}



//=============================================
//输出数据to Device
//=============================================
u8 I2C_WriteMultiData(u8 DeveiceAdress, u8 RegiserAddress,u8 mdata[],u8 cnt)
{
   
   u8  ack;
   u8  i;  
   TWI_START();
   
   TWI_SendByte(DeveiceAdress); /*写命令*/
   TWI_SendByte(RegiserAddress); /*写命令*/   
   
   for(i = 0; i < cnt ; i++)
   {
      ack = TWI_SendByte(mdata[i]); /*写命令*/
      
      if(ack == TWI_NACK)
          {
            TWI_STOP(); 
            return (1);
          }
   }     
   TWI_STOP(); 
   return (0);
}


void I2C_ReadMultiData(u8 DeveiceAdress, u8 RegiserAddress , u8  Rx_Buff[], u8  cnt) /*多字节*/
{
   u8 i = 0;
   TWI_START();
   TWI_SendByte(DeveiceAdress); /*写命令*/
   TWI_SendByte(RegiserAddress); /*写地址*/

   TWI_START();
   TWI_SendByte(DeveiceAdress | 0x01); /*读命令*/
   
   for(i = 0; i < cnt - 1; i++)
    {
    Rx_Buff[i] = TWI_ReceiveByte();
    TWI_SendACK();
    }
   
    Rx_Buff[cnt - 1] = TWI_ReceiveByte();
    TWI_SendNACK();
    
    TWI_STOP();
}
