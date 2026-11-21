#include "types.h"          // Includes user-defined data types
#include "delay.h"					// Includes delay function declarations
// Function to generate delay in microseconds
void delay_us(u32 dlyUs)
{
    // Multiplies the required delay by the loop count
    // Executes the loop until the counter reaches zero
    for(dlyUs *= 12; dlyUs > 0; dlyUs--);
}


// Function to generate delay in milliseconds
void delay_ms(u32 dlyMs)
{
    // Multiplies milliseconds by 12000 to generate the required delay
    // Executes the loop until the counter reaches zero
    for(dlyMs *= 12000; dlyMs > 0; dlyMs--);
}


// Function to generate delay in seconds
void delay_s(u32 dlyS)
{
    // Multiplies seconds by 12000000 to generate the required delay
    // Executes the loop until the counter reaches zero
    for(dlyS *= 12000000; dlyS > 0; dlyS--);
}
