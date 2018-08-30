/*----------------------------------------------------------------
 *
 * 文件名： Key.c
 *      说明：  
 *          该程序完成比较通用的键盘库函数，只需改写GetKey函数和键码
 *          数组KeyCode，即可很方便的把程序移植到各种键盘。
 *
 *          使用时只需把Key.c添加到工程中，然后在要调用键盘的程序文件
 *          中加入对Key.h的包含；然后就可以调用头文件中声明的各个函数。
 *          scanf移植时，必须有两个按键：回车，退格，我的是把右上角的
 *          按键作为退格，右下角的作为回车，然后左上9格 1-9，后一行中
 *          间 0，其他四个按键保留，键码是'\0'
 *          "123\b456\000789\0\0000\0\r";  4*4,scanf移植
 *          
 * 
**----------------------------------------------------------------*/

#include <msp430x14x.h>
#include <stdio.h>
#include "Key.h"

/**********************宏定义***********************/
#define KeySize     4           //键码值队列
#define Length      KeySize+1   //队列数组元素个数
/***************************************************/

/**********************键值队列*********************/
//可KeySize(Length-1)个键码循环队列占用一个元素空间
char Key[Length];
char KeyCode[] = "0123";    /*4个按键时*/
//char KeyCode[] = "0123456789ABCDEF"; /* 4*4个按键时*/

//char KeyCode[] = "123\b456\000789\0\0000\0\r"; /* 4*4,scanf移植*/
char front;             //队列首指针
char rear;              //队列尾指针
/***************************************************/

/************************************************
函数名称：KeyInit
功    能：键盘用到的相关资源初始化
参    数：无
返回值  ：无
*************************************************/
void KeyInit()
{
   // WDTCTL=WDT_ADLY_16;   //看门狗内部定时器模式16ms
   // IE1 |= WDTIE;         //允许看门狗中断
    front = 0;
    rear = 0;
}

/************************************************
函数名称：ReadKey
功    能：从键盘队列读取键盘值
参    数：无
返回值  ：队首键码值
*************************************************/
char ReadKey()
{
    char temp;
    if(rear==front) return '\0';    //无按键
    while(rear==front);
    temp = Key[front];
    front=(front+1)%Length;
    return temp;
}

/************************************************
函数名称：AddKeyCode
功    能：向键盘队列中加入键码值
参    数：无
返回值  ：无
*************************************************/
void AddKeyCode(char keyCode)
{
    if((rear+1)%Length==front)      //队满
    {
        front=(front+1)%Length;     //出队一个
    }
    Key[rear] = keyCode;
    rear=(rear+1)%Length;
}

/************************************************
函数名称：GetKey
功    能：获取原始键值，无按键则返回0xFF(4个按键)
参    数：无
返回值  ：原始扫描得到的键值
说明    ：4按按键均低电平有效，接在P2.0-P2.3
*************************************************/
char GetKey()
{
  // char ss;
  //ss=P2IN&0x0f;
    if((P2IN&0x0F)==0x0E)
    {
        return 0;
    }                           //键enter按下
    if((P2IN&0x0F)==0x0D)
    {
        return 1;
    }                           //键set按下
    if((P2IN&0x0F)==0x0B)
    {
        return 2;
    }                           //键up按下
    if((P2IN&0x0F)==0x07)
    {
        return 3;
    }                           //键down按下
    return 0xff;
}

/************************************************
函数名称：GetKey
功    能：获取原始键值，无按键则返回0xFF(4*4按键)
参    数：无
返回值  ：原始扫描得到的键值
说明    ：P1.0-P1.3行线输入，P1.4-P1.7列线扫描
*************************************************/
/*char GetKey()
{
    P1DIR |= 0XF0;                  //高四位输出
    for(int i=0;i<4;i++)
    {
        P1OUT = 0XEF << i;
        for(int j=0;j<4;j++)
        {
            if((P1IN&(0x01<<j))==0)
            {
                return (i+4*j);
            }
        }
    }
    return 0xff;
}
*/
/************************************************
函数名称：KeyProcess
功    能：键盘处理函数
参    数：无
返回值  ：无
说明    ：此函数为键盘函数的处理函数,需要每10-20ms
          运行一次，即放入中断函数。
*************************************************/
void KeyProcess()
{
    static char keyValue = 0xff;    //按键标识，键值
    static char addedFlag = 0;      //加入队列标志
    char keyVal = GetKey();
    if(keyVal==0xff)                //无按键
    {
        keyValue = 0xff;
        addedFlag = 0;
        return;
    }
    if(keyValue==0xff)              //之前状态无按键
    {
        keyValue = keyVal;
        return;
    }
    if(keyValue!=keyVal)            //和前次按键不同
    {
        keyValue = keyVal;          //保存新按键值
        return;
    }
    if(addedFlag==1)                //已加入队列
    {
        return;
    }
    addedFlag = 1;
    AddKeyCode(KeyCode[keyVal]);
}

/************************************************
函数名称：WDT_ISR
功    能：看门狗定时中断（16ms）
参    数：无
返回值  ：无
*************************************************/
/*#pragma vector=WDT_VECTOR
__interrupt void WDT_ISR()
{
    KeyProcess();
}*/