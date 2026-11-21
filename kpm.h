#include "types.h"       // Includes user-defined data types

void Init_kpm(void);    // Initializes the keypad module

u8 ColScan(void);       // Scans the columns of the keypad to detect key press

u8 RowCheck(void);      // Checks which row is selected or pressed

u8 ColCheck(void);      // Checks which column is selected or pressed

u8 KeyScan(void);       // Scans the keypad and returns the pressed key value

u32 ReadNum(void);      // Reads a numeric value from the keypad

void ReadNum2(u32 *,u8 *); // Reads a number from the keypad and stores the number and digit count using pointers

