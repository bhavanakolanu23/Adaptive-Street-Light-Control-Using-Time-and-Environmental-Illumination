#include <LPC214X.h>				// Includes LPC214x microcontroller register definitions

#include "intrp_defines.h"	// Includes interrupt-related macros and definitions
#include "lcd.h"						// Includes LCD function declarations
#include "lcd_defines.h"		// Includes LCD-related macros and definitions

#include "kpm.h"           // Includes keypad function declarations
#include "kpm_defines.h"   // Includes keypad-related macros and definitions

#include "rtc.h"           // Includes RTC function declarations
#include "rtc_defines.h"   // Includes RTC-related macros and definitions

#include "delay.h"         // Includes delay function declarations

#include "types.h"					// Includes user-defined data types

// External global variables used to store ON and OFF time
extern u32 onHH,onMM;
extern u32 offHH,offMM;
extern  u32 onSS,offSS;
// External global variables used to store RTC time
extern u32 hour,min,sec;
// External global variables used to store RTC date
extern u32 date,month,year;

u8 Keyv; // Variable used to store the keypad input

// Function to display the main menu and select an option
void Menu()
{
	u32 num; // Stores the selected menu option
	while(1)
	{
		CmdLCD(CLEAR);              // Clears the LCD
		CmdLCD(GOTO_LINE1_POS0);    // Moves cursor to first line
		StrLCD("1.stime 2.sRTC");   // Displays time setting options
		CmdLCD(GOTO_LINE2_POS0);    // Moves cursor to second line
		StrLCD("3.sdate 4.exit");   // Displays date and exit options
		num=KeyScan()-48;           // Reads the key and converts ASCII to integer
		delay_ms(100);              // Provides a small delay for key detection	
		while(ColScan()==0);        // Waits until the pressed key is released
		switch(num)
		{
			case 1:stime();        // Calls the function to set ON/OFF time
					break;
			case 2:sRTC();         // Calls the function to set RTC time
					break;
			case 3:sdate();        // Calls the function to set RTC date
					break;
			case 4: CmdLCD(0x01);   // Clears the LCD
					return;         // Exits the menu function
			default:StrLCD("invalid"); // Displays an invalid option message				   
		}	
	}					 
}
// Function to select ON time or OFF time settings
void stime()
{
	u32 num; // Stores the selected option

	while(1)
	{
		CmdLCD(CLEAR);              // Clears the LCD
    StrLCD("1.ontime");         // Displays ON time option
    CmdLCD(GOTO_LINE2_POS0);    // Moves cursor to second line
    StrLCD("2.offtime");        // Displays OFF time option
		num=0;
		num=KeyScan()-48;           // Reads keypad input and converts ASCII to integer
    delay_ms(100);              // Provides keypad debounce delay
		while(ColScan()==0);        // Waits until the key is released
	
		switch(num)
		{
			case 1:Ontime(&onHH,&onMM,&onSS);		 // Passes ON time variable addresses
					break;
			case 2:OffTime(&offHH,&offMM,&offSS);	 // Passes OFF time variable addresses
					break;
			default:CmdLCD(0x01);	  // Clears the LCD
					return;       // Returns to the main menu
		}
	}
}
// Function to configure ON time using pointers
void Ontime(u32 *onHH,u32 *onMM, u32 *onSS)
{	
	u32 num;// Stores the selected option 
	while(1)
	{
		CmdLCD(CLEAR);              // Clears the LCD
    StrLCD("1.HH 2.MM 3.SS");   // Displays hour, minute and second options
		num=0;
		num=KeyScan()-48;           // Reads keypad input and converts ASCII to integer
    delay_ms(100);              // Provides keypad debounce delay
		while(ColScan()==0);        // Waits until the key is released
		switch(num)
		{
			case 1: CmdLCD(CLEAR);  // Clears the LCD
			StrLCD("enter onHH"); // Asks the user to enter ON hour
      num=ReadNum();  // Reads the hour value from keypad

       if(num<1 || num>24) // Checks whether hour is within valid range
					{
						CmdLCD(CLEAR);  // Clears the LCD
						StrLCD("invalid"); // Displays an error message
						delay_s(1);         // Waits for one second
						break;
					}
					*onHH=num;      // Updates the ON hour using pointer
						break;
					
			case 2:	CmdLCD(CLEAR);  // Clears the LCD
					StrLCD("enter onMM"); // Asks the user to enter ON minutes
					Keyv=0;
					num=ReadNum();  // Reads the minute value from keypad
					if(num<1 || num>60)// Checks minute range
					{
						CmdLCD(CLEAR);  // Clears the LCD
						StrLCD("invalid"); // Displays an error message
						delay_s(1);         // Waits for one second
						break;
					}
					*onMM=num;     // Updates the ON minute using pointer

					break;
			case 3:	CmdLCD(CLEAR); // Clears the LCD
					StrLCD("enter onSS"); // Asks the user to enter ON seconds
					num=ReadNum(); // Reads the second value from keypad
					if(num<1 || num>60) // Checks second range
					{
						CmdLCD(CLEAR);  // Clears the LCD
						StrLCD("invalid"); // Displays an error message
						delay_s(1);         // Waits for one second
						break;
					}
					*onSS=num;      // Updates the ON seconds using pointer
					break;
			default:CmdLCD(0x01); // Clears the LCD
			return;        // Returns to the previous menu

		}
	}
}
// Function to configure OFF time using pointers
void OffTime(u32 *offHH,u32 *offMM, u32 *offSS)
{	
	u32 num; // Stores the selected option or entered time value

	while(1)
	{
		CmdLCD(CLEAR); // Clears the LCD
		StrLCD("1.HH 2.MM 3.SS");  // Displays time setting options
		num=0;
		num=KeyScan()-48;           // Reads keypad input and converts ASCII to integer
		delay_ms(100);              // Provides debounce delay	
		while(ColScan()==0);        // Waits until the key is released

		switch(num)
		{
			case 1:	CmdLCD(CLEAR);// Clears the LCD
					StrLCD("enter offHH"); // Asks for OFF hour
					num=ReadNum();					  // Reads OFF hour
					if(num<1 || num>24)			// Validates hour
					{
						CmdLCD(CLEAR);  // Clears the LCD
						StrLCD("invalid"); // Displays an error message
						delay_s(1);         // Waits for one second
						break;
					}
					*offHH=num;     // Updates OFF hour using pointer
					break;
			case 2:	CmdLCD(CLEAR);// Clears the LCD
					StrLCD("enter offMM"); // Asks for OFF minutes
					num=ReadNum(); // Reads OFF minutes
					if(num<1 || num>60) // Validates minutes
					{
						CmdLCD(CLEAR);  // Clears the LCD
						StrLCD("invalid"); // Displays an error message
						delay_s(1);         // Waits for one second
						break;
					}
					*offMM=num;     // Updates OFF minutes using pointer
					break;
					
			case 3:	CmdLCD(CLEAR);// Clears the LCD
					StrLCD("enter offSS"); // Asks for OFF seconds
					
					num=ReadNum();  // Reads OFF seconds
					if(num<1 || num>60) // Validates seconds
					{
						CmdLCD(CLEAR);  // Clears the LCD
						StrLCD("invalid"); // Displays an error message
						delay_s(1);         // Waits for one second
						break;
					}
					*offSS=num;     // Updates OFF seconds using pointer
					
			default: CmdLCD(0x01);// Clears the LCD
					return;       // Returns to the previous menu
		}
	}
}
// Function to configure RTC time
void sRTC()
{
	u32 num; // Stores the selected option
	while(1)
		{
		CmdLCD(CLEAR);// Clears the LCD
		StrLCD("1.HH 2.MM 3.SS");   // Displays RTC time options
		num=0;
		num=KeyScan()-48;          // Reads keypad input
		delay_ms(100);              // Provides debounce delay	
		while(ColScan()==0);       // Waits until the key is released
		switch(num)
		{
			case 1: CmdLCD(CLEAR);// Clears the LCD
					StrLCD("enter rHH"); // Asks for RTC hour
					Keyv=0;
					Keyv=ReadNum(); // Reads hour from keypad
					U32LCD(Keyv);  // Displays entered hour on LCD
					if(Keyv<1 || Keyv>24) // Validates hour
					{
						CmdLCD(CLEAR);  // Clears the LCD
						StrLCD("invalid"); // Displays an error message
						delay_s(1);         // Waits for one second
						break;
					}
					hour=Keyv;      // Updates RTC hour
					break;
			case 2:CmdLCD(CLEAR);// Clears the LCD
					StrLCD("enter rMM"); // Asks for RTC minutes
					Keyv=0;
					Keyv=ReadNum(); // Reads minutes
					U32LCD(Keyv);  // Displays entered minutes

					if(Keyv<1 || Keyv>60) // Validates minutes
					{
						CmdLCD(CLEAR);  // Clears the LCD
						StrLCD("invalid"); // Displays an error message
						delay_s(1);         // Waits for one second
						break;
					}
					min=Keyv;       // Updates RTC minutes
					break;	
			case 3: CmdLCD(CLEAR);// Clears the LCD
					StrLCD("enter rSS"); // Asks for RTC second
					Keyv=0;
					Keyv=ReadNum(); // Reads seconds
					U32LCD(Keyv);  // Displays entered seconds

					if(Keyv<1 || Keyv>60) // Validates seconds
					{
						CmdLCD(CLEAR);  // Clears the LCD
						StrLCD("invalid"); // Displays an error message
						delay_s(1);         // Waits for one second
						break;
					}
					sec=Keyv;       // Updates RTC seconds
					break;
					
			default:CmdLCD(0x01);// Clears the LCD
					return;       // Returns to the previous menu
		}
		SetRTCTime(hour,min,sec);    // Updates RTC registers with entered time
	}
}
// Function to configure RTC date
void sdate()
{
	u32 num; // Stores the selected option

	while(1)
	{
		CmdLCD(CLEAR);// Clears the LCD
		StrLCD("1.dt 2.mon 3.yr"); // Displays date, month and year options

   		num=0;
		num=KeyScan()-48;          // Reads keypad input
		delay_ms(100);              // Provides debounce delay	
		while(ColScan()==0);       // Waits until the key is released
		switch(num)
		{
		case 1: CmdLCD(CLEAR);// Clears the LCD
				StrLCD("enter date");
				Keyv=0;
				Keyv=ReadNum(); // Reads date from keypad
				U32LCD(Keyv);   // Displays entered date
				date=Keyv;      // Updates date variable
				break;
		case 2:CmdLCD(CLEAR);// Clears the LCD
				StrLCD("enter month"); // Asks for month
				Keyv=0;
				Keyv=ReadNum(); // Reads month
				U32LCD(Keyv);   // Displays entered month
				month=Keyv;    // Updates month variable
				break;
		case 3: CmdLCD(CLEAR);// Clears the LCD
				StrLCD("enter year");// Asks for year
				Keyv=0;
				Keyv=ReadNum(); // Reads year
				U32LCD(Keyv);   // Displays entered year
				year=Keyv;     // Updates year variable
				break;
		default:CmdLCD(0x01);// Clears the LCD
				return;       // Returns to the previous menu
		}	 
	
	SetRTCDate(date,month,year);
	}
}
