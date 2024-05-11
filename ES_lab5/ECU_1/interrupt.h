
/******************************************************************************
 *
 * Module: external interrupts
 *
 * File Name: interrupt.h
 *
 * Description: header file for the AVR external interrupts driver dynamic configurations
 *
 * Author: Mohamed Ezzat
 *
 * Created on: march 21, 2023
 *
 * Version : v1.0.1
 *
 *******************************************************************************/

#ifndef INTERRUPT_H_
#define INTERRUPT_H_


/*******************************************************************************
 *                              	Includes		                           *
 *******************************************************************************/

#include"std_types.h"
#include"common_macros.h"

/*******************************************************************************
 *                              Type definition		                           *
 *******************************************************************************/

/*
 * Description :
 * used to discuss which external interrupt we will enable and it puts the value
 * in GICR register
 */
typedef enum{
	INT0_ID=64,INT1_ID=128,INT2_ID=32
}INT_NUMBER;

/*
 * Description :
 * used to discuss the way which an external interrupt been done
 */
typedef enum{
	ANY_LOGIC_CHANGE=1,FALLING_EDGE=2,RISING_EDGE=3
}INT_MODE;

/*
 * Description :
 * used to discuss the way which an external interrupt been done
 */
typedef struct{
	uint8 intNumber;
	uint8 intMode;
}INT_CONF;

/*******************************************************************************
 *                              Functions Prototypes                           *
 *******************************************************************************/

/*
 * Description :
 * A function to initialize our external interrupt
 */
void INT_init(const INT_CONF* config);

/*
 * Description :
 * A function to initialize our external interrupt
 */
void INT_deInit(const INT_CONF* config);

/*
 * Description :
 * A function to change the interrupt cause mode
 */
void INT_changeConfig(const INT_CONF* config);

/*
 * Description :
 * A function to set ISR function code
 */
void INT_setISR(void (*ptr)(void) , uint8 interrupt_number);

#endif /* INTERRUPT_H_ */
