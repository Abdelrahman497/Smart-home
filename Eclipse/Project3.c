#include "MiddleWare.h"

/*******************************************************************************
 *                             Main Function                                   *
 *******************************************************************************/

int main (void)
{
	/* Initialize the LEDs
	 * Initialize the LCD
	 * Initialize the DC Motor
	 * Initialize the ADC module
	 */
	Initialization ();

	while(1)
	{

		if(  FlameSensor_getValue()  == 1 )
		{
			/*
			 * Function to detect fire using a flame sensor and trigger an alert system.
			 * It displays an alert message on the LCD and activates a buzzer when fire is detected.
			 * The system remains in alert mode until the flame is no longer detected, then it resets the display.
			 */
			Fire_Detection_and_Alert () ;
		}
		else
		{
			/*
			 * Function to display the temperature and LDR (light sensor) values on the LCD
			 */
			Display_Temp_and_LDR ();

			/*
			 * Intensity < 15%: All 3 LEDs (Red, Green, and Blue) turn ON.
			 * Intensity 16–50%: Red and Green LEDs turn ON.
			 * Intensity 51–70%: Only the Red LED turns ON.
			 * Intensity > 70%: All LEDs are turned OFF.
			 */
			Automatic_Lighting_Control ();

			/*
			 * Temperature ≥ 40°C: Fan ON at 100% speed.
			 * Temperature ≥ 35°C and < 40°C: Fan ON at 75% speed.
			 * Temperature ≥ 30°C and < 35°C: Fan ON at 50% speed.
			 * Temperature ≥ 25°C and < 30°C: Fan ON at 25% speed.
			 * Temperature < 25°C: Fan OFF.
			 */
			Automatic_Fan_Speed_Control ();
		}

	}
}
