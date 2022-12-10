/******************************************************************************
* @file: i2c.c
*
* @brief: This files consists of the declarations of i2c communication functionalities
*
* @author: Raghu Sai Phani Sriraj Vemparala
* @date:  9-DECEMBER-2022
* @references: dean book - Serial communication chapter
*******************************************************************************/

/*******************************************************************************
Header files
*******************************************************************************/
#include <stdint.h>

/*******************************************************************************
 Macros
*******************************************************************************/
#define I2C_M_START 	I2C0->C1 |= I2C_C1_MST_MASK
#define I2C_M_STOP  	I2C0->C1 &= ~I2C_C1_MST_MASK
#define I2C_M_RSTART 	I2C0->C1 |= I2C_C1_RSTA_MASK

#define I2C_TRAN			I2C0->C1 |= I2C_C1_TX_MASK
#define I2C_REC				I2C0->C1 &= ~I2C_C1_TX_MASK

#define BUSY_ACK 	    while(I2C0->S & 0x01)
#define TRANS_COMP		while(!(I2C0->S & 0x80))
#define I2C_WAIT 			i2c_wait();

#define NACK 	        I2C0->C1 |= I2C_C1_TXAK_MASK
#define ACK           I2C0->C1 &= ~I2C_C1_TXAK_MASK

/*******************************************************************************
 Function declarations
*******************************************************************************/
/*******************************************************************************
* @Function Name: i2c_init()
* @Description: Initializes the I2c module for communication with accelerometer
* @input param : none
* @return: none
*******************************************************************************/
void i2c_init(void);

/*******************************************************************************
* @Function Name: i2c_start
* @Description: sends start bit
* @input param : none
* @return: none
*******************************************************************************/
void i2c_start(void);

/*******************************************************************************
* @Function Name : i2c_read_setup
* @Description : send device and register addresses
* @input param 1 : the device address
* @input param 2 : the address register of the device from where data is to be read
* @return : none
*******************************************************************************/
void i2c_read_setup(uint8_t dev, uint8_t address);

/*******************************************************************************
* @Function Name : i2c_repeated_read
* @Description : read a byte and ack/nack as appropriate
* @input param 1 : the device address to be sent for communication set-up
* @return : the byte read
*******************************************************************************/
uint8_t i2c_repeated_read(uint8_t);
/*******************************************************************************
* @Function Name : i2c_read_byte
* @Description : this function is used for reading and writing a single byte
* using 7bit addressing and  reads a byte from device addressed
* @input param 1 : the device address
* @input param 2 : the address in the device from where the data has to be read
* @return : the byte read
*******************************************************************************/
uint8_t i2c_read_byte(uint8_t dev, uint8_t address);
/*******************************************************************************
* @Function Name : i2c_write_byte
* @Description : this function uses 7bit addressing to write a byte data to
* device addressed
* @input param 1 : the device address
* @input param 2 : the address in the device from where the data has to be read
* @input param 3 : the data to be written to the device
* @return : the byte read
*******************************************************************************/
void i2c_write_byte(uint8_t dev, uint8_t address, uint8_t data);

/*******************************************************************************
* @Function Name: i2c_wait
* @Description: The function purpose is to release the bus in if an acknowledgment occurs
* is not received from the device under communication
* @input param : none
* @return: none
*******************************************************************************/
void i2c_wait(void);

/*******************************************************************************
* @Function Name: i2c_busy
* @Description: This condition is entered when the I2c bus is busy
* @input param : none
* @return: none
*******************************************************************************/
void i2c_busy(void);
