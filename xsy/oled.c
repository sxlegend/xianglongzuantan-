//#include <msp430x14x.h>
#include "oled.h"

#include "oledfont.h"  	 
	   
void delay(unsigned int ms)
{                         
	unsigned int a;
	while(ms)
	{
		a=1800;
		while(a--);
		ms--;
	}
	return;
}

/**********************************************
//IICT Start
**********************************************/
void IICT_Start()
{

	OLEDT_SCLK_Set();
	OLEDT_SDIN_Set();
	OLEDT_SDIN_Clr();
	OLEDT_SCLK_Clr();
}

/**********************************************
//IICT Stop
**********************************************/
void IICT_Stop()
{
OLEDT_SCLK_Set() ;
//	OLEDT_SCLK_Clr();
	OLEDT_SDIN_Clr();
	OLEDT_SDIN_Set();
	
}

void IICT_Wait_Ack()
{

	OLEDT_SCLK_Set() ;
	OLEDT_SCLK_Clr();
}

/**********************************************
// IICT Write byte
**********************************************/

void Write_IICT_Byte(unsigned char IICT_Byte)
{
	unsigned char i;
	unsigned char m,da;
	da=IICT_Byte;
	OLEDT_SCLK_Clr();
	for(i=0;i<8;i++)		
	{
			m=da;
		//	OLEDT_SCLK_Clr();
		m=m&0x80;
		if(m==0x80)
		{OLEDT_SDIN_Set();}
		else OLEDT_SDIN_Clr();
			da=da<<1;
		OLEDT_SCLK_Set();
		OLEDT_SCLK_Clr();
		}


}

/**********************************************
// IICT Write Command
**********************************************/
void Write_IICT_Command(unsigned char IICT_Command)
{
   IICT_Start();
   Write_IICT_Byte(0x78);            //Slave address,SA0=0
	IICT_Wait_Ack();	
   Write_IICT_Byte(0x00);			//write command
	IICT_Wait_Ack();	
   Write_IICT_Byte(IICT_Command); 
	IICT_Wait_Ack();	
   IICT_Stop();
}
/**********************************************
// IICT Write Data
**********************************************/
void Write_IICT_Data(unsigned char IICT_Data)
{
   IICT_Start();
   Write_IICT_Byte(0x78);			//D/C#=0; R/W#=0
	IICT_Wait_Ack();	
   Write_IICT_Byte(0x40);			//write data
	IICT_Wait_Ack();	
   Write_IICT_Byte(IICT_Data);
	IICT_Wait_Ack();	
   IICT_Stop();
}


void OLEDT_WR_Byte(unsigned dat,unsigned cmd)
{
	if(cmd)
			{

   Write_IICT_Data(dat);
   
		}
	else {
   Write_IICT_Command(dat);
		
	}


}

void fillT_picture(unsigned char fill_Data)
{
	unsigned char m,n;
	for(m=0;m<8;m++)
	{
		OLEDT_WR_Byte(0xb0+m,0);		//page0-page1
		OLEDT_WR_Byte(0x00,0);		//low column start address
		OLEDT_WR_Byte(0x10,0);		//high column start address
		for(n=0;n<128;n++)
			{
				OLEDT_WR_Byte(fill_Data,1);
			}
	}
}




//坐标设置

	void OLEDT_Set_Pos(unsigned char x, unsigned char y) 
{ 	OLEDT_WR_Byte(0xb0+y,OLEDT_CMD);
	OLEDT_WR_Byte(((x&0xf0)>>4)|0x10,OLEDT_CMD);
	OLEDT_WR_Byte((x&0x0f),OLEDT_CMD); 
}   	  
//开启OLEDT显示    
void OLEDT_Display_On(void)
{
	OLEDT_WR_Byte(0X8D,OLEDT_CMD);  //SET DCDC命令
	OLEDT_WR_Byte(0X14,OLEDT_CMD);  //DCDC ON
	OLEDT_WR_Byte(0XAF,OLEDT_CMD);  //DISPLAY ON
}
//关闭OLEDT显示     
void OLEDT_Display_Off(void)
{
	OLEDT_WR_Byte(0X8D,OLEDT_CMD);  //SET DCDC命令
	OLEDT_WR_Byte(0X10,OLEDT_CMD);  //DCDC OFF
	OLEDT_WR_Byte(0XAE,OLEDT_CMD);  //DISPLAY OFF
}		   			 
//清屏函数,清完屏,整个屏幕是黑色的!和没点亮一样!!!	  
void OLEDT_Clear(void)  
{  
	u8 i,n;		    
	for(i=0;i<8;i++)  
	{  
		OLEDT_WR_Byte (0xb0+i,OLEDT_CMD);    //设置页地址（0~7）
		OLEDT_WR_Byte (0x00,OLEDT_CMD);      //设置显示位置—列低地址
		OLEDT_WR_Byte (0x10,OLEDT_CMD);      //设置显示位置—列高地址   
		for(n=0;n<132;n++)OLEDT_WR_Byte(0,OLEDT_DATA); 
	} //更新显示
}

