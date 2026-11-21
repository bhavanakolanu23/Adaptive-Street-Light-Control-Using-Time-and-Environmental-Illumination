#include "types.h"          // Includes user-defined data types

void WriteLCD(u8 data);     // Sends data/command to the LCD

void CmdLCD(u8 cmd);        // Sends a command instruction to the LCD

void CharLCD(u8 ascii);     // Displays a single character on the LCD

void InitLCD(void);         // Initializes the LCD in the required operating mode

void StrLCD(s8 *);          // Displays a string of characters on the LCD

void U32LCD(u32);           // Displays an unsigned 32-bit integer on the LCD

void S32LCD(s32);           // Displays a signed 32-bit integer on the LCD

void F32LCD(f32,u8);        // Displays a floating-point number with specified precision

void BuildCGRAM(u8 *,u8);   // Creates a custom character and stores its pattern in CGRAM
