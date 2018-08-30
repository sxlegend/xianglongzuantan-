#ifndef __24CXX_H
#define __24CXX_H

#include   <intrinsics.h> 
#define AT24C01		127
#define AT24C02		255
#define AT24C04		511
#define AT24C08		1023
#define AT24C16		2047
#define AT24C32		4095
#define AT24C64	        8191
#define AT24C128	16383
#define AT24C256	32767 
#define AT24C512        65535
//Mini STM32������ʹ�õ���24c02�����Զ���EE_TYPEΪAT24C02
#define EE_TYPE AT24C16
					  
unsigned char AT24CXX_ReadOneByte(unsigned short ReadAddr);							//ָ����ַ��ȡһ���ֽ�
void AT24CXX_WriteOneByte(unsigned short WriteAddr,unsigned char DataToWrite);		//ָ����ַд��һ���ֽ�
void AT24CXX_WriteLenByte(unsigned short WriteAddr,unsigned int DataToWrite,unsigned char Len);//ָ����ַ��ʼд��ָ�����ȵ�����
unsigned int AT24CXX_ReadLenByte(unsigned short ReadAddr,unsigned char Len);					//ָ����ַ��ʼ��ȡָ����������
void AT24CXX_Write(unsigned short WriteAddr,unsigned char *pBuffer,unsigned short NumToWrite);	//��ָ����ַ��ʼд��ָ�����ȵ�����
void AT24CXX_Read(unsigned short ReadAddr,unsigned char *pBuffer,unsigned short NumToRead);   	//��ָ����ַ��ʼ����ָ�����ȵ�����

unsigned char AT24CXX_Check(void);  //�������



#endif
















