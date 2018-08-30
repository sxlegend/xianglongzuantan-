#include <msp430x14x.h>
#include "OLED.h"
#include "conver.h"
//#include "Config.h"
#include "realtime.h"
extern unsigned char flag_page,key_num,flag_jz;
extern int mm,mm1;
extern unsigned char key;
extern unsigned char flag_Jgkg,flag_netive,flag_DW,flag_FWQL,flag_SPXZ,flag_JP,flag_plus;
extern unsigned char Angle_YawF,Angle_DWF;
extern char Angle_RollF;
extern int Angle_YawD,Angle_RollD,Angle_DWD;
extern unsigned char SET_Angle;
unsigned char F_wei;
extern unsigned char nn,nn1;
unsigned char Num_wei,Fvalue,D_fh;
int Dvalue=324;
extern unsigned char  func_index,Addr_num,flag_SAV;
extern int Sav1_D,Sav1_F,Sav2_D,Sav2_F,Sav3_D,Sav3_F;
extern int Sav4_D,Sav4_F,Sav5_D,Sav5_F,Sav6_D,Sav6_F;
extern int Sav7_D,Sav7_F,Sav8_D,Sav8_F,Sav9_D,Sav9_F;
extern int hour,min,sec;
extern void LYPD();
Time SetTime;
char time_flag=0;
  unsigned char minute1,minute2;
extern unsigned int AD_BATV,TEMP_AD,AD_BAT,AD_num;
extern void Send_Byte(unsigned char data);
void delay_ms(unsigned long ms)                        // 延时子程序
{    
  unsigned long a,b; 
  for(a=ms;a>0;a--)
  for(b=1000;b>0;b--);
}


  void Battery(unsigned int AD_Battery)       
{
  unsigned int temp_ADBT;
  temp_ADBT=AD_Battery;
    if(temp_ADBT<=2400)                          //一格电量
  {
    OLEDT_ShowBattery(104,0,1); 
  }
  else if(temp_ADBT>2400&&temp_ADBT<=2450)
  {
    OLEDT_ShowBattery(104,0,2); 
  }
  else if(temp_ADBT>2450&&temp_ADBT<=2550)
  {
    OLEDT_ShowBattery(104,0,3); 
  }
  else if(temp_ADBT>2550&&temp_ADBT<=2650)
  {
    OLEDT_ShowBattery(104,0,4); 
  }
  else 
  {
    OLEDT_ShowBattery(104,0,5);           //满格
  }
//  if(temp_ADBT<=2450)                          //一格电量
//  {
//    OLEDT_ShowBattery(104,0,1); 
//  }
//  else if(temp_ADBT>2450&&temp_ADBT<=2550)
//  {
//    OLEDT_ShowBattery(104,0,2); 
//  }
//  else if(temp_ADBT>2550&&temp_ADBT<=2650)
//  {
//    OLEDT_ShowBattery(104,0,3); 
//  }
//  else if(temp_ADBT>2650&&temp_ADBT<=2750)
//  {
//    OLEDT_ShowBattery(104,0,4); 
//  }
//  else 
//  {
//    OLEDT_ShowBattery(104,0,5);           //满格
//  }
}
/**************************************第一层 测角仪  方位角  倾斜角 ****************************************/
void fun1()   
{
 if( flag_page!=1)
 { 
  flag_page=1;
  OLED_Clear();
  OLEDT_Clear() ;
 
//  OLED_ShowCHinese(30,0,5);//测
//  OLED_ShowCHinese(55,0,2);//角
//  OLED_ShowCHinese(80,0,6);//仪
  
  OLED_ShowCHinese(5,1,0);//方
  OLED_ShowCHinese(21,1,1);//位
  OLED_ShowCHinese(37,1,2);//角
  

  
  
  


//  OLEDT_ShowCHinese(30,0,5);//测
//  OLEDT_ShowCHinese(55,0,2);//角
//  OLEDT_ShowCHinese(80,0,6);//仪
    
  OLEDT_ShowCHinese(5,1,3);//倾
  OLEDT_ShowCHinese(21,1,4);//斜
  OLEDT_ShowCHinese(37,1,2);//角  
  

 }
 
  OLED_ShowNum(80,1,hour,2,16);
  OLED_ShowChar(96,1,':',16);
  OLED_ShowNum(104,1,min,2,16);
//  OLED_ShowChar(46,0,':',16);
//  OLED_ShowNum(54,0,sec,2,16);
 
  
  OLED_ShowNum32(16,4,Angle_YawD,3,32);
  OLED_ShowNum32(80,4,Angle_YawF,2,32);
  OLED_NUM32(64,4,10);
  OLED_NUM32(112,4,11);

  
    if(flag_netive==1)
  {
    //OLEDT_ShowChar(16,4,'-',16);
    OLEDT_NUM32(16,4,12);
  }
  else
  {
    OLEDT_NUM32(16,4,13);
  }
  
  OLEDT_ShowNum32(32,4,Angle_RollD,2,32);
  OLEDT_ShowNum32(80,4,Angle_RollF,2,32);
  OLEDT_NUM32(64,4,10);
  OLEDT_NUM32(112,4,11);
  
  Battery(AD_BATV);
  
  flag_page=1;
}

/**************************************第一层 测角仪  激光方位灯  激光定位灯 ****************************************/
//void fun3()
//{
//}
//{
//  if(flag_page!=2)
//  {
//    flag_page=2;
//    OLED_Clear() ;
//    OLED_ShowCHinese(30,0,5);//测
//    OLED_ShowCHinese(55,0,2);//角
//    OLED_ShowCHinese(80,0,6);//仪
//    
//    OLED_ShowCHinese(10,3,7);//激
//    OLED_ShowCHinese(26,3,8);//光
//    OLED_ShowCHinese(42,3,11);//方
//    OLED_ShowCHinese(58,3,1);//位
//    OLED_ShowCHinese(74,3,9);//灯  
//       
//    
//    OLED_ShowCHinese(10,6,7);//激
//    OLED_ShowCHinese(26,6,8);//光
//    OLED_ShowCHinese(42,6,10);//定
//    OLED_ShowCHinese(58,6,1);//位
//    OLED_ShowCHinese(74,6,9);//灯 
//  }
//  
//  if(flag_page==2)
//    {
//      if(flag_Jgkg==0)
//      {
//        OLED_ShowCHinese(106,3,13);//关  
//        OLED_ShowCHinese(106,6,13);//关 
//        P4OUT|=BIT0;
//        P6OUT|=BIT7;
//      }
//      else if(flag_Jgkg==1)
//      {
//        OLED_ShowCHinese(106,3,12);//开 
//        OLED_ShowCHinese(106,6,13);//关 
//        P4OUT&= ~BIT0;
//        P6OUT|=BIT7;
//      }
//      else
//      {
//        OLED_ShowCHinese(106,3,13);//关 
//        OLED_ShowCHinese(106,6,12);//开   
//        P4OUT|=BIT0;
//        P6OUT&= ~BIT7;
//      }
//    }
//}

