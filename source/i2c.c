/******************************************************************************
* @file: i2c.c
*
* @brief: This files consists of the logic to acheive i2c communication
*
* @author: Raghu Sai Phani Sriraj Vemparala
* @date:  9-DECEMBER-2022
* @references: dean book - Serial communication chapter
*******************************************************************************/
/*******************************************************************************
Header files
*******************************************************************************/
#include <MKL25Z4.H>
#include "i2c.h"
/*******************************************************************************
 Global variables
*******************************************************************************/
int lock_detect=0;
int i2c_lock=0;

/*******************************************************************************
 Function definitions
*******************************************************************************/
/*******************************************************************************
* @Function Name: i2c_init()
* @Description: Initializes the I2c module for communication with accelerometer
* @input param : none
* @return: none
*******************************************************************************/
void i2c_init(void)
{
	//clock i2c peripheral and port E
	SIM->SCGC4 |= SIM_SCGC4_I2C0_MASK;
	SIM->SCGC5 |= (SIM_SCGC5_PORTE_MASK);

	//set pins to I2C function
	PORTE->PCR[24] |= PORT_PCR_MUX(5);
	PORTE->PCR[25] |= PORT_PCR_MUX(5);

	//set to 100k baud
	//baud = bus freq/(scl_div+mul)
 	//~400k = 24M/(64); icr=0x12 sets scl_div to 64

 	I2C0->F = (I2C_F_ICR(0x10) | I2C_F_MULT(0));

	//enable i2c and set to master mode
	I2C0->C1 |= (I2C_C1_IICEN_MASK);

	// Select high drive mode
	I2C0->C2 |= (I2C_C2_HDRS_MASK);
}

/*******************************************************************************
* @Function Name: i2c_busy
* @Description: This condition is entered when the I2c bus is busy
* @input param : none
* @return: none
*******************************************************************************/
void i2c_busy(void){
	// Start Signal
	lock_detect=0;
	I2C0->C1 &= ~I2C_C1_IICEN_MASK;
	I2C_TRAN;
	I2C_M_START;
	I2C0->C1 |=  I2C_C1_IICEN_MASK;
	// Write to clear line
	I2C0->C1 |= I2C_C1_MST_MASK; /* set MASTER mode */
	I2C0->C1 |= I2C_C1_TX_MASK; /* Set transmit (TX) mode */
	I2C0->D = 0xFF;
	while ((I2C0->S & I2C_S_IICIF_MASK) == 0U)
	{
	} /* wait interrupt */
	I2C0->S |= I2C_S_IICIF_MASK; /* clear interrupt bit */


	/* Clear arbitration error flag*/
	I2C0->S |= I2C_S_ARBL_MASK;


	/* Send start */
	I2C0->C1 &= ~I2C_C1_IICEN_MASK;
	I2C0->C1 |= I2C_C1_TX_MASK; /* Set transmit (TX) mode */
	I2C0->C1 |= I2C_C1_MST_MASK; /* START signal generated */

	I2C0->C1 |= I2C_C1_IICEN_MASK;
	/*Wait until start is send*/

	/* Send stop */
	I2C0->C1 &= ~I2C_C1_IICEN_MASK;
	I2C0->C1 |= I2C_C1_MST_MASK;
	I2C0->C1 &= ~I2C_C1_MST_MASK; /* set SLAVE mode */
	I2C0->C1 &= ~I2C_C1_TX_MASK; /* Set Rx */
	I2C0->C1 |= I2C_C1_IICEN_MASK;


	/* wait */
	/* Clear arbitration error & interrupt flag*/
	I2C0->S |= I2C_S_IICIF_MASK;
	I2C0->S |= I2C_S_ARBL_MASK;
	lock_detect=0;
	i2c_lock=1;
}

/*******************************************************************************
* @Function Name: i2c_wait
* @Description: The function purpose is to release the bus in if an acknowledgment occurs
* is not received from the device under communication
* @input param : none
* @return: none
*******************************************************************************/
void i2c_wait(void) {
	lock_detect = 0;
	while(((I2C0->S & I2C_S_IICIF_MASK)==0) & (lock_detect < 200)) {
		lock_detect++;
	}
	if (lock_detect >= 200)
		i2c_busy();
	I2C0->S |= I2C_S_IICIF_MASK;
}

