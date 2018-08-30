
//******************************************************************************/
#ifndef __OLED_H
#define __OLED_H			  	 
#include	<msp430x14x.h>
//#include	<in430.h>
#include	<intrinsics.h> 
#define  u8 unsigned char 
#define  u32 unsigned int 
#define OLED_CMD  0	//写命令
#define OLED_DATA 1	//写数据
#define OLED_MODE 0

#define OLEDT_CMD  0	//写命令
#define OLEDT_DATA 1	//写数据
#define OLEDT_MODE 0



#define		Set_Bit(val, bitn)		(val |= (/*1 <<*/(bitn)))		//竚琘 1
#define		Clr_Bit(val, bitn)		(val &= ~(/*1<<*/(bitn)))		//竚琘 0
#define		Get_Bit(val, bitn)		(val & (1<<(bitn)) )		//眔琘

//----------------------------------------------------------------------------------
//OLED SSD1306 IIC  时钟D0
//#define		OLED_SSD1306_SCLK_DIR			(P1DIR)
//#define		OLED_SSD1306_SCLK_OUT			(P1OUT)
#define		OLED_SSD1306_SCLK_PIN_NUM		(BIT5)

#define		OLED_SSD1306_SCLK_IO_INIT		(Set_Bit(P1DIR,OLED_SSD1306_SCLK_PIN_NUM))
#define		OLED_SCLK_Set()			        (Set_Bit(P1OUT,OLED_SSD1306_SCLK_PIN_NUM))
#define		OLED_SCLK_Clr()				(Clr_Bit(P1OUT,OLED_SSD1306_SCLK_PIN_NUM))

//----------------------------------------------------------------------------------
//OLED SSD1306 IIC 数据D1
//#define		OLED_SSD1306_SDIN_DIR			(P1DIR)
//#define		OLED_SSD1306_SDIN_OUT			(P1OUT)
#define		OLED_SSD1306_SDIN_PIN_NUM		(BIT6)

#define		OLED_SSD1306_SDIN_IO_INIT		(Set_Bit(P1DIR,OLED_SSD1306_SDIN_PIN_NUM))
#define		OLED_SDIN_Set()				(Set_Bit(P1OUT,OLED_SSD1306_SDIN_PIN_NUM))
#define		OLED_SDIN_Clr()			        (Clr_Bit(P1OUT,OLED_SSD1306_SDIN_PIN_NUM))

//----------------------------------------------------------------------------------
//OLEDT SSD1306 IIC  时钟D0
//#define		OLEDT_SSD1306_SCLK_DIR			(P1DIR)
//#define		OLEDT_SSD1306_SCLK_OUT			(P1OUT)
#define		OLEDT_SSD1306_SCLK_PIN_NUM		(BIT5)

#define		OLEDT_SSD1306_SCLK_IO_INIT		(Set_Bit(P2DIR,OLEDT_SSD1306_SCLK_PIN_NUM))
#define		OLEDT_SCLK_Set()			(Set_Bit(P2OUT,OLEDT_SSD1306_SCLK_PIN_NUM))
#define		OLEDT_SCLK_Clr()	        	(Clr_Bit(P2OUT,OLEDT_SSD1306_SCLK_PIN_NUM))

//----------------------------------------------------------------------------------
//OLEDT SSD1306 IIC 数据D1
//#define		OLEDT_SSD1306_SDIN_DIR			(P1DIR)
//#define		OLEDT_SSD1306_SDIN_OUT			(P1OUT)
#define		OLEDT_SSD1306_SDIN_PIN_NUM		(BIT6)

#define		OLEDT_SSD1306_SDIN_IO_INIT		(Set_Bit(P2DIR,OLEDT_SSD1306_SDIN_PIN_NUM))
#define		OLEDT_SDIN_Set()			(Set_Bit(P2OUT,OLEDT_SSD1306_SDIN_PIN_NUM))
#define		OLEDT_SDIN_Clr()		        (Clr_Bit(P2OUT,OLEDT_SSD1306_SDIN_PIN_NUM))

    	
#define SIZE 16
#define XLevelL		0x02
#define XLevelH		0x10
#define Max_Column	128
#define Max_Row		64
#define	Brightness	0xFF 
#define X_WIDTH 	128
#define Y_WIDTH 	64	  

