/******************************************************************************
* @file: main.c
*
* @brief: This files consists of the main logic to start state machine.
*
* @author: Raghu Sai Phani Sriraj Vemparala
* @date:  12-DECEMBER-2022
* @references: Making Embedded Systems - White
* @references: Dean book
*******************************************************************************/
/*******************************************************************************
Header files
*******************************************************************************/
#include <MKL25Z4.h>
#include <stdio.h>
#include <math.h>
#include "i2c.h"
#include "accelerometer.h"
#include "delay.h"
#include "sysclock.h"
#include "UARTcomm.h"
#include "circularbufferqueue.h"
#include "string.h"
#include "stdio.h"
#include "pin_mux.h"
#include "clock_config.h"
#include "PWM.h"
#include "statemachine.h"
#include "string.h"
#include "stdio.h"
#include "peripherals.h"
#include "board.h"
#include "inputtrigger.h"
#include "test_accel.h"


/*******************************************************************************
Macros
*******************************************************************************/
#define UART_BAUDRATE 38400
/*******************************************************************************
Global variables
*******************************************************************************/
extern accelerometerState curr_state;
int data_rec_flag = 0;
char *inputstr;
char str[256];
int enter_flag = 0;
int i =0;
char command;
extern float ref_roll_val;
extern int roll_value;
/*******************************************************************************
Function prototype
*******************************************************************************/
void calibrate_cmd_check();
/*******************************************************************************
Function definition
*******************************************************************************/

/*******************************************************************************
* @Function Name: calibrate_cmd_check
* @Description: Used to check if calibrate command is sent
* @input param: None
* @return: None
*******************************************************************************/
void calibrate_cmd_check()
{
	// memset(str,'\0',256);
		//get character from user
		command = getchar();
		if(command!= 0)
		{
		//loop until ENTER character is pressed
			if(command!='\r')
			{
			//Convert capital alphabets to small alphabets
				if((command>= 'A') && (command <='Z'))
				{
					command = command + 32;
				}
				//If backspace is detected go back to previous character location
				if(command == 0x08)
				{
					i--;
					str[i] = '\0';
					command = getchar();
				}
				else
				{
					str[i] = command;
					i++;
					//command = getchar();
				}
			}
			else if(command == '\r')
			{
				//If enter key is pressed
				enter_flag = 1;
				//i++;
				str[i] = '\0';
			}
		}

		if(enter_flag == 1)
		{
			printf("Entered string is %s\n\r", str);
			/* Command processing start*/
			int cmp,cmp1;
			// compare if the command received is calibrate
			cmp =strcmp(str,"calibrate");
			cmp1 = strcmp(str,"angle");
			printf("\n\r");
				//If valid command enter
			if(cmp== 0)
			{
				data_rec_flag = 1;
				enter_flag = 0;
				i = 0;

			}
			else if(cmp1 == 0)
			{
				printf("angle is: %d",roll_value);
				enter_flag = 0;
				 i = 0;
			}
			else
			{
				printf("Invalid Command\n\r");
				i = 0;
				enter_flag = 0;
				 //memcpy(str,0,sizeof(str));
			}
				printf("\n\r");
				printf("Enter the command\n\r");
				 //memcpy(str,0,sizeof(str));
		}
}
/*******************************************************************************
* @Function Name: main
* @Description: Starts the application
* @input param: None
* @return: int
*******************************************************************************/
int main(void)
{
	BOARD_InitBootPins();
	BOARD_InitBootClocks();
	BOARD_InitBootPeripherals();
	#ifndef BOARD_INIT_DEBUG_CONSOLE_PERIPHERAL
	    /* Init FSL debug console. */
	    BOARD_InitDebugConsole();
	#endif
	//Init_RGB_LEDs();
	i2c_init();										/* init i2c	*/
	if (!init_mma())
	{												/* init mma peripheral */
		while (1);									/* not able to initialize mma */
	}
	Delay(100);
	sysclock_init();
	//UART initialization
	uart0_init(UART_BAUDRATE);
	GPIO_PB_init();
	PWM_init();
	__enable_irq();
	test_led_PWM();
	printf("Enter the command\n\r");
	while (1) {
		calibrate_cmd_check();
		statemachine();
	}
}
