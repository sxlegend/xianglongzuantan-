#include "UART.h"
//#include "Config.h"

#define CPU_F ((double)8000000)   //�ⲿ��Ƶ����8MHZ
//���ڲ����ʼ��㣬��BRCLK=CPU_Fʱ������Ĺ�ʽ���Լ��㣬����Ҫ�������ü����Ƶϵ��
#define baud           9600                                //���ò����ʵĴ�С
#define baud_setting   (unsigned int)((unsigned long)CPU_F/((unsigned long)baud))  //�����ʼ��㹫ʽ
#define baud_h         (unsigned char)(baud_setting>>8)            //��ȡ��λ
#define baud_l         (unsigned char)(baud_setting)               //��λ

extern unsigned char flag_TX0,flag_TX1,flag_1,flag_2,m1,m;
extern long yaw,Roll;
extern unsigned char RX_BUFF[11];
extern void delay_ms(unsigned long ms);                        // ��ʱ�ӳ���
extern unsigned char Angle_YawF,Angle_DWF,flag_netive;
extern char Angle_RollF;
extern int Angle_YawD,Angle_RollD,Angle_DWD;
extern int readcont;
unsigned char flag_JZ1,flag_JZ2,flag_jz;
char XOR_check(unsigned char *buff, int len);
unsigned char JZ_BUFF[5];
//*************************************************************************
//               MSP430���ڳ�ʼ��
//*************************************************************************


void UART_Init1()
{
  U1CTL|=SWRST + CHAR;                //��λSWRST��8λ����ģʽ
  U1TCTL|=SSEL1;                      //SMCLKΪ����ʱ��
  U1BR1=baud_h;                       //BRCLK=8MHZ,Baud=BRCLK/N
  U1BR0=baud_l;                       //N=UBR+(UxMCTL)/8
  U1MCTL=0x00;                        //΢���Ĵ���Ϊ0��������9600bps
  ME2|=UTXE1;                         //UART1����ʹ��
  ME2|=URXE1;                         //UART1����ʹ��
  U1CTL&=~SWRST;
  IE2|=URXIE1;                        //�����ж�ʹ��λ
  
  P3SEL|= (BIT6 + BIT7);                //����IO��Ϊ�ڶ�����ģʽ������UART����
  P3DIR|= BIT6;                       //����TXD1�ڷ���Ϊ���
  
  P4DIR |= (BIT1+BIT2);
  P4OUT |= (BIT1+BIT2);
}


//*************************************************************************
//              ����1�������ݺ���
//*************************************************************************

void Send_Byte(unsigned char data)
{
  while(!(IFG2&UTXIFG1));          //���ͼĴ����յ�ʱ��������
    U1TXBUF=data;
}

//*************************************************************************
//              ����1�����ַ�������
//*************************************************************************
void Print_Str(unsigned char *s)
{
    while(*s != '\0')
    {
        Send_Byte(*s++);
    }
}

//*************************************************************************
//             bluetooth����
//*************************************************************************
void LYPD()
{
   unsigned char test1[4]={0x2B,0x2B,0x2B,0x61};     
   unsigned char test2[10]={0x41,0x54,0x2B,0x53,0x43,0x41,0x4E,0x3F,0x0D,0x0A};
   unsigned char test3[11]={0x41,0x54,0x2B,0x43,0x4F,0x4E,0x4E,0x3D,0x31,0x0D,0x0A};

   for(int i=0;i<4;i++)
   {
    Send_Byte(test1[i]);
   }
   delay_ms(500);


   for(int i=0;i<10;i++)
   {
    Send_Byte(test2[i]);
   }   
   delay_ms(500);
   delay_ms(500);
   delay_ms(500);
   delay_ms(500);
   delay_ms(500);
   delay_ms(500); 
   
   for(int i=0;i<11;i++)
   {
    Send_Byte(test3[i]);
   }
   delay_ms(500);
   delay_ms(500);
   delay_ms(500);
   delay_ms(500);
   delay_ms(500);
}


//*************************************************************************
//              ���ܴ���������
//*************************************************************************
char checktoken=0;
void RX()
{
  unsigned char data;
  

    data=U1RXBUF;  
    if(data==0xA5)
      {
        flag_1=1;
        m1=1;
      }
     
    else if(flag_1==1)
    {
        m1++;
        if(m1==2)//�趨��2λΪ�ж�λ
        {
          if(data==0x5A)  //�ڶ�λ�����ж�
          {
            flag_2=1;
            flag_1=0;
            m=2;
          }
          else
          m1=0;
          flag_1=0;
        }
    }
    
     else if(flag_2==1)
      {
        RX_BUFF[m]=data;
        m++;
        if(m>10)
        { 
          readcont=0;
          m=0;

          flag_1=0;
          flag_2=0;
          RX_BUFF[0]=0xA5;
          RX_BUFF[1]=0x5A;
          checktoken=XOR_check(RX_BUFF,10);
          if(checktoken==RX_BUFF[10])
          {  
          
          Angle_YawD=(RX_BUFF[4]<<8)+RX_BUFF[5];
          Angle_YawF=RX_BUFF[6];
          Angle_RollD=(RX_BUFF[7]<<8)+RX_BUFF[8];
          Angle_RollF=RX_BUFF[9];
          if(Angle_RollD<0)
          {
            flag_netive=1;
            Angle_RollD=-Angle_RollD;
          }

          else if((Angle_RollF>127)&&(Angle_RollD==0))
          {
            flag_netive=1;
            Angle_RollF=-Angle_RollF;
          }
          else
          {
            flag_netive=0;
           }
         
          }
        }
      }
    
        if(data==0xB5)
      {
        flag_JZ1=1;
        m1=1;
      }
     
    else if(flag_JZ1==1)
    {
        m1++;
        if(m1==2)//�趨��2λΪ�ж�λ
        {
          if(data==0x5B)  //�ڶ�λ�����ж�
          {
            flag_JZ2=1;
            flag_JZ1=0;
            m=2;
          }
          else
          m1=0;
          flag_JZ1=0;
        }
    }
    
     else if(flag_JZ2==1)
      {
        JZ_BUFF[m]=data;
        m++;
        if(m>4)
        { 
          readcont=0;
          m=0;

          flag_JZ1=0;
          flag_JZ2=0;
          JZ_BUFF[0]=0xB5;
          JZ_BUFF[1]=0x5B;
          checktoken=XOR_check(JZ_BUFF,4);
          if(checktoken==JZ_BUFF[4])
          {  
            if(JZ_BUFF[2]==0x00)
            {
              if(JZ_BUFF[3]==0x01)          //��б�Ǵ�ֱУ׼
              flag_jz=1;
              else if(JZ_BUFF[3]==0x02)     //��б��ˮƽУ׼
              flag_jz=2;
            }
            else if(JZ_BUFF[2]==0x01)       //��λ�ǽǶ�����
            {
              if(JZ_BUFF[3]==0x01)
              flag_jz=3;
              else if(JZ_BUFF[3]==0x02)      //��λ�ǽǶȶ�λ
              flag_jz=4;
            }
          }
        }
      }
  
  }
  

char XOR_check(unsigned char *buff, int len)
{
  char checksum=buff[0];
  for(int i=1;i<len;i++)
  {
    checksum^=buff[i];
  }
  
  return checksum;
}