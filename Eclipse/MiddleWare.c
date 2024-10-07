#include "MiddleWare.h"
#include <util/delay.h>


/*******************************************************************************
 *                          Global Variables                                   *
 *******************************************************************************/

uint8 Temp = 0;
uint8 LDR = 0;
uint8 FLAG = 0 ;


/*******************************************************************************
 *                          Functions Definitions                              *
 *******************************************************************************/

/* Initialize the LEDs
 * Initialize the LCD
 * Initialize the DC Motor
 * Initialize the ADC module
 */
void Initialization (void)
{
	/* Initialize the LEDs by setting up their pins as output */
	LEDS_init();
	/* Initialize the LCD for displaying information */
	LCD_init();
	/* Initialize the DC Motor by setting the motor pins as output and turning it off */
	DcMotor_Init();
	/* Display initial static text on the LCD */
	LCD_displayStringRowColumn(0,0,"Fan is ");
	LCD_displayStringRowColumn(1,0,"Temp=");
	LCD_displayStringRowColumn(1,9,"LDR=");

	/* Configure the ADC module for temperature and light readings */
	ADMUX_ConfigType  Ptr1  = { Right , INTERNAL } ;
	ADCSRA_ConfigType Ptr2  = { F_CPU_128 , Disable , Disable } ;
	SFIOR_ConfigType  Ptr3  = { Free_Run } ;
	ADC_init( &Ptr1 , &Ptr2 , &Ptr3 );

}

/*
 * Function to display the temperature and LDR (light sensor) values on the LCD
 */
void Display_Temp_and_LDR (void)
{
	Temp = LM35_getTemperature();

	/* Display the temperature value every time at same position */
	LCD_moveCursor(1,5);
	if(Temp >= 100)
	{
		LCD_intgerToString(Temp);
	}
	else
	{
		LCD_intgerToString(Temp);
		/* In case the digital value is two or one digits print space in the next digit place */
		LCD_displayCharacter(' ');
	}

	LDR = LDR_getLightIntensity();
	LCD_moveCursor(1,13);
	if(LDR >= 100)
	{
		LCD_intgerToString(LDR);
	}
	else
	{
		LCD_intgerToString(LDR);
		/* In case the digital value is two or one digits print space in the next digit place */
		LCD_displayCharacter(' ');
	}
}


/*
 * Intensity < 15%: All 3 LEDs (Red, Green, and Blue) turn ON.
 * Intensity 16–50%: Red and Green LEDs turn ON.
 * Intensity 51–70%: Only the Red LED turns ON.
 * Intensity > 70%: All LEDs are turned OFF.
 */
void  Automatic_Lighting_Control (void)
{

	if(LDR <= 15)
	{
		led_on(PIN0);  /* RED   */
		led_on(PIN1);  /* GREEN */
		led_on(PIN2);  /* BLUE  */
	}
	else if(LDR >= 16 && LDR <= 50)
	{
		led_on(PIN0);  /* RED   */
		led_on(PIN1);  /* GREEN */
		led_off(PIN2); /* BLUE  */
	}
	else if(LDR >= 51 && LDR <= 70)
	{
		led_on(PIN0);  /* RED   */
		led_off(PIN1); /* GREEN */
		led_off(PIN2); /* BLUE  */
	}
	else if(LDR >= 71)
	{
		led_off(PIN0); /* RED   */
		led_off(PIN1); /* GREEN */
		led_off(PIN2); /* BLUE  */
	}
}

/*
 * Temperature ≥ 40°C: Fan ON at 100% speed.
 * Temperature ≥ 35°C and < 40°C: Fan ON at 75% speed.
 * Temperature ≥ 30°C and < 35°C: Fan ON at 50% speed.
 * Temperature ≥ 25°C and < 30°C: Fan ON at 25% speed.
 * Temperature < 25°C: Fan OFF.
 */
void  Automatic_Fan_Speed_Control (void)
{
	if(Temp < 25)
	{
		LCD_displayStringRowColumn(0,7,"OFF");
		DcMotor_Rotate( CW , DUTY_CYCLE_0 );
	}
	else if(Temp >= 25 && Temp < 30)
	{
		LCD_displayStringRowColumn(0,7,"ON");
		LCD_displayCharacter(' ');
		DcMotor_Rotate( CW , DUTY_CYCLE_25 );
	}
	else if(Temp >= 30 && Temp < 35)
	{
		LCD_displayStringRowColumn(0,7,"ON");
		LCD_displayCharacter(' ');
		DcMotor_Rotate( CW , DUTY_CYCLE_50 );
	}
	else if(Temp >= 35 && Temp < 40)
	{
		LCD_displayStringRowColumn(0,7,"ON");
		LCD_displayCharacter(' ');
		DcMotor_Rotate( CW , DUTY_CYCLE_75 );
	}
	else if(Temp >= 40)
	{
		LCD_displayStringRowColumn(0,7,"ON");
		LCD_displayCharacter(' ');
		DcMotor_Rotate( CW , MAX_DUTY_CYCLE_100 );
	}

}

/*
 * Function to detect fire using a flame sensor and trigger an alert system.
 * It displays an alert message on the LCD and activates a buzzer when fire is detected.
 * The system remains in alert mode until the flame is no longer detected, then it resets the display.
 */
void Fire_Detection_and_Alert(void)
{
	/* Clear the LCD and display the alert message */
	LCD_clearScreen();
	LCD_moveCursor(0, 0);
	LCD_displayString("Critical alert!");

	/* Turn on the buzzer */
	Buzzer_on();

	/* Continuously check the flame sensor until the flame is gone */
	while (FlameSensor_getValue() == 1)
	{
		/* Add a small delay to avoid constant polling */
		_delay_ms(100);
		/*Turn off the led */
		led_off(PIN0); /* RED   */
		led_off(PIN1); /* GREEN */
		led_off(PIN2); /* BLUE  */
		/* Stop te motor */
		DcMotor_Rotate( STOP , DUTY_CYCLE_0 );
	}

	/* Once the fire is no longer detected, turn off the buzzer and reset the display */
	Buzzer_off();
	/* Clear the screen and restore the normal display */
	LCD_clearScreen();
	LCD_displayStringRowColumn(0, 0, "Fan is ");
	LCD_displayStringRowColumn(1, 0, "Temp=");
	LCD_displayStringRowColumn(1, 9, "LDR=");
}







