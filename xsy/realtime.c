#include <msp430x14x.h>
#include "realtime.h"

void Delay_ms(unsigned long nValue)
{
 unsigned long nCount;
 int i;
 unsigned long j;
 nCount=2667;
 for(i=nValue;i>0;i--)
 {
  for(j=nCount;j>0;j--); 
 }
 
}

void IIC_SDA_HIGH()
{
 P2DIR |= BIT7;
 P2OUT |= BIT7;
_NOP();
_NOP();
_NOP();
 
}

void IIC_SDA_LOW()
{
 P2DIR |= BIT7;
 P2OUT &=~ BIT7;
_NOP();
_NOP();
_NOP();

}

void IIC_SCK_HIGH()
{
 P3DIR |= BIT0;
 P3OUT |= BIT0;
_NOP();
_NOP();
_NOP();

}

void IIC_SCK_LOW()
{
 P3DIR |= BIT0;
 P3OUT &=~ BIT0;
_NOP();
_NOP();
_NOP();
 
}


/**********************************************
//IIC Start
**********************************************/
void PCF8563_Start()
{
 
 IIC_SDA_HIGH();
 
 IIC_SCK_HIGH();
 
 IIC_SDA_LOW();

 
}

/**********************************************
//IICT Stop
**********************************************/
void PCF8563_Stop()
{
 int i;
 IIC_SDA_LOW();
 for(i=5;i>0;i--);
// IIC_SCK_LOW();
// for(i=5;i>0;i--)
 IIC_SCK_HIGH();
 for(i=5;i>0;i--) ;  
 IIC_SDA_HIGH();

// IIC_SCK_LOW();
// Delay_ms(10);
 
	
}

void PCF8563_Wait_NAck()
{

//	IIC_SCK_LOW();
        IIC_SDA_HIGH();
	IIC_SCK_HIGH();
        IIC_SDA_LOW();
        
}

void PCF8563_Wait_Ack()
{
//       IIC_SCK_LOW();
       IIC_SDA_LOW();
       IIC_SCK_HIGH();
       IIC_SCK_LOW();
       
}

/**********************************************
// IIC Write byte
**********************************************/

void Write_PCF8563_Byte(int Value)
{
	int i;
       
      IIC_SCK_LOW();
	for(i=0;i<8;i++)		
	{
		if(Value&0x80)
                {
		  IIC_SDA_HIGH();
                }
		else 
                {
                  IIC_SDA_LOW();
                }
		Value<<=1;
                
                
                IIC_SCK_HIGH();
                
                
                IIC_SCK_LOW();
                
         }
                
                IIC_SDA_HIGH();
               
                IIC_SCK_HIGH();
                
                P2DIR &=~ BIT7;
                
                if(P2IN&BIT7)
                 {
                   IIC_SCK_LOW();
                 }
                else
                 {
                   IIC_SCK_LOW();
                 }

}

/**********************************************
// IICT Write Command
**********************************************/
void Write_PCF8563_Command(char Command)
{
   PCF8563_Start();
   Write_PCF8563_Byte(0x78);            //Slave address,SA0=0
	PCF8563_Wait_Ack();	
   Write_PCF8563_Byte(0x00);			//write command
	PCF8563_Wait_Ack();	
   Write_PCF8563_Byte(Command); 
	PCF8563_Wait_Ack();	
   PCF8563_Stop();
}
/**********************************************
// IICT Write Data
**********************************************/
void Write_PCF8563_Data(char Data)
{
   PCF8563_Start();
   Write_PCF8563_Byte(0x78);			//D/C#=0; R/W#=0
		
   Write_PCF8563_Byte(0x40);			//write data
		
   Write_PCF8563_Byte(Data);
		
   PCF8563_Stop();
}

void I2C_WriteData(char DeveiceAdress, char RegiserAddress, char mdata)
{
   PCF8563_Start();
   Write_PCF8563_Byte(DeveiceAdress); /*写命令*/
   Write_PCF8563_Byte(RegiserAddress); /*写地址*/
   Write_PCF8563_Byte(mdata); /*写数据*/
   PCF8563_Stop();  
}

