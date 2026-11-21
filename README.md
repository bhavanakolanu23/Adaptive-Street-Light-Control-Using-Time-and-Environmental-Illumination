# Adaptive-Street-Light-Control-Using-Time-and-Environmental-Illumination
To implement an intelligent streetlight control system that uses RTC-based  scheduling and environmental illumination sensing, with user-configurable  ON/OFF timings through an interrupt-driven menu system, to reduce energy  consumption and improve operational efficiency. 
Adaptive Street Light Control Using LPC2148
An Embedded C-based adaptive street lighting system that controls a street light using a configurable RTC schedule and ambient illumination measured through an LDR sensor.
Overview
This project uses the ARM7-based LPC2148 microcontroller to automate street light operation. The firmware combines real-time scheduling with ambient light sensing:
- The RTC maintains the current time and date.
- A 4×4 matrix keypad lets the user configure the ON and OFF times.
- An LDR sensor is read through the LPC2148 ADC.
- A 16×2 LCD displays time, date, and light status.
- An external interrupt (EINT0) is used to enter the configuration menu.
The street light is switched ON when the configured time window is active and the measured illumination is below the configured threshold. The LED output in the current firmware is active-low.
Features
- Configurable street light ON and OFF times.
- RTC time and date configuration.
- LDR-based ambient light measurement using ADC.
- Automatic control based on schedule and illumination threshold.
- 16×2 LCD user interface.
- 4×4 matrix keypad input with numeric entry, backspace, and confirmation.
- EINT0-triggered menu access.
- Modular peripheral drivers.
Hardware
Component	Purpose
LPC2148	Main microcontroller
LDR and voltage-divider circuit	Ambient light sensing
16×2 LCD	User interface and status display
4×4 matrix keypad	Time and date configuration
On-chip RTC	Timekeeping
LED / LED driver stage	Street light output indication
Custom PCB	Hardware integration


Hardware note: Add the final schematic and PCB images to the hardware/ directory. Confirm the exact LDR ADC pin and LCD wiring against the physical board before publishing.

Pin Configuration
The following assignments are visible in the current firmware definitions:
Signal	LPC2148 pin	Notes
Keypad Row 0	P1.16	GPIO
Keypad Row 1	P1.17	GPIO
Keypad Row 2	P1.18	GPIO
Keypad Row 3	P1.19	GPIO
Keypad Column 0	P1.20	GPIO
Keypad Column 1	P1.21	GPIO
Keypad Column 2	P1.22	GPIO
Keypad Column 3	P1.23	GPIO
Menu interrupt	P0.1	EINT0
Street light LED	P0.3	Active-low output
LDR	Verify actual ADC input	Confirm channel and pin mux from the final ADC driver and PCB


LCD data and control pins are defined in lcd_defines.h. Refer to the project schematic for the complete connection details.
Active-low LED behavior
- GPIO LOW: LED ON
- GPIO HIGH: LED OFF
System Operation
1. Initialization: Configure GPIO, LCD, keypad, RTC, ADC, and EINT0. Set the LED output to its OFF state.
2. Configuration: Trigger EINT0 to enter the menu. Use the keypad to set the ON time, OFF time, and RTC date/time.
3. Time check: Read the RTC and determine whether the current time is within the configured operating window.
4. Light measurement: Read the LDR through the ADC and calculate the corresponding sensor values.
5. Decision: Turn the LED ON only when the schedule is active and the measured illumination is below THRESHOLD; otherwise keep it OFF.
6. Display: Update the LCD with the current time, date, and light status.
The firmware includes logic for a schedule that crosses midnight (for example, 18:00 to 06:00). Verify this behavior on hardware with the intended time values.
Clock Configuration
The current definitions specify:
Parameter	Value
External crystal (FOSC)	12 MHz
CPU clock (CCLK)	60 MHz
Peripheral clock (PCLK)	15 MHz
ADC clock (ADC_CLK)	3 MHz
ADC divider (CLKDIV_VAL)	4


The divider is calculated as:
CLKDIV_VAL = (PCLK / ADC_CLK) - 1;
Confirm that the PLL and VPB divider are configured consistently with these definitions in the startup/system configuration.
Firmware Modules
Module	Responsibility
main.c	Application flow and street light decision logic
types.h	Project-specific type aliases
defines.h	GPIO bit manipulation macros
lcd.c, lcd.h	LCD driver
lcd_defines.h	LCD commands and pin definitions
kpm.c, kpm.h	4×4 keypad driver
kpm_defines.h	Keypad row and column definitions
ADC.c, ADC.h	ADC initialization and conversion
ADC_defines.h	ADC clock and register bit definitions
RTC.c, RTC.h	RTC initialization and time/date operations
RTC_defines.h	RTC-related definitions
delay.c, delay.h	Software delay routines
intrp.c, intrp.h	External interrupt configuration and ISR


Rename this table to match the exact filenames in the repository.
Build and Flash
This project is intended for an LPC2148 ARM7 development environment.
1. Install Keil µVision and the LPC2148 device support package.
2. Open the project file (.uvproj / .uvprojx, if included).
3. Confirm the target device, oscillator frequency, PLL setup, and peripheral clock divider.
4. Add all required .c files and include paths.
5. Build the project and resolve compiler warnings/errors.
6. Generate the HEX output if required by the programmer.
7. Flash the firmware to the LPC2148 board.
8. Verify keypad input, RTC updates, LDR readings, LCD output, and active-low LED operation.
The repository template does not include a Keil project file or compiled HEX image. Add them only if you intend to distribute them.

Configuration
The illumination threshold is currently defined in the application code:
#define THRESHOLD 20
Calibrate this value using actual ADC/LDR readings on the target hardware. The calculated lux value is an estimate and depends on the LDR characteristics and voltage-divider resistor values.

The ON and OFF times are held in the firmware variables onHH, onMM, offHH, and offMM.
Validation Checklist
- [ ] Confirm the LDR ADC channel matches the actual pin configuration.
- [ ] Confirm LCD data/control wiring against lcd_defines.h.
- [ ] Verify keypad row/column wiring and key mapping.
- [ ] Verify RTC time and date setting and reading.
- [ ] Test a schedule within one day (for example, 18:00–23:00).
- [ ] Test a schedule crossing midnight (for example, 18:00–06:00).
- [ ] Test LED active-low ON/OFF behavior.
- [ ] Calibrate the LDR threshold under bright and dark conditions.
- [ ] Check behavior at the exact ON and OFF boundary times.
- [ ] Test invalid keypad entries and repeated key presses.
Future Improvements
- PWM-based brightness control.
- Energy consumption measurement and reporting.
- Remote monitoring and configuration.
- Sensor fault detection and diagnostics.
- RTC alarm-based scheduling to reduce continuous polling.
- Event and operating-hour logging.
Repository Structure
Adaptive-Street-Light-Control/
├── src/                 # Place application and driver .c files here
├── include/             # Place project .h files here
├── hardware/
│   ├── README.md        # Hardware documentation checklist
│   └── images/          # Add schematic and PCB photographs
├── docs/
│   └── TESTING.md       # Hardware validation record
├── .gitignore
└── README.md
The folder structure is a suggested organization. You can retain your existing Keil project layout and update this tree to reflect it.
