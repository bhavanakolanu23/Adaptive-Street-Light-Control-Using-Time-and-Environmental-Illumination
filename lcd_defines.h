// LCD Command Definitions

#define CLEAR               0X01  // Clears the LCD display and moves cursor to home position

#define RET_HOME            0X02  // Returns cursor to the home position

#define SHT_CUR_RIGHT       0X06  // Shifts cursor position to the right after writing data

#define SHT_CUR_LEFT        0X07  // Shifts cursor position to the left after writing data

#define DISP_OFF            0X08  // Turns OFF the LCD display

#define DISP_ON_CUR_OFF     0X0C  // Turns ON display and hides cursor

#define DISP_ON_CUR_ON      0X0E  // Turns ON display and shows cursor

#define DISP_ON_CUR_BLK     0X0F  // Turns ON display with blinking cursor


// LCD Display Shift Commands

#define SHT_DISP_LEFT       0X10  // Shifts the entire LCD display to the left

#define SHT_DISP_RIGHT      0X14  // Shifts the entire LCD display to the right


// LCD Interface Mode Configuration

#define BIT4_1LINE          0X20  // Configures LCD in 4-bit mode with one display line

#define BIT8_1LINE          0X30  // Configures LCD in 8-bit mode with one display line

#define BIT4_2LINE          0X28  // Configures LCD in 4-bit mode with two display lines

#define BIT8_2LINE          0X38  // Configures LCD in 8-bit mode with two display lines


// LCD Cursor Position Commands

#define GOTO_LINE1_POS0     0X80  // Moves cursor to first line, position 0

#define GOTO_LINE2_POS0     0XC0  // Moves cursor to second line, position 0

#define GOTO_LINE3_POS0     0X94  // Moves cursor to third line, position 0

#define GOTO_LINE4_POS0     0XD4  // Moves cursor to fourth line, position 0


// LCD Custom Character Generation

#define CGRAM               0X40  // Sets the CGRAM address for creating custom characters


// LCD Pin Configuration

#define LCD_DATA            16    // Defines the starting GPIO pin for LCD data lines

#define LCD_RS              15    // Defines the GPIO pin connected to Register Select

#define LCD_RW              13    // Defines the GPIO pin connected to Read/Write

#define LCD_EN              14    // Defines the GPIO pin connected to Enable
