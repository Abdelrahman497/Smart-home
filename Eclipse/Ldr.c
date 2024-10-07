#include "Ldr.h"
#include "adc.h"

/*******************************************************************************
 *                          Functions Definitions                              *
 *******************************************************************************/

/*
 * This function reads the analog value from the LDR sensor using the ADC,
 * converts the ADC value to voltage, and then converts the voltage to light intensity.
 * return The light intensity from the LDR sensor.
 */
uint16 LDR_getLightIntensity(void)
{
	uint16 adc_value = 0;
	float32 voltage  = 0;
	float32 light_intensity =0;

	/* Read ADC value */
	adc_value = ADC_readChannel(LDR_SENSOR_CHANNEL_ID);
	/* Convert ADC value to voltage */
	voltage = ((float)adc_value / ADC_LDR_MAXIMUM_VALUE) * LDR_SENSOR_MAX_VOLT_VALUE;
	/* Convert voltage to light intensity, scaling appropriately */
	light_intensity = (voltage / LDR_SENSOR_MAX_VOLT_VALUE) * LDR_SENSOR_MAX_LIGHT_INTENSITY;

	return (uint16)light_intensity;
}


