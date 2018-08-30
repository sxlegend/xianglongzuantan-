


#ifndef _REALTIME_H
#define _REALTIME_H

#include	<intrinsics.h> 



typedef struct Time_
    {

        char    second;
        char    minute;
        char    hour;
        char    day;
        char    weekday;
        char    month;
        int     year;
    }   Time;


/*Regs*/
#define RT_Status1          (0x00)
#define RT_Control1         (0x00)
#define RT_Status2          (0x01)
#define RT_Control2         (0x01)
#define RT_Seconds          (0x02)
#define RT_Minutes          (0x03)
#define RT_Hours            (0x04)
#define RT_Days             (0x05)
#define RT_Weekdays         (0x06)
#define RT_Months           (0x07)
#define RT_Century          (0x07)
#define RT_Years            (0x08)
#define RT_MinuteAlarm      (0x09)
#define RT_HourAlarm        (0x0A)
#define RT_DayAlarm         (0x0B)
#define RT_WeekdayAlarm     (0x0C)
#define RT_CLKOUT_Control   (0x0D)
#define RT_TimerControl     (0x0E)
#define RT_Timer            (0x0F)

#define RTMASK_TEST1        (0x80)
#define RTMASK_STOP         (0x20)
#define RTMASK_TESTC        (0x08)

#define RTMASK_TI_TP        (0x10)
#define RTMASK_AF           (0x08)
#define RTMASK_TF           (0x04)
#define RTMASK_AIE          (0x02)
#define RTMASK_TIE          (0x01)

#define RTMASK_VL           (0x80)

#define RTMASK_Seconds       (0x7F)
#define RTMASK_Minutes       (0x7F)
#define RTMASK_Hours         (0x3F)
#define RTMASK_Days          (0x3F)
#define RTMASK_Weekdays      (0x07)
#define RTMASK_C             (0x80)
#define RTMASK_Months        (0x1F)

#define RTMASK_F32768Hz       (0x00)
#define RTMASK_F1024Hz        (0x01)
#define RTMASK_F32Hz          (0x10)
#define RTMASK_F1Hz           (0x11)
#define RTMASK_FE            (0x80)

#define RTMASK_AE            (0x80)

#define RTMASK_T4096Hz       (0x00)
#define RTMASK_T64Hz         (0x01)
#define RTMASK_T1Hz          (0x10)
#define RTMASK_T1_60Hz       (0x11)

#define RTMASK_TE            (0x80)

#define RT_Device_Address   (0xA2)
typedef enum
    {
    Sunday = 0,
    Monday,
    Tuesday,
    Wednesday,
    Thursday,
    Friday,
    Saturday   
    } weekdays;

typedef enum
    {
    January = 1,
    February,
    March,
    April,
    May ,
    June ,
    July,
    August ,
    September ,
    October ,
    November,
    December
    } months;

typedef struct
    {
    int         year;
    months     month;
    char          day;
    char        weekday;
    } date;

typedef struct
    {
    char          hour;
    char          minute;
    char          second;
    } time;
#ifndef __cplusplus
typedef enum {FALSE = 0, TRUE = !FALSE} bool;
#endif



char  BCD2Num(char data);
char  Num2BCD(char data);
void RealTime_Init(void);
void GetDate(date *pDate);
void Get_Time(Time *pTime);
void SetDate(date *pDate);
void Set_Time(Time *pTime);
void WeekdayLookup(date *pDate);
void WeekdayLookup2(Time *pTime);
//void GetTime(time *pTime);

void SetAlarmDate(char date , bool Status);
void SetAlarmWeekday(weekdays week, bool Status);
void SetAlarmHour(char hour, bool Status);
void SetAlarmMinute(char minute, bool Status);
void RTInterruptFlag_Clear(char flag);
void RTInterrupt_Config(char cmd, bool Status);
char RTInterruptFlag_Get(void);
bool RTVoltLower_Get(void);
void RTTime_Config(char tHzmask, bool Status);
bool Alarm_Get(void);

void PCF8563_Start();
void PCF8563_Stop();
void PCF8563_Wait_NAck();
void PCF8563_Wait_Ack();
void Write_PCF8563_Byte(int Value);
void Write_PCF8563_Command(char Command);
void Write_PCF8563_Data(char Data);
void I2C_WriteData(char DeveiceAdress, char RegiserAddress, char mdata);
int I2C_ReadData(char DeveiceAdress, char RegiserAddress);
#endif