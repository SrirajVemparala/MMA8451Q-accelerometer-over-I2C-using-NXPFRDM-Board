/******************************************************************************
* @file: test_accel.c
*
* @brief: This files consists of the logic to acheive testing of PWM communication
*
* @author: Raghu Sai Phani Sriraj Vemparala
* @date:  9-DECEMBER-2022
*******************************************************************************/
#include "test_accel.h"
#include "sysclock.h"
#include "PWM.h"
#include "fsl_debug_console.h"
#include <stdio.h>

/*******************************************************************************
* @Function Name: test_led_PWM
* @Description: Tests PWM.
* @input param  : none
* @return: none
*******************************************************************************/
void test_led_PWM()
{
	/*testing RED LED*/
	PWM_trigger(255,0,0);
	reset_timer();
	while(get_timer() < DELAY_500MSEC);
	printf("Red LED Working\r\n");
	/*testing GREEN LED*/
	PWM_trigger(0,255,0);
	reset_timer();
	while(get_timer() < DELAY_500MSEC);
	printf("Green LED Working\r\n");
	/*testing BLUE LED*/
	PWM_trigger(0,0,255);
	reset_timer();
	while(get_timer() < DELAY_500MSEC);
	printf("Blue LED Working\r\n");
	/*testing WHITE LED*/
	PWM_trigger(255,255,255);
	reset_timer();
	while(get_timer() < DELAY_500MSEC);
	printf("White LED Working\r\n");

	PWM_trigger(0,0,0);
	printf("PWM testing is successful\r\n");

}
