#ifndef MIDDLEWARE_H_
#define MIDDLEWARE_H_

/*******************************************************************************
 *                                  Includes                                   *
 *******************************************************************************/

#include "std_types.h"
#include "lcd.h"
#include "Ldr.h"
#include "Led.h"
#include "adc.h"
#include "Motor.h"
#include "Flame.h"
#include "Buzzer.h"
#include "Timer0_PWM.h"
#include "lm35_sensor.h"


/*******************************************************************************
 *                      Functions Prototypes                                   *
 *******************************************************************************/

/* Initialize the LEDs
 * Initialize the LCD
 * Initialize the DC Motor
 */
void Initialization (void);

/*
 * Function to display the temperature and LDR (light sensor) values on the LCD
 */
void Display_Temp_and_LDR (void);

/*
 * Intensity < 15%: All 3 LEDs (Red, Green, and Blue) turn ON.
 * Intensity 16–50%: Red and Green LEDs turn ON.
 * Intensity 51–70%: Only the Red LED turns ON.
 * Intensity > 70%: All LEDs are turned OFF.
 */
void Automatic_Lighting_Control (void);

/*
 * Temperature ≥ 40°C: Fan ON at 100% speed.
 * Temperature ≥ 35°C and < 40°C: Fan ON at 75% speed.
 * Temperature ≥ 30°C and < 35°C: Fan ON at 50% speed.
 * Temperature ≥ 25°C and < 30°C: Fan ON at 25% speed.
 * Temperature < 25°C: Fan OFF.
 */
void  Automatic_Fan_Speed_Control (void);

/*
 * Function to detect fire using a flame sensor and trigger an alert system.
 * It displays an alert message on the LCD and activates a buzzer when fire is detected.
 * The system remains in alert mode until the flame is no longer detected, then it resets the display.
 */
void  Fire_Detection_and_Alert (void);


#endif /* MIDDLEWARE_H_ */