/**************************************第二层 参数设置 【方位角设置 】 倾斜角设置  ****************************************/
void fun2()   
{
   if( flag_page!=2)
 { 
    OLEDT_Clear() ;
   if( flag_page==1)
   {
    OLED_Clear(); 
   
  OLED_ShowCHinese(2,2,0);//方
  OLED_ShowCHinese(18,2,1);//位
  OLED_ShowCHinese(34,2,2);//角
  
  OLED_ShowChar(88,3,'!',16);
  OLED_ShowChar(112,3,'$',16);

    
  OLED_ShowCHinese(2,5,3);//倾
  OLED_ShowCHinese(18,5,4);//斜
  OLED_ShowCHinese(34,5,2);//角  
  

  OLED_ShowChar(88,2,'!',16);
  OLED_ShowChar(112,2,'$',16);

  OLED_ShowChar(88,5,'!',16);
  OLED_ShowChar(112,5,'$',16);
   }
  flag_page=2;
  
  
  OLEDT_Clearnum(3,9);
//  OLED_ShowCHinese(30,0,5);//测
//  OLED_ShowCHinese(55,0,2);//角
//  OLED_ShowCHinese(80,0,6);//仪
  

 }
 
  OLED_ShowNum(64,2,Angle_YawD,3,16);
  OLED_ShowNum(96,2,Angle_YawF,2,16);
  
    if(flag_netive==1)
  {
    OLED_ShowChar(64,5,'-',16);
  }
  else
  {
    OLED_ShowChar(64,5,' ',16);
  }
  OLED_ShowNum(72,5,Angle_RollD,2,16);
  OLED_ShowNum(96,5,Angle_RollF,2,16);  
  
  OLEDT_ShowCHinese(25,0,14);//参
  OLEDT_ShowCHinese(45,0,15);//数
  OLEDT_ShowCHinese(65,0,16);//设
  OLEDT_ShowCHinese(85,0,17);//置
  
  OLEDT_ShowCHinese(20,3,0);//方
  OLEDT_ShowCHinese(36,3,1);//位
  OLEDT_ShowCHinese(52,3,2);//角  
  OLEDT_ShowCHinese(68,3,16);//设
  OLEDT_ShowCHinese(84,3,17);//置
  OLEDT_ShowChar(105,3,'<',16);//<<
  OLEDT_ShowChar(113,3,'<',16);
  
  OLEDT_ShowCHinese(20,6,3);//倾
  OLEDT_ShowCHinese(36,6,4);//斜
  OLEDT_ShowCHinese(52,6,2);//角  
  OLEDT_ShowCHinese(68,6,16);//设
  OLEDT_ShowCHinese(84,6,17);//置
  
 //OLED_ShowCHinese(50,6,18);//返
 // OLED_ShowCHinese(70,6,19);//回
  
  OLEDT_ShowChar(105,6,' ',16);//<<
  OLEDT_ShowChar(113,6,' ',16);
  
  //OLED_ShowChar(105,6,' ',16); 
  //OLED_ShowChar(113,6,' ',16);

  flag_page=2;
 
}

/**************************************第二层 参数设置  方位角设置  【倾斜角设置】  ****************************************/
void fun3()   
{
   if( flag_page!=3)
 { 
  flag_page=3;

  OLEDT_Clearnum(0,9);

  
//  OLED_ShowCHinese(2,2,0);//方
//  OLED_ShowCHinese(18,2,1);//位
//  OLED_ShowCHinese(34,2,2);//角
//  
//  OLED_ShowChar(88,3,'!',16);
//  OLED_ShowChar(112,3,'$',16);
//
//    
//  OLED_ShowCHinese(2,5,3);//倾
//  OLED_ShowCHinese(18,5,4);//斜
//  OLED_ShowCHinese(34,5,2);//角   
//  
//
//  OLED_ShowChar(88,2,'!',16);
//  OLED_ShowChar(112,2,'$',16);
//
//  OLED_ShowChar(88,5,'!',16);
//  OLED_ShowChar(112,5,'$',16);
 }
 
  OLED_ShowNum(64,2,Angle_YawD,3,16);
  OLED_ShowNum(96,2,Angle_YawF,2,16);
  
    if(flag_netive==1)
  {
    OLED_ShowChar(64,5,'-',16);
  }
  else
  {
    OLED_ShowChar(64,5,' ',16);
  }
  OLED_ShowNum(72,5,Angle_RollD,2,16);
  OLED_ShowNum(96,5,Angle_RollF,2,16);  
  
  OLEDT_ShowCHinese(25,0,14);//参
  OLEDT_ShowCHinese(45,0,15);//数
  OLEDT_ShowCHinese(65,0,16);//设
  OLEDT_ShowCHinese(85,0,17);//置
  
  OLEDT_ShowCHinese(20,3,0);//方
  OLEDT_ShowCHinese(36,3,1);//位
  OLEDT_ShowCHinese(52,3,2);//角  
  OLEDT_ShowCHinese(68,3,16);//设
  OLEDT_ShowCHinese(84,3,17);//置
  OLEDT_ShowChar(105,3,' ',16);//<<
  OLEDT_ShowChar(113,3,' ',16);
  
  OLEDT_ShowCHinese(20,6,3);//倾
  OLEDT_ShowCHinese(36,6,4);//斜
  OLEDT_ShowCHinese(52,6,2);//角  
  OLEDT_ShowCHinese(68,6,16);//设
  OLEDT_ShowCHinese(84,6,17);//置
  
 //OLED_ShowCHinese(50,6,18);//返
 // OLED_ShowCHinese(70,6,19);//回
  
  OLEDT_ShowChar(105,6,'<',16);//<<
  OLEDT_ShowChar(113,6,'<',16);
  
  //OLED_ShowChar(105,6,' ',16); 
  //OLED_ShowChar(113,6,' ',16);

  
 
}

/**************************************第二层 参数设置  倾斜角设置  【蓝牙设置】  ****************************************/
void fun4()   
{
   if( flag_page!=4)
 { 
   if(flag_page==14)
   {  
   OLEDT_Clear();
   }
   
  flag_page=4;

 OLEDT_Clearnum(3,9);

//  OLED_ShowCHinese(2,2,0);//方
//  OLED_ShowCHinese(18,2,1);//位
//  OLED_ShowCHinese(34,2,2);//角
//  
//  OLED_ShowChar(88,3,'!',16);
//  OLED_ShowChar(112,3,'$',16);
//
//    
//  OLED_ShowCHinese(2,5,3);//倾
//  OLED_ShowCHinese(18,5,4);//斜
//  OLED_ShowCHinese(34,5,2);//角    
//  
//
//  OLED_ShowChar(88,2,'!',16);
//  OLED_ShowChar(112,2,'$',16);
//
//  OLED_ShowChar(88,5,'!',16);
//  OLED_ShowChar(112,5,'$',16);
 }
 
  OLED_ShowNum(64,2,Angle_YawD,3,16);
  OLED_ShowNum(96,2,Angle_YawF,2,16);
  
    if(flag_netive==1)
  {
    OLED_ShowChar(64,5,'-',16);
  }
  else
  {
    OLED_ShowChar(64,5,' ',16);
  }
  OLED_ShowNum(72,5,Angle_RollD,2,16);
  OLED_ShowNum(96,5,Angle_RollF,2,16);  
  
  OLEDT_ShowCHinese(25,0,14);//参
  OLEDT_ShowCHinese(45,0,15);//数
  OLEDT_ShowCHinese(65,0,16);//设
  OLEDT_ShowCHinese(85,0,17);//置
  
  OLEDT_ShowCHinese(20,3,3);//倾
  OLEDT_ShowCHinese(36,3,4);//斜
  OLEDT_ShowCHinese(52,3,2);//角  
  OLEDT_ShowCHinese(68,3,16);//设
  OLEDT_ShowCHinese(84,3,17);//置
  OLEDT_ShowChar(105,3,' ',16);//<<
  OLEDT_ShowChar(113,3,' ',16);
  

  

  OLEDT_ShowCHinese(20,6,40);//蓝
  OLEDT_ShowCHinese(36,6,41);//牙  
  OLEDT_ShowCHinese(52,6,16);//设
  OLEDT_ShowCHinese(68,6,17);//置
  OLEDT_ShowChar(105,6,'<',16);//<<
  OLEDT_ShowChar(113,6,'<',16);
  


  flag_page=4;
 
}


/**************************************第二层 参数设置  倾斜角设置  【蓝牙设置】  ****************************************/
void fun5()   
{
   if( flag_page!=5)
 { 
   if(flag_page==15)
   {  
   OLEDT_Clear();
   }
  flag_page=5;

  OLEDT_Clearnum(3,9);

  
//  OLED_ShowCHinese(2,2,0);//方
//  OLED_ShowCHinese(18,2,1);//位
//  OLED_ShowCHinese(34,2,2);//角
//  
//  OLED_ShowChar(88,3,'!',16);
//  OLED_ShowChar(112,3,'$',16);
//
//    
//  OLED_ShowCHinese(2,5,3);//倾
//  OLED_ShowCHinese(18,5,4);//斜
//  OLED_ShowCHinese(34,5,2);//角  
//  
//
//  OLED_ShowChar(88,2,'!',16);
//  OLED_ShowChar(112,2,'$',16);
//
//  OLED_ShowChar(88,5,'!',16);
//  OLED_ShowChar(112,5,'$',16);
 }
 
  OLED_ShowNum(64,2,Angle_YawD,3,16);
  OLED_ShowNum(96,2,Angle_YawF,2,16);
  
    if(flag_netive==1)
  {
    OLED_ShowChar(64,5,'-',16);
  }
  else
  {
    OLED_ShowChar(64,5,' ',16);
  }
  OLED_ShowNum(72,5,Angle_RollD,2,16);
  OLED_ShowNum(96,5,Angle_RollF,2,16);  
  
  OLEDT_ShowCHinese(25,0,14);//参
  OLEDT_ShowCHinese(45,0,15);//数
  OLEDT_ShowCHinese(65,0,16);//设
  OLEDT_ShowCHinese(85,0,17);//置
  
  OLEDT_ShowCHinese(20,3,40);//蓝
  OLEDT_ShowCHinese(36,3,41);//牙  
  OLEDT_ShowCHinese(52,3,16);//设
  OLEDT_ShowCHinese(68,3,17);//置
  OLEDT_ShowChar(105,3,' ',16);//<<
  OLEDT_ShowChar(113,3,' ',16);
  

  

  OLEDT_ShowCHinese(20,6,42);//蓝
  OLEDT_ShowCHinese(36,6,43);//牙  
  OLEDT_ShowCHinese(52,6,16);//设
  OLEDT_ShowCHinese(68,6,17);//置
  OLEDT_ShowChar(105,6,'<',16);//<<
  OLEDT_ShowChar(113,6,'<',16);
  


  flag_page=5;
 
}

