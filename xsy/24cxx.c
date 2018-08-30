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
//������ACKӦ��		    
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
//	SDA_IN();      //SDA����Ϊ����  
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
	IICee_SCK_LOW();//ʱ�����0 	   
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
  //IICee_SCK_LOW();//׼�����ٴν�������
  IICee_SCK_HIGH();//����ʱ��������[������],�ôӻ�׼��������
  temp<<=1;
  
  if(P1IN&BIT3) //������״̬
  {
   temp|=0x01;

  }
  else
  {
   temp&=0xfe;
  }
  
  IICee_SCK_LOW();//׼�����ٴν�������

 }
//     if (!ack)
//        IIC_NAck();//����nACK
//    else
//        IIC_Ack(); //����ACK 
 return temp;
}

//��AT24CXXָ����ַ����һ������
//ReadAddr:��ʼ�����ĵ�ַ  
//����ֵ  :����������
unsigned char AT24CXX_ReadOneByte(unsigned short ReadAddr)
{				  
       int temp=0;		  	    																 
       FM24C16_Start();  
	if(EE_TYPE>AT24C16)
	{
		Write_FM24C16_Byte(0xA0);	   //����д����
		FM24C16_Wait_Ack();
		Write_FM24C16_Byte(ReadAddr>>8);//���͸ߵ�ַ
		//IIC_Wait_Ack();		 
	}
        else
        {  
          Write_FM24C16_Byte(0xA0+((ReadAddr/256)<<1));   //����������ַ0XA0,д���� 	 
        }
	//FM24C16_Wait_Ack();
        IIC_Ack();
        Write_FM24C16_Byte(ReadAddr%256);   //���͵͵�ַ
	//FM24C16_Wait_Ack();	
        IIC_Ack();
	FM24C16_Start();  	 	   
	Write_FM24C16_Byte(0xA1);           //�������ģʽ			   
	//FM24C16_Wait_Ack();	
        IIC_Ack();
        temp=FM24C16_ReceiveByte();		   
        FM24C16_Stop();//����һ��ֹͣ����	
        //delay_ms(10);	    
	return temp;
}
//��AT24CXXָ����ַд��һ������
//WriteAddr  :д�����ݵ�Ŀ�ĵ�ַ    
//DataToWrite:Ҫд�������
void AT24CXX_WriteOneByte(unsigned short WriteAddr,unsigned char DataToWrite)
{				   	  	    																 
        FM24C16_Start();  
	if(EE_TYPE>AT24C16)
	{
		Write_FM24C16_Byte(0xA0);	    //����д����
		FM24C16_Wait_Ack();
		Write_FM24C16_Byte(WriteAddr>>8);//���͸ߵ�ַ
 	}else
	{
		Write_FM24C16_Byte(0xA0+((WriteAddr/256)<<1));   //����������ַ0XA0,д���� 
	}	 
	//FM24C16_Wait_Ack();	
        IIC_Ack();
        Write_FM24C16_Byte(WriteAddr%256);   //���͵͵�ַ
	//FM24C16_Wait_Ack(); 	
        IIC_Ack();
	Write_FM24C16_Byte(DataToWrite);     //�����ֽ�							   
	//FM24C16_Wait_Ack();  
        IIC_Ack();
        FM24C16_Stop();//����һ��ֹͣ���� 
	//delay_ms(10);	 
}
//��AT24CXX�����ָ����ַ��ʼд�볤��ΪLen������
//�ú�������д��16bit����32bit������.
//WriteAddr  :��ʼд��ĵ�ַ  
//DataToWrite:���������׵�ַ
//Len        :Ҫд�����ݵĳ���2,4
void AT24CXX_WriteLenByte(unsigned short WriteAddr,unsigned int DataToWrite,unsigned char Len)
{  	
	unsigned char t;
	for(t=0;t<Len;t++)
	{
		AT24CXX_WriteOneByte(WriteAddr+t,(DataToWrite>>(8*t))&0xff);
	}												    
}

//��AT24CXX�����ָ����ַ��ʼ��������ΪLen������
//�ú������ڶ���16bit����32bit������.
//ReadAddr   :��ʼ�����ĵ�ַ 
//����ֵ     :����
//Len        :Ҫ�������ݵĳ���2,4
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
//���AT24CXX�Ƿ�����
//��������24XX�����һ����ַ(255)���洢��־��.
//���������24Cϵ��,�����ַҪ�޸�
//����1:���ʧ��
//����0:���ɹ�
unsigned char AT24CXX_Check(void)
{
	unsigned char temp;
	temp=AT24CXX_ReadOneByte(1023);//����ÿ�ο�����дAT24CXX			   
	if(temp==0x55)
          return 0;		   
	else//�ų���һ�γ�ʼ�������
	{
	    AT24CXX_WriteOneByte(1023,0x55);
            //delay_ms(500);
	    temp=AT24CXX_ReadOneByte(1023);	  
	    if(temp==0x55)
              return 0;
	}
	return 1;											  
}

//��AT24CXX�����ָ����ַ��ʼ����ָ������������
//ReadAddr :��ʼ�����ĵ�ַ ��24c02Ϊ0~255
//pBuffer  :���������׵�ַ
//NumToRead:Ҫ�������ݵĸ���
void AT24CXX_Read(unsigned short ReadAddr,unsigned char *pBuffer,unsigned short NumToRead)
{
	while(NumToRead)
	{
		*pBuffer++=AT24CXX_ReadOneByte(ReadAddr++);	
		NumToRead--;
	}
}  
//��AT24CXX�����ָ����ַ��ʼд��ָ������������
//WriteAddr :��ʼд��ĵ�ַ ��24c02Ϊ0~255
//pBuffer   :���������׵�ַ
//NumToWrite:Ҫд�����ݵĸ���
void AT24CXX_Write(unsigned short WriteAddr,unsigned char *pBuffer,unsigned short NumToWrite)
{
	while(NumToWrite--)
	{
		AT24CXX_WriteOneByte(WriteAddr,*pBuffer);
		WriteAddr++;
		pBuffer++;
	}
}
 











