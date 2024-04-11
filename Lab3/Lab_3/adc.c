/*
 ================================================================================================================================
 * File Name   : adc.c
 *
 * Module Name : adc
 *

 ================================================================================================================================
 */
#include "adc_interface.h"
#include "adc_private.h"
#include <avr/interrupt.h>

#if USE_ADC_IN_INTERRUPT_MODE
/*******************************************************************************
 *                          Global Variables                                   *
 *******************************************************************************/
volatile uint16 g_adcResult = 0;
#endif

/*******************************************************************************
 *                              Functions Definition                           *
 *******************************************************************************/

/* Description :
 * initiate the ADC module
 */
void ADC_init(const ADC_config* conf)
{
	/* Set reference voltage , ADC Left Adjust Result , channel is 0 at default*/
	ADC_ADMUX_REG.Byte|=(conf->bits)|(conf->volt);

	/* Enable ADC & set our prescaler N */
	ADC_ADCSRA_REG.Byte|=conf->pre;
	ADC_ADCSRA_REG.Bits.ADEN_BIT=1;
}

/*
 * Description :
 * Function responsible for read analog data from a certain ADC channel
 * and convert it to digital using the ADC driver.
 */
#if (USE_ADC_IN_INTERRUPT_MODE==FALSE)
uint16 ADC_readChannel(ch_no channel_num)
{
	/*ADC_ADMUX_REG.Byte &= 0xE0;        	 Clear first 5 bits in the ADMUX (channel number MUX4:0 bits) before set the required channel */
	/*ADC_ADMUX_REG.Byte |=channel_num;  	 Choose the correct channel by setting the channel number in MUX4:0 bits */
	ADC_ADMUX_REG.Byte = (ADC_ADMUX_REG.Byte & 0xE0) | (channel_num);

	/*start conversation */
	ADC_ADCSRA_REG.Bits.ADSC_BIT=1;

	/* Wait for conversion to complete, ADIF becomes '1' */
	while(!(ADC_ADCSRA_REG.Bits.ADIF_BIT));
	/* Clear ADIF by write '1' to it for next conversion */
	ADC_ADCSRA_REG.Bits.ADIF_BIT=1;
	/* Read the digital value from the data register */
	return ADC_ADC_REG.Two_Bytes;
}
#else
/* Description :
 * Function to Start  the value of certain channel
 * It is ASynchronous Function
 */
void ADC_readChannel(ch_no channel_num)
{
	/*ADC_ADMUX_REG.Byte &= 0xE0;        	 Clear first 5 bits in the ADMUX (channel number MUX4:0 bits) before set the required channel */
		/*ADC_ADMUX_REG.Byte |=channel_num;  	 Choose the correct channel by setting the channel number in MUX4:0 bits */
	ADC_ADMUX_REG.Byte = (ADC_ADMUX_REG.Byte & 0xE0) | (channel_num);

	/*start conversation */
	ADC_ADCSRA_REG.Bits.ADSC_BIT=1;
}
ISR(ADC_vect)
{
	ADC_ADC_REG.Two_Bytes==g_adcResult;
}
#endif