void OLEDT_Clearnum(unsigned char line1,unsigned char line2)  
{  
	u8 i,n;		    
	for(i=line1;i<line2;i++)  
	{  
		OLEDT_WR_Byte (0xb0+i,OLED_CMD);    //设置页地址（0~7）
		OLEDT_WR_Byte (0x00,OLED_CMD);      //设置显示位置—列低地址
		OLEDT_WR_Byte (0x10,OLED_CMD);      //设置显示位置—列高地址   
		for(n=0;n<132;n++)OLEDT_WR_Byte(0,OLED_DATA); 
	} //更新显示
}
void OLEDT_On(void)  
{  
	u8 i,n;		    
	for(i=0;i<8;i++)  
	{  
		OLEDT_WR_Byte (0xb0+i,OLEDT_CMD);    //设置页地址（0~7）
		OLEDT_WR_Byte (0x00,OLEDT_CMD);      //设置显示位置—列低地址
		OLEDT_WR_Byte (0x10,OLEDT_CMD);      //设置显示位置—列高地址   
		for(n=0;n<128;n++)OLEDT_WR_Byte(1,OLEDT_DATA); 
	} //更新显示
}
//在指定位置显示一个字符,包括部分字符
//x:0~127
//y:0~63
//mode:0,反白显示;1,正常显示				 
//size:选择字体 16/12 
void OLEDT_ShowChar(u8 x,u8 y,u8 chr,u8 Char_Size)
{      	
	unsigned char c=0,i=0;	
		c=chr-' ';//得到偏移后的值			
		if(x>Max_Column-1){x=0;y=y+2;}
		if(Char_Size ==16)
			{
			OLEDT_Set_Pos(x,y);	
			for(i=0;i<8;i++)
			OLEDT_WR_Byte(F8X16[c*16+i],OLEDT_DATA);
			OLEDT_Set_Pos(x,y+1);
			for(i=0;i<8;i++)
			OLEDT_WR_Byte(F8X16[c*16+i+8],OLEDT_DATA);
			}
			else {	
				OLEDT_Set_Pos(x,y);
				for(i=0;i<6;i++)
				OLEDT_WR_Byte(F6x8[c][i],OLEDT_DATA);
				
			}
}

//显示12*24数字
void OLEDT_NUM24(u8 x,u8 y,u8 no)
{
  u8 t,adder=0;
  OLEDT_Set_Pos(x,y);
  for(t=0;t<12;t++)
    {
      OLEDT_WR_Byte(NUM24[3*no][t],OLEDT_DATA);
      adder+=1;
     }	
  OLEDT_Set_Pos(x,y+1);	
  for(t=0;t<12;t++)
    {	
      OLEDT_WR_Byte(NUM24[3*no+1][t],OLEDT_DATA);
      adder+=1;
      }	
  OLEDT_Set_Pos(x,y+2);	
  for(t=0;t<12;t++)
    {	
      OLEDT_WR_Byte(NUM24[3*no+2][t],OLEDT_DATA);
      adder+=1;
      }
  
}