int PCF8563_ReceiveByte(void)
{
 int temp=0;
 int i;
 
 IIC_SDA_HIGH();
 IIC_SCK_LOW();
  _NOP();
  _NOP();
  _NOP();  
 
 for(i=0;i<8;i++)
 {
  IIC_SCK_HIGH();//产生时钟上升沿[正脉冲],让从机准备好数据
  temp<<=1;
  P2DIR &=~ BIT7;
  if(P2IN&BIT7) //读引脚状态
  {
   temp|=0x01;
  }
  
  IIC_SCK_LOW();//准备好再次接收数据

 }

 return temp;
}

int I2C_ReadData(char DeveiceAdress, char RegiserAddress) /*单字节*/
{  
   int rdata;

   PCF8563_Start();
   Write_PCF8563_Byte(DeveiceAdress); /*写命令*/
   
   Write_PCF8563_Byte(RegiserAddress); /*写地址*/
  
   PCF8563_Start();
   Write_PCF8563_Byte(DeveiceAdress | 0x01); /*读命令*/
   
   rdata=PCF8563_ReceiveByte();
   PCF8563_Wait_NAck();
   PCF8563_Stop();
   return(rdata);
}
#define ReadData(x)         I2C_ReadData(RT_Device_Address,x) 

char  BCD2Num(char data)
{
  char temp;
  temp = ((data >> 0x04) *10 + (data & 0x0f));
  return temp;
}

char  Num2BCD(char data)
{
  char temp;
  temp = (data / 10) * 16 + (data % 10);
  return temp;
}

static void WeekdayLookup(date *pDate);



/*取得日期*/
void GetDate(date *pDate )
{
  char temp;
  char century;
  temp = ReadData(RT_Months); 
  century = temp & RTMASK_C;
  temp = temp & RTMASK_Months;
  pDate -> month = (months)BCD2Num(temp);
  
  temp = ReadData(RT_Years);
  if(century) pDate -> year = 1900 + BCD2Num(temp); //=1,为19XX
  else        pDate -> year = 2000 + BCD2Num(temp); 
  
  temp = ReadData(RT_Days) & RTMASK_Days;
  pDate -> day = BCD2Num(temp);
  
  temp = ReadData(RT_Weekdays) & RTMASK_Weekdays;
  pDate -> weekday = (weekdays)BCD2Num(temp);
}

/*取得时间*/
void Get_Time(Time *pTime)
{
  unsigned char temp;
  unsigned char century;
  
  temp = ReadData(RT_Hours) & RTMASK_Hours;
  pTime -> hour = BCD2Num(temp);  
  
  temp = ReadData(RT_Minutes) & RTMASK_Minutes;
  pTime -> minute = BCD2Num(temp);  
  
  temp = ReadData(RT_Seconds) & RTMASK_Seconds;
  pTime -> second = BCD2Num(temp); 
  
  temp = ReadData(RT_Months); 
  century = temp & RTMASK_C;
  temp = temp & RTMASK_Months;
  pTime -> month = (months)BCD2Num(temp);
  
  temp = ReadData(RT_Years);
  if(century)
      pTime -> year = 1900 + BCD2Num(temp); 
  else
      pTime -> year = 2000 + BCD2Num(temp); 
    
  temp = ReadData(RT_Days) & RTMASK_Days;
  pTime -> day = BCD2Num(temp);
 
  WeekdayLookup2(pTime);
}

/*设置日期*/
void SetDate(date *pDate)
{
  char  temp;

  temp = (char)(pDate -> year % 100);
  temp = Num2BCD(temp);

  I2C_WriteData(RT_Device_Address,RT_Years,temp);
  
  temp = Num2BCD(pDate -> month);
  I2C_WriteData(RT_Device_Address,RT_Months,temp);
  
  temp = Num2BCD(pDate -> day);
  I2C_WriteData(RT_Device_Address,RT_Days,temp);
  
  WeekdayLookup(pDate);
  temp = Num2BCD(pDate -> weekday);
  I2C_WriteData(RT_Device_Address,RT_Weekdays,temp);
}

