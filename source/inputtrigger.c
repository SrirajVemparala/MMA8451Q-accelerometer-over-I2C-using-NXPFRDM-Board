/******************************************************************************
* @file: inputtrigger.c
*
* @brief: This files consists of the GPIO push button functionality
*
* @author: Raghu Sai Phani Sriraj Vemparala
* @date:  9-DECEMBER-2022
* @Reference: Dean text book
*******************************************************************************/

#include <MKL25Z4.h>

#define SW_POS 7
int gpio_trig_flag = 0;

//*****************Function Prototypes****************
/*******************************************************************************
* @Function Name: GPIO_PB_init
* @Description: GPIO push button is initialized
* @input param  : none
* @return: none
*******************************************************************************/
void GPIO_PB_init(void)
{

	/* Enable clock source to the pin */
		SIM->SCGC5 |= SIM_SCGC5_PORTD_MASK;

		/* Setting up port multiplexing for GPIO */
		PORTD->PCR[SW_POS] &= ~PORT_PCR_MUX_MASK;
		PORTD->PCR[SW_POS] |= PORT_PCR_MUX(1);

		/* Enable the pull select and pull enable */
		PORTD->PCR[SW_POS] |= PORT_PCR_PE(1) | PORT_PCR_PS(1);

		/* Enable the interrupt on any edge */
		PORTD->PCR[SW_POS] |= PORT_PCR_IRQC(11);

		/* Set direction to input */
		GPIOD->PDDR &= ~(1 << SW_POS);

		/* Set the priority of switch */
		NVIC_EnableIRQ(PORTD_IRQn);
}

/*******************************************************************************
* @Function Name: PORTD_IRQHandler
* @Description: Interrup for PortD input pin
* @input param  : none
* @return: none
*******************************************************************************/
void PORTD_IRQHandler(void)
{
	gpio_trig_flag = 0;

	if ((PORTD->ISFR & (1 << SW_POS)))
	{
		/* clearing on purpose to create a de-bounce condition */
		//gpio_trig_flag = 0;

		/* reading again to confirm that the
		 * switch was not pressed accidentally */
		if((1 << SW_POS)& (GPIOD->PDIR) == 0)
		{
			/* Set the switch flag as the
			 * switch is pressed in reality */
			gpio_trig_flag = 1;
		}
	}

	/* Clear the switch pin flag*/
	PORTD->ISFR |= (1 << SW_POS);
}
