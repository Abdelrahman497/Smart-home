#ifndef LED_H_
#define LED_H_
#include "std_types.h"
#include "gpio.h"

/*******************************************************************************
 *                         Types Declaration                                   *
 *******************************************************************************/

typedef enum
{
	PIN0,PIN1,PIN2,PIN3,PIN4,PIN5,PIN6,PIN7
}LED_ID;


/*******************************************************************************
 *                                Definitions                                  *
 *******************************************************************************/
#define NUM_OF_LEDS 		   3
#define LED_PORT_ID         PORTB_ID

#define POSTIVE_LOGIC


/*******************************************************************************
 *                              Functions Prototypes                           *
 *******************************************************************************/

/* Function to initialize the LED pins as output */
void LEDS_init(void);

/* Function to turn on a specific LED using ID */
void led_on(LED_ID id);

/* Function to turn off a specific LED using ID */
void led_off(LED_ID id);

#endif /* LED_H_ */
