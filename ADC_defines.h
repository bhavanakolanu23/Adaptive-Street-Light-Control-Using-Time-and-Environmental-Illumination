// Define the external crystal frequency as 12 MHz
#define FOSC 12000000

// Define the CPU clock frequency
// PLL multiplies the crystal frequency by 5
#define CCLK (FOSC * 5)

// Define the peripheral clock frequency
// Peripheral clock is one-fourth of the CPU clock
#define PCLK (CCLK / 4)

// Define the ADC clock frequency as 3 MHz
#define ADC_CLK 3000000


// Definitions for ADCR (ADC Control Register)

// Bit position used to configure the ADC clock divider
#define CLKDIV_BITS 8

// Bit position of PDN (Power Down) bit
// Setting this bit to 1 powers ON the ADC
#define PDN_BIT 21

// Bit position of START bits
// Used to select when ADC conversion should start
#define ADC_CONV_START_BIT 24

// Calculate the ADC clock divider value
// ADC clock = PCLK / (CLKDIV + 1)
#define CLKDIV_VAL ((PCLK / ADC_CLK) - 1)


// Definitions for ADDR (ADC Data Register)

// Starting bit position of the digital conversion result
#define DIGITAL_DATA_BITS 6

// Bit position of DONE flag
// When DONE becomes 1, ADC conversion is completed
#define DONE_BIT 31


// Pin function selection definitions for ADC input pins

// Configure the corresponding pin as ADC input AIN0
#define AIN0_FUNC 0X00400000

// Configure the corresponding pin as ADC input AIN1
#define AIN1_FUNC 0x01000000

// Configure the corresponding pin as ADC input AIN2
#define AIN2_FUNC 0x04000000

// Configure the corresponding pin as ADC input AIN3
#define AIN3_FUNC 0X10000000


// ADC channel number used for the LDR sensor
#define AIN_CHNO 0
