
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
	uchar up;//向上翻索引号
	uchar down;//向下翻索引号
	uchar enter;//确认翻索引号
	void (*current_operation)();
    } key_table;

key_table const table[30]=
 {
 	{0,0,0,1,(*fun1)},//第一层 OLED  方位角   第一层 OLEDT  倾斜角
        
        {1,5,2,6,(*fun2)},//第二层 参数设置 【方位角设置 】 倾斜角设置                         
        {2,1,3,10,(*fun3)},//第二层 参数设置 方位角设置  【 倾斜角设置】
	{3,2,4,13,(*fun4)},//第二层 参数设置 倾斜角设置  【蓝牙设置】
	{4,3,5,14,(*fun5)},//第二层 参数设置  蓝牙配对   【时间设置】 
      	{5,4,1,0,(*fun6)},//第二层 参数设置  时间设置   【返回】
        
	{6,9,7,6,(*fun7)},//第三层  方位角 【定位角设置】 角度定位 
	{7,6,8,18,(*fun8)}, //第三层  方位角 定位角设置 【角度定位】  
        {8,7,9,17,(*fun9)},//第三层  方位角 角度定位【角度清零】 
	{9,8,6,1,(*fun10)},//第三层  方位角  方位角  【返回】		
        
	{10,12,11,16,(*fun11)},//第三层  倾斜角 【水平校准】 垂直校准  
	{11,10,12,15,(*fun12)}, // 第三层  倾斜角 水平校准 【垂直校准】 	
       	{12,11,10,2,(*fun13)},//第三层  倾斜角 垂直校准  【返回】	
        
	{13,13,13,3,(*fun14)}, //第三层  蓝牙设置     【返回】
       	{14,14,14,4,(*fun15)}, //第三层  时间设置     【返回】    
        
        {15,15,15,11,(*fun16)}, //第四层  垂直校准   【返回】
        
        {16,16,16,10,(*fun17)}, //第四层  水平校准   【返回】
        
        {17,17,17,8,(*fun18)}, //第四层  方位角清零   【返回】
        {18,18,18,7,(*fun19)}, //第四层  方位角定位   【返回】
//        
//	{15,17,16,22,(*fun12)},// 第四层  定位角设置 【输入定位角 】 读取定位角  
// 	{16,15,17,23,(*fun13)}, //第四层  定位角设置 输入定位角  【读取定位角】  
//        {17,16,15,6,(*fun14)}, //第四层 定位角设置 读取定位角  【返回】	
//        
//	{18,18,18,7,(*fun15)}, //第四层  方位角定位     【返回】
//       	{19,19,19,7,(*fun16)}, //第四层  方位角清零     【返回】 
//        
//        {20,20,20,10,(*fun17)}, //第四层  水平校准   【返回】 
//        {21,21,21,11,(*fun18)}, //第四层  水平角度修正   【返回】
//        
//        {22,22,22,15,(*fun19)}, //第五层  输入定位角度   【返回】
//        {23,23,23,16,(*fun20)}, //第五层  读取定位角度   【返回】
        
               	
};

//定时器B初始化
void InitTimerB()
{
  TBCTL=TBSSEL1+ID1+ID0+MC0+TBCLR;//选择1/8SMCLK 增计数 清除TAR
  TBCCTL0=CCIE;//CCR0中断允许 比较模式
  TBCCR0=10000;//时间间隔10ms
}

unsigned char buff[50];
//int x=0;
int main( void )
{
  // Stop watchdog timer to prevent time out reset
  WDTCTL = WDTPW + WDTHOLD;
  
  
  Clock_Init();                       //系统时钟设置
  

 
  InitTimerB();

  delay_ms(500);                      //延时100ms
  

   UART_Init1();                        //蓝牙串口设置初始化
  

   P1DIR|=BIT5+BIT6;                 //OLED IIC端口 P1.5 P1.6
   P1OUT&= ~(BIT5+BIT6);
   
   P2DIR|=BIT5+BIT6;                 //OLEDT IIC端口 P2.5 P2.6
   P2OUT&= ~(BIT5+BIT6);

   
   ADC_Init();                         //初始化ADC配置

   _EINT();                            //使能中断
 
  OLED_Init();			//初始化OLED  
  OLED_Clear(); 
  OLEDT_Init();			//初始化OLED  
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
   




      ADC12CTL0 |= ADC12SC;           //开启转换
      
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
        

      break;        //给不同的键赋键值，键值2，亮2个LED灯
      
      case 0x30:
       if(flag_JP==0)
        { 
          func_index=table[func_index].enter; 

        }
        else
        {
          key_num=2;
        }
        

      break;	 //给不同的键赋键值，键值3，亮2个LED灯
                  
      case 0x32: 

        if(flag_JP==0)
        { 
          func_index=table[func_index].up; 
   
        }
        else
        {
         
          key_num=1;
          
        }

       break;	 //给不同的键赋键值，键值4，亮2个LED灯
       
       default:
         key_num=0xFF;
       break;
                                  
      }
     //clear_ddram();          
   } 

     current_operation_index=table[func_index].current_operation;//取current_operation_index地址
    (*current_operation_index)();//执行*current_operation_index地址程序 

       
          
  } 


  
  
  // return 0;
}


//定时器B中断
#pragma vector=TIMERB0_VECTOR
__interrupt void TimerBINT()
{
      KeyProcess();
      ADC12CTL0 |= ADC12SC;           //开启转换
      TEMP_AD = ADC12MEM0;
      AD_BAT=AD_BAT+TEMP_AD;
      AD_num++;
      if(AD_num>99)
      {
        AD_num=0;
        AD_BATV=AD_BAT/100;          //修改数值，3.3基于满格
        AD_BAT=0;
      } 
  
  num++;
  if(num>100)
  {
     readcont++;
     num=0;//中断50次为0.5s
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
//               处理来自串口1的接收中断
//*************************************************************************

#pragma vector=UART1RX_VECTOR
__interrupt void UART1_RX_ISR(void)
{
   
   RX();
}

