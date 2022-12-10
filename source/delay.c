/*
 * delay.c
 *
 *  Created on: 07-Dec-2022
 *      Author: VSR
 */


#include <MKL25Z4.H>

void Delay (uint32_t dly) {
  volatile uint32_t t;

	for (t=dly*10000; t>0; t--)
		;
}
