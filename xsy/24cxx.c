#include <msp430x14x.h>
#include "24cxx.h" 



void IICee_SDA_HIGH()
{
 P1DIR |= BIT3;
 P1OUT |= BIT3;
_NOP();
_NOP();
_NOP();
_NOP();
_NOP();
_NOP();
_NOP();
_NOP();
}

void IICee_SDA_LOW()
{
 P1DIR |= BIT3;
 P1OUT &=~ BIT3;
_NOP();
_NOP();
_NOP();
_NOP();
_NOP();
_NOP();
_NOP();
_NOP();

}

void IICee_SCK_HIGH()
{
 P1DIR |= BIT2;
 P1OUT |= BIT2;
_NOP();
_NOP();
_NOP();
_NOP();
_NOP();
_NOP();
_NOP();
_NOP();

}

void IICee_SCK_LOW()
{
 P1DIR |= BIT2;
 P1OUT &=~ BIT2;
_NOP();
_NOP();
_NOP();
_NOP();
_NOP();
_NOP();
_NOP();
_NOP();
 
}


/**********************************************
//IIC Start
**********************************************/
void FM24C16_Start()
{
 
 IICee_SDA_HIGH();
 
 IICee_SCK_HIGH();
 
 IICee_SDA_LOW();

 IICee_SCK_LOW();
}

/**********************************************
//IICT Stop
**********************************************/
void FM24C16_Stop()
{

 IICee_SCK_LOW();
 IICee_SDA_LOW();

// IIC_SCK_LOW();
// for(i=5;i>0;i--)
 IICee_SCK_HIGH();
 
 IICee_SDA_HIGH();

// IIC_SCK_LOW();
// Delay_ms(10);
 
	
}

void IIC_Ack(void)
{
	//IICee_SCK_LOW();
	
	IICee_SDA_LOW();
	
	IICee_SCK_HIGH();
	
	IICee_SCK_LOW();
        
       
}
//不产生ACK应答		    
void IIC_NAck(void)
{
	IICee_SCK_LOW();
	
	IICee_SDA_HIGH();
	
	IICee_SCK_HIGH();
	
	IICee_SCK_LOW();
}

unsigned char FM24C16_Wait_Ack(void)
{
	unsigned char ucErrTime=0;
//	SDA_IN();      //SDA设置为输入  
	//IICee_SDA_HIGH();  
	IICee_SCK_HIGH();
        P1DIR &=~ BIT3;
  
	while(P1IN&BIT3)
	{
		ucErrTime++;
		if(ucErrTime>250)
		{
			FM24C16_Stop();
			return 1;
		}
	}
	IICee_SCK_LOW();//时钟输出0 	   
	return 0; 
       
}

/**********************************************
// IIC Write byte
**********************************************/

void Write_FM24C16_Byte(unsigned char Value)
{
	int i;
        
        IICee_SCK_LOW();
	for(i=0;i<8;i++)		
	{
		if(Value&0x80)
                {
		  IICee_SDA_HIGH();
                }
		else 
                {
                  IICee_SDA_LOW();
                }
		
                
                
                IICee_SCK_HIGH();
                
                
                IICee_SCK_LOW();
                
                Value<<=1;
                
         }
                
 

}

int FM24C16_ReceiveByte(void)
{
 int temp=0;
 int i;
 
// IICee_SDA_HIGH();
   IICee_SCK_LOW();
//  _NOP();
//  _NOP();
//  _NOP();  
 P1DIR &=~ BIT3;
 for(i=0;i<8;i++)
 {
  //IICee_SCK_LOW();//准备好再次接收数据
  IICee_SCK_HIGH();//产生时钟上升沿[正脉冲],让从机准备好数据
  temp<<=1;
  
  if(P1IN&BIT3) //读引脚状态
  {
   temp|=0x01;

  }
  else
  {
   temp&=0xfe;
  }
  
  IICee_SCK_LOW();//准备好再次接收数据

 }
//     if (!ack)
//        IIC_NAck();//发送nACK
//    else
//        IIC_Ack(); //发送ACK 
 return temp;
}

