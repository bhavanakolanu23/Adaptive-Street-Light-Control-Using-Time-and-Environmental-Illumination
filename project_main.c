#include <LPC214X.h>       // Includes LPC214x microcontroller register definitions

#include "delay.h"         // Includes delay function declarations
#include "rtc.h"           // Includes RTC function declarations
#include "rtc_defines.h"   // Includes RTC register definitions and macros

#include "kpm.h"            // Includes keypad function declarations
#include "kpm_defines.h"    // Includes keypad-related macros

#include "lcd.h"            // Includes LCD function declarations
#include "lcd_defines.h"    // Includes LCD commands and definitions

#include "intrp_defines.h"  // Includes interrupt-related macros

#include "ADC_defines.h"    // Includes ADC-related macros
#include "ADC.h"            // Includes ADC function declarations


#define THRESHOLD 20      // Defines the LDR illumination threshold in lux

// Global variables to store configured ON and OFF time
u32 onHH,onMM,offHH,offMM;
u32 onSS,offSS;

// Variables to store current time, ON time and OFF time in minutes
u32 cur_time,on_time,off_time;

// Variables to store LDR sensor readings
u32 tadc;                   // Stores ADC digital value
f32 tvolt;                  // Stores calculated voltage
f32 tresis;                 // Stores calculated LDR resistance
f32 tlux;                   // Stores calculated light intensity in lux

u8 flag;                    // Interrupt flag to indicate menu activation

// Global variables to store RTC time and date
u32 hour,min,sec,date,month,year,day;
// Main function
int main()
{
	  InitLCD();              // Initializes the LCD
    Init_kpm();             // Initializes the keypad
    Init_INT();             // Initializes External Interrupt 0
    RTC_Init();             // Initializes the Real-Time Clock
    Init_ADC();             // Initializes the ADC module
	  IODIR0 |= (1<<3);       // Configures P0.3 as output pin for LED

    IOSET0 = 1<<3;          // Turns OFF the active-low LED initially

    GetRTCDate(&date,&month,&year); // Reads date, month and year from RTC

    DisplayRTCDate(date,month,year); // Displays RTC date on LCD
 
	
 // Infinite loop to continuously monitor RTC and LDR sensor
	while(1)
	{
			 // Checks whether an external interrupt has occurred
		if(flag==1)
		{	
			 Menu();         // Calls the menu function when interrupt occurs
       flag=0;         // Clears the interrupt flag after menu execution
		}
		CmdLCD(0x80);      // Moves LCD cursor to first line, position 0

		GetRTCTime(&hour,&min,&sec); // Reads current RTC hours, minutes and seconds

    DisplayRTCTime(hour,min,sec); // Displays current RTC time on LCD


    CmdLCD(0xc0);       // Moves LCD cursor to second line, position 0

    GetRTCDate(&date,&month,&year); // Reads current RTC date

    DisplayRTCDate(date,month,year); // Displays current RTC date on LCD
		
		Read_LDR(&tadc,&tvolt,&tresis,&tlux);// Reads LDR ADC value, voltage, resistance and lux
		
// Converts current RTC time into total minutes
		cur_time=(HOUR * 60) + MIN;
// Converts configured ON time into total minutes
		on_time=(onHH * 60) + onMM;
// Converts configured OFF time into total minutes
		off_time=(offHH * 60) + offMM;
 // Checks whether ON time is earlier than OFF time		 
	 if(on_time<off_time)
		 {	
				 // Checks whether current time is within ON/OFF range
            // and illumination is below the threshold
			 if((cur_time>=on_time && cur_time<off_time)&& (tlux<THRESHOLD))
		 	{
           IOCLR0=1<<3;  // Turns ON active-low LED by clearing P0.3

           CmdLCD(GOTO_LINE1_POS0+10); // Moves cursor to display LED status
           StrLCD("      ");           // Clears previous status message

           CmdLCD(GOTO_LINE1_POS0+10);
           StrLCD("ON");               // Displays LED ON status
			}
			else{
				IOSET0=1<<3;  // Turns OFF active-low LED by setting P0.3
				CmdLCD(GOTO_LINE1_POS0+10);// Moves cursor to display LED status
				StrLCD("      ");           // Clears previous status message
				CmdLCD(GOTO_LINE1_POS0+10);// Moves cursor to display LED status
				StrLCD("Off");             // Displays LED OFF status
			}
		}
		  // Checks whether ON time is later than OFF time
        // This condition handles an ON period crossing midnight
		else if(on_time > off_time)
		{	
			 // Checks whether current time is after ON time
            // or before OFF time, and illumination is below threshold
			if(((cur_time>=on_time)||(cur_time<off_time))&& (tlux<THRESHOLD))
			{
				IOCLR0=1<<3;  // Turns ON active-low LED
				CmdLCD(GOTO_LINE1_POS0+10);// Moves cursor to display LED status
				StrLCD("      ");          // Clears previous status message
				CmdLCD(GOTO_LINE1_POS0+10);// Moves cursor to display LED status
				StrLCD("ON");              // Displays LED ON status
			}
			else
			{
				IOSET0=1<<3;  // Turns OFF active-low LED by setting P0.3
				CmdLCD(GOTO_LINE1_POS0+10);// Moves cursor to display LED status
				StrLCD("      ");          // Clears previous status message
				CmdLCD(GOTO_LINE1_POS0+10);// Moves cursor to display LED status
				StrLCD("Off");              // Displays LED OFF status
			}
		}
		// Executes when ON time and OFF time are equal
		else
		{
			IOSET0=1<<3;        // Keeps active-low LED OFF
			CmdLCD(GOTO_LINE1_POS0+10);// Moves cursor to display LED status
			StrLCD("      ");          // Clears previous status message
			CmdLCD(GOTO_LINE1_POS0+10);// Moves cursor to display LED status
			StrLCD("Off");              // Displays LED OFF status
		}
	}
}
		
			

