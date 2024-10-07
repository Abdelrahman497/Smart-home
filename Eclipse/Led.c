#include "Led.h"
#include <avr/io.h>

/*******************************************************************************
 *                          Global Variables                                   *
 *******************************************************************************/

/* Array to store the pin numbers for each LED.
 * Adjusted according to number of leds.
 */
static uint8 led_pins[NUM_OF_LEDS] = { PIN5 , PIN6 , PIN7} ;

/*******************************************************************************
 *                          Functions Definitions                              *
 *******************************************************************************/

/* Function to initialize the LED pins as output */
void LEDS_init(void)
{
	 /* Loop makes each LED pin as output */
	for (uint8 i = 0 ; i < NUM_OF_LEDS ; i++)
	{
		GPIO_setupPinDirection(LED_PORT_ID , led_pins [i] , PIN_OUTPUT);
	}
}

/* Function to turn on a specific LED using ID */
void led_on(LED_ID id)
{
		#ifdef POSTIVE_LOGIC
		{
		GPIO_writePin(LED_PORT_ID , led_pins [id] , LOGIC_HIGH);
		}
		#else
		{
		GPIO_writePin(LED_PORT_ID , led_pins [id] , LOGIC_LOW);
		}
		#endif
}

/* Function to turn off a specific LED using ID */
void led_off(LED_ID id)
{
		#ifdef POSTIVE_LOGIC
		{
		GPIO_writePin(LED_PORT_ID , led_pins [id] , LOGIC_LOW);
		}
		#else
		{
		GPIO_writePin(LED_PORT_ID , led_pins [id] , LOGIC_HIGH);
		}
		#endif
}