//显示16*32数字
void OLEDT_NUM32(u8 x,u8 y,u8 no)
{
  u8 t,adder=0;
  OLEDT_Set_Pos(x,y);
  for(t=0;t<16;t++)
    {
      OLEDT_WR_Byte(NUM[4*no][t],OLEDT_DATA);
      adder+=1;
     }	
  OLEDT_Set_Pos(x,y+1);	
  for(t=0;t<16;t++)
    {	
      OLEDT_WR_Byte(NUM[4*no+1][t],OLEDT_DATA);
      adder+=1;
      }	
  OLEDT_Set_Pos(x,y+2);	
  for(t=0;t<16;t++)
    {	
      OLEDT_WR_Byte(NUM[4*no+2][t],OLEDT_DATA);
      adder+=1;
      }
  OLEDT_Set_Pos(x,y+3);	
  for(t=0;t<16;t++)
    {	
      OLEDT_WR_Byte(NUM[4*no+3][t],OLEDT_DATA);
      adder+=1;
      }	
}

//m^n函数
u32 OLEDT_pow(u8 m,u8 n)
{
	u32 result=1;	 
	while(n--)result*=m;    
	return result;
}				  
//显示2个数字
//x,y :起点坐标	 
//len :数字的位数
//size:字体大小
//mode:模式	0,填充模式;1,叠加模式
//num:数值(0~4294967295);	 		  
void OLEDT_ShowNum(u8 x,u8 y,u32 num,u8 len,u8 size2)
{         	
	u8 t,temp;
	u8 enshow=1;						   
	for(t=0;t<len;t++)
	{
		temp=(num/OLEDT_pow(10,len-t-1))%10;
		if(enshow==0&&t<(len-1))
		{
			if(temp==0)
			{
				OLEDT_ShowChar(x+(size2/2)*t,y,' ',size2);
				continue;
			}else enshow=1; 
		 	 
		}
	 	OLEDT_ShowChar(x+(size2/2)*t,y,temp+'0',size2); 
	}
} 

//显示2个数字
//x,y :起点坐标	 
//len :数字的位数
//size:字体大小
//mode:模式	0,填充模式;1,叠加模式
//num:数值(0~4294967295);	 		  
void OLEDT_ShowNum32(u8 x,u8 y,u32 num,u8 len,u8 size2)
{         	
	u8 t,temp;
	//u8 enshow=0;						   
	for(t=0;t<len;t++)
	{
		temp=(num/OLEDT_pow(10,len-t-1))%10;
		/*if(enshow==0&&t<(len-1))
		{
			if(temp==0)
			{
				OLEDT_ShowChar(x+(size2/2)*t,y,' ');
				continue;
			}else enshow=1; 
		 	 
		}*/
	 	OLEDT_NUM32(x+(size2/2)*t,y,temp); 
	}
} 

void OLEDT_ShowNum24(u8 x,u8 y,u32 num,u8 len,u8 size2)
{         	
	u8 t,temp;
	//u8 enshow=0;						   
	for(t=0;t<len;t++)
	{
		temp=(num/OLEDT_pow(10,len-t-1))%10;
		/*if(enshow==0&&t<(len-1))
		{
			if(temp==0)
			{
				OLEDT_ShowChar(x+(size2/2)*t,y,' ');
				continue;
			}else enshow=1; 
		 	 
		}*/
	 	OLEDT_NUM24(x+(size2/2)*t,y,temp); 
	}
} 


//显示一个字符号串
void OLEDT_ShowString(u8 x,u8 y,u8 *chr,u8 Char_Size)
{
	unsigned char j=0;
	while (chr[j]!='\0')
	{		OLEDT_ShowChar(x,y,chr[j],Char_Size);
			x+=8;
		if(x>120){x=0;y+=2;}
			j++;
	}
}

//显示汉字
void OLEDT_ShowCHinese(u8 x,u8 y,u8 no)
{      			    
	u8 t,adder=0;
	OLEDT_Set_Pos(x,y);	
    for(t=0;t<16;t++)
		{
				OLEDT_WR_Byte(Hzk1[2*no][t],OLEDT_DATA);
				adder+=1;
     }	
		OLEDT_Set_Pos(x,y+1);	
    for(t=0;t<16;t++)
			{	
				OLEDT_WR_Byte(Hzk1[2*no+1][t],OLEDT_DATA);
				adder+=1;
      }					
}

