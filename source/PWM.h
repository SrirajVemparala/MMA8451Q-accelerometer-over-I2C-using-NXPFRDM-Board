/******************************************************************************
* @file: PWM.c
*
* @brief: This files consists of the declarations to achieve PWM functionalities
*
* @author: Raghu Sai Phani Sriraj Vemparala
* @date:   9-DECEMBER-2022
* @references: dean book
*******************************************************************************/

#ifndef PWM_H_
#define PWM_H_

/***********************************************************************
 * Function Name: PWM_init
 * Use: PWM_init function is used to initialize PWM.
 * Return Type: void
 ***********************************************************************/
void PWM_init();

/***************************************************************************
 * Function Name: PWM_trigger
 * Use:Trigger PWM signal.
 * Return Type: void
 ***************************************************************************/
void PWM_trigger(int,int,int);

#endif /* PWM_H_ */
