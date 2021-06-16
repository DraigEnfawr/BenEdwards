/******************** (C) COPYRIGHT 2018-2019 University of South Wales *******************************
* File Name          : ISR.c
* Author             : SS
* Version            : V1.0.2
* Date               : 21-August-2019
* Description        : (User) Interrupt Service Routine Definitions
***************************************************************************************************
* THE PRESENT FIRMWARE WHICH IS FOR GUIDANCE ONLY AIMS AT PROVIDING STUDENTS
* WITH CODING INFORMATION REGARDING THEIR ASSIGNMENT IN ORDER FOR THEM DELIVER TO THE STANDARD.
* AS A RESULT, UNIVERSITY OF SOUTH WALES SHALL NOT BE HELD LIABLE FOR ANY DIRECT,
* INDIRECT OR CONSEQUENTIAL DAMAGES WITH RESPECT TO ANY CLAIMS ARISING FROM THE
* CONTENT OF SUCH FIRMWARE AND/OR THE USE MADE BY STUDENTS OF THE CODING
* INFORMATION CONTAINED HEREIN IN CONNECTION WITH THEIR PRODUCTS,PROJECT OR ASSIGNMENTS.
****************************************************************************************************/

#include "iodefine.h"
#include "typedefine.h"
#include "d_stop_watch.h"



extern clock_t countup_tim;			// temp timer structures for countup clock
extern clock_t countdown_tim;		// count down clock
extern clock_t chess_P_One_tim;		// chess player 1 clock
extern clock_t chess_P_two_tim;		// chess player 2 clock

unsigned int ms_count = 0;


unsigned char toggle_led = 0;



//******************************FLAGS**********************************************
unsigned char countup_flag = 0;		//initialise flag
//unsigned char Chess_Player_One = 0;	//initialise flag
//unsigned char Chess_Player_Two = 0;	//initialise flag
unsigned char countdown_flag = 0;
unsigned char alarm_flag = 0;
unsigned char chesscountdown_flag = 2;
//*********************************************************************************


/* External Interrupts */
#pragma interrupt (sw1_isr (vect = VECT(ICU, IRQ4)))	// Vector = 68
void sw1_isr (void)
{

}

#pragma interrupt (sw2_isr (vect = VECT(ICU, IRQ5)))    // Vector = 69
void sw2_isr (void)
{


}

#pragma interrupt (sw3_isr (vect = VECT(ICU, IRQ7)))    // Vector = 71
void sw3_isr (void)
{


}


/* TPU Timer Interrupts  */
#pragma interrupt (tpu0_isr (vect = VECT(TPU0, TGI0A)))   // Vector = 126
void tpu0_isr (void)
{


}

