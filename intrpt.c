#include <LPC214X.h>       // Includes LPC214x microcontroller register definitions

#include "delay.h"         // Includes delay function declarations

#include "kpm.h"           // Includes keypad function declarations
#include "kpm_defines.h"   // Includes keypad-related macros

#include "lcd.h"           // Includes LCD function declarations
#include "lcd_defines.h"   // Includes LCD commands and definitions

#include "rtc.h"           // Includes RTC function declarations
#include "rtc_defines.h"   // Includes RTC-related macros

#include "types.h"         // Includes user-defined data types
#include "intrp_defines.h" // Includes interrupt-related macros and definitions

// Declaring an external flag to indicate that an interrupt has occurred
extern u8 flag;

// Function to initialize External Interrupt 0 (EINT0)
void Init_INT()
{	
	//cfg p0.1 pin as EINT0 pin
	PINSEL0 &=~(3<<(1*2));                 // Clears the function selection bits of P0.1
	PINSEL0 |= EINT0_PIN_FUNC <<(1*2);      // Selects EINT0 function for P0.1

	//cfg for VIC peripheral
	//all eints are dafault irq types
	//VICIntSelect=0;                       // Selects IRQ mode (default configuration)
	//cfg EINT0 as v.irq0
	VICVectCntl0=(1<<5)|EINT_CH_NO;       // Enables VIC slot 0 and assigns EINT0 channel

	//load EINT0_isr address
	VICVectAddr0=(unsigned)eint0_isr;       // Stores ISR address in VIC vector address register

	//enable EINT0 in VIC
	VICIntEnable=1<<EINT_CH_NO;          // Enables the EINT0 interrupt channel
	
	//cfg for external interrupts peripherals
	//enable EINT0,default all eints are enabled
	EXTINT=0;                               // Clears pending external interrupt flags

	//cfg for eint0 as edge triggered
	EXTMODE=1<<0;                        // Selects edge-triggered mode for EINT0

	// cfg for eint0 as falling edge triggerd
	//EXTPOLAR=0;//default all EINTs are falling edge

	 
}	

// Interrupt Service Routine (ISR) for External Interrupt 0
void eint0_isr(void)__irq
{
	 // ISR activity begins

    flag = 1;                // Sets the flag to indicate that EINT0 interrupt has occurred

    // ISR activity ends

    // Clear the EINT0 interrupt status and allow it to trigger again
    EXTINT = 1 << 0;         // Clears the EINT0 interrupt flag

    // Clear the interrupt status in the VIC
    VICVectAddr = 0;         // Signals the VIC that the current interrupt has been serviced
}
