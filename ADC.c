#include "types.h"       // Includes user-defined data types
#include <LPC21xx.h>     // Includes LPC21xx microcontroller register definitions
#include "ADC_defines.h" // Includes ADC-related macros and definitions
#include "delay.h"       // Includes delay function declarations
#include "ADC.h"         // Includes ADC function declarations
void Init_ADC(void)
{	//cfg pins p0.27 to p0.30 selectively 
    //for AIN0-AIN1 pin functions
	PINSEL1 &= ~(3<<(27-16)*2);
	PINSEL1 |= AIN1_FUNC;
	  //cfg ADCR
	ADCR |= (1<<PDN_BIT) | (CLKDIV_VAL << CLKDIV_BITS);
}
void Read_ADC(u8  chNo,u16 *dVal,f32 *eAR)
{
	//claer any prev channel selection
	ADCR &= 0XFFFFFF00;
	//updtae on reg channel selection
	//start sample for adc conversion
	ADCR |=(1<<ADC_CONV_START_BIT) |(1<< chNo);
	//wait for convo time
	delay_us(3);
	//check status of conv
	while(((ADDR>>DONE_BIT)&1)==0);
	//stop sampling &conversion
	ADCR &= ~(1<<ADC_CONV_START_BIT);
	//read /extract digital data
	*dVal =((ADDR>>DIGITAL_DATA_BITS)&1023);
	//represent in equivalent voltage level
	*eAR=*dVal*(3.3/1023);
}