#pragma interrupt (tpu1_isr (vect = VECT(TPU1, TGI1A)))  // Vector = 130
void tpu1_isr (void)
{
	if (++ms_count>999)		//a count to create a delay that will count for 1 second and then continue the code
	{
		ms_count = 0;	// resets the count

		if (alarm_flag==1)	// will make the led alarm start to flash when the flag has been raised.
		{
			toggle_led =! toggle_led;
			PORTE.PODR.BYTE = toggle_led;
		}

		//*********************************COUNT DOWN CODE****************************************************
		if(countdown_flag==1)
						{
						 if(countdown_tim.sec==0)
						 {
							 countdown_tim.sec = 59;
							 if(countdown_tim.min==0)
							 {
								 countdown_tim.min = 59;
								 if(countdown_tim.hour==0)
								 {

									 //******************dont use this*********************
									 //countdown_tim.hour = 23;
									 //****************************************************

									 //YADA YADA FLASH ALARM CODE PUT HERE
									 PORTE.PODR.BYTE = toggle_led = 0;
									 countdown_flag =! countdown_flag;		//sets flag to logic 0 and stops the countdown
									 countdown_tim.min = 0;
									 countdown_tim.sec = 0;
									 alarm_flag =! alarm_flag;


								 }
								 else
								 {
									 countdown_tim.hour = countdown_tim.hour - 1;
								 }
							 }
							 else
							 {
								 countdown_tim.min = countdown_tim.min - 1;
							 }
						 }
						 else
						 {
							 countdown_tim.sec = countdown_tim.sec - 1;
				 	 	 }
						}




//****************************************COUNT UP CODE*********************************************************
		if(countup_flag==1)		// checks if flag has been raised
		{
		 if(countup_tim.sec>=59)	//checks if the time is 60 seconds
		 {
			 countup_tim.sec = 0;
			 if(countup_tim.min>=59)	//checks if the time is 60 minutes
			 {
				 countup_tim.min = 0;
				 if(countup_tim.hour>=23)	//checks if the time is 24 hours
				 {
					 countup_tim.hour = 0;
				 }
				 else
				 {
					 countup_tim.hour = countup_tim.hour + 1;
				 }
			 }
			 else
			 {
				countup_tim.min = countup_tim.min + 1;
			 }
		 }
		 else
		 {
			 countup_tim.sec = countup_tim.sec+1;
		 }
		}


	//*****************************************CHESS COUNT DOWN CODE*********************************************

		//PLAYER ONE SECTION
			if(chesscountdown_flag == 0 )	//checks if the flag is equal to 0 which is player 1
			{
				if(chess_P_One_tim.sec==0)
				{
					chess_P_One_tim.sec = 59;
					if(chess_P_One_tim.min==0)
					{
						chess_P_One_tim.min = 59;
						if(chess_P_One_tim.hour==0)
						{

							//FLASH ALARM CODE
							chess_P_One_tim.min = 0;		//resets the time to zero to stop 00:59:59 issue
							chess_P_One_tim.sec = 0;
							alarm_flag =! alarm_flag;		// triggers alarm flag
							chesscountdown_flag = 3;		//SETS THE FLAG TO A VALUE THAT WILL NOT TRIGGER EITHER PLAYERS

						}
						else
						{
							chess_P_One_tim.hour = chess_P_One_tim.hour - 1;
						}
					}
					else
					{
						chess_P_One_tim.min = chess_P_One_tim.min - 1;
					}
				}
				else
				{
					chess_P_One_tim.sec = chess_P_One_tim.sec - 1;
				}
			}

			//PLAYER 2 SECTION
			else if(chesscountdown_flag == 1 )	//checks if the flag is equal to 0 which is player 1
			{
				 if(chess_P_two_tim.sec==0)
				 {
					 chess_P_two_tim.sec = 59;
					 if(chess_P_two_tim.min==0)
					 {
						 chess_P_two_tim.min = 59;
						 if(chess_P_two_tim.hour==0)
						 {
							 //FLASH ALARM CODE
							 chess_P_two_tim.min = 0;		//resets the time to zero to stop 00:59:59 issue
							 chess_P_two_tim.sec = 0;
							 alarm_flag =! alarm_flag;		// triggers alarm flag
							 chesscountdown_flag = 3;		//SETS THE FLAG TO A VALUE THAT WILL NOT TRIGGER EITHER PLAYERS
						 }
						 else
						 {
							 chess_P_two_tim.hour = chess_P_two_tim.hour - 1;
						 }
					 }
					 else
					 {
						 chess_P_two_tim.min = chess_P_two_tim.min - 1;
					 }
				 }
				 else
				 {
					 chess_P_two_tim.sec = chess_P_two_tim.sec - 1;
				 }
			}
	}
}

#pragma interrupt (tpu2_isr (vect = VECT(TPU2, TGI2A)))  // Vector = 132
void tpu2_isr (void)
{

}

#pragma interrupt (tpu3_isr (vect = VECT(TPU3, TGI3A)))  // Vector = 134
void tpu3_isr (void)
{


}


#pragma interrupt (tpu4_isr (vect = VECT(TPU4, TGI4A)))  // Vector = 138
void tpu4_isr (void)
{


}


#pragma interrupt (tpu5_isr (vect = VECT(TPU5, TGI5A)))  // Vector = 140
void tpu5_isr (void)
{


}

/*ADC Interrupts */

/* 12 bit ADC */
#pragma interrupt (sa12ad0_isr (vect = VECT(S12AD0, S12ADI0)))  // Vector = 102
void sa12ad0_isr (void)
{


}


#pragma interrupt (adi0_isr (vect = VECT(AD0, ADI0)))   // Vector = 98
void adi0_isr (void)
{


}