void OLEDT_ShowBattery(u8 x,u8 y,u8 no)
{      			    
	u8 t,adder=0;
	OLEDT_Set_Pos(x,y);	
    for(t=0;t<16;t++)
		{
				OLEDT_WR_Byte(Hzk[2*no][t],OLEDT_DATA);
				adder+=1;
     }	
		OLEDT_Set_Pos(x,y+1);	
    for(t=0;t<16;t++)
			{	
				OLEDT_WR_Byte(Hzk[2*no+1][t],OLEDT_DATA);
				adder+=1;
      }					
}
/***********功能描述：显示显示BMP图片128×64起始点坐标(x,y),x的范围0～127，y为页的范围0～7*****************/
void OLEDT_DrawBMP(unsigned char x0, unsigned char y0,unsigned char x1, unsigned char y1,unsigned char BMP[])
{ 	
 unsigned int j=0;
 unsigned char x,y;
  
  if(y1%8==0) y=y1/8;      
  else y=y1/8+1;
	for(y=y0;y<y1;y++)
	{
		OLEDT_Set_Pos(x0,y);
    for(x=x0;x<x1;x++)
	    {      
	    	OLEDT_WR_Byte(BMP[j++],OLEDT_DATA);	    	
	    }
	}
} 

//初始化SSD1306					    
void OLEDT_Init(void)
{ 	

        OLEDT_WR_Byte(0xAE,OLEDT_CMD);//--turn off OLEDT panel
	OLEDT_WR_Byte(0x02,OLEDT_CMD);//---set low column address
	OLEDT_WR_Byte(0x10,OLEDT_CMD);//---set high column address
	OLEDT_WR_Byte(0x40,OLEDT_CMD);//--set start line address  Set Mapping RAM Display Start Line (0x00~0x3F)
	OLEDT_WR_Byte(0x81,OLEDT_CMD);//--set contrast control register
	OLEDT_WR_Byte(0xCF,OLEDT_CMD); // Set SEG Output Current Brightness
	OLEDT_WR_Byte(0xA1,OLEDT_CMD);//--Set SEG/Column Mapping     0xa1从左开始，0xa0从右开始
	OLEDT_WR_Byte(0xC8,OLEDT_CMD);//Set COM/Row Scan Direction   0xc8从顶部开始，0xc0从底部开始
	OLEDT_WR_Byte(0xA6,OLEDT_CMD);//--set normal display
	OLEDT_WR_Byte(0xA8,OLEDT_CMD);//--set multiplex ratio(1 to 64)
	OLEDT_WR_Byte(0x3f,OLEDT_CMD);//--1/64 duty
	OLEDT_WR_Byte(0xD3,OLEDT_CMD);//-set display offset	Shift Mapping RAM Counter (0x00~0x3F)
	OLEDT_WR_Byte(0x00,OLEDT_CMD);//-not offset
	OLEDT_WR_Byte(0xd5,OLEDT_CMD);//--set display clock divide ratio/oscillator frequency
	OLEDT_WR_Byte(0x80,OLEDT_CMD);//--set divide ratio, Set Clock as 100 Frames/Sec
	OLEDT_WR_Byte(0xD9,OLEDT_CMD);//--set pre-charge period
	OLEDT_WR_Byte(0xF1,OLEDT_CMD);//Set Pre-Charge as 15 Clocks & Discharge as 1 Clock
	OLEDT_WR_Byte(0xDA,OLEDT_CMD);//--set com pins hardware configuration
	OLEDT_WR_Byte(0x12,OLEDT_CMD);
	OLEDT_WR_Byte(0xDB,OLEDT_CMD);//--set vcomh
	OLEDT_WR_Byte(0x40,OLEDT_CMD);//Set VCOM Deselect Level
	OLEDT_WR_Byte(0x20,OLEDT_CMD);//-Set Page Addressing Mode (0x00/0x01/0x02)
	OLEDT_WR_Byte(0x02,OLEDT_CMD);//
	OLEDT_WR_Byte(0x8D,OLEDT_CMD);//--set Charge Pump enable/disable
	OLEDT_WR_Byte(0x14,OLEDT_CMD);//--set(0x10) disable
	OLEDT_WR_Byte(0xA4,OLEDT_CMD);// Disable Entire Display On (0xa4/0xa5全屏显示）
	OLEDT_WR_Byte(0xA6,OLEDT_CMD);// Disable Inverse Display On (0xa6/a7反显) 
	OLEDT_WR_Byte(0xAF,OLEDT_CMD);//--turn on OLEDT panel
	
	OLEDT_WR_Byte(0xAF,OLEDT_CMD); //display ON 
	OLEDT_Clear();
} 