//-----------------OLED端口定义----------------  					   

void delay(unsigned int ms);


 		     

//OLED控制用函数
void OLED_WR_Byte(unsigned dat,unsigned cmd);  
void OLED_Display_On(void);
void OLED_Display_Off(void);	   							   		    
void OLED_Init(void);
void OLED_Clear(void);
void OLED_Clearnum(unsigned char line1,unsigned char line2) ;

void OLED_DrawPoint(u8 x,u8 y,u8 t);
void OLED_Fill(u8 x1,u8 y1,u8 x2,u8 y2,u8 dot);
void OLED_ShowChar(u8 x,u8 y,u8 chr,u8 Char_Size);
void OLED_ShowNum(u8 x,u8 y,u32 num,u8 len,u8 size);
void OLED_ShowString(u8 x,u8 y, u8 *p,u8 Char_Size);	 
void OLED_Set_Pos(unsigned char x, unsigned char y);
void OLED_ShowCHinese(u8 x,u8 y,u8 no);
void OLED_DrawBMP(unsigned char x0, unsigned char y0,unsigned char x1, unsigned char y1,unsigned char BMP[]);
void Delay_50ms(unsigned int Del_50ms);
void Delay_1ms(unsigned int Del_1ms);
void fill_picture(unsigned char fill_Data);
void Picture();
void IIC_Start();
void IIC_Stop();
void Write_IIC_Command(unsigned char IIC_Command);
void Write_IIC_Data(unsigned char IIC_Data);
void Write_IIC_Byte(unsigned char IIC_Byte);
void IIC_Wait_Ack();

void OLED_NUM24(u8 x,u8 y,u8 no);
void OLED_NUM32(u8 x,u8 y,u8 no);

void OLED_ShowNum32(u8 x,u8 y,u32 num,u8 len,u8 size2);
void OLED_ShowNum24(u8 x,u8 y,u32 num,u8 len,u8 size2);

void OLED_ShowBattery(u8 x,u8 y,u8 no);


//OLEDT控制用函数
void OLEDT_WR_Byte(unsigned dat,unsigned cmd);  
void OLEDT_Display_On(void);
void OLEDT_Display_Off(void);	   							   		    
void OLEDT_Init(void);
void OLEDT_Clear(void);
void OLEDT_Clearnum(unsigned char line1,unsigned char line2) ;
void OLEDT_DrawPoint(u8 x,u8 y,u8 t);
void OLEDT_Fill(u8 x1,u8 y1,u8 x2,u8 y2,u8 dot);
void OLEDT_ShowChar(u8 x,u8 y,u8 chr,u8 Char_Size);
void OLEDT_ShowNum(u8 x,u8 y,u32 num,u8 len,u8 size);
void OLEDT_ShowString(u8 x,u8 y, u8 *p,u8 Char_Size);	 
void OLEDT_Set_Pos(unsigned char x, unsigned char y);
void OLEDT_ShowCHinese(u8 x,u8 y,u8 no);
void OLEDT_DrawBMP(unsigned char x0, unsigned char y0,unsigned char x1, unsigned char y1,unsigned char BMP[]);

void fill_picture(unsigned char fill_Data);
void Picture();
void IIC_Start();
void IIC_Stop();
void Write_IIC_Command(unsigned char IIC_Command);
void Write_IIC_Data(unsigned char IIC_Data);
void Write_IIC_Byte(unsigned char IIC_Byte);
void IIC_Wait_Ack();

void OLEDT_NUM24(u8 x,u8 y,u8 no);
void OLEDT_NUM32(u8 x,u8 y,u8 no);

void OLEDT_ShowNum32(u8 x,u8 y,u32 num,u8 len,u8 size2);
void OLEDT_ShowNum24(u8 x,u8 y,u32 num,u8 len,u8 size2);

void OLEDT_ShowBattery(u8 x,u8 y,u8 no);
#endif  
	 



