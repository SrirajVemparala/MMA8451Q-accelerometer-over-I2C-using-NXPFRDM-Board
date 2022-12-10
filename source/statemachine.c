/******************************************************************************
* @file: statemachine.c
*
* @brief: This files consists of the state machine functionality
*
* @author: Raghu Sai Phani Sriraj Vemparala
* @date:  9-DECEMBER-2022
*******************************************************************************/

/*******************************************************************************
Header files
*******************************************************************************/
#include "statemachine.h"
#include "PWM.h"
#include "accelerometer.h"
#include "stdio.h"
#include "inputtrigger.h"
#include <math.h>

/*******************************************************************************
Global variables
*******************************************************************************/
typedef enum
{
    ANGLE_0 = 0,
    ANGLE_30 = 30,
	ANGLE_45 = 45,
	ANGLE_60 = 60,
	ANGLE_90 = 90
}angles_detected;

/*******************************************************************************
Macros
*******************************************************************************/
#define LED_MAX_INTENSITY 255
#define LED_MIN_INTENSITY 0
/*******************************************************************************
 Global Variables
*******************************************************************************/
float roll_val = 0;
float ref_roll_val = 0;
float reef_pitch_val;
extern int data_rec_flag;
extern int gpio_trig_flag;
int roll_value = 0;

int led_color[3];
accelerometerState curr_state = OBTAIN_DATA_ZERO_CALIB;

/*******************************************************************************
* @Function Name: statemachine
* @Description: State machine process starts
* @input param: None
* @return: None
*******************************************************************************/
void statemachine()
{
	int calib_complete;
	switch(curr_state)
	{
		//state 1
		case OBTAIN_DATA_ZERO_CALIB:
			zero_calib(&calib_complete);
			if(calib_complete == 1)
			{
				//switch to ANGLE_DATA_DISPLAY if zero_calib is completed
				curr_state = ANGLE_DATA_DISPLAY;

			}
			else if((data_rec_flag == 1)||(gpio_trig_flag == 1))
			{
				//switch to calibrate_angle state if command is received or gpio button is pressed
				curr_state = CALIBRATE_ANGLE;
			}
			break;
			//state 2
		case CALIBRATE_ANGLE:
			if(calibrate_angle() == 1)
			{
				//switch to angle display if calibration is complete
				curr_state = ANGLE_DATA_DISPLAY;
				data_rec_flag = 0;
				gpio_trig_flag = 0;
			}
			break;
			//state 3
		case ANGLE_DATA_DISPLAY:
			display_angle();//display the angle
			if((data_rec_flag == 1)||(gpio_trig_flag == 1))
			{
				curr_state = CALIBRATE_ANGLE;
			}
			break;
	}
}

/****************************************************************************************
* @Function Name: zero_calib
* @Description: Calibrate the sensor and start angle detection if zero angle is detected
* @input param: int*
* @return: None
******************************************************************************************/
void zero_calib(int *calib_flag)
{
	float roll_value = 0.0;
	read_full_xyz();
	roll_value = convert_xyz_to_roll_pitch();
	if(roll_value == 0.0)
	{
		ref_roll_val = roll_value;
		//printf("Ref Roll value is %d\n\r",accel_parameters.ref_roll_val);
		*calib_flag = 1;
	}
}

/****************************************************************************************
* @Function Name: display_angle
* @Description: Detect angle and change the LED color
* @input param: None
* @return: None
******************************************************************************************/
void display_angle()
{

	read_full_xyz();
	roll_val = convert_xyz_to_roll_pitch();
	//printf("WO sub roll value is %d\n\r",roll_val);
	roll_value =  (int)(fabs((roll_val) - ref_roll_val));
	//printf("Angle value is %d\n\r",roll_value);
	if((roll_value) == ANGLE_30)
	{
		//printf("30 degree detected\n\r");
		led_color[0] = LED_MAX_INTENSITY;
		led_color[1] = LED_MIN_INTENSITY;
		led_color[2] = LED_MIN_INTENSITY;
		//printf("Enter Command\n\r");
	}
	else if((roll_value) == ANGLE_45)
	{
		//printf("45 degree detected\n\r");
		//printf("roll value is %d\n\r",roll_value);
		led_color[0] = LED_MIN_INTENSITY;
		led_color[1] = LED_MAX_INTENSITY;
		led_color[2] = LED_MIN_INTENSITY;
		//printf("Enter Command\n\r");

	}
	else if((roll_value) == ANGLE_60)
	{
		//printf("60 degree detected\n\r");
		led_color[0] = LED_MIN_INTENSITY;
		led_color[1] = LED_MIN_INTENSITY;
		led_color[2] = LED_MAX_INTENSITY;
		//printf("Enter Command\n\r");
	}
	else if(roll_value == ANGLE_90)
	{
		//printf("90 degree detected\n\r");
		led_color[0] = LED_MAX_INTENSITY;
		led_color[1] = LED_MAX_INTENSITY;
		led_color[2] = LED_MAX_INTENSITY;
		//printf("Enter Command\n\r");
	}
	else
	{
		led_color[0] = LED_MIN_INTENSITY;
		led_color[1] = LED_MIN_INTENSITY;
		led_color[2] = LED_MIN_INTENSITY;
	}
	PWM_trigger(led_color[0],led_color[1],led_color[2]);

}

/****************************************************************************************
* @Function Name: calibrate_angle
* @Description: Calibrate the angle to zero
* @input param: int*
* @return: None
******************************************************************************************/
int calibrate_angle()
{
		float roll_value1 = 0.0;
		read_full_xyz();
		roll_value1 = convert_xyz_to_roll_pitch();
		ref_roll_val = roll_value1;
			//printf("Ref Roll value is %d\n\r",accel_parameters.ref_roll_val);
		return 1;
}
