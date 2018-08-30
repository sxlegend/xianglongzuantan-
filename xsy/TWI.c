/*
���ļ�ʵ����һ��ģ���I2C���ߣ���ΪSTM32�� Ӳ��I2C����һֱû�е�ͨ
*/
#include "TWI.h"

#define TWI_NOP TWI_Delay()

/*�趨I2C�ٶȣ���λΪHz*/
u32 prv_I2C_Speed =400000; 

/*******************************************************************************
 * ��������:TWI_Delay
 * ��    ��:��ʱ����
 *
 * ��    ��:��
 * ��    ��:��
 * ��    ��:��
 * ��    ��:÷������
 * �޸�����:2010��6��8��
 *******************************************************************************/
void TWI_Delay(void)
{
 u32 i= (u32)(1008000 / prv_I2C_Speed);
 while(i--);
}

/*******************************************************************************
 * ��������:TWI_START
 * ��    ��:��������
 *
 * ��    ��:��
 * ��    ��:��
 * ��    ��:��
 * ��    ��:÷������
 * �޸�����:2010��6��8��
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
 * ��������:TWI_STOP
 * ��    ��:����ֹͣλ
 *
 * ��    ��:��
 * ��    ��:��
 * ��    ��:��
 * ��    ��:÷������
 * �޸�����:2010��6��8��
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
 * ��������:TWI_SendACK
 * ��    ��:�յ�����,����ACK
 *
 * ��    ��:��
 * ��    ��:��
 * ��    ��:��
 * ��    ��:÷������
 * �޸�����:2010��6��8��
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
 * ��������:TWI_SendNACK
 * ��    ��:�յ�����,����NACK
 *
 * ��    ��:��
 * ��    ��:��
 * ��    ��:��
 * ��    ��:÷������
 * �޸�����:2010��6��8��
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
 * ��������:TWI_SendByte
 * ��    ��:����һ���ֽ�
 *
 * ��    ��:��
 * ��    ��:��
 * ��    ��:TWI_ACK/TWI_NACK
 * ��    ��:÷������
 * �޸�����:2010��6��8��
 *******************************************************************************/
u8 TWI_SendByte(u8 Data)
{
 u8 i;
 TWI_SCL_0;
 for(i=0;i<8;i++)
 {
  //---------���ݽ���----------
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
  //---���ݽ�������һ����ʱ----

  //----����һ��������[������]
  TWI_SCL_1;
  TWI_NOP;
  TWI_SCL_0;
  TWI_NOP;//��ʱ,��ֹSCL��û��ɵ�ʱ�ı�SDA,�Ӷ�����START/STOP�ź�
  //---------------------------
 }
 //���մӻ���Ӧ��
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
 * ��������:TWI_ReceiveByte
 * ��    ��:����һ���ֽ�
 *
 * ��    ��:��
 * ��    ��:��
 * ��    ��:���ؽ��յ�������
 * ��    ��:÷������
 * �޸�����:2010��6��8��
 *******************************************************************************/
u8 TWI_ReceiveByte(void)
{
 u8 i,Dat;
 TWI_SDA_1;
 TWI_SCL_0;
 Dat=0;
 for(i=0;i<8;i++)
 {
  TWI_SCL_1;//����ʱ��������[������],�ôӻ�׼��������
  TWI_NOP;
  Dat<<=1;
  if(TWI_SDA_STATE) //������״̬
  {
   Dat|=0x01;
  }
  TWI_SCL_0;//׼�����ٴν�������
  TWI_NOP;//�ȴ�����׼����
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
//�������to Device
//=============================================
void I2C_WriteData(u8 DeveiceAdress, u8 RegiserAddress,u8 mdata)
{
   TWI_START();
   TWI_SendByte(DeveiceAdress); /*д����*/
   TWI_SendByte(RegiserAddress); /*д��ַ*/
   TWI_SendByte(mdata); /*д����*/
   TWI_STOP(); 
}

//=============================================
//�������to Device
//=============================================
void I2C_WriteFMData(u8 DeveiceAdress, u8 RegiserAddress,u8 mdata1,u8 mdata2)
{
   TWI_START();
   TWI_SendByte(DeveiceAdress); /*д����*/
   TWI_SendByte(RegiserAddress); /*д��ַ*/
   TWI_SendByte(mdata1); /*д����*/
   
   TWI_SendByte(mdata2); /*д����*/
   TWI_STOP();
}




void I2C_WriteComm(u8 DeveiceAdress, u8 RegiserAddress)
{
   TWI_START();
   TWI_SendByte(DeveiceAdress); /*д����*/
   TWI_SendByte(RegiserAddress); /*д��ַ*/
//   TWI_SendByte(mdata); /*д����*/
   TWI_STOP();
}
void I2C_WriteData2(u8 DeveiceAdress, u8 RegiserAddress,u8 mdata1,u8 mdata2)
{
   TWI_START();
   TWI_SendByte(DeveiceAdress); /*д����*/
   TWI_SendByte(RegiserAddress); /*д��ַ*/
   TWI_SendByte(mdata1); /*д����*/
   TWI_SendByte(mdata2); /*д����*/
   TWI_STOP();
}

//==========================================
//��������from Device
//==========================================
u8 I2C_ReadData(u8 DeveiceAdress, u8 RegiserAddress) /*���ֽ�*/
{  
   u8 rdata;

   TWI_START();
   TWI_SendByte(DeveiceAdress); /*д����*/
   TWI_SendByte(RegiserAddress); /*д��ַ*/
   TWI_START();
   TWI_SendByte(DeveiceAdress | 0x01); /*������*/
   rdata=TWI_ReceiveByte();
   TWI_SendNACK();
   TWI_STOP();
   return(rdata);
}



//=============================================
//�������to Device
//=============================================
u8 I2C_WriteMultiData(u8 DeveiceAdress, u8 RegiserAddress,u8 mdata[],u8 cnt)
{
   
   u8  ack;
   u8  i;  
   TWI_START();
   
   TWI_SendByte(DeveiceAdress); /*д����*/
   TWI_SendByte(RegiserAddress); /*д����*/   
   
   for(i = 0; i < cnt ; i++)
   {
      ack = TWI_SendByte(mdata[i]); /*д����*/
      
      if(ack == TWI_NACK)
          {
            TWI_STOP(); 
            return (1);
          }
   }     
   TWI_STOP(); 
   return (0);
}


void I2C_ReadMultiData(u8 DeveiceAdress, u8 RegiserAddress , u8  Rx_Buff[], u8  cnt) /*���ֽ�*/
{
   u8 i = 0;
   TWI_START();
   TWI_SendByte(DeveiceAdress); /*д����*/
   TWI_SendByte(RegiserAddress); /*д��ַ*/

   TWI_START();
   TWI_SendByte(DeveiceAdress | 0x01); /*������*/
   
   for(i = 0; i < cnt - 1; i++)
    {
    Rx_Buff[i] = TWI_ReceiveByte();
    TWI_SendACK();
    }
   
    Rx_Buff[cnt - 1] = TWI_ReceiveByte();
    TWI_SendNACK();
    
    TWI_STOP();
}
