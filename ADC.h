#include "types.h"       // Includes user-defined data types like u8, u16, u32 and f32

// Function to initialize the ADC peripheral
void Init_ADC(void);

// Function to read the ADC value from the selected channel
// chNo - ADC channel number
// dVal - Pointer to store the digital ADC value
// eAr  - Pointer to store the equivalent analog voltage
void Read_ADC(u8 chNo, u16 *dVal, f32 *eAr);

// Function to read LDR sensor values
// tadc   - Pointer to store the digital ADC value
// tvolt  - Pointer to store the calculated voltage
// tresis - Pointer to store the calculated resistance
// tlux   - Pointer to store the calculated light intensity in lux
void Read_LDR(u32 *tadc, f32 *tvolt, f32 *tresis, f32 *tlux);

// Function to read LM35 temperature sensor values
// tDegc - Pointer to store temperature in degrees Celsius
// tDeg  - Pointer to store the other temperature value/unit as implemented
void Read_lm35(u8 *tDegc, u8 *tDeg);