/*******************************************************************************
* @Function Name: i2c_start
* @Description: sends start bit
* @input param : none
* @return: none
*******************************************************************************/
void i2c_start()
{
	I2C_TRAN;							/*set to transmit mode */
	I2C_M_START;					/*send start	*/
}

/*******************************************************************************
* @Function Name : i2c_read_setup
* @Description : send device and register addresses
* @input param 1 : the device address
* @input param 2 : the address register of the device from where data is to be read
* @return : none
*******************************************************************************/
void i2c_read_setup(uint8_t dev, uint8_t address)
{
	I2C0->D = dev;			  /*send dev address	*/
	I2C_WAIT							/*wait for completion */

	I2C0->D =  address;		/*send read address	*/
	I2C_WAIT							/*wait for completion */

	I2C_M_RSTART;				   /*repeated start */
	I2C0->D = (dev|0x1);	 /*send dev address (read)	*/
	I2C_WAIT							 /*wait for completion */

	I2C_REC;						   /*set to receive mode */

}

/*******************************************************************************
* @Function Name : i2c_repeated_read
* @Description : read a byte and ack/nack as appropriate
* @input param 1 : the device address to be sent for communication set-up
* @return : the byte read
*******************************************************************************/
uint8_t i2c_repeated_read(uint8_t isLastRead)
{
	uint8_t data;

	lock_detect = 0;

	if(isLastRead)	{
		NACK;								/*set NACK after read	*/
	} else	{
		ACK;								/*ACK after read	*/
	}

	data = I2C0->D;				/*dummy read	*/
	I2C_WAIT							/*wait for completion */

	if(isLastRead)	{
		I2C_M_STOP;					/*send stop	*/
	}
	data = I2C0->D;				/*read data	*/

	return  data;
}

/*******************************************************************************
* @Function Name : i2c_read_byte
* @Description : this function is used for reading and writing a single byte
* using 7bit addressing and  reads a byte from device addressed
* @input param 1 : the device address
* @input param 2 : the address in the device from where the data has to be read
* @return : the byte read
*******************************************************************************/
uint8_t i2c_read_byte(uint8_t dev, uint8_t address)
{
	uint8_t data;

	I2C_TRAN;							/*set to transmit mode */
	I2C_M_START;					/*send start	*/
	I2C0->D = dev;			  /*send dev address	*/
	I2C_WAIT							/*wait for completion */

	I2C0->D =  address;		/*send read address	*/
	I2C_WAIT							/*wait for completion */

	I2C_M_RSTART;				   /*repeated start */
	I2C0->D = (dev|0x1);	 /*send dev address (read)	*/
	I2C_WAIT							 /*wait for completion */

	I2C_REC;						   /*set to recieve mode */
	NACK;									 /*set NACK after read	*/

	data = I2C0->D;					/*dummy read	*/
	I2C_WAIT								/*wait for completion */

	I2C_M_STOP;							/*send stop	*/
	data = I2C0->D;					/*read data	*/

	return data;
}

/*******************************************************************************
* @Function Name : i2c_write_byte
* @Description : this function uses 7bit addressing to write a byte data to
* device addressed
* @input param 1 : the device address
* @input param 2 : the address in the device from where the data has to be read
* @input param 3 : the data to be written to the device
* @return : the byte read
*******************************************************************************/
void i2c_write_byte(uint8_t dev, uint8_t address, uint8_t data)
{

	I2C_TRAN;							/*set to transmit mode */
	I2C_M_START;					/*send start	*/
	I2C0->D = dev;			  /*send dev address	*/
	I2C_WAIT						  /*wait for ack */

	I2C0->D =  address;		/*send write address	*/
	I2C_WAIT

	I2C0->D = data;				/*send data	*/
	I2C_WAIT
	I2C_M_STOP;

}
