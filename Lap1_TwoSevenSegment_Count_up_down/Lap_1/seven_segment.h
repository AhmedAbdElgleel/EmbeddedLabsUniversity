 /******************************************************************************
 * Module     : sevenSegment
 *
 * File Name  : sevenSegment.h
 *
 * Description: header file for seven segment driver
 *
 * Author     : Ahmed Abd Elgleel
 *
 * Date	      : Oct 11, 2023
 *******************************************************************************/
#ifndef SEVEN_SEGMENT_H_
#define SEVEN_SEGMENT_H_
#include "std_types.h"
/*******************************************************************************
 *                                Definitions                                  *
 *******************************************************************************/
/*Choose only one the the following 3 definitions depends on your connection*/
/*#define SEVEN_SEGMENT_WITH_DECODER*/
/*#define SEVEN_SEGMENT_COMMON_ANODE_WITHOUT_DECODER*/
#define SEVEN_SEGMENT_COMMON_CATHODE_WITHOUT_DECODER*/

#define FIRST_SEVEN_SEGMENT 	  0									/*THIS  #define to make the code readable in the app */
#define SECOND_SEVEN_SEGMENT	  1									/*THIS  #define to make the code readable in the app */
#define SEVEN_SEGMENT_PORT_ID					PORTA_ID			/*Seven Segment Port ID that connected on it*/
#define SEVEN_SEGMENT_FIRST_PIN_ID				PIN1_ID				/*Seven Segment first pin ID that connected on it*/
#define SEVEN_SEGMENT_CONTROL_ENABLE_PORT_ID	PORTC_ID			/*Control Enable port for Seven segment*/
#define SEVEN_SEGMENT_FIRST_CONTROL_ENABLE_PIN	PIN6_ID				/*first control line for fist seven segment*/
#define SEVEN_SEGMENT_SECOND_CONTROL_ENABLE_PIN	PIN7_ID				/*second control line for second seven segment*/
#define CONTROL_ENABLE							LOGIC_HIGH			/*Enable with LOGIC_1 in case NPN transistor  */
#define CONTROL_DISABLE							LOGIC_LOW			/*Disable with LOGIC_0 in case NPN transistor */
																	/*Note if you will using Multiplexing technique via PnP transistor U
													  	  	  	  	  Have to change Control_Enable to LOGIC_LOW AND CONTROL_Disable to LOGIC HIGH */
#ifdef SEVEN_SEGMENT_COMMON_CATHODE_WITHOUT_DECODER
#define TURN_ON_THIS_SEGMENT            LOGIC_HIGH
#define TURN_OFF_THIS_SEGMENT           LOGIC_LOW
#endif


#ifdef SEVEN_SEGMENT_COMMON_ANODE_WITHOUT_DECODER
#define TURN_ON_THIS_SEGMENT            LOGIC_LOW
#define TURN_OFF_THIS_SEGMENT           LOGIC_HIGH
#endif
/*******************************************************************************
 *                      Functions Prototypes                                   *
 *******************************************************************************/
/*
* Description :
* Initialize the Seven Segment:
* 	Setup the Seven Segment pins directions by use the GPIO driver.
*/
void SEVENSEGMENT_init(void);
/*
* Description :
* Enable a certain Seven Segment on using multiplixing techique:
*/
void SEVENSEGMENT_enable(uint8 a_sevenSegmentNum);
/*
* Description :
* disable a certain Seven Segment on using multiplixing techique:
*/
void SEVENSEGMENT_disable(uint8 a_sevenSegmentNum);
#ifdef SEVEN_SEGMENT_WITH_DECODER
/*
* Description :
* Display on the Seven Segment using Decoder:
* 	Display the value on 4 pins by use the GPIO driver.
*/
void SEVENSEGMENT_DisplayWithDecoder(uint8 a_value);
#else
/*
* Description :
* Display on the Seven Segment without using Decoder:
* 	Display the value on 4 pins by use the GPIO driver.
*/
void SEVENSEGMENT_DisplayWithoutDecoder(uint8 a_value);
#endif
#endif /* SEVEN_SEGMENT_H_ */
