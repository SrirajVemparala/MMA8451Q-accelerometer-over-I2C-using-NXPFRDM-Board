/*
 * state_machine.h
 *
 *  Created on: 08-Dec-2022
 *      Author: VSR
 */

#ifndef STATEMACHINE_H_
#define STATEMACHINE_H_

/*******************************************************************************
Global variables
*******************************************************************************/
typedef enum
{
	OBTAIN_DATA_ZERO_CALIB = 0,					/* In this state the calibration for zero is performed */
    CALIBRATE_ANGLE,				/* In this state the calibration (reference) is performed */
    ANGLE_DATA_DISPLAY 			/* In this state the angles are displayed */
}accelerometerState;

/*******************************************************************************
* @Function Name: statemachine
* @Description: State machine process starts
* @input param: None
* @return: None
*******************************************************************************/
void statemachine();

/****************************************************************************************
* @Function Name: display_angle
* @Description: Calibrate the sensor and start angle detection if zero angle is detected
* @input param: int*
* @return: None
******************************************************************************************/
void display_angle();

/****************************************************************************************
* @Function Name: zero_calib
* @Description: Calibrate the sensor and start angle detection if zero angle is detected
* @input param: int*
* @return: None
******************************************************************************************/
void zero_calib(int *);

/****************************************************************************************
* @Function Name: calibrate_angle
* @Description: Calibrate the angle to zero
* @input param: int*
* @return: None
******************************************************************************************/
int calibrate_angle();

#endif /* STATEMACHINE_H_ */
