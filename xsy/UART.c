#include "UART.h"
//#include "Config.h"

#define CPU_F ((double)8000000)   //外部高频晶振8MHZ
//串口波特率计算，当BRCLK=CPU_F时用下面的公式可以计算，否则要根据设置加入分频系数
#define baud           9600                                //设置波特率的大小
#define baud_setting   (unsigned int)((unsigned long)CPU_F/((unsigned long)baud))  //波特率计算公式
#define baud_h         (unsigned char)(baud_setting>>8)            //提取高位
#define baud_l         (unsigned char)(baud_setting)               //低位

extern unsigned char flag_TX0,flag_TX1,flag_1,flag_2,m1,m;
extern long yaw,Roll;
extern unsigned char RX_BUFF[11];
extern void delay_ms(unsigned long ms);                        // 延时子程序
extern unsigned char Angle_YawF,Angle_DWF,flag_netive;
extern char Angle_RollF;
extern int Angle_YawD,Angle_RollD,Angle_DWD;
extern int readcont;
unsigned char flag_JZ1,flag_JZ2,flag_jz;
char XOR_check(unsigned char *buff, int len);
unsigned char JZ_BUFF[5];
//*************************************************************************
//               MSP430串口初始化
//*************************************************************************


void UART_Init1()
{
  U1CTL|=SWRST + CHAR;                //复位SWRST，8位数据模式
  U1TCTL|=SSEL1;                      //SMCLK为串口时钟
  U1BR1=baud_h;                       //BRCLK=8MHZ,Baud=BRCLK/N
  U1BR0=baud_l;                       //N=UBR+(UxMCTL)/8
  U1MCTL=0x00;                        //微调寄存器为0，波特率9600bps
  ME2|=UTXE1;                         //UART1发送使能
  ME2|=URXE1;                         //UART1接收使能
  U1CTL&=~SWRST;
  IE2|=URXIE1;                        //接收中断使能位
  
  P3SEL|= (BIT6 + BIT7);                //设置IO口为第二功能模式，启用UART功能
  P3DIR|= BIT6;                       //设置TXD1口方向为输出
  
  P4DIR |= (BIT1+BIT2);
  P4OUT |= (BIT1+BIT2);
}


//*************************************************************************
//              串口1发送数据函数
//*************************************************************************

void Send_Byte(unsigned char data)
{
  while(!(IFG2&UTXIFG1));          //发送寄存器空的时候发送数据
    U1TXBUF=data;
}

//*************************************************************************
//              串口1发送字符串函数
//*************************************************************************
void Print_Str(unsigned char *s)
{
    while(*s != '\0')
    {
        Send_Byte(*s++);
    }
}

//*************************************************************************
//             bluetooth函数
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
//              接受处理函数函数
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
        if(m1==2)//设定第2位为判断位
        {
          if(data==0x5A)  //第二位符合判断
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
        if(m1==2)//设定第2位为判断位
        {
          if(data==0x5B)  //第二位符合判断
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
              if(JZ_BUFF[3]==0x01)          //倾斜角垂直校准
              flag_jz=1;
              else if(JZ_BUFF[3]==0x02)     //倾斜角水平校准
              flag_jz=2;
            }
            else if(JZ_BUFF[2]==0x01)       //方位角角度清零
            {
              if(JZ_BUFF[3]==0x01)
              flag_jz=3;
              else if(JZ_BUFF[3]==0x02)      //方位角角度定位
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