/******************************************************************************
* @file: accelerometer.h
*
* @brief: This files consists of accelerometer conversion logic
*
* @author: Raghu Sai Phani Sriraj Vemparala
* @date:  9-DECEMBER-2022
* @references: https://github.com/alexander-g-dean/ESF/tree/master/NXP/Code/Chapter_8/I2C-Demo
*******************************************************************************/

#ifndef ACCELEROMETER_H_
#define ACCELEROMETER_H_

#ifndef MMA8451_H
#define MMA8451_H
#include <stdint.h>

/*******************************************************************************
 Macros
*******************************************************************************/
#define MMA_ADDR 0x3A

#define REG_XHI 0x01
#define REG_XLO 0x02
#define REG_YHI 0x03
#define REG_YLO 0x04
#define REG_ZHI	0x05
#define REG_ZLO 0x06

#define REG_WHOAMI 0x0D
#define REG_CTRL1  0x2A
#define REG_CTRL4  0x2D

#define WHOAMI 0x1A

#define COUNTS_PER_G (4096.0)
#define M_PI (3.14159265)

/*******************************************************************************
 Global Variables
*******************************************************************************/
extern float roll, pitch;
extern int16_t acc_X, acc_Y, acc_Z;
/*******************************************************************************
* @Function Name: init_mma
* @Description: initializes mma8451 sensor. Ensure I2C_Init is called before.
* @input param  : none
* @return: success or failure
*******************************************************************************/
int init_mma(void);
/*******************************************************************************
* @Function Name: read_full_xyz
* @Description: reads the accelerometer's x,y,z values
* @input param : none
* @return : none
*******************************************************************************/
void read_full_xyz(void);
//void read_xyz(void);
/*******************************************************************************
* @Function Name: convert_xyz_to_roll_pitch
* @Description: converts the x,y,z values into roll and pitch
* @input param : none
* @return : int
*******************************************************************************/
int convert_xyz_to_roll_pitch(void);


#endif

#endif /* ACCELEROMETER_H_ */
