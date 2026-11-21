#include <LPC214X.h>       // Includes LPC214x microcontroller register definitions
#include "rtc.h"           // Includes RTC function declarations
#include "rtc_defines.h"   // Includes RTC-related macros and register definitions

//include LCD header files
#include "lcd.h"           // Includes LCD function declarations
#include "lcd_defines.h"   // Includes LCD commands and definitions


#include "types.h"        // Includes user-defined data types
// Define microcontroller selection
#define LPC2129 0
#define LPC2148 1
#define CPU 1             // Selects LPC2148 as the target microcontroller

// Array to hold names of days of the week
char week[][4]={"SUN","MON","TUE","WED","THU","FRI","SAT"};
// Enumeration to assign numerical values to days of the week
enum days{SUN,MON,TUE,WED,THU,FRI,SAT};

/*
Initialize the Real-Time Clock (RTC)
This function disables the RTC, sets the prescaler values, 
and then enables the RTC.
*/
void RTC_Init(void)
{
	// Disable and reset the RTC
	CCR =RTC_RESET;

	#if CPU==LPC2129
	// Set prescaler integer and fractional parts
	PREINT=PREINT_VAL;
	PREFRAC=PREFRAC_VAL;
	// Enable the RTC
	CCR=RTC_ENABLE;

	#elif CPU==LPC2148
	// Enable the RTC with external clock source
	CCR=RTC_ENABLE |CLKSRC;

	#endif
}
/*
Set the RTC time
Hour to set (0-23)
Minute to set (0-59)
Second to set (0-59)
*/
void SetRTCTime(u32 hour,u32 min,u32 sec)
{
	 HOUR = hour;           // Loads the hour value into RTC hour register
    MIN = min;             // Loads the minute value into RTC minute register
    SEC = sec;             // Loads the second value into RTC second register
}
/*
Get the current RTC time
hour Pointer to store the current hour
minute Pointer to store the current minute
second Pointer to store the current second
*/
void GetRTCTime(u32 *hour,u32 *min,u32 *sec)
{
	*hour=HOUR;            // Reads RTC hour register and stores it in the variable
    *min=MIN;              // Reads RTC minute register and stores it in the variable
    *sec=SEC;              // Reads RTC second register and stores it in the variable
}
/*
Display the RTC time on LCD
hour value (0-23)
minute value (0-59)
second value (0-59) seperated by ':'
*/
void DisplayRTCTime(u32 hour,u32 min,u32 sec)
{
	CmdLCD(GOTO_LINE1_POS0); // Moves LCD cursor to first line, position 0

    CharLCD((hour/10)+48);   // Displays tens digit of hour
    CharLCD((hour%10)+48);   // Displays units digit of hour

    CharLCD(':');            // Displays colon separator

    CharLCD((min/10)+48);    // Displays tens digit of minute
    CharLCD((min%10)+48);    // Displays units digit of minute

    CharLCD(':');            // Displays colon separator

    CharLCD((sec/10)+48);    // Displays tens digit of second
    CharLCD((sec%10)+48);    // Displays units digit of second
}
/*
Set the RTC date
day of month to set (1-31)
month to set (1-12)
year to set (four digits)
*/
void SetRTCDate(u32 date,u32 month,u32 year)
{
	  DOM = date;              // Loads date into RTC day-of-month register
    MONTH = month;           // Loads month into RTC month register
    YEAR = year;             // Loads year into RTC year register
}
/*
Get the current RTC date
day Pointer to store the current date (1-31)
month Pointer to store the current month (1-12)
year Pointer to store the current year (four digits)
*/
void GetRTCDate(u32 *date,u32 *month,u32 *year)
{
	  *date=DOM;               // Reads date from RTC day-of-month register
    *month=MONTH;             // Reads month from RTC month register
    *year=YEAR;               // Reads year from RTC year register
}
/*
Display the RTC date on LCD
Day of month (1-31)
Month (1-12)
Year (four digits) and seperated by '/'
*/
void DisplayRTCDate(u32 date,u32 month,u32 year)
{
	  CmdLCD(GOTO_LINE2_POS0);  // Moves LCD cursor to second line, position 0

    CharLCD((date/10)+48);   // Displays tens digit of date
    CharLCD((date%10)+48);   // Displays units digit of date

    CharLCD('/');            // Displays date separator

    CharLCD((month/10)+48);  // Displays tens digit of month
    CharLCD((month%10)+48);  // Displays units digit of month

    CharLCD('/');            // Displays date separator

    U32LCD(year);            // Displays the complete year on LCD
}
/*
Get the current day of the week
dow Pointer to store Day of Week (0=Sunday, ..., 6=Saturday)
*/
void GetRTCDay(u32 *day)
{
	*day =DOW;             // Reads day-of-week value from RTC register
}
/*
Set the day of the week in RTC
Day of Week to set (0=Sunday, ..., 6=Saturday)
*/
void SetRTCDay(u32 day)
{
	DOW = day;              // Loads the day value into RTC day-of-week register
}
/*
Display the current day of the week on LCD
dow (Day of Week) (0=Sunday, ..., 6=Saturday)
*/
void DisplayRTCDay(u32 day)
{
	CmdLCD(GOTO_LINE1_POS0+11); // Moves cursor to first line, position 11

   StrLCD((s8 *)week[day]);    // Displays the corresponding day name from the array
}


