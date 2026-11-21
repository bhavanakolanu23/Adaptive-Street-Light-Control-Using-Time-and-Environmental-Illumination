#include <LPC21XX.h>       // Header file for LPC2129/LPC2148 microcontroller registers
#include "types.h"         // User-defined data types like u8, u32, s32, f32
#include "defines.h"       // General macros and bit manipulation macros
#include "lcd_defines.h"   // LCD pin connections and command definitions
#include "delay.h"         // Delay function declarations
#include "lcd.h"           // LCD function declarations
// Function to send one byte of data or command to the LCD
void WriteLCD(u8 dat)
{	
	  // Place the 8-bit data on LCD data pins D0 to D7
    WRITEBYTE(IOPIN0,LCD_DATA,dat);

    // Select write operation by making RW pin LOW
    IOCLR0=1<<LCD_RW;

    // Generate a HIGH-to-LOW pulse on Enable pin to latch the data
    IOSET0=1<<LCD_EN;
    delay_us(100);          // Keep Enable HIGH for a short time
    IOCLR0=1<<LCD_EN;       // Make Enable LOW to complete the pulse

    delay_ms(2);            // Wait for LCD to complete the operation
}
// Function to send a command to the LCD
void CmdLCD(u8 cmd)
{
	  // Select Command Register by making RS pin LOW
    IOCLR0=1<<LCD_RS;

    // Send the command byte to the LCD
    WriteLCD(cmd);
}
// Function to display a single character on the LCD
void CharLCD(u8 ascii)
{
	  // Select Data Register by making RS pin HIGH
    IOSET0=1<<LCD_RS;

    // Send the character to the LCD for display
    WriteLCD(ascii);
}
// Function to initialize the LCD
void InitLCD(void)
{
		 // Configure LCD data pins D0-D7, RS, RW and EN as GPIO outputs
	
    // WRITEBYTE(IODIR0,LCD_DATA,0xFF);
    // SETBIT(IODIR0,LCD_RS);
    // SETBIT(IODIR0,LCD_RW);
    // SETBIT(IODIR0,LCD_EN);

    // Set all LCD-connected pins as output pins
    IODIR0=(0XFF<<LCD_DATA)|(1<<LCD_RS)|(1<<LCD_RW)|(1<<LCD_EN);

    // Wait for LCD power supply to stabilize
    delay_ms(15);

    // Send the initial 8-bit interface command
    CmdLCD(0x30);
    delay_ms(4);

    // Send the 8-bit interface command again
    delay_us(100);
    CmdLCD(0x30);

    // Send the 8-bit interface command for the third time
    delay_us(100);
    CmdLCD(0x30);

    // Configure LCD for 8-bit mode and 2 display lines
    CmdLCD(BIT8_2LINE);

    // Turn ON the display and enable cursor blinking
    CmdLCD(DISP_ON_CUR_BLK);

    // Clear all characters from the LCD display
    CmdLCD(CLEAR);

    // Set cursor movement direction to increment after writing data
    CmdLCD(SHT_CUR_RIGHT);
}

// Function to display a string on the LCD
void StrLCD(s8 *s)
{
    // Continue until the null character '\0' is encountered
    while(*s)
    {
        // Display the current character and move to the next character
        CharLCD(*s++);
    }
}
// Function to display an unsigned 32-bit integer on the LCD
void U32LCD(u32 n)
{
    u8 a[10];               // Array to store individual digits
    s32 i=0;                // Index for the digit array

    // Check if the number is zero
    if(n==0)
    {
        CharLCD('0');       // Directly display zero
    }
    else
    {
        // Extract digits one by one from the number
        while(n)
        {
            a[i]=n%10+48;   // Get last digit and convert it to ASCII
            n/=10;          // Remove the last digit
            i++;            // Move to the next array position
        }

        // Display digits in reverse order to get the correct number
        for(--i;i>=0;i--)
        {
            CharLCD(a[i]);
        }
    }
}
// Function to display a signed 32-bit integer on the LCD
void S32LCD(s32 n)
{
    // Check whether the number is negative
    if(n<0)
    {
        CharLCD('-');       // Display minus sign
        n=-n;               // Convert the number to positive
    }

    // Display the number using the unsigned integer function
    U32LCD(n);
}
// Function to display a floating-point number on the LCD
// fn = floating-point number, m = number of digits after decimal point
void F32LCD(f32 fn,u8 m)
{
    u32 n,i;

    // Check whether the floating-point number is negative
    if(fn<0.0)
    {
        CharLCD('-');       // Display minus sign
        fn=-fn;             // Convert the number to positive
    }

    // Extract the integer part of the floating-point number
    n=fn;

    // Display the integer part
    U32LCD(n);

    // Display the decimal point
    CharLCD('.');

    // Extract and display the required digits after decimal point
    for(i=0;i<m;i++)
    {
        fn=(fn-n)*10;       // Remove integer part and shift next decimal digit
        n=fn;               // Store the next decimal digit
        CharLCD(n+48);      // Convert digit to ASCII and display it
    }
}

// Function to write custom character data into LCD CGRAM
void BuildCGRAM(u8 *p,u8 nBytes)
{
    u32 i;

    // Select CGRAM address to store custom character pattern
    CmdLCD(CGRAM);

    // Select Data Register to write character pattern bytes
    IOSET0=1<<LCD_RS;

    // Select write operation
    IOCLR0=1<<LCD_RW;

    // Write each byte of the custom character pattern into CGRAM
    for(i=0;i<nBytes;i++)
    {
        WriteLCD(p[i]);
    }

    // Return to DDRAM and set cursor to the first position of line 1
    CmdLCD(GOTO_LINE1_POS0);
}
