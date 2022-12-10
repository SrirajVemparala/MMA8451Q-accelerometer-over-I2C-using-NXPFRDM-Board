/* 
 * sysclock.c - configuration routines for KL25Z system clock
 * 
 * Author Howdy Pierce, howdy.pierce@colorado.edu
 *
 * See section 24 of the KL25Z Reference Manual to understand this code
 *
 * Inspired by https://learningmicro.wordpress.com/configuring-device-clock-and-using-systick-system-tick-timer-module-to-generate-software-timings/

 */

#include "MKL25Z4.h"
#include "sysclock.h"

static volatile ticktime_t timerafterstart=0;
static volatile ticktime_t count=0;
int delay_time;
int flag = 0;


/* Function Name: init_systick
 * Use: Systick initialization
 * Return Type: void
 */
void sysclock_init()
{
	SysTick->LOAD=479999;
	NVIC_SetPriority(SysTick_IRQn,3);
	SysTick->VAL=0;
	SysTick->CTRL=SysTick_CTRL_TICKINT_Msk|SysTick_CTRL_ENABLE_Msk|SysTick_CTRL_CLKSOURCE_Msk ;
}
/* Function Name: now
 * Use: Provides time since start of program
 * Return Type: ticktime_t
 */
ticktime_t now()
{
return timerafterstart;
}
/* Function Name: reset_time
 * Use:Resets time to zero
 * Return Type: void
 */
void reset_timer()
{
	count=0;
}
/* Function Name: get_timer
 * Use:returns count
 * Return Type: ticktime_t
 */
ticktime_t get_timer()
{
return count;
}
/* Function Name: SysTick_Handler
 * Use:Increments count and timerafterstart
 * Return Type: void
 */
void SysTick_Handler()
{
count++;
timerafterstart++;
flag = 1;
}