/**********************************************
//IIC Start
**********************************************/
void IIC_Start()
{

	OLED_SCLK_Set() ;
	OLED_SDIN_Set();
	OLED_SDIN_Clr();
	OLED_SCLK_Clr();
}

/**********************************************
//IIC Stop
**********************************************/
void IIC_Stop()
{
OLED_SCLK_Set() ;
//	OLED_SCLK_Clr();
	OLED_SDIN_Clr();
	OLED_SDIN_Set();
	
}

void IIC_Wait_Ack()
{

	OLED_SCLK_Set() ;
	OLED_SCLK_Clr();
}

/**********************************************
// IIC Write byte
**********************************************/

void Write_IIC_Byte(unsigned char IIC_Byte)
{
	unsigned char i;
	unsigned char m,da;
	da=IIC_Byte;
	OLED_SCLK_Clr();
	for(i=0;i<8;i++)		
	{
			m=da;
		//	OLED_SCLK_Clr();
		m=m&0x80;
		if(m==0x80)
		{OLED_SDIN_Set();}
		else OLED_SDIN_Clr();
			da=da<<1;
		OLED_SCLK_Set();
		OLED_SCLK_Clr();
		}


}

/**********************************************
// IIC Write Command
**********************************************/
void Write_IIC_Command(unsigned char IIC_Command)
{
   IIC_Start();
   Write_IIC_Byte(0x78);            //Slave address,SA0=0
	IIC_Wait_Ack();	
   Write_IIC_Byte(0x00);			//write command
	IIC_Wait_Ack();	
   Write_IIC_Byte(IIC_Command); 
	IIC_Wait_Ack();	
   IIC_Stop();
}
/**********************************************
// IIC Write Data
**********************************************/
void Write_IIC_Data(unsigned char IIC_Data)
{
   IIC_Start();
   Write_IIC_Byte(0x78);			//D/C#=0; R/W#=0
	IIC_Wait_Ack();	
   Write_IIC_Byte(0x40);			//write data
	IIC_Wait_Ack();	
   Write_IIC_Byte(IIC_Data);
	IIC_Wait_Ack();	
   IIC_Stop();
}


void OLED_WR_Byte(unsigned dat,unsigned cmd)
{
	if(cmd)
			{

   Write_IIC_Data(dat);
   
		}
	else {
   Write_IIC_Command(dat);
		
	}


}

void fill_picture(unsigned char fill_Data)
{
	unsigned char m,n;
	for(m=0;m<8;m++)
	{
		OLED_WR_Byte(0xb0+m,0);		//page0-page1
		OLED_WR_Byte(0x00,0);		//low column start address
		OLED_WR_Byte(0x10,0);		//high column start address
		for(n=0;n<128;n++)
			{
				OLED_WR_Byte(fill_Data,1);
			}
	}
}


/***********************Delay****************************************/
void Delay_50ms(unsigned int Del_50ms)
{
	unsigned int m;
	for(;Del_50ms>0;Del_50ms--)
		for(m=6245;m>0;m--);
}

void Delay_1ms(unsigned int Del_1ms)
{
	unsigned char j;
	while(Del_1ms--)
	{	
		for(j=0;j<123;j++);
	}
}

