#include <lpc21xx.h>       // Includes LPC21xx microcontroller register definitions
#include "adc_defines.h"   // Includes ADC-related macros and definitions
#include <math.h>          // Includes mathematical functions like pow()
#include "lcd.h"           // Includes LCD function declarations
#include "lcd_defines.h"   // Includes LCD commands and definitions
#include "types.h"         // Includes user-defined data types
#include "adc.h"           // Includes ADC function declarations

// Function to read LDR sensor values and calculate voltage, resistance and illumination
void Read_LDR(u32 *tadc,f32 *tvolt,f32 *tresis,f32 *tlux)
{
	static s32 opened;     // Static variable to initialize ADC only once

    u16 dval;              // Stores the digital value obtained from ADC
    f32 eAR;               // Stores the equivalent analog voltage value

    if(opened==0)          // Checks whether ADC is initialized or not
    {
        Init_ADC();        // Initializes the ADC module
        opened=1;          // Indicates that ADC initialization is completed
    }

    Read_ADC(1,&dval,&eAR); // Reads ADC channel 1 and gets digital value and voltage

    *tadc=dval;            // Stores ADC digital value using pointer
    *tvolt=eAR;            // Stores the measured voltage using pointer

    // Calculates LDR resistance using the voltage divider formula
    *tresis = ((10000.0f*eAR)/(3.3f-eAR));

    // Calculates light intensity in lux using the LDR resistance
    *tlux=10.0f*(pow((12000.0f/ *tresis),(1.0f/0.7f)));
	
	          

}