/**************************************第二层 参数设置  倾斜角设置  【蓝牙设置】  ****************************************/
void fun6()   
{
   if( flag_page!=6)
 { 
 

  OLEDT_Clearnum(3,9);

  
//  OLED_ShowCHinese(2,2,0);//方
//  OLED_ShowCHinese(18,2,1);//位
//  OLED_ShowCHinese(34,2,2);//角
//  
//  OLED_ShowChar(88,3,'!',16);
//  OLED_ShowChar(112,3,'$',16);
//
//    
//  OLED_ShowCHinese(2,5,3);//倾
//  OLED_ShowCHinese(18,5,4);//斜
//  OLED_ShowCHinese(34,5,2);//角  
//  
//
//  OLED_ShowChar(88,2,'!',16);
//  OLED_ShowChar(112,2,'$',16);
//
//  OLED_ShowChar(88,5,'!',16);
//  OLED_ShowChar(112,5,'$',16);
 }
 
  OLED_ShowNum(64,2,Angle_YawD,3,16);
  OLED_ShowNum(96,2,Angle_YawF,2,16);
  
    if(flag_netive==1)
  {
    OLED_ShowChar(64,5,'-',16);
  }
  else
  {
    OLED_ShowChar(64,5,' ',16);
  }
  OLED_ShowNum(72,5,Angle_RollD,2,16);
  OLED_ShowNum(96,5,Angle_RollF,2,16);  
  
  OLEDT_ShowCHinese(25,0,14);//参
  OLEDT_ShowCHinese(45,0,15);//数
  OLEDT_ShowCHinese(65,0,16);//设
  OLEDT_ShowCHinese(85,0,17);//置

  OLEDT_ShowCHinese(20,3,42);//shi
  OLEDT_ShowCHinese(36,3,43);//jian 
  OLEDT_ShowCHinese(52,3,16);//设
  OLEDT_ShowCHinese(68,3,17);//置
  OLEDT_ShowChar(105,3,' ',16);//<<
  OLEDT_ShowChar(113,3,' ',16);
  
  OLEDT_ShowCHinese(50,6,18);//返
  OLEDT_ShowCHinese(70,6,19);//回    
  OLEDT_ShowChar(105,6,'<',16);//<<
  OLEDT_ShowChar(113,6,'<',16);
  


  flag_page=6;
 
}

///************************************** 第三层  方位角 【定位角设置】 角度定位  ****************************************/
void fun7()   
{
  if(flag_page!=7)
    {
     OLEDT_Clear() ;
  OLED_ShowCHinese(2,2,0);//方
  OLED_ShowCHinese(18,2,1);//位
  OLED_ShowCHinese(34,2,2);//角
  
  OLED_ShowChar(88,3,'!',16);
  OLED_ShowChar(112,3,'$',16);

    
  OLED_ShowCHinese(2,5,3);//倾
  OLED_ShowCHinese(18,5,4);//斜
  OLED_ShowCHinese(34,5,2);//角  
  

  OLED_ShowChar(88,2,'!',16);
  OLED_ShowChar(112,2,'$',16);

  OLED_ShowChar(88,5,'!',16);
  OLED_ShowChar(112,5,'$',16);
 }
 
  OLED_ShowNum(64,2,Angle_YawD,3,16);
  OLED_ShowNum(96,2,Angle_YawF,2,16);
  
    if(flag_netive==1)
  {
    OLED_ShowChar(64,5,'-',16);
  }
  else
  {
    OLED_ShowChar(64,5,' ',16);
  }
  OLED_ShowNum(72,5,Angle_RollD,2,16);
  OLED_ShowNum(96,5,Angle_RollF,2,16);  
    
  
  OLEDT_ShowCHinese(30,0,0);//方
  OLEDT_ShowCHinese(55,0,1);//位
  OLEDT_ShowCHinese(80,0,2);//角
    
  OLEDT_ShowCHinese(20,3,10);//定
  OLEDT_ShowCHinese(36,3,1);//位
  OLEDT_ShowCHinese(52,3,2);//角  
  OLEDT_ShowCHinese(68,3,16);//设
  OLEDT_ShowCHinese(84,3,17);//置 
  
  OLEDT_ShowCHinese(25,6,2);//角
  OLEDT_ShowCHinese(45,6,20);//度
  OLEDT_ShowCHinese(65,6,10);//定
  OLEDT_ShowCHinese(85,6,1);//位
  
  OLEDT_ShowChar(105,3,'<',16);//<<
  OLEDT_ShowChar(113,3,'<',16);
  
  OLEDT_ShowChar(105,6,' ',16);//<<
  OLEDT_ShowChar(113,6,' ',16);
  
  flag_page=7;  
  
}

/**************************************第三层  方位角 定位角设置 【角度定位】  ****************************************/
void fun8()   
{
  if(flag_page!=8)
  {
    OLEDT_Clear() ;
  OLED_ShowCHinese(2,2,0);//方
  OLED_ShowCHinese(18,2,1);//位
  OLED_ShowCHinese(34,2,2);//角
  
  OLED_ShowChar(88,3,'!',16);
  OLED_ShowChar(112,3,'$',16);

    
  OLED_ShowCHinese(2,5,3);//倾
  OLED_ShowCHinese(18,5,4);//斜
  OLED_ShowCHinese(34,5,2);//角  
  

  OLED_ShowChar(88,2,'!',16);
  OLED_ShowChar(112,2,'$',16);

  OLED_ShowChar(88,5,'!',16);
  OLED_ShowChar(112,5,'$',16);
 }
 
  OLED_ShowNum(64,2,Angle_YawD,3,16);
  OLED_ShowNum(96,2,Angle_YawF,2,16);
  
    if(flag_netive==1)
  {
    OLED_ShowChar(64,5,'-',16);
  }
  else
  {
    OLED_ShowChar(64,5,' ',16);
  }
  OLED_ShowNum(72,5,Angle_RollD,2,16);
  OLED_ShowNum(96,5,Angle_RollF,2,16); 
  
  OLEDT_ShowCHinese(30,0,0);//方
  OLEDT_ShowCHinese(55,0,1);//位
  OLEDT_ShowCHinese(80,0,2);//角
  
  OLEDT_ShowCHinese(20,3,10);//定
  OLEDT_ShowCHinese(36,3,1);//位
  OLEDT_ShowCHinese(52,3,2);//角  
  OLEDT_ShowCHinese(68,3,16);//设
  OLEDT_ShowCHinese(84,3,17);//置 
  
  OLEDT_ShowCHinese(25,6,2);//角
  OLEDT_ShowCHinese(45,6,20);//度
  OLEDT_ShowCHinese(65,6,10);//定
  OLEDT_ShowCHinese(85,6,1);//位
  
  OLEDT_ShowChar(105,3,' ',16);//<<
  OLEDT_ShowChar(113,3,' ',16);
  
  OLEDT_ShowChar(105,6,'<',16);//<<
  OLEDT_ShowChar(113,6,'<',16);
  
  flag_page=8;
}