//坐标设置

	void OLED_Set_Pos(unsigned char x, unsigned char y) 
{ 	OLED_WR_Byte(0xb0+y,OLED_CMD);
	OLED_WR_Byte(((x&0xf0)>>4)|0x10,OLED_CMD);
	OLED_WR_Byte((x&0x0f),OLED_CMD); 
}   	  
//开启OLED显示    
void OLED_Display_On(void)
{
	OLED_WR_Byte(0X8D,OLED_CMD);  //SET DCDC命令
	OLED_WR_Byte(0X14,OLED_CMD);  //DCDC ON
	OLED_WR_Byte(0XAF,OLED_CMD);  //DISPLAY ON
}
//关闭OLED显示     
void OLED_Display_Off(void)
{
	OLED_WR_Byte(0X8D,OLED_CMD);  //SET DCDC命令
	OLED_WR_Byte(0X10,OLED_CMD);  //DCDC OFF
	OLED_WR_Byte(0XAE,OLED_CMD);  //DISPLAY OFF
}		   			 
//清屏函数,清完屏,整个屏幕是黑色的!和没点亮一样!!!	  
void OLED_Clear(void)  
{  
	u8 i,n;		    
	for(i=0;i<8;i++)  
	{  
		OLED_WR_Byte (0xb0+i,OLED_CMD);    //设置页地址（0~7）
		OLED_WR_Byte (0x00,OLED_CMD);      //设置显示位置—列低地址
		OLED_WR_Byte (0x10,OLED_CMD);      //设置显示位置—列高地址   
		for(n=0;n<132;n++)OLED_WR_Byte(0,OLED_DATA); 
	} //更新显示
}

void OLED_Clearnum(unsigned char line1,unsigned char line2)  
{  
	u8 i,n;		    
	for(i=line1;i<line2;i++)  
	{  
		OLED_WR_Byte (0xb0+i,OLED_CMD);    //设置页地址（0~7）
		OLED_WR_Byte (0x00,OLED_CMD);      //设置显示位置—列低地址
		OLED_WR_Byte (0x10,OLED_CMD);      //设置显示位置—列高地址   
		for(n=0;n<132;n++)OLED_WR_Byte(0,OLED_DATA); 
	} //更新显示
}
void OLED_On(void)  
{  
	u8 i,n;		    
	for(i=0;i<8;i++)  
	{  
		OLED_WR_Byte (0xb0+i,OLED_CMD);    //设置页地址（0~7）
		OLED_WR_Byte (0x00,OLED_CMD);      //设置显示位置—列低地址
		OLED_WR_Byte (0x10,OLED_CMD);      //设置显示位置—列高地址   
		for(n=0;n<128;n++)OLED_WR_Byte(1,OLED_DATA); 
	} //更新显示
}
//在指定位置显示一个字符,包括部分字符
//x:0~127
//y:0~63
//mode:0,反白显示;1,正常显示				 
//size:选择字体 16/12 
void OLED_ShowChar(u8 x,u8 y,u8 chr,u8 Char_Size)
{      	
	unsigned char c=0,i=0;	
		c=chr-' ';//得到偏移后的值			
		if(x>Max_Column-1){x=0;y=y+2;}
		if(Char_Size ==16)
			{
			OLED_Set_Pos(x,y);	
			for(i=0;i<8;i++)
			OLED_WR_Byte(F8X16[c*16+i],OLED_DATA);
			OLED_Set_Pos(x,y+1);
			for(i=0;i<8;i++)
			OLED_WR_Byte(F8X16[c*16+i+8],OLED_DATA);
			}
			else {	
				OLED_Set_Pos(x,y);
				for(i=0;i<6;i++)
				OLED_WR_Byte(F6x8[c][i],OLED_DATA);
				
			}
}

//显示12*24数字
void OLED_NUM24(u8 x,u8 y,u8 no)
{
  u8 t,adder=0;
  OLED_Set_Pos(x,y);
  for(t=0;t<12;t++)
    {
      OLED_WR_Byte(NUM24[3*no][t],OLED_DATA);
      adder+=1;
     }	
  OLED_Set_Pos(x,y+1);	
  for(t=0;t<12;t++)
    {	
      OLED_WR_Byte(NUM24[3*no+1][t],OLED_DATA);
      adder+=1;
      }	
  OLED_Set_Pos(x,y+2);	
  for(t=0;t<12;t++)
    {	
      OLED_WR_Byte(NUM24[3*no+2][t],OLED_DATA);
      adder+=1;
      }
  
}

