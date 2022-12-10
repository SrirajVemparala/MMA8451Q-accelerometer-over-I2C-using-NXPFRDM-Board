/******************************************************************************
* @file: PWM.c
*
* @brief: This files consists of the declarations to achieve PWM functionalities
*
* @author: Raghu Sai Phani Sriraj Vemparala
* @date:   9-DECEMBER-2022
* @references: dean book
*******************************************************************************/

/*******************************************************************************
Header files
*******************************************************************************/
#include <MKL25Z4.H>

/*******************************************************************************
 Macros
*******************************************************************************/
#define RED_LED	18
#define GREEN_LED 19
#define BLUE_LED 1

/***********************************************************************
 * Function Name: PWM_init
 * Use: PWM_init function is used to initialize PWM.
 * Return Type: void
 ***********************************************************************/
void PWM_init()
{
	SIM->SCGC5 |= SIM_SCGC5_PORTD_MASK;// Enable clock for port D
	SIM->SCGC5 |= SIM_SCGC5_PORTB_MASK;// Enable clock for port B
	SIM->SCGC6 |= SIM_SCGC6_TPM0_MASK;// Enable clock for TPM0
	SIM->SCGC6 |= SIM_SCGC6_TPM2_MASK;// Enable clock for TPM2
	PORTB->PCR [RED_LED] &=~PORT_PCR_MUX_MASK;
	PORTB->PCR [RED_LED]|=PORT_PCR_MUX(3);//Setting pin to Alternate function 3
	PORTB->PCR [GREEN_LED] &=~PORT_PCR_MUX_MASK;
	PORTB->PCR [GREEN_LED]|=PORT_PCR_MUX(3);
	PORTD->PCR [BLUE_LED] &=~PORT_PCR_MUX_MASK;
	PORTD->PCR [BLUE_LED]|=PORT_PCR_MUX(4);//Set Pin 1 of port D as Alternate function
	SIM->SOPT2 |= (SIM_SOPT2_TPMSRC (1) | SIM_SOPT2_PLLFLLSEL_MASK);
	TPM2->MOD=480000;
	TPM0->MOD=480000;
	TPM2->SC= TPM_SC_PS(1);
	TPM0->SC= TPM_SC_PS(1);
	TPM2->CONF|=TPM_CONF_DBGMODE(3);
	TPM0->CONF|=TPM_CONF_DBGMODE(3);
	TPM2->CONTROLS[0]. CnSC= TPM_CnSC_MSB_MASK | TPM_CnSC_ELSA_MASK;
	TPM2->CONTROLS [0].CnV=0;
	TPM2->CONTROLS[1]. CnSC= TPM_CnSC_MSB_MASK | TPM_CnSC_ELSA_MASK;
	TPM2->CONTROLS [1].CnV=0;
	TPM0->CONTROLS[1]. CnSC= TPM_CnSC_MSB_MASK | TPM_CnSC_ELSA_MASK;
	TPM0->CONTROLS [1].CnV=0;
	TPM2->SC |=TPM_SC_CMOD(1);
	TPM0->SC |=TPM_SC_CMOD(1);
}

/***************************************************************************
 * Function Name: PWM_trigger
 * Use:Trigger PWM signal.
 * Return Type: void
 ***************************************************************************/
void PWM_trigger(int redintensity, int blueintensity, int greenintensity)
{
	TPM2->CONTROLS[0].CnV  = redintensity;
	TPM2->CONTROLS[1].CnV  = blueintensity;
	TPM0->CONTROLS[1].CnV  = greenintensity;
}