/**************************************第三层  方位角 角度定位【角度清零】    ****************************************/
void fun9()   
{
  if(flag_page!=9)
    {
      OLEDT_Clear() ;
      OLED_ShowCHinese(2,2,0);//方
  OLED_ShowCHinese(18,2,1);//位
  OLED_ShowCHinese(34,2,2);//角
  
  OLED_ShowChar(88,3,'!',16);
  OLED_ShowChar(112,3,'$',16);

    
  OLED_ShowCHinese(2,5,3);//倾
  OLED_ShowCHinese(18,5,4);//斜
  OLED_ShowCHinese(34,5,2);//角  
  

  OLED_ShowChar(88,2,'!',16);
  OLED_ShowChar(112,2,'$',16);

  OLED_ShowChar(88,5,'!',16);
  OLED_ShowChar(112,5,'$',16);
 }
 
  OLED_ShowNum(64,2,Angle_YawD,3,16);
  OLED_ShowNum(96,2,Angle_YawF,2,16);
  
    if(flag_netive==1)
  {
    OLED_ShowChar(64,5,'-',16);
  }
  else
  {
    OLED_ShowChar(64,5,' ',16);
  }
  OLED_ShowNum(72,5,Angle_RollD,2,16);
  OLED_ShowNum(96,5,Angle_RollF,2,16);  
  
  OLEDT_ShowCHinese(30,0,0);//方
  OLEDT_ShowCHinese(55,0,1);//位
  OLEDT_ShowCHinese(80,0,2);//角
  
  OLEDT_ShowCHinese(25,3,2);//角
  OLEDT_ShowCHinese(45,3,20);//度
  OLEDT_ShowCHinese(65,3,10);//定
  OLEDT_ShowCHinese(85,3,1);//位  
  
  OLEDT_ShowCHinese(25,6,2);//角
  OLEDT_ShowCHinese(45,6,20);//度
  OLEDT_ShowCHinese(65,6,21);//清
  OLEDT_ShowCHinese(85,6,22);//零
  
  OLEDT_ShowChar(105,6,'<',16);//<<
  OLEDT_ShowChar(113,6,'<',16);
  
  flag_page=9;
  
}

/**************************************第三层  方位角  角度清零  【返回】  ****************************************/
void fun10()   
{
  if(flag_page!=10)
    {
      OLEDT_Clear() ;
      OLED_ShowCHinese(2,2,0);//方
  OLED_ShowCHinese(18,2,1);//位
  OLED_ShowCHinese(34,2,2);//角
  
  OLED_ShowChar(88,3,'!',16);
  OLED_ShowChar(112,3,'$',16);

    
  OLED_ShowCHinese(2,5,3);//倾
  OLED_ShowCHinese(18,5,4);//斜
  OLED_ShowCHinese(34,5,2);//角  
  

  OLED_ShowChar(88,2,'!',16);
  OLED_ShowChar(112,2,'$',16);

  OLED_ShowChar(88,5,'!',16);
  OLED_ShowChar(112,5,'$',16);
 }
 
  OLED_ShowNum(64,2,Angle_YawD,3,16);
  OLED_ShowNum(96,2,Angle_YawF,2,16);
  
    if(flag_netive==1)
  {
    OLED_ShowChar(64,5,'-',16);
  }
  else
  {
    OLED_ShowChar(64,5,' ',16);
  }
  OLED_ShowNum(72,5,Angle_RollD,2,16);
  OLED_ShowNum(96,5,Angle_RollF,2,16);  
  
  OLEDT_ShowCHinese(30,0,0);//方
  OLEDT_ShowCHinese(55,0,1);//位
  OLEDT_ShowCHinese(80,0,2);//角

  OLEDT_ShowCHinese(25,3,2);//角
  OLEDT_ShowCHinese(45,3,20);//度
  OLEDT_ShowCHinese(65,3,21);//清
  OLEDT_ShowCHinese(85,3,22);//零
  
  OLEDT_ShowCHinese(50,6,18);//返
  OLEDT_ShowCHinese(70,6,19);//回    

  OLEDT_ShowChar(105,6,'<',16);//<<
  OLEDT_ShowChar(113,6,'<',16);
  
  flag_page=10;
}

/**************************************第三层  倾斜角 【水平校准】 角度修正     ****************************************/
void fun11()   
{
    if(flag_page!=11)
    {
      
       OLEDT_Clear() ;
      

  OLED_ShowCHinese(2,2,0);//方
  OLED_ShowCHinese(18,2,1);//位
  OLED_ShowCHinese(34,2,2);//角
  
  OLED_ShowChar(88,3,'!',16);
  OLED_ShowChar(112,3,'$',16);

    
  OLED_ShowCHinese(2,5,3);//倾
  OLED_ShowCHinese(18,5,4);//斜
  OLED_ShowCHinese(34,5,2);//角  
  

  OLED_ShowChar(88,2,'!',16);
  OLED_ShowChar(112,2,'$',16);

  OLED_ShowChar(88,5,'!',16);
  OLED_ShowChar(112,5,'$',16);
 }
 
  OLED_ShowNum(64,2,Angle_YawD,3,16);
  OLED_ShowNum(96,2,Angle_YawF,2,16);
  
    if(flag_netive==1)
  {
    OLED_ShowChar(64,5,'-',16);
  }
  else
  {
    OLED_ShowChar(64,5,' ',16);
  }
  OLED_ShowNum(72,5,Angle_RollD,2,16);
  OLED_ShowNum(96,5,Angle_RollF,2,16); 
  
  OLEDT_ShowCHinese(30,0,3);//倾
  OLEDT_ShowCHinese(55,0,4);//斜
  OLEDT_ShowCHinese(80,0,2);//角
  
  OLEDT_ShowCHinese(25,3,23);//水
  OLEDT_ShowCHinese(45,3,24);//平
  OLEDT_ShowCHinese(65,3,25);//校
  OLEDT_ShowCHinese(85,3,26);//准  
  
  OLEDT_ShowCHinese(25,6,44);//角
  OLEDT_ShowCHinese(45,6,45);//度
  OLEDT_ShowCHinese(65,6,25);//修
  OLEDT_ShowCHinese(85,6,26);//正

  OLEDT_ShowChar(105,3,'<',16);//<<
  OLEDT_ShowChar(113,3,'<',16);
  
  OLEDT_ShowChar(105,6,' ',16);//<<
  OLEDT_ShowChar(113,6,' ',16); 
  
  flag_page=11;

  
}

/**************************************第三层  倾斜角 水平校准 【角度修正 】  ****************************************/
void fun12()   
{
  if(flag_page!=12)
  {
    OLEDT_Clear() ;;

    
   OLED_ShowCHinese(2,2,0);//方
  OLED_ShowCHinese(18,2,1);//位
  OLED_ShowCHinese(34,2,2);//角
  
  OLED_ShowChar(88,3,'!',16);
  OLED_ShowChar(112,3,'$',16);

    
  OLED_ShowCHinese(2,5,3);//倾
  OLED_ShowCHinese(18,5,4);//斜
  OLED_ShowCHinese(34,5,2);//角  
  

  OLED_ShowChar(88,2,'!',16);
  OLED_ShowChar(112,2,'$',16);

  OLED_ShowChar(88,5,'!',16);
  OLED_ShowChar(112,5,'$',16);
 }
 
  OLED_ShowNum(64,2,Angle_YawD,3,16);
  OLED_ShowNum(96,2,Angle_YawF,2,16);
  
    if(flag_netive==1)
  {
    OLED_ShowChar(64,5,'-',16);
  }
  else
  {
    OLED_ShowChar(64,5,' ',16);
  }
  OLED_ShowNum(72,5,Angle_RollD,2,16);
  OLED_ShowNum(96,5,Angle_RollF,2,16);
  
     OLEDT_ShowCHinese(30,0,3);//倾
     OLEDT_ShowCHinese(55,0,4);//斜
     OLEDT_ShowCHinese(80,0,2);//角

    OLEDT_ShowCHinese(25,3,23);//水
    OLEDT_ShowCHinese(45,3,24);//平
    OLEDT_ShowCHinese(65,3,25);//校
    OLEDT_ShowCHinese(85,3,26);//准  
    
    OLEDT_ShowCHinese(25,6,44);//角
    OLEDT_ShowCHinese(45,6,45);//度
    OLEDT_ShowCHinese(65,6,25);//修
    OLEDT_ShowCHinese(85,6,26);//正
    
    OLEDT_ShowChar(105,3,' ',16);//<<
    OLEDT_ShowChar(113,3,' ',16);
    
    OLEDT_ShowChar(105,6,'<',16);//<<
    OLEDT_ShowChar(113,6,'<',16); 
  flag_page=12;
}


