#include "types.h"          // Includes user-defined data types

void RTC_Init(void);        // Initializes the Real-Time Clock (RTC)

void GetRTCTime(u32 *,u32 *, u32 *); // Reads hours, minutes and seconds from RTC
void SetRTCTime(u32,u32,u32);         // Sets hours, minutes and seconds in RTC
void DisplayRTCTime(u32,u32,u32);     // Displays RTC time on LCD

void GetRTCDate(u32 *,u32 *,u32 *);   // Reads date, month and year from RTC
void SetRTCDate(u32,u32,u32);         // Sets date, month and year in RTC
void DisplayRTCDate(u32,u32,u32);     // Displays RTC date on LCD

void GetRTCDay(u32 *);                // Reads the day of the week from RTC
void SetRTCDay(u32);                  // Sets the day of the week in RTC
void DisplayRTCDay(u32);               // Displays the day of the week on LCD