//在AT24CXX指定地址读出一个数据
//ReadAddr:开始读数的地址  
//返回值  :读到的数据
unsigned char AT24CXX_ReadOneByte(unsigned short ReadAddr)
{				  
       int temp=0;		  	    																 
       FM24C16_Start();  
	if(EE_TYPE>AT24C16)
	{
		Write_FM24C16_Byte(0xA0);	   //发送写命令
		FM24C16_Wait_Ack();
		Write_FM24C16_Byte(ReadAddr>>8);//发送高地址
		//IIC_Wait_Ack();		 
	}
        else
        {  
          Write_FM24C16_Byte(0xA0+((ReadAddr/256)<<1));   //发送器件地址0XA0,写数据 	 
        }
	//FM24C16_Wait_Ack();
        IIC_Ack();
        Write_FM24C16_Byte(ReadAddr%256);   //发送低地址
	//FM24C16_Wait_Ack();	
        IIC_Ack();
	FM24C16_Start();  	 	   
	Write_FM24C16_Byte(0xA1);           //进入接收模式			   
	//FM24C16_Wait_Ack();	
        IIC_Ack();
        temp=FM24C16_ReceiveByte();		   
        FM24C16_Stop();//产生一个停止条件	
        //delay_ms(10);	    
	return temp;
}
//在AT24CXX指定地址写入一个数据
//WriteAddr  :写入数据的目的地址    
//DataToWrite:要写入的数据
void AT24CXX_WriteOneByte(unsigned short WriteAddr,unsigned char DataToWrite)
{				   	  	    																 
        FM24C16_Start();  
	if(EE_TYPE>AT24C16)
	{
		Write_FM24C16_Byte(0xA0);	    //发送写命令
		FM24C16_Wait_Ack();
		Write_FM24C16_Byte(WriteAddr>>8);//发送高地址
 	}else
	{
		Write_FM24C16_Byte(0xA0+((WriteAddr/256)<<1));   //发送器件地址0XA0,写数据 
	}	 
	//FM24C16_Wait_Ack();	
        IIC_Ack();
        Write_FM24C16_Byte(WriteAddr%256);   //发送低地址
	//FM24C16_Wait_Ack(); 	
        IIC_Ack();
	Write_FM24C16_Byte(DataToWrite);     //发送字节							   
	//FM24C16_Wait_Ack();  
        IIC_Ack();
        FM24C16_Stop();//产生一个停止条件 
	//delay_ms(10);	 
}
//在AT24CXX里面的指定地址开始写入长度为Len的数据
//该函数用于写入16bit或者32bit的数据.
//WriteAddr  :开始写入的地址  
//DataToWrite:数据数组首地址
//Len        :要写入数据的长度2,4
void AT24CXX_WriteLenByte(unsigned short WriteAddr,unsigned int DataToWrite,unsigned char Len)
{  	
	unsigned char t;
	for(t=0;t<Len;t++)
	{
		AT24CXX_WriteOneByte(WriteAddr+t,(DataToWrite>>(8*t))&0xff);
	}												    
}

//在AT24CXX里面的指定地址开始读出长度为Len的数据
//该函数用于读出16bit或者32bit的数据.
//ReadAddr   :开始读出的地址 
//返回值     :数据
//Len        :要读出数据的长度2,4
unsigned int AT24CXX_ReadLenByte(unsigned short ReadAddr,unsigned char Len)
{  	
	unsigned char t;
	unsigned int temp=0;
	for(t=0;t<Len;t++)
	{
		temp<<=8;
		temp+=AT24CXX_ReadOneByte(ReadAddr+Len-t-1); 	 				   
	}
	return temp;												    
}
//检查AT24CXX是否正常
//这里用了24XX的最后一个地址(255)来存储标志字.
//如果用其他24C系列,这个地址要修改
//返回1:检测失败
//返回0:检测成功
unsigned char AT24CXX_Check(void)
{
	unsigned char temp;
	temp=AT24CXX_ReadOneByte(1023);//避免每次开机都写AT24CXX			   
	if(temp==0x55)
          return 0;		   
	else//排除第一次初始化的情况
	{
	    AT24CXX_WriteOneByte(1023,0x55);
            //delay_ms(500);
	    temp=AT24CXX_ReadOneByte(1023);	  
	    if(temp==0x55)
              return 0;
	}
	return 1;											  
}

//在AT24CXX里面的指定地址开始读出指定个数的数据
//ReadAddr :开始读出的地址 对24c02为0~255
//pBuffer  :数据数组首地址
//NumToRead:要读出数据的个数
void AT24CXX_Read(unsigned short ReadAddr,unsigned char *pBuffer,unsigned short NumToRead)
{
	while(NumToRead)
	{
		*pBuffer++=AT24CXX_ReadOneByte(ReadAddr++);	
		NumToRead--;
	}
}  
//在AT24CXX里面的指定地址开始写入指定个数的数据
//WriteAddr :开始写入的地址 对24c02为0~255
//pBuffer   :数据数组首地址
//NumToWrite:要写入数据的个数
void AT24CXX_Write(unsigned short WriteAddr,unsigned char *pBuffer,unsigned short NumToWrite)
{
	while(NumToWrite--)
	{
		AT24CXX_WriteOneByte(WriteAddr,*pBuffer);
		WriteAddr++;
		pBuffer++;
	}
}
 











