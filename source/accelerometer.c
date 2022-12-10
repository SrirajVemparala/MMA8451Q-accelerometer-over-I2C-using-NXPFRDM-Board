/******************************************************************************
* @file: accelerometer.c
*
* @brief: This files consists of accelerometer conversion logic
*
* @author: Raghu Sai Phani Sriraj Vemparala
* @date:  9-DECEMBER-2022
* @references: https://github.com/alexander-g-dean/ESF/tree/master/NXP/Code/Chapter_8/I2C-Demo
*******************************************************************************/

/*******************************************************************************
 Header Files
*******************************************************************************/
#include <MKL25Z4.H>
#include "accelerometer.h"
#include "i2c.h"
#include "delay.h"
#include <math.h>
/*******************************************************************************
 Global Variables
*******************************************************************************/
int16_t acc_X=0, acc_Y=0, acc_Z=0;
float roll=0.0, pitch=0.0;

//mma data ready
extern uint32_t DATA_READY;

/*******************************************************************************
* @Function Name: init_mma
* @Description: initializes mma8451 sensor. Ensure I2C_Init is called before.
* @input param  : none
* @return: success or failure
*******************************************************************************/
int init_mma()
{
	//set active mode, 14 bit samples and 800 Hz ODR
	i2c_write_byte(MMA_ADDR, REG_CTRL1, 0x01);
	return 1;
}

/*******************************************************************************
* @Function Name: read_full_xyz
* @Description: reads the accelerometer's x,y,z values
* @input param : none
* @return : none
*******************************************************************************/
void read_full_xyz()
{
	int i;
	uint8_t data[6];
	int16_t temp[3];

	i2c_start();
	i2c_read_setup(MMA_ADDR , REG_XHI);

	// Read five bytes in repeated mode
	for( i=0; i<5; i++)	{
		data[i] = i2c_repeated_read(0);
	}
	// Read last byte ending repeated mode
	data[i] = i2c_repeated_read(1);

	for ( i=0; i<3; i++ ) {
		temp[i] = (int16_t) ((data[2*i]<<8) | data[2*i+1]);
	}

	// Align for 14 bits
	acc_X = temp[0]/4;
	acc_Y = temp[1]/4;
	acc_Z = temp[2]/4;

}

/*******************************************************************************
* @Function Name: convert_xyz_to_roll_pitch
* @Description: converts the x,y,z values into roll and pitch
* @input param : none
* @return : int
*******************************************************************************/
int convert_xyz_to_roll_pitch(void) {
	float ax = acc_X/COUNTS_PER_G,
				ay = acc_Y/COUNTS_PER_G,
				az = acc_Z/COUNTS_PER_G;

	roll = atan2(ay, az)*180/M_PI;
	pitch = atan2(ax, sqrt(ay*ay + az*az))*180/M_PI;

	return roll;
}

