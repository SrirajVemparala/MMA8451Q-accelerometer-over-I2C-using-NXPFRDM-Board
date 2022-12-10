/* 
 * sysclock.h - configuration routines for KL25Z system clock
 * 
 * Author Howdy Pierce, howdy.pierce@colorado.edu
 */

#ifndef _SYSCLOCK_H_
#define _SYSCLOCK_H_

#include "stdbool.h"
#include "stdint.h"
#define SYSCLOCK_FREQUENCY (24000000U)
typedef uint32_t ticktime_t;
/*
 * Initializes the system clock. You should call this first in your
 * program.
 */
void sysclock_init();

/* Function Name: reset_time
 * Use:Resets time to zero
 * Return Type: void
 */
void reset_timer();
bool get_int_status();
typedef uint32_t ticktime_t;
/* Function Name: get_timer
 * Use:returns count
 * Return Type: ticktime_t
 */
ticktime_t get_timer();
/* Function Name: now
 * Use: Provides time since start of program
 * Return Type: ticktime_t
 */
ticktime_t now();
#endif  // _SYSCLOCK_H_
