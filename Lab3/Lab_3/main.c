/*
================================================================================================================================
 * File Name   : Main.c
 *
================================================================================================================================
 */
/* Including necessary header files */
#include "lcd.h"
#include "gpio_interface.h"
#include "adc_interface.h"
#include "ext_interrupt_interface.h"
#include <avr/interrupt.h>
#include <util/delay.h>
#define LAST_COL_LCD_ADDRESS	17

void DisplayAdcValue(void)
{
	uint8 adc_value=0;
	/*read channel number 0 ADC0 */
	adc_value=ADC_readChannel(ADC0);

	/*Display On LCD the value*/
	LCD_clearScreen();
	LCD_moveCursor(0, 0);
	LCD_intgerToString(adc_value);

	/*wait for 2 second*/
	_delay_ms(2000);
}


/* Main function */
int main(void)
{
	/*Initialize ADC*/
	ADC_config ADC_configuration={N_64,LSBs,AVCC_5V};
	ADC_init(&ADC_configuration);

	/*Intialize External Interrupt ON INT0*/
	Interrupt_Config Ext_Configuration={INT0_ID,FALLING_EDGE};
	INT_init(&Ext_Configuration);

	/*Enable Global Interrupt*/
	SREG|=(1<<7);

	/*Set Call Back Function*/
	INT_setISR(DisplayAdcValue,0);


	/* Initializing variables for row ,column and counter to count the size */
	sint8 rowNumber=0, colNumber=0;
	uint8 count=0;
	GPIO_setupPortDirection(2, 0XFF);
	const char *displayedString="DR.Hossam";

	/*while loop to determine the length of string*/
	while(displayedString[count] != '\0')
	{
		LCD_displayCharacter(displayedString[count]);
		count++;
	}

	/* Initializing LCD */
	LCD_init();

	/* Infinite loop for continuous execution */
	for(;;)
	{
		/* Nested loops for display on LCD in Forward Direction */
		for(rowNumber=0; rowNumber<2; rowNumber++)
		{
			for(colNumber=0; colNumber<LAST_COL_LCD_ADDRESS-count; colNumber++)
			{
				/* Displaying the string at the specified row and column */
				LCD_displayStringRowColumn(rowNumber, colNumber, displayedString);

				/* Delay for 1000 milliseconds to observe the displayed string */
				_delay_ms(500);

				/* Clearing the entire LCD screen */
				LCD_clearScreen();
		}
		}
		/* Nested loops for display on LCD in Reverse Direction */
		for(rowNumber=1; rowNumber>=0; rowNumber--)
		{
			for(colNumber=(LAST_COL_LCD_ADDRESS-count)-2; colNumber>=0; colNumber--)
			{
				/* Displaying the string at the specified row and column */
				LCD_displayStringRowColumn(rowNumber, colNumber, displayedString);

				/* Delay for 1000 milliseconds to observe the displayed string */
				_delay_ms(500);

				/* Clearing the entire LCD screen */
				LCD_clearScreen();
			}
		}
	}
}
