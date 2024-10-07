#ifndef ADC_H_
#define ADC_H_

#include "std_types.h"

/*******************************************************************************
 *                         Types Declaration                                   *
 *******************************************************************************/

/*ADMUX Configuration  */

typedef enum
{
	Right,Left
}ADC_AdjustResult;

typedef enum
{
	AREF,AVCC,INTERNAL=3

}ADC_VoltageReference;

typedef struct
{
	ADC_AdjustResult Result;
	ADC_VoltageReference Reference;

}ADMUX_ConfigType;

/*ADCSRA Configuration  */
typedef enum
{
	F_CPU_2=1,F_CPU_4,F_CPU_8,F_CPU_16,F_CPU_32,F_CPU_64,F_CPU_128
}ADC_Prescaler;

typedef enum
{
	Enable,Disable
}ADC_Enables;

typedef struct
{
	ADC_Prescaler Prescaler;
	ADC_Enables Interrupt;
	ADC_Enables AutoTrigger;
	
}ADCSRA_ConfigType;

/*SFIOR Configuration  */
typedef enum
{
	Free_Run,Analog_Comp,Int0,Timer0_Comp,Timer0_OVF,Timer1_CompB,Timer1_OVF,Timer1_CE,
}ADC_AutoTriggerSource;

typedef struct
{
	ADC_AutoTriggerSource AutoTrigger;

}SFIOR_ConfigType;

/*******************************************************************************
 *                                Definitions                                  *
 *******************************************************************************/
#define ADC_MAXIMUM_VALUE    1023
#define ADC_REF_VOLT_VALUE   2.56
#define POLLING

#define ADC_0  0
#define ADC_1  1
#define ADC_2  2
#define ADC_3  3
#define ADC_4  4
#define ADC_5  5
#define ADC_6  6
#define ADC_7  7

/*******************************************************************************
 *                      Functions Prototypes                                   *
 *******************************************************************************/

/*
 * Description :
 * Function responsible for initialize the ADC driver.
 */
void ADC_init(const ADMUX_ConfigType * Config_Ptr ,const ADCSRA_ConfigType * Config_Ptr2 , const SFIOR_ConfigType * Config_Ptr3);

#ifdef POLLING
/*
 * Description :
 * Function responsible for read analog data from a certain ADC channel
 * and convert it to digital using the ADC driver.
 */
uint16 ADC_readChannel(uint8 channel_num);

#else
{
	void ADC_readChannel(uint8 channel_num);
}
#endif

#endif /* ADC_H_ */