/**************************************第三层  倾斜角 角度修正  【返回】****************************************/
void fun13()   
{
   if(flag_page!=13)
    {
      OLEDT_Clear() ;
     OLED_ShowCHinese(2,2,0);//方
  OLED_ShowCHinese(18,2,1);//位
  OLED_ShowCHinese(34,2,2);//角
  
  OLED_ShowChar(88,3,'!',16);
  OLED_ShowChar(112,3,'$',16);

    
  OLED_ShowCHinese(2,5,3);//倾
  OLED_ShowCHinese(18,5,4);//斜
  OLED_ShowCHinese(34,5,2);//角  
  

  OLED_ShowChar(88,2,'!',16);
  OLED_ShowChar(112,2,'$',16);

  OLED_ShowChar(88,5,'!',16);
  OLED_ShowChar(112,5,'$',16);
 }
 
  OLED_ShowNum(64,2,Angle_YawD,3,16);
  OLED_ShowNum(96,2,Angle_YawF,2,16);
  
    if(flag_netive==1)
  {
    OLED_ShowChar(64,5,'-',16);
  }
  else
  {
    OLED_ShowChar(64,5,' ',16);
  }
  OLED_ShowNum(72,5,Angle_RollD,2,16);
  OLED_ShowNum(96,5,Angle_RollF,2,16);
  
  OLEDT_ShowCHinese(30,0,3);//倾
  OLEDT_ShowCHinese(55,0,4);//斜
  OLEDT_ShowCHinese(80,0,2);//角
  
    OLEDT_ShowCHinese(25,3,44);//角
    OLEDT_ShowCHinese(45,3,45);//度
    OLEDT_ShowCHinese(65,3,25);//修
    OLEDT_ShowCHinese(85,3,26);//正
    
    OLEDT_ShowCHinese(50,6,18);//返
    OLEDT_ShowCHinese(70,6,19);//回    
  
    OLEDT_ShowChar(105,6,'<',16);//<<
    OLEDT_ShowChar(113,6,'<',16);   
    
    flag_page=13;
}

/**************************************第三层  蓝牙设置  【返回】****************************************/
void fun14()
{
  if(flag_page!=14)
 {
  OLEDT_Clear() ;
  OLED_ShowCHinese(2,2,0);//方
  OLED_ShowCHinese(18,2,1);//位
  OLED_ShowCHinese(34,2,2);//角
  
  OLED_ShowChar(88,3,'!',16);
  OLED_ShowChar(112,3,'$',16);

    
  OLED_ShowCHinese(2,5,3);//倾
  OLED_ShowCHinese(18,5,4);//斜
  OLED_ShowCHinese(34,5,2);//角  
  

  OLED_ShowChar(88,2,'!',16);
  OLED_ShowChar(112,2,'$',16);

  OLED_ShowChar(88,5,'!',16);
  OLED_ShowChar(112,5,'$',16);
 }
 
  OLED_ShowNum(64,2,Angle_YawD,3,16);
  OLED_ShowNum(96,2,Angle_YawF,2,16);
  
    if(flag_netive==1)
  {
    OLED_ShowChar(64,5,'-',16);
  }
  else
  {
    OLED_ShowChar(64,5,' ',16);
  }
  OLED_ShowNum(72,5,Angle_RollD,2,16);
  OLED_ShowNum(96,5,Angle_RollF,2,16);
  

  OLEDT_ShowCHinese(32,0,40);//位
  OLEDT_ShowCHinese(54,0,41);//角  
  OLEDT_ShowCHinese(76,0,16);//定
  OLEDT_ShowCHinese(98,0,17);//位
  
  OLEDT_ShowCHinese(20,3,16);//定
  OLEDT_ShowCHinese(36,3,17);//位
  OLEDT_ShowChar(52,3,':',16);
  
  


  OLEDT_ShowCHinese(50,6,18);//返
  OLEDT_ShowCHinese(70,6,19);//回   
  
  OLEDT_ShowChar(105,6,'<',16);//<<
  OLEDT_ShowChar(113,6,'<',16); 
  
    if(key_num==14)
    {
      
      OLEDT_ShowChar(80,3,'*',16);
      OLEDT_ShowChar(96,3,'*',16); 
      
      LYPD();
      
      OLEDT_ShowChar(80,3,'O',16);
      OLEDT_ShowChar(96,3,'K',16);


      
    }
    flag_page=14;
}

/**************************************第三层  时间设置  【返回】****************************************/
void fun15()
{
  


  
  if(flag_page!=15)
 {
  OLEDT_Clear() ;
  

  
  Get_Time(&SetTime);
  minute1=SetTime.minute/10;
  minute2=SetTime.minute%10;
  
  OLED_ShowCHinese(2,2,0);//方
  OLED_ShowCHinese(18,2,1);//位
  OLED_ShowCHinese(34,2,2);//角
  
  OLED_ShowChar(88,3,'!',16);
  OLED_ShowChar(112,3,'$',16);

    
  OLED_ShowCHinese(2,5,3);//倾
  OLED_ShowCHinese(18,5,4);//斜
  OLED_ShowCHinese(34,5,2);//角  
  

  OLED_ShowChar(88,2,'!',16);
  OLED_ShowChar(112,2,'$',16);

  OLED_ShowChar(88,5,'!',16);
  OLED_ShowChar(112,5,'$',16);
  
  
 }
 
  OLED_ShowNum(64,2,Angle_YawD,3,16);
  OLED_ShowNum(96,2,Angle_YawF,2,16);
  
    if(flag_netive==1)
  {
    OLED_ShowChar(64,5,'-',16);
  }
  else
  {
    OLED_ShowChar(64,5,' ',16);
  }
  OLED_ShowNum(72,5,Angle_RollD,2,16);
  OLED_ShowNum(96,5,Angle_RollF,2,16);
  

  OLEDT_ShowCHinese(32,0,42);//位
  OLEDT_ShowCHinese(54,0,43);//角  
  OLEDT_ShowCHinese(76,0,16);//定
  OLEDT_ShowCHinese(98,0,17);//位
  
  OLEDT_ShowNum(20,3,SetTime.hour,2,16);//xiaoshi 
  OLEDT_ShowNum(44,3,SetTime.minute,2,16);//xiaoshi 
  OLEDT_ShowChar(36,3,':',16);
  
  


  OLEDT_ShowCHinese(50,6,18);//返
  OLEDT_ShowCHinese(70,6,19);//回   
  
  OLEDT_ShowChar(105,6,'<',16);//<<
  OLEDT_ShowChar(113,6,'<',16); 
  
        
      switch(key)
      {
      case 0x33:
        time_flag++;
        if(time_flag==3)
        {
          time_flag=0;
          OLEDT_ShowChar(20,4,'-',16);
          OLEDT_ShowChar(28,4,'-',16); 
          OLEDT_ShowChar(44,4,' ',16);
          OLEDT_ShowChar(52,4,' ',16);           
        }
        else if(time_flag==1)
        {
          OLEDT_ShowChar(20,4,' ',16);
          OLEDT_ShowChar(28,4,' ',16);
          OLEDT_ShowChar(44,4,' ',16);
          OLEDT_ShowChar(52,4,'-',16);  
        }
        else if(time_flag==2)
        {
          OLEDT_ShowChar(20,4,' ',16);
          OLEDT_ShowChar(28,4,' ',16);
          OLEDT_ShowChar(44,4,'-',16);
          OLEDT_ShowChar(52,4,' ',16);  
        }

        break;
      case 0x32:
        if(time_flag==0)
        {
          
          if((SetTime.hour+1)>=24)
          {
            SetTime.hour=0;
          }
          else
            SetTime.hour++;
        }
        else if(time_flag==1)
        {
            if((minute2+1)>=10)
            {
              minute2=0;
            }
            else
            minute2++;
        }
        else if(time_flag==2)
        {
            if((minute1+1)>=6)
            {
              minute1=0;
            }
            else
            minute1++;
        }        
        SetTime.minute=minute1*10+minute2;
        break;
      default:
        break;
      }
  
    if(key_num==15)
    {
     
      Set_Time(&SetTime);
      
      OLEDT_ShowChar(20,4,' ',16);
      OLEDT_ShowChar(28,4,' ',16);
      OLEDT_ShowChar(44,4,' ',16);
      OLEDT_ShowChar(52,4,' ',16);  

      
      OLEDT_ShowChar(80,3,'O',16);
      OLEDT_ShowChar(96,3,'K',16);


      
    }
    flag_page=15;
}


/**************************************第四层  倾斜角 垂直校准****************************************/
void fun16()   
{
  unsigned char czjz[5]={0xB5,0x5B,0x00,0x01,0xEF};
   if(flag_page!=16)
    {
      flag_jz=0;
      OLEDT_Clear() ;
     OLED_ShowCHinese(2,2,0);//方
  OLED_ShowCHinese(18,2,1);//位
  OLED_ShowCHinese(34,2,2);//角
  
  OLED_ShowChar(88,3,'!',16);
  OLED_ShowChar(112,3,'$',16);

    
  OLED_ShowCHinese(2,5,3);//倾
  OLED_ShowCHinese(18,5,4);//斜
  OLED_ShowCHinese(34,5,2);//角  
  

  OLED_ShowChar(88,2,'!',16);
  OLED_ShowChar(112,2,'$',16);

  OLED_ShowChar(88,5,'!',16);
  OLED_ShowChar(112,5,'$',16);
 }
 
  OLED_ShowNum(64,2,Angle_YawD,3,16);
  OLED_ShowNum(96,2,Angle_YawF,2,16);
  
    if(flag_netive==1)
  {
    OLED_ShowChar(64,5,'-',16);
  }
  else
  {
    OLED_ShowChar(64,5,' ',16);
  }
  OLED_ShowNum(72,5,Angle_RollD,2,16);
  OLED_ShowNum(96,5,Angle_RollF,2,16);
  
  OLEDT_ShowCHinese(30,0,3);//倾
  OLEDT_ShowCHinese(55,0,4);//斜
  OLEDT_ShowCHinese(80,0,2);//角
  
    OLEDT_ShowCHinese(10,3,44);//垂
    OLEDT_ShowCHinese(26,3,45);//直
    OLEDT_ShowCHinese(42,3,25);//校
    OLEDT_ShowCHinese(58,3,26);//准
    OLEDT_ShowChar(74,3,':',16);
    
    OLEDT_ShowCHinese(50,6,18);//返
    OLEDT_ShowCHinese(70,6,19);//回    
      OLEDT_ShowChar(105,6,'<',16);//<<
  OLEDT_ShowChar(113,6,'<',16); 
  
  
        if(key_num==16)
    {
      OLEDT_ShowChar(90,3,'*',16);
      OLEDT_ShowChar(106,3,'*',16);
      
        for(int i=0;i<5;i++)
       {
         Send_Byte(czjz[i]);
       }
       delay_ms(1000);
       delay_ms(1000);
       delay_ms(1000);
       if(flag_jz==1)
       {
         
        flag_jz=0;
        OLEDT_ShowChar(90,3,'O',16);
        OLEDT_ShowChar(106,3,'K',16);

       }
       else if(flag_jz==0)
       {
         OLEDT_ShowChar(90,3,'N',16);
         OLEDT_ShowChar(106,3,'C',16);
       }
      
    }
  
    
    flag_page=16;
}
///**************************************第四层  倾斜角 水平校准****************************************/
void fun17()   
{
   unsigned char czjz[5]={0xB5,0x5B,0x00,0x02,0xEC};
   if(flag_page!=17)
    {
      flag_jz=0;
      OLEDT_Clear() ;
     OLED_ShowCHinese(2,2,0);//方
  OLED_ShowCHinese(18,2,1);//位
  OLED_ShowCHinese(34,2,2);//角
  
  OLED_ShowChar(88,3,'!',16);
  OLED_ShowChar(112,3,'$',16);

    
  OLED_ShowCHinese(2,5,3);//倾
  OLED_ShowCHinese(18,5,4);//斜
  OLED_ShowCHinese(34,5,2);//角  
  

  OLED_ShowChar(88,2,'!',16);
  OLED_ShowChar(112,2,'$',16);

  OLED_ShowChar(88,5,'!',16);
  OLED_ShowChar(112,5,'$',16);
 }
 
  OLED_ShowNum(64,2,Angle_YawD,3,16);
  OLED_ShowNum(96,2,Angle_YawF,2,16);
  
    if(flag_netive==1)
  {
    OLED_ShowChar(64,5,'-',16);
  }
  else
  {
    OLED_ShowChar(64,5,' ',16);
  }
  OLED_ShowNum(72,5,Angle_RollD,2,16);
  OLED_ShowNum(96,5,Angle_RollF,2,16);
  
  OLEDT_ShowCHinese(30,0,3);//倾
  OLEDT_ShowCHinese(55,0,4);//斜
  OLEDT_ShowCHinese(80,0,2);//角
  
    OLEDT_ShowCHinese(10,3,23);//水
    OLEDT_ShowCHinese(26,3,24);//平
    OLEDT_ShowCHinese(42,3,25);//校
    OLEDT_ShowCHinese(58,3,26);//准
    OLEDT_ShowChar(74,3,':',16);
    
    OLEDT_ShowCHinese(50,6,18);//返
    OLEDT_ShowCHinese(70,6,19);//回    
      OLEDT_ShowChar(105,6,'<',16);//<<
  OLEDT_ShowChar(113,6,'<',16); 
  
  
        if(key_num==17)
    {
      OLEDT_ShowChar(90,3,'*',16);
      OLEDT_ShowChar(106,3,'*',16);
      
        for(int i=0;i<5;i++)
       {
         Send_Byte(czjz[i]);
       }
       delay_ms(1000);
       delay_ms(1000);
       delay_ms(1000);
       if(flag_jz==2)
       {
         
        flag_jz=0;
        OLEDT_ShowChar(90,3,'O',16);
        OLEDT_ShowChar(106,3,'K',16);

       }
       else 
       {
         OLEDT_ShowChar(90,3,'N',16);
         OLEDT_ShowChar(106,3,'C',16);
       }
      
    }
  
    
    flag_page=17;
}




///**************************************第四层  方位角清零     【返回】****************************************/
void fun18()   
{
   unsigned char czjz[5]={0xB5,0x5B,0x01,0x01,0xEE};
   if(flag_page!=18)
    {
      flag_jz=0;
      OLEDT_Clear() ;
     OLED_ShowCHinese(2,2,0);//方
     OLED_ShowCHinese(18,2,1);//位
  OLED_ShowCHinese(34,2,2);//角
  
  OLED_ShowChar(88,3,'!',16);
  OLED_ShowChar(112,3,'$',16);

    
  OLED_ShowCHinese(2,5,3);//倾
  OLED_ShowCHinese(18,5,4);//斜
  OLED_ShowCHinese(34,5,2);//角  
  

  OLED_ShowChar(88,2,'!',16);
  OLED_ShowChar(112,2,'$',16);

  OLED_ShowChar(88,5,'!',16);
  OLED_ShowChar(112,5,'$',16);
 }
 
  OLED_ShowNum(64,2,Angle_YawD,3,16);
  OLED_ShowNum(96,2,Angle_YawF,2,16);
  
    if(flag_netive==1)
  {
    OLED_ShowChar(64,5,'-',16);
  }
  else
  {
    OLED_ShowChar(64,5,' ',16);
  }
  OLED_ShowNum(72,5,Angle_RollD,2,16);
  OLED_ShowNum(96,5,Angle_RollF,2,16);
  
    OLEDT_ShowCHinese(30,0,0);//方
    OLEDT_ShowCHinese(55,0,1);//位
    OLEDT_ShowCHinese(80,0,2);//角
  
    OLEDT_ShowCHinese(10,3,2);//角
    OLEDT_ShowCHinese(26,3,20);//度
    OLEDT_ShowCHinese(42,3,21);//清
    OLEDT_ShowCHinese(58,3,22);//零
    OLEDT_ShowChar(74,3,':',16);
    
    OLEDT_ShowCHinese(50,6,18);//返
    OLEDT_ShowCHinese(70,6,19);//回    
    OLEDT_ShowChar(105,6,'<',16);//<<
    OLEDT_ShowChar(113,6,'<',16); 
  
  
        if(key_num==18)
    {
      OLEDT_ShowChar(90,3,'*',16);
      OLEDT_ShowChar(106,3,'*',16);
      
        for(int i=0;i<5;i++)
       {
         Send_Byte(czjz[i]);
       }
       delay_ms(1000);
       delay_ms(1000);
       delay_ms(1000);
       
       if(flag_jz==3)
       {
         
        flag_jz=0;
        OLEDT_ShowChar(90,3,'O',16);
        OLEDT_ShowChar(106,3,'K',16);

       }
       else  
       {
         OLEDT_ShowChar(90,3,'N',16);
         OLEDT_ShowChar(106,3,'C',16);
       }
      
    }
  
    
    flag_page=18;
  
  
}


///**************************************第四层  方位角定位     【返回】****************************************/
void fun19()   
{
  unsigned char czjz[5]={0xB5,0x5B,0x01,0x02,0xED};
   if(flag_page!=19)
    {
      flag_jz=0;
      OLEDT_Clear() ;
     OLED_ShowCHinese(2,2,0);//方
     OLED_ShowCHinese(18,2,1);//位
  OLED_ShowCHinese(34,2,2);//角
  
  OLED_ShowChar(88,3,'!',16);
  OLED_ShowChar(112,3,'$',16);

    
  OLED_ShowCHinese(2,5,3);//倾
  OLED_ShowCHinese(18,5,4);//斜
  OLED_ShowCHinese(34,5,2);//角  
  

  OLED_ShowChar(88,2,'!',16);
  OLED_ShowChar(112,2,'$',16);

  OLED_ShowChar(88,5,'!',16);
  OLED_ShowChar(112,5,'$',16);
 }
 
  OLED_ShowNum(64,2,Angle_YawD,3,16);
  OLED_ShowNum(96,2,Angle_YawF,2,16);
  
    if(flag_netive==1)
  {
    OLED_ShowChar(64,5,'-',16);
  }
  else
  {
    OLED_ShowChar(64,5,' ',16);
  }
  OLED_ShowNum(72,5,Angle_RollD,2,16);
  OLED_ShowNum(96,5,Angle_RollF,2,16);
  
    OLEDT_ShowCHinese(30,0,0);//方
    OLEDT_ShowCHinese(55,0,1);//位
    OLEDT_ShowCHinese(80,0,2);//角
  
    OLEDT_ShowCHinese(10,3,2);//角
    OLEDT_ShowCHinese(26,3,20);//度
    OLEDT_ShowCHinese(42,3,10);//定
    OLEDT_ShowCHinese(58,3,1);//位
    OLEDT_ShowChar(74,3,':',16);
    
    OLEDT_ShowCHinese(50,6,18);//返
    OLEDT_ShowCHinese(70,6,19);//回    
    OLEDT_ShowChar(105,6,'<',16);//<<
    OLEDT_ShowChar(113,6,'<',16); 
  
  
        if(key_num==19)
    {
      OLEDT_ShowChar(90,3,'*',16);
      OLEDT_ShowChar(106,3,'*',16);
      
        for(int i=0;i<5;i++)
       {
         Send_Byte(czjz[i]);
       }
       delay_ms(1000);
       delay_ms(1000);
       delay_ms(1000);
       if(flag_jz==4)
       {
         
        flag_jz=0;
        OLEDT_ShowChar(90,3,'O',16);
        OLEDT_ShowChar(106,3,'K',16);

       }
       else  
       {
         OLEDT_ShowChar(90,3,'N',16);
         OLEDT_ShowChar(106,3,'C',16);
       }
      
    }
  
    
    flag_page=19;
}
///**************************************第四层  方位角清零     【返回】****************************************/
//void fun17()   
//{
//  flag_page=17;
//  
//  OLED_ShowCHinese(10,0,0);//方
//  OLED_ShowCHinese(32,0,1);//位
//  OLED_ShowCHinese(54,0,2);//角  
//  OLED_ShowCHinese(76,0,21);//清
//  OLED_ShowCHinese(98,0,22);//零
//  
//  OLED_ShowCHinese(20,3,21);//清
//  OLED_ShowCHinese(36,3,22);//零
//  OLED_ShowChar(52,3,':',16);
//  
//  
//  OLED_ShowChar(80,3,'*',16);
//  OLED_ShowChar(96,3,'*',16); 
//
//  OLED_ShowCHinese(50,6,18);//返
//  OLED_ShowCHinese(70,6,19);//回   
//  
//  OLED_ShowChar(105,6,'<',16);//<<
//  OLED_ShowChar(113,6,'<',16); 
//
//  if(key_num==17)
//    {
//      OLED_ShowCHinese(80,3,12);//开
//      OLED_ShowCHinese(96,3,33);//始
//      
//      flag_FWQL=1;
//      delay_ms(1000);
//      
//      OLED_ShowCHinese(80,3,34);//结
//      OLED_ShowCHinese(96,3,35);//束
//      
//      flag_FWQL=0;
//      delay_ms(1000);
//      
//      OLED_ShowChar(80,3,' ',16);
//      OLED_ShowChar(88,3,' ',16); 
//      OLED_ShowChar(96,3,' ',16);
//      OLED_ShowChar(104,3,' ',16); 
//
//      OLED_ShowChar(80,3,'*',16);//<<
//      OLED_ShowChar(96,3,'*',16); 
//
//      
//    }
//}
//
///**************************************第四层   水平校准   【返回】****************************************/
//void fun18()   
//{
//  flag_page=18;
//  
//  OLED_ShowCHinese(10,0,23);//水
//  OLED_ShowCHinese(40,0,24);//平
//  OLED_ShowCHinese(70,0,25);//校  
//  OLED_ShowCHinese(100,0,26);//准
// 
//  
//  OLED_ShowCHinese(20,3,25);//校
//  OLED_ShowCHinese(36,3,26);//准
//  OLED_ShowChar(52,3,':',16);
//  
//  
//  OLED_ShowChar(80,3,'*',16);
//  OLED_ShowChar(96,3,'*',16); 
//
//  OLED_ShowCHinese(50,6,18);//返
//  OLED_ShowCHinese(70,6,19);//回   
//  
//  OLED_ShowChar(105,6,'<',16);//<<
//  OLED_ShowChar(113,6,'<',16); 
//
//  if(key_num==18)
//    {
//      OLED_ShowCHinese(80,3,12);//开
//      OLED_ShowCHinese(96,3,33);//始
//      
//      flag_SPXZ=1;
//      delay_ms(1000);
//      
//      OLED_ShowCHinese(80,3,34);//结
//      OLED_ShowCHinese(96,3,35);//束
//      
//      flag_SPXZ=0;
//      delay_ms(1000);
//      
//      OLED_ShowChar(80,3,' ',16);
//      OLED_ShowChar(88,3,' ',16); 
//      OLED_ShowChar(96,3,' ',16);
//      OLED_ShowChar(104,3,' ',16); 
//
//      OLED_ShowChar(80,3,'*',16);//<<
//      OLED_ShowChar(96,3,'*',16); 
//
//      
//    }
//}
//
///**************************************第四层  水平角度修正   【返回】】****************************************/
//void fun19()   
//{
//  flag_page=19;
//  flag_JP=1;
//  
//  OLED_ShowCHinese(10,0,23);//水
//  OLED_ShowCHinese(26,0,24);//平
//  OLED_ShowCHinese(42,0,2);//角
//  OLED_ShowCHinese(58,0,20);//度
//  OLED_ShowCHinese(74,0,27);//修
//  OLED_ShowCHinese(92,0,28);//正  
//  
//  OLED_ShowCHinese(80,3,36);//确
//  OLED_ShowCHinese(100,3,37);//认   
//  
//  OLED_ShowCHinese(40,6,18);//返
//  OLED_ShowCHinese(60,6,19);//回   
//  
//  OLED_ShowChar(105,6,'<',16);//<<
//  OLED_ShowChar(113,6,'<',16); 
//  
//  //OLED_ShowNum(56,3,mm,4,16);
//  Num_wei=set_wei(Num_wei);
//  Fvalue=set_fvalue(Fvalue);
//  Dvalue=set_Dvalue(Dvalue);
////  set_FValue();
//  SETXS_F(Fvalue);
//  SETXS_D(Dvalue);
//  
//  if(key_num==2)
//  {
//    func_index=9;
//    OLED_Clear() ;
//    flag_JP=0;
//  }
//  
//  if(key_num==19)
//  {
//   flag_FWQL=1;
//   set_enter();
//  }
//}
//
///**************************************第五层  输入定位角度   【返回】****************************************/
//void fun20()   
//{
//  flag_page=20;
//  flag_JP=1;
//  
//  OLED_ShowCHinese(10,0,29);//输
//  OLED_ShowCHinese(26,0,30);//入
//  OLED_ShowCHinese(42,0,10);//定
//  OLED_ShowCHinese(58,0,1);//位
//  OLED_ShowCHinese(74,0,2);//角
//  OLED_ShowCHinese(92,0,20);//度  
//  
//  OLED_ShowCHinese(80,3,36);//确
//  OLED_ShowCHinese(100,3,37);//认   
//  
//  OLED_ShowCHinese(40,6,18);//返
//  OLED_ShowCHinese(60,6,19);//回   
//  
//  OLED_ShowChar(105,6,'<',16);//<<
//  OLED_ShowChar(113,6,'<',16); 
//  
//  //OLED_ShowNum(56,3,mm,4,16);
//  Num_wei=set_wei(Num_wei);
//  Fvalue=set_fvalue(Fvalue);
//  Dvalue=set_Dvalue(Dvalue);
////  set_FValue();
//  SETXS_F(Fvalue);
//  SETXS_D(Dvalue);
//  
//  if(key_num==2)
//  {
//    func_index=12;
//    OLED_Clear() ;
//    flag_JP=0;
//  }
//  
//  if(key_num==20)
//  {
//    func_index=21;
//    OLED_Clear() ;
//    flag_JP=0;
//    
// /*   Angle_DWF=Fvalue;
//    Angle_DWD=Dvalue;
//    OLED_ShowChar(80,3,' ',16);//O
//    OLED_ShowChar(88,3,'O',16);//K
//    OLED_ShowChar(100,3,'K',16);
//    OLED_ShowChar(108,3,' ',16);
//    
//      
//    flag_FWQL=1;
//    delay_ms(1000);
//      
//    OLED_ShowCHinese(80,3,36);//确
//    OLED_ShowCHinese(100,3,37);//认 */
//  }
//}
//
//
///**************************************第五层  读取定位角度   【返回】****************************************/
//void fun21()   
//{
// // unsigned char temp;
//  
//  flag_page=21;
//  flag_JP=1;
//  
//  OLED_ShowCHinese(10,0,31);//读
//  OLED_ShowCHinese(26,0,32);//取
//  OLED_ShowCHinese(42,0,10);//定
//  OLED_ShowCHinese(58,0,1);//位
//  OLED_ShowCHinese(74,0,2);//角
//  OLED_ShowCHinese(92,0,20);//度  
//  
//  OLED_ShowCHinese(90,3,36);//确
//  OLED_ShowCHinese(106,3,37);//认   
//  
//  OLED_ShowCHinese(40,6,18);//返
//  OLED_ShowCHinese(60,6,19);//回   
//  
//  OLED_ShowChar(105,6,'<',16);//<<
//  OLED_ShowChar(113,6,'<',16); 
//  
//  
//  switch(Addr_num)
//  {
//    case 0:
//      OLED_ShowChar(75,3,'1',16);
//      mm=0;
//      nn=0;
//    break;    
//    
//    case 1:
//      OLED_ShowChar(75,3,'2',16);     
//      mm=1;
//      nn=1;
//    break;   
//      
//    case 2:
//      OLED_ShowChar(75,3,'3',16);
//      mm=2;
//      nn=2;
//    break;   
//      
//    case 3:
//      OLED_ShowChar(75,3,'4',16);
//      mm=3;
//      nn=3;
//    break;    
//    
//    case 4:
//      OLED_ShowChar(75,3,'5',16);
//      mm=4;
//      nn=4;
//    break;    
//
//    case 5:
//      OLED_ShowChar(75,3,'6',16);
//      mm=0;
//      nn=0;
//    break;    
//    
//    case 6:
//      OLED_ShowChar(75,3,'7',16);     
//      mm=1;
//      nn=1;
//    break;   
//      
//    case 7:
//      OLED_ShowChar(75,3,'8',16);
//      mm=2;
//      nn=2;
//    break;   
//      
//    case 8:
//      OLED_ShowChar(75,3,'9',16);
//      mm=3;
//      nn=3;
//    break;    
//  }
//  
//   OLED_ShowNum(10,3,mm,3,16);
//   OLED_ShowChar(34,3,'!',16);
//   OLED_ShowNum(42,3,nn,2,16);
//   OLED_ShowChar(58,3,'$',16);
//    
//  if(key_num==21)
//  {
//    flag_FWQL=1;
//    set_enter(); 
//  }
//  
//  if(key_num==2)
//  {
//    OLED_Clear() ;
//    flag_JP=0;    
//    func_index=12;
//
//  }
//
//  
//  if(key_num==1)
//  {
//    Addr_num++;
//    if(Addr_num>8)
//    {
//      Addr_num=0;
//    }
//  }
//  
//}
//
//
///**************************************第五层  定位角度存储   【返回】****************************************/
//void fun22()   
//{
//  flag_page=22;
//  flag_JP=1;
//  
//  OLED_ShowCHinese(10,0,10);//定
//  OLED_ShowCHinese(26,0,1);//位
//  OLED_ShowCHinese(42,0,2);//角
//  OLED_ShowCHinese(58,0,20);//度
//  OLED_ShowCHinese(74,0,38);//存
//  OLED_ShowCHinese(92,0,39);//储  
//  
//  OLED_ShowCHinese(90,3,36);//确
//  OLED_ShowCHinese(106,3,37);//认   
//  
//  OLED_ShowCHinese(40,6,18);//返
//  OLED_ShowCHinese(60,6,19);//回   
//  
//  OLED_ShowChar(105,6,'<',16);//<<
//  OLED_ShowChar(113,6,'<',16);   
//  
//  OLED_ShowNum(10,3,Dvalue,3,16);
//  OLED_ShowChar(34,3,'!',16);
//  OLED_ShowNum(42,3,Fvalue,2,16);
//  OLED_ShowChar(58,3,'$',16); 
//  
//  switch(Addr_num)
//  {
//    case 0:
//      OLED_ShowChar(75,3,'1',16);
//      if(key_num==22)
//      {
//        Sav1_D=Dvalue;
//        Sav1_F=Fvalue;
//        flag_SAV=1;
//        set_enter();
//      }
//    break;    
//    
//    case 1:
//      OLED_ShowChar(75,3,'2',16);     
//      if(key_num==22)
//      {
//        Sav2_D=Dvalue;
//        Sav2_F=Fvalue;
//        flag_SAV=1;
//        set_enter();
//      }
//    break;   
//      
//    case 2:
//      OLED_ShowChar(75,3,'3',16);
//     if(key_num==22)
//      {
//        Sav3_D=Dvalue;
//        Sav3_F=Fvalue;
//        flag_SAV=1;
//        set_enter();
//      }
//    break;   
//      
//    case 3:
//      OLED_ShowChar(75,3,'4',16);
//     if(key_num==22)
//      {
//        Sav4_D=Dvalue;
//        Sav4_F=Fvalue;
//        flag_SAV=1;
//        set_enter();
//      }
//    break;    
//    
//    case 4:
//      OLED_ShowChar(75,3,'5',16);
//     if(key_num==22)
//      {
//        Sav5_D=Dvalue;
//        Sav5_F=Fvalue;
//        flag_SAV=1;
//        set_enter();
//      }
//    break;    
//
//    case 5:
//      OLED_ShowChar(75,3,'6',16);
//     if(key_num==22)
//      {
//        Sav6_D=Dvalue;
//        Sav6_F=Fvalue;
//        flag_SAV=1;
//        set_enter();
//      }
//    break;    
//    
//    case 6:
//      OLED_ShowChar(75,3,'7',16);     
//     if(key_num==22)
//      {
//        Sav7_D=Dvalue;
//        Sav7_F=Fvalue;
//        flag_SAV=1;
//        set_enter();
//      }
//    break;   
//      
//    case 7:
//      OLED_ShowChar(75,3,'8',16);
//     if(key_num==22)
//      {
//        Sav8_D=Dvalue;
//        Sav8_F=Fvalue;
//        flag_SAV=1;
//        set_enter();
//      }    break;   
//      
//    case 8:
//      OLED_ShowChar(75,3,'9',16);
//     if(key_num==22)
//      {
//        Sav9_D=Dvalue;
//        Sav9_F=Fvalue;
//        flag_SAV=1;
//        set_enter();
//      }
//    break;    
//  }  
//
//  if(key_num==2)
//  {
//    OLED_Clear() ;
//    flag_JP=0;    
//    func_index=19;
//
//  }
//
//  
//  if(key_num==1)
//  {
//    Addr_num++;
//    if(Addr_num>8)
//    {
//      Addr_num=0;
//    }
//  }  
//  
//}