#include <LPC21xx.h>       // Header file for LPC21xx microcontroller registers
#include "types.h"         // User-defined data types
#include "defines.h"       // General macros and bit manipulation macros
#include "kpm.h"            // Keypad function declarations
#include "kpm_defines.h"    // Keypad row and column pin definitions
#include "lcd.h"            // LCD function declarations
#include "delay.h"          // Delay function declarations
#include "lcd_defines.h"    // LCD command definitions

// 4x4 keypad lookup table
// Each row represents a keypad row and each column represents a keypad column
u8 kpmLUT[4][4]={
					{'1','2','3','A'},{'4','5','6','B'},
					{'7','8','9','C'},{'*','0','#','D'}	};

// Function to initialize the keypad					
void Init_kpm(void)
{ 
		// Configure four row pins (P1.16 to P1.19) as output pins
 		WRITENIBBLE(IODIR1,ROW0,15);
}

// Function to check whether any keypad column is pressed
u8 ColScan(void)
{
	u8 t;
	// Read four column pins (P1.20 to P1.23)
    // If the value is less than 15, at least one key is pressed
    // Return 0 if a key is pressed, otherwise return 1
	t=(READNIBBLE(IOPIN1,COL0)<15)?0:1;
	return t;
}

// Function to identify which row contains the pressed key
u8 RowCheck(void)
{
	u8 r;
	 // Scan all four rows one by one
	for(r=0;r<4;r++)
	{
		// Make the selected row LOW and keep the remaining rows HIGH
		WRITENIBBLE(IOPIN1,ROW0,~(1<<r));
		// Check whether any column becomes LOW
		if(!ColScan())
		break;         // Key is found in this row
	}
	 // Make all four rows LOW after scanning
	WRITENIBBLE(IOPIN1,ROW0,0);
	return r;              // Return the detected row number
}

// Function to identify which column contains the pressed key
u8 ColCheck(void)
{
	u8 c;
	 // Check each column one by one
	for(c=0;c<4;c++)
	{
		  // Check whether the current column pin is LOW
		if(READBIT(IOPIN1,COL0 + c) == 0)
		break;         // Key is found in this column
	}
	return c;             // Return the detected column number
}

// Function to scan the keypad and identify the pressed key
u8 KeyScan(void)
{
	u8 r,c,KeyV;
	// Wait until a key is pressed
	while(ColScan());
	r=RowCheck();// Identify the row of the pressed key
	c=ColCheck();// Identify the column of the pressed key
	KeyV=kpmLUT[r][c];// Get the actual key value from the lookup table
	return KeyV;           // Return the pressed key
}

// Function to read a multi-digit number from the keypad
u32 ReadNum(void)
{
	u8 KeyV;
	u32 sum=0;             // Stores the number entered by the user
	CmdLCD(GOTO_LINE2_POS0);// Move LCD cursor to the beginning of the second line
	while(1)
	{
		 // Scan the keypad and get the pressed key
		KeyV=KeyScan();
		delay_ms(100);// Small delay for debouncing
		while(ColScan()==0);// Wait until the pressed key is released
		if((KeyV>='0')&&(KeyV<='9'))// Check whether the pressed key is a digit from 0 to 9
		{
			sum=(sum*10)+(KeyV-'0'); // Append the new digit to the existing number
			CharLCD(KeyV); // Display the entered digit on LCD
            
		}
		// B key is used for backspace
		else if(KeyV=='B')
		{
			sum/=10;// Remove the last digit from the number
			CmdLCD(0x10);// Move cursor one position to the left
			CharLCD(' '); // Erase the previous character
			CmdLCD(0x10); // Move cursor one position to the left again
		}
		// C key is used to confirm the entered number
		else if(KeyV=='C')
		{
			break;         // Exit the loop
		}
	}
	return sum;            // Return the final entered number

}
// Function to read a number and also return the last pressed key
// num stores the entered number
// lastkey stores the most recently pressed keypad key
void ReadNum2(u32 *num,u8 *lastkey)
{

	CmdLCD(GOTO_LINE2_POS0); // Move LCD cursor to the beginning of the second line
	while(1)
	{
		
	*lastkey=KeyScan();// Scan keypad and store the pressed key through the pointer
	delay_ms(100);        // Small delay for debouncing

	while(ColScan()==0); // Wait until the pressed key is released
	if((*lastkey>='0')&&(*lastkey<='9')) // Check whether the pressed key is a digit
	{
		*num=(*num * 10)+(*lastkey-'0');// Append the entered digit to the number
		CharLCD(*lastkey); // Display the pressed digit on LCD
	}				
		// C key is used to confirm the entered number
	else if(*lastkey=='C')
	{
		break;        // Exit the loop
	}
	// B key is used for backspace
	if(*lastkey=='B')
	{	
		*num=*num/10;// Remove the last digit
		CmdLCD(0x10);// Move cursor one position to the left
		CharLCD(' ');// Erase the previous character
		CmdLCD(0x10);// Move cursor one position to the left again
	} 
	}
}

