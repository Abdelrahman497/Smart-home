#ifndef FLAME_H_
#define FLAME_H_
#include "std_types.h"

/*******************************************************************************
 *                                Definitions                                  *
 *******************************************************************************/
#define FLAME_PORT_ID 		   PORTD_ID
#define FLAME_PIN_ID           PIN2_ID


/*******************************************************************************
 *                              Functions Prototypes                           *
 *******************************************************************************/

/* Configures the pin connected to the flame sensor*/
void FlameSensor_init(void);

/* This function reads and returns the current state of the flame sensor */
uint8 FlameSensor_getValue(void);

#endif /* FLAME_H_ */
