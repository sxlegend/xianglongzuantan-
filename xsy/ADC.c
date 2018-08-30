#include "ADC.h"

//*************************************************************************
//	ADC初始化程序，用于配置ADC相关寄存器
//*************************************************************************
void ADC_Init()
{
  P6SEL|=0x01;                                    //选择ADC通道，设置对应IO口的功能模式
  ADC12CTL0|= ADC12ON + SHT0_2 + REF2_5V + REFON; //ADC电源控制开，16个CLK，内部基准2.5V
  //ADC12CTL1|= ADC12SSEL1 + ADC12SSEL0;            //SMCLK做时钟源
 /// ADC12CTL1|=SHP+CONSEQ_2+CSTARTADD_1+SHS_0;
  ADC12CTL1|=SHP;
  ADC12MCTL0= SREF_1 + INCH_0;                     //参考控制位及通道选择
  //ADC12IE|= 0x01;                                 //中断允许
  ADC12CTL0|= ENC;                                //使能转换器
//  ADC12CTL0 |= ADC12SC;           //开启转换
}

//*************************************************************************
//		电压数据处理函数
//*************************************************************************
/*void Data_do(uint temp_d)
{
  ulong temp_3;
  temp_3=(ulong)(temp_d)*100;            //转换公式，ADC数字量转换为电压大小，注意数据类型
  Precent = temp_3/0xFFF;	             //算出百分比

}*/



//*************************************************************************
//	ADC中断服务程序
//*************************************************************************
#pragma vector=ADC_VECTOR
__interrupt void ADC12ISR(void)
{
 // uchar j;
 // yback=190-(1.50*Precent);             //为了波形平滑，要保留前一次采样值对应的坐标点
  while((ADC12CTL1&0x01)==1);           //如果ADC忙，则等待，否则读取ADC转换数值
  //flag_adc = 1 ;
 // TEMP = ADC12MEM0;                     //读取ADC转换值
 /* count++;
  Data_do(TEMP);                        //处理ADC值，用于显示
  if(count<235)                         //决定显示到X轴的什么位置，显示到此位置后要清除数据，else语句执行清除
  {
    GUIpoint(30+count,190-(1.50*Precent),Red);     //把电压值打点在坐标区域，采用百分比算法
   
    GUIline(30+count-1,yback,30+count,190-(1.50*Precent),Red);  //将每个点之间用直线连接，形成波形
    delay_ms(50);
  }
  else
  {
    count=1;                      
    Show_RGB(31,265,40,189,Black);     //当显示完满屏时，用背景色清除显示区
  }*/
}
