#ifndef __UART_H
#define __UART_H			  	 
#include	<msp430x14x.h>

//void UART_Init0();
void UART_Init1();
void Send_Byte(unsigned char data);
void Print_Str(unsigned char *s);
void RX();
void LYPD();
#endif 