#include "ADC.h"

//*************************************************************************
//	ADC��ʼ��������������ADC��ؼĴ���
//*************************************************************************
void ADC_Init()
{
  P6SEL|=0x01;                                    //ѡ��ADCͨ�������ö�ӦIO�ڵĹ���ģʽ
  ADC12CTL0|= ADC12ON + SHT0_2 + REF2_5V + REFON; //ADC��Դ���ƿ���16��CLK���ڲ���׼2.5V
  //ADC12CTL1|= ADC12SSEL1 + ADC12SSEL0;            //SMCLK��ʱ��Դ
 /// ADC12CTL1|=SHP+CONSEQ_2+CSTARTADD_1+SHS_0;
  ADC12CTL1|=SHP;
  ADC12MCTL0= SREF_1 + INCH_0;                     //�ο�����λ��ͨ��ѡ��
  //ADC12IE|= 0x01;                                 //�ж�����
  ADC12CTL0|= ENC;                                //ʹ��ת����
//  ADC12CTL0 |= ADC12SC;           //����ת��
}

//*************************************************************************
//		��ѹ���ݴ�������
//*************************************************************************
/*void Data_do(uint temp_d)
{
  ulong temp_3;
  temp_3=(ulong)(temp_d)*100;            //ת����ʽ��ADC������ת��Ϊ��ѹ��С��ע����������
  Precent = temp_3/0xFFF;	             //����ٷֱ�

}*/



//*************************************************************************
//	ADC�жϷ������
//*************************************************************************
#pragma vector=ADC_VECTOR
__interrupt void ADC12ISR(void)
{
 // uchar j;
 // yback=190-(1.50*Precent);             //Ϊ�˲���ƽ����Ҫ����ǰһ�β���ֵ��Ӧ�������
  while((ADC12CTL1&0x01)==1);           //���ADCæ����ȴ��������ȡADCת����ֵ
  //flag_adc = 1 ;
 // TEMP = ADC12MEM0;                     //��ȡADCת��ֵ
 /* count++;
  Data_do(TEMP);                        //����ADCֵ��������ʾ
  if(count<235)                         //������ʾ��X���ʲôλ�ã���ʾ����λ�ú�Ҫ������ݣ�else���ִ�����
  {
    GUIpoint(30+count,190-(1.50*Precent),Red);     //�ѵ�ѹֵ������������򣬲��ðٷֱ��㷨
   
    GUIline(30+count-1,yback,30+count,190-(1.50*Precent),Red);  //��ÿ����֮����ֱ�����ӣ��γɲ���
    delay_ms(50);
  }
  else
  {
    count=1;                      
    Show_RGB(31,265,40,189,Black);     //����ʾ������ʱ���ñ���ɫ�����ʾ��
  }*/
}