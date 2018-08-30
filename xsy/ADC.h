#ifndef __ADC_H
#define __ADC_H			  	 
#include	<msp430x14x.h>

void ADC_Init();

#pragma vector=ADC_VECTOR
__interrupt void ADC12ISR(void);


#endif 