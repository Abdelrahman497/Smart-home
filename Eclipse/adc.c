#include "avr/io.h" /* To use the ADC Registers */
#include <avr/interrupt.h> /* For ADC ISR */
#include "adc.h"
#include "common_macros.h" /* To use the macros like SET_BIT */

#ifdef INTERRUPT
/*******************************************************************************
 *                          Global Variables                                   *
 *******************************************************************************/

volatile uint16 g_adcResult = 0;

/*******************************************************************************
 *                          ISR's Definitions                                  *
 *******************************************************************************/

ISR(ADC_vect)
{
	/* Read ADC Data after conversion complete */
		g_adcResult = ADC;
}

#endif

/*******************************************************************************
 *                          Functions Definitions                              *
 *******************************************************************************/

void ADC_init(const ADMUX_ConfigType * Config_Ptr1 ,const ADCSRA_ConfigType * Config_Ptr2 , const SFIOR_ConfigType * Config_Ptr3)
{
	/* ADMUX Register Bits Description:
	 * REFS1:0 : To choose Voltage Reference
	 * ADLAR   : To Adjust Result Presentation 
	 * MUX4:0  : To choose channel X as initialization
	 */
	ADMUX = (ADMUX & 0XDF) | (Config_Ptr1 -> Result);
	ADMUX = (ADMUX & 0x3F) | (Config_Ptr1->Reference << 6);


	/* ADCSRA Register Bits Description:
	 * ADEN 0 or 1 : Disable or Enable (ADC Enable)
	 * ADIE 0 or 1 : Disable or Enable (ADC Enable Interrupt)
	 * ADATE 0 or 1 : Disable or Enable  (Auto Trigger)
	 * ADPS2:0 : To choose ADC_Clock
	 */
	ADCSRA = (ADCSRA & 0XF8) | (Config_Ptr2 -> Prescaler);
	ADCSRA = (ADCSRA & 0XF7) | (Config_Ptr2 -> Interrupt);
	ADCSRA = (ADCSRA & 0XDF) | (Config_Ptr2 -> AutoTrigger);
	ADCSRA |= (1<<ADEN) ;

	/* SFIOR Register Bits Description:
	 * ADTS2:0 : Select which source will trigger
	 */
	SFIOR = (SFIOR & 0X1F) | (Config_Ptr3 -> AutoTrigger);
}

#ifdef POLLING

uint16 ADC_readChannel(uint8 channel_num)
{
	channel_num &= 0x07; /* Input channel number must be from 0 --> 7 */
	ADMUX &= 0xE0; /* Clear first 5 bits in the ADMUX (channel number MUX4:0 bits) before set the required channel */
	ADMUX = ADMUX | channel_num; /* Choose the correct channel by setting the channel number in MUX4:0 bits */
	SET_BIT(ADCSRA,ADSC); /* Start conversion write '1' to ADSC */
	while(BIT_IS_CLEAR(ADCSRA,ADIF)); /* Wait for conversion to complete, ADIF becomes '1' */
	SET_BIT(ADCSRA,ADIF); /* Clear ADIF by write '1' to it :) */
	return ADC; /* Read the digital value from the data register */
}
#else
{
	void ADC_readChannel(uint8 channel_num)
	{
		channel_num &= 0x07; /* Input channel number must be from 0 --> 7 */
		ADMUX &= 0xE0; /* Clear first 5 bits in the ADMUX (channel number MUX4:0 bits) before set the required channel */
		ADMUX = ADMUX | channel_num; /* Choose the correct channel by setting the channel number in MUX4:0 bits */
		SET_BIT(ADCSRA,ADSC); /* Start conversion write '1' to ADSC */
	}
}
#endif