//显示16*32数字
void OLED_NUM32(u8 x,u8 y,u8 no)
{
  u8 t,adder=0;
  OLED_Set_Pos(x,y);
  for(t=0;t<16;t++)
    {
      OLED_WR_Byte(NUM[4*no][t],OLED_DATA);
      adder+=1;
     }	
  OLED_Set_Pos(x,y+1);	
  for(t=0;t<16;t++)
    {	
      OLED_WR_Byte(NUM[4*no+1][t],OLED_DATA);
      adder+=1;
      }	
  OLED_Set_Pos(x,y+2);	
  for(t=0;t<16;t++)
    {	
      OLED_WR_Byte(NUM[4*no+2][t],OLED_DATA);
      adder+=1;
      }
  OLED_Set_Pos(x,y+3);	
  for(t=0;t<16;t++)
    {	
      OLED_WR_Byte(NUM[4*no+3][t],OLED_DATA);
      adder+=1;
      }	
}

//m^n函数
u32 oled_pow(u8 m,u8 n)
{
	u32 result=1;	 
	while(n--)result*=m;    
	return result;
}				  
//显示2个数字
//x,y :起点坐标	 
//len :数字的位数
//size:字体大小
//mode:模式	0,填充模式;1,叠加模式
//num:数值(0~4294967295);	 		  
void OLED_ShowNum(u8 x,u8 y,u32 num,u8 len,u8 size2)
{         	
	u8 t,temp;
	u8 enshow=1;						   
	for(t=0;t<len;t++)
	{
		temp=(num/oled_pow(10,len-t-1))%10;
		if(enshow==0&&t<(len-1))
		{
			if(temp==0)
			{
				OLED_ShowChar(x+(size2/2)*t,y,' ',size2);
				continue;
			}else enshow=1; 
		 	 
		}
	 	OLED_ShowChar(x+(size2/2)*t,y,temp+'0',size2); 
	}
} 

//显示2个数字
//x,y :起点坐标	 
//len :数字的位数
//size:字体大小
//mode:模式	0,填充模式;1,叠加模式
//num:数值(0~4294967295);	 		  
void OLED_ShowNum32(u8 x,u8 y,u32 num,u8 len,u8 size2)
{         	
	u8 t,temp;
	//u8 enshow=0;						   
	for(t=0;t<len;t++)
	{
		temp=(num/oled_pow(10,len-t-1))%10;
		/*if(enshow==0&&t<(len-1))
		{
			if(temp==0)
			{
				OLED_ShowChar(x+(size2/2)*t,y,' ');
				continue;
			}else enshow=1; 
		 	 
		}*/
	 	OLED_NUM32(x+(size2/2)*t,y,temp); 
	}
} 

void OLED_ShowNum24(u8 x,u8 y,u32 num,u8 len,u8 size2)
{         	
	u8 t,temp;
	//u8 enshow=0;						   
	for(t=0;t<len;t++)
	{
		temp=(num/oled_pow(10,len-t-1))%10;
		/*if(enshow==0&&t<(len-1))
		{
			if(temp==0)
			{
				OLED_ShowChar(x+(size2/2)*t,y,' ');
				continue;
			}else enshow=1; 
		 	 
		}*/
	 	OLED_NUM24(x+(size2/2)*t,y,temp); 
	}
} 


//显示一个字符号串
void OLED_ShowString(u8 x,u8 y,u8 *chr,u8 Char_Size)
{
	unsigned char j=0;
	while (chr[j]!='\0')
	{		OLED_ShowChar(x,y,chr[j],Char_Size);
			x+=8;
		if(x>120){x=0;y+=2;}
			j++;
	}
}

//显示汉字
void OLED_ShowCHinese(u8 x,u8 y,u8 no)
{      			    
	u8 t,adder=0;
	OLED_Set_Pos(x,y);	
    for(t=0;t<16;t++)
		{
				OLED_WR_Byte(Hzk1[2*no][t],OLED_DATA);
				adder+=1;
     }	
		OLED_Set_Pos(x,y+1);	
    for(t=0;t<16;t++)
			{	
				OLED_WR_Byte(Hzk1[2*no+1][t],OLED_DATA);
				adder+=1;
      }					
}

