
#include <msp430x14x.h>
#include "Config.h" 
#include <Ctype.h>
#include"stdio.h"
#include "OLED.h"
#include "FUN.h"
#include "Flash.h"
#include "bmp.h"
#include "conver.h"
#include "ADC.h"
#include "Key.h"
#include "UART.h"
#include "realtime.h"
#include "24cxx.h" 
#include <string.h>






int Angle_YawD,Angle_RollD;
unsigned char Angle_YawF,Angle_DWF;
char Angle_RollF;
int Angle_YawD,Angle_RollD,Angle_DWD;

unsigned char flag_adc,num;
unsigned int TEMP;
long long TEMP_yaw,TEMP_Roll;
unsigned char key,key_num,flag_JP;
unsigned char flag_Jgkg,flag_netive,flag_DW,flag_FWQL,flag_SPXZ,flag_plus;
unsigned char flag_page,flag_SAV;

unsigned char  func_index=0,Addr_num;
unsigned char flag_TX0,flag_TX1,flag_1,flag_2,m1,m;
long yaw,Roll;

unsigned char RX_BUFF[11];

unsigned char SET_Angle;
int Sav1_D,Sav1_F,Sav2_D,Sav2_F,Sav3_D,Sav3_F;
int Sav4_D,Sav4_F,Sav5_D,Sav5_F,Sav6_D,Sav6_F;
int Sav7_D,Sav7_F,Sav8_D,Sav8_F,Sav9_D,Sav9_F;

unsigned int AD_BATV,TEMP_AD,AD_num;
unsigned long AD_BAT;
Time Realtime;

int hour,min,sec;
void (*current_operation_index)();
int readcont=0;
typedef struct
   {
	uchar current;
	uchar up;//���Ϸ�������
	uchar down;//���·�������
	uchar enter;//ȷ�Ϸ�������
	void (*current_operation)();
    } key_table;

key_table const table[30]=
 {
 	{0,0,0,1,(*fun1)},//��һ�� OLED  ��λ��   ��һ�� OLEDT  ��б��
        
        {1,5,2,6,(*fun2)},//�ڶ��� �������� ����λ������ �� ��б������                         
        {2,1,3,10,(*fun3)},//�ڶ��� �������� ��λ������  �� ��б�����á�
	{3,2,4,13,(*fun4)},//�ڶ��� �������� ��б������  ���������á�
	{4,3,5,14,(*fun5)},//�ڶ��� ��������  �������   ��ʱ�����á� 
      	{5,4,1,0,(*fun6)},//�ڶ��� ��������  ʱ������   �����ء�
        
	{6,9,7,6,(*fun7)},//������  ��λ�� ����λ�����á� �Ƕȶ�λ 
	{7,6,8,18,(*fun8)}, //������  ��λ�� ��λ������ ���Ƕȶ�λ��  
        {8,7,9,17,(*fun9)},//������  ��λ�� �Ƕȶ�λ���Ƕ����㡿 
	{9,8,6,1,(*fun10)},//������  ��λ��  ��λ��  �����ء�		
        
	{10,12,11,16,(*fun11)},//������  ��б�� ��ˮƽУ׼�� ��ֱУ׼  
	{11,10,12,15,(*fun12)}, // ������  ��б�� ˮƽУ׼ ����ֱУ׼�� 	
       	{12,11,10,2,(*fun13)},//������  ��б�� ��ֱУ׼  �����ء�	
        
	{13,13,13,3,(*fun14)}, //������  ��������     �����ء�
       	{14,14,14,4,(*fun15)}, //������  ʱ������     �����ء�    
        
        {15,15,15,11,(*fun16)}, //���Ĳ�  ��ֱУ׼   �����ء�
        
        {16,16,16,10,(*fun17)}, //���Ĳ�  ˮƽУ׼   �����ء�
        
        {17,17,17,8,(*fun18)}, //���Ĳ�  ��λ������   �����ء�
        {18,18,18,7,(*fun19)}, //���Ĳ�  ��λ�Ƕ�λ   �����ء�
//        
//	{15,17,16,22,(*fun12)},// ���Ĳ�  ��λ������ �����붨λ�� �� ��ȡ��λ��  
// 	{16,15,17,23,(*fun13)}, //���Ĳ�  ��λ������ ���붨λ��  ����ȡ��λ�ǡ�  
//        {17,16,15,6,(*fun14)}, //���Ĳ� ��λ������ ��ȡ��λ��  �����ء�	
//        
//	{18,18,18,7,(*fun15)}, //���Ĳ�  ��λ�Ƕ�λ     �����ء�
//       	{19,19,19,7,(*fun16)}, //���Ĳ�  ��λ������     �����ء� 
//        
//        {20,20,20,10,(*fun17)}, //���Ĳ�  ˮƽУ׼   �����ء� 
//        {21,21,21,11,(*fun18)}, //���Ĳ�  ˮƽ�Ƕ�����   �����ء�
//        
//        {22,22,22,15,(*fun19)}, //�����  ���붨λ�Ƕ�   �����ء�
//        {23,23,23,16,(*fun20)}, //�����  ��ȡ��λ�Ƕ�   �����ء�
        
               	
};

//��ʱ��B��ʼ��
void InitTimerB()
{
  TBCTL=TBSSEL1+ID1+ID0+MC0+TBCLR;//ѡ��1/8SMCLK ������ ���TAR
  TBCCTL0=CCIE;//CCR0�ж����� �Ƚ�ģʽ
  TBCCR0=10000;//ʱ����10ms
}

unsigned char buff[50];
//int x=0;
int main( void )
{
  // Stop watchdog timer to prevent time out reset
  WDTCTL = WDTPW + WDTHOLD;
  
  
  Clock_Init();                       //ϵͳʱ������
  

 
  InitTimerB();

  delay_ms(500);                      //��ʱ100ms
  

   UART_Init1();                        //�����������ó�ʼ��
  

   P1DIR|=BIT5+BIT6;                 //OLED IIC�˿� P1.5 P1.6
   P1OUT&= ~(BIT5+BIT6);
   
   P2DIR|=BIT5+BIT6;                 //OLEDT IIC�˿� P2.5 P2.6
   P2OUT&= ~(BIT5+BIT6);

   
   ADC_Init();                         //��ʼ��ADC����

   _EINT();                            //ʹ���ж�
 
  OLED_Init();			//��ʼ��OLED  
  OLED_Clear(); 
  OLEDT_Init();			//��ʼ��OLED  
  OLEDT_Clear(); 
 


  while(1)
  {
//     RX_BUFF[0]=0x01;
//     RX_BUFF[1]=0x02;
//     RX_BUFF[2]=0x11;
//     AT24CXX_WriteOneByte(0x00,0x03);
//     buff[2]=AT24CXX_ReadOneByte(0x00);
//     AT24CXX_Write(0x00,RX_BUFF,3);
//     AT24CXX_Read(0x00,buff,3);
   
      Get_Time(&Realtime);
      hour=Realtime.hour;
      min=Realtime.minute;
      sec=Realtime.second;
   




      ADC12CTL0 |= ADC12SC;           //����ת��
      
      TEMP = ADC12MEM0;

                                      
   key=ReadKey();
   if(key!=0xFF)    
   {  
     switch(key)
    {
      
      case 0x33: 
       if(flag_JP==0)
        {
          func_index=table[func_index].down;  

        }
        else
        {
          key_num=5;
        }  

      break;    
      
      case 0x31: 
       if(flag_page==14)
        {
          key_num=14;
        }         
          
       else if(flag_page==15)
        {
          key_num=15;
        }
       else if(flag_page==16)
        {
          key_num=16;
        }
       else if(flag_page==17)
        {
          key_num=17;
        }
       
        else if(flag_page==18)
        {
          key_num=18;
        }
       
        else if(flag_page==19)
        {
          key_num=19;
        }
       
       else if(flag_page==20)
        {
          key_num=20;
        }
       else if(flag_page==21)
        {
          key_num=21;
        }
        else if(flag_page==22)
        {
          key_num=22;
        }
       else
        {
          key_num=3;
        }
        

      break;        //����ͬ�ļ�����ֵ����ֵ2����2��LED��
      
      case 0x30:
       if(flag_JP==0)
        { 
          func_index=table[func_index].enter; 

        }
        else
        {
          key_num=2;
        }
        

      break;	 //����ͬ�ļ�����ֵ����ֵ3����2��LED��
                  
      case 0x32: 

        if(flag_JP==0)
        { 
          func_index=table[func_index].up; 
   
        }
        else
        {
         
          key_num=1;
          
        }

       break;	 //����ͬ�ļ�����ֵ����ֵ4����2��LED��
       
       default:
         key_num=0xFF;
       break;
                                  
      }
     //clear_ddram();          
   } 

     current_operation_index=table[func_index].current_operation;//ȡcurrent_operation_index��ַ
    (*current_operation_index)();//ִ��*current_operation_index��ַ���� 

       
          
  } 


  
  
  // return 0;
}


//��ʱ��B�ж�
#pragma vector=TIMERB0_VECTOR
__interrupt void TimerBINT()
{
      KeyProcess();
      ADC12CTL0 |= ADC12SC;           //����ת��
      TEMP_AD = ADC12MEM0;
      AD_BAT=AD_BAT+TEMP_AD;
      AD_num++;
      if(AD_num>99)
      {
        AD_num=0;
        AD_BATV=AD_BAT/100;          //�޸���ֵ��3.3��������
        AD_BAT=0;
      } 
  
  num++;
  if(num>100)
  {
     readcont++;
     num=0;//�ж�50��Ϊ0.5s
  }
  else if(readcont>10)
  {
   Angle_YawD=0;
   Angle_YawF=0;
   Angle_RollD=0;
   Angle_RollF=0;
   flag_netive=0;
   readcont=0;
  }
}



//*************************************************************************
//               �������Դ���1�Ľ����ж�
//*************************************************************************

#pragma vector=UART1RX_VECTOR
__interrupt void UART1_RX_ISR(void)
{
   
   RX();
}

