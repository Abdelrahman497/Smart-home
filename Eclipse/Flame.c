#include "Flame.h"
#include "gpio.h"
#include <avr/io.h>

/*******************************************************************************
 *                          Functions Definitions                              *
 *******************************************************************************/

/* Configures the pin connected to the flame sensor*/
void FlameSensor_init(void)
{
	/* Set the flame sensor pin as input */
	GPIO_setupPinDirection(FLAME_PORT_ID , FLAME_PIN_ID , PIN_INPUT);
}

/* This function reads and returns the current state of the flame sensor */
uint8 FlameSensor_getValue(void)
{
	uint8 value = 0;
	  /* Read the value from the flame sensor pin */
	value = GPIO_readPin( FLAME_PORT_ID , FLAME_PIN_ID );

	return value;
}