//显示电池电量
void OLED_ShowBattery(u8 x,u8 y,u8 no)
{      			    
	u8 t,adder=0;
	OLED_Set_Pos(x,y);	
    for(t=0;t<16;t++)
		{
				OLED_WR_Byte(Hzk[2*no][t],OLED_DATA);
				adder+=1;
     }	
		OLED_Set_Pos(x,y+1);	
    for(t=0;t<16;t++)
			{	
				OLED_WR_Byte(Hzk[2*no+1][t],OLED_DATA);
				adder+=1;
      }					
}

/***********功能描述：显示显示BMP图片128×64起始点坐标(x,y),x的范围0～127，y为页的范围0～7*****************/
void OLED_DrawBMP(unsigned char x0, unsigned char y0,unsigned char x1, unsigned char y1,unsigned char BMP[])
{ 	
 unsigned int j=0;
 unsigned char x,y;
  
  if(y1%8==0) y=y1/8;      
  else y=y1/8+1;
	for(y=y0;y<y1;y++)
	{
		OLED_Set_Pos(x0,y);
    for(x=x0;x<x1;x++)
	    {      
	    	OLED_WR_Byte(BMP[j++],OLED_DATA);	    	
	    }
	}
} 

//初始化SSD1306					    
void OLED_Init(void)
{ 	

        OLED_WR_Byte(0xAE,OLED_CMD);//--turn off oled panel
	OLED_WR_Byte(0x02,OLED_CMD);//---set low column address
	OLED_WR_Byte(0x10,OLED_CMD);//---set high column address
	OLED_WR_Byte(0x40,OLED_CMD);//--set start line address  Set Mapping RAM Display Start Line (0x00~0x3F)
	OLED_WR_Byte(0x81,OLED_CMD);//--set contrast control register
	OLED_WR_Byte(0xCF,OLED_CMD); // Set SEG Output Current Brightness
	OLED_WR_Byte(0xA1,OLED_CMD);//--Set SEG/Column Mapping     0xa1从左开始，0xa0从右开始
	OLED_WR_Byte(0xC8,OLED_CMD);//Set COM/Row Scan Direction   0xc8从顶部开始，0xc0从底部开始
	OLED_WR_Byte(0xA6,OLED_CMD);//--set normal display
	OLED_WR_Byte(0xA8,OLED_CMD);//--set multiplex ratio(1 to 64)
	OLED_WR_Byte(0x3f,OLED_CMD);//--1/64 duty
	OLED_WR_Byte(0xD3,OLED_CMD);//-set display offset	Shift Mapping RAM Counter (0x00~0x3F)
	OLED_WR_Byte(0x00,OLED_CMD);//-not offset
	OLED_WR_Byte(0xd5,OLED_CMD);//--set display clock divide ratio/oscillator frequency
	OLED_WR_Byte(0x80,OLED_CMD);//--set divide ratio, Set Clock as 100 Frames/Sec
	OLED_WR_Byte(0xD9,OLED_CMD);//--set pre-charge period
	OLED_WR_Byte(0xF1,OLED_CMD);//Set Pre-Charge as 15 Clocks & Discharge as 1 Clock
	OLED_WR_Byte(0xDA,OLED_CMD);//--set com pins hardware configuration
	OLED_WR_Byte(0x12,OLED_CMD);
	OLED_WR_Byte(0xDB,OLED_CMD);//--set vcomh
	OLED_WR_Byte(0x40,OLED_CMD);//Set VCOM Deselect Level
	OLED_WR_Byte(0x20,OLED_CMD);//-Set Page Addressing Mode (0x00/0x01/0x02)
	OLED_WR_Byte(0x02,OLED_CMD);//
	OLED_WR_Byte(0x8D,OLED_CMD);//--set Charge Pump enable/disable
	OLED_WR_Byte(0x14,OLED_CMD);//--set(0x10) disable
	OLED_WR_Byte(0xA4,OLED_CMD);// Disable Entire Display On (0xa4/0xa5全屏显示）
	OLED_WR_Byte(0xA6,OLED_CMD);// Disable Inverse Display On (0xa6/a7反显) 
	OLED_WR_Byte(0xAF,OLED_CMD);//--turn on oled panel
	
	OLED_WR_Byte(0xAF,OLED_CMD); //display ON 
	OLED_Clear();
}      
  
        
        
  