/*设置时间*/
void Set_Time(Time *pTime)
{
    char  temp;

    WeekdayLookup2(pTime);

    temp = Num2BCD(pTime -> hour);
    I2C_WriteData(RT_Device_Address,RT_Hours,temp);
    
    temp = Num2BCD(pTime -> minute);
    I2C_WriteData(RT_Device_Address,RT_Minutes,temp);
    
    temp = Num2BCD(pTime -> second);
    I2C_WriteData(RT_Device_Address,RT_Seconds,temp);  
    
    temp = Num2BCD(pTime -> weekday);
    I2C_WriteData(RT_Device_Address,RT_Weekdays,temp);
    
    temp = (char)(pTime -> year % 100);
    temp = Num2BCD(temp);

    I2C_WriteData(RT_Device_Address,RT_Years,temp);
    
    temp = Num2BCD(pTime -> month);
    I2C_WriteData(RT_Device_Address,RT_Months,temp);
    
    temp = Num2BCD(pTime -> day);
    I2C_WriteData(RT_Device_Address,RT_Days,temp);
    
}

/*设置报警日期*/
void SetAlarmDate(char date , bool Status)
{
  char  temp;
  if(Status)  temp = Num2BCD(date)| RTMASK_AE;
  else  temp = Num2BCD(date) & (~RTMASK_AE);
  I2C_WriteData(RT_Device_Address,RT_DayAlarm,temp);
}


/*设置报警周*/
void SetAlarmWeekday(weekdays week, bool Status)
{
  char temp;
  if(!Status) temp = (Num2BCD(week)|RTMASK_AE);
  else temp = (Num2BCD(week)&(~RTMASK_AE));
  I2C_WriteData(RT_Device_Address,RT_WeekdayAlarm,temp);
}

/*设置报警时间*/
void SetAlarmHour(char hour, bool Status)
{
  char  temp;
  if(!Status) temp = Num2BCD(hour)| RTMASK_AE;
  else temp = Num2BCD(hour)& (~ RTMASK_AE);
  I2C_WriteData(RT_Device_Address,RT_HourAlarm,temp);
}

/*设置报警分钟*/
void SetAlarmMinute(char minute, bool Status)
{
  char  temp;
  if(!Status) temp = Num2BCD(minute)| RTMASK_AE;
  else temp =Num2BCD(minute)& (~RTMASK_AE);
  I2C_WriteData(RT_Device_Address,RT_MinuteAlarm,temp);    
}

static char reg_control2  = 0x00;

void RTInterruptFlag_Clear(char flag)
{
  reg_control2 &= ~flag;  
  I2C_WriteData(RT_Device_Address,RT_Control2,reg_control2);  
}









/*下面使用蔡勒公式计算，只适用于1582年10月4的星期计算*/
void WeekdayLookup(date *pDate)
{
  int c,y,w;
  int Year, Month;
  
  Year = pDate -> year;
  Month =  (int)(pDate ->month);
  
  if(Month < 3)
      {
      Month +=12;
      Year -=1;
      }
  
  c = (int)(Year / 100);
  y = Year - 100 * c;
  w = (int)(c / 4) - 2*c + y + (int)(y/4) + (int)(26 * (Month + 1)/10 ) + (pDate ->day - 1);
  w = ( w % 7 + 7 ) % 7;
  
  pDate -> weekday = (weekdays)w;
}

void WeekdayLookup2(Time *pTime)
{
  int c,y,w;
  int Year, Month;
  
  Year = pTime -> year;
  Month =  (int)(pTime ->month);
  
  if(Month < 3)
      {
      Month +=12;
      Year -=1;
      }

  c = (int)(Year / 100);
  y = Year - 100 * c;
  w = (int)(c / 4) - 2*c + y + (int)(y/4) + (int)(26 * (Month + 1)/10 ) + (pTime ->day - 1);
  w = ( w % 7 + 7 ) % 7;
  if (w == 0)
  w = w + 7;

  pTime -> weekday = w;
}
///*取得时间*/
//void GetTime(time *pTime)
//{
//    unsigned char temp;
//    
//    temp = ReadData(RT_Hours) & RTMASK_Hours;
//    pTime -> hour = BCD2Num(temp);  
//    
//    temp = ReadData(RT_Minutes) & RTMASK_Minutes;
//    pTime -> minute = BCD2Num(temp);  
//    
//    temp = ReadData(RT_Seconds) & RTMASK_Seconds;
//    pTime -> second = BCD2Num(temp); 
//      
//
//}