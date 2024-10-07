#ifndef LDR_H_
#define LDR_H_


#include "std_types.h"
#include "adc.h"

/*******************************************************************************
 *                                Definitions                                  *
 *******************************************************************************/

#define  LDR_SENSOR_CHANNEL_ID             ADC_0
#define  LDR_SENSOR_MAX_VOLT_VALUE         2.56
#define  ADC_LDR_MAXIMUM_VALUE             1023
#define  LDR_SENSOR_MAX_LIGHT_INTENSITY    100

/*******************************************************************************
 *                      Functions Prototypes                                   *
 *******************************************************************************/

/*
 * Description :
 * Function responsible for calculate the temperature from the ADC digital value.
 */
uint16 LDR_getLightIntensity(void);

#endif /* LDR_H_ */
