#include "types.h"              // Includes user-defined data types

#define EINT0_PIN_FUNC  3        // Defines function selection value for EINT0 pin
#define EINT_CH_NO      14       // Defines VIC interrupt channel number for EINT0
#define STATUS_LED      16       // Defines the GPIO pin number connected to status LED

void Init_INT(void);             // Function declaration to initialize External Interrupt 0

void eint0_isr(void)__irq;       // Function declaration for EINT0 Interrupt Service Routine

void Menu(void);                 // Function declaration to display and handle the main menu

void DisplayOnTime(void);        // Function declaration to display the configured ON time

void DisplayOffTime(void);       // Function declaration to display the configured OFF time

void Ontime(u32 *,u32 *,u32 *);  // Function declaration to configure ON hour, minute and second using pointers

void OffTime(u32*,u32 *,u32 *);  // Function declaration to configure OFF hour, minute and second using pointers

void sRTC(void);                 // Function declaration to set RTC time

void stime(void);                // Function declaration to configure ON and OFF time

void sdate(void);                // Function declaration to set RTC date
