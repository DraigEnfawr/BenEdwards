/******************** (C) COPYRIGHT 2018-2019 University of South Wales *******************************
* File Name          : d_stop_watch.c
* Author             : SS
* Version            : V1.0.1
* Date               : 18-September-2019
* Description        : NG2S901 Assignment Template (Digital Stop Watch)
***************************************************************************************************
* THE PRESENT FIRMWARE WHICH IS FOR GUIDANCE ONLY AIMS AT PROVIDING STUDENTS
* WITH CODING INFORMATION REGARDING THEIR ASSIGNMENT IN ORDER FOR THEM DELIVER TO THE STANDARD.
* AS A RESULT, UNIVERSITY OF SOUTH WALES SHALL NOT BE HELD LIABLE FOR ANY DIRECT,
* INDIRECT OR CONSEQUENTIAL DAMAGES WITH RESPECT TO ANY CLAIMS ARISING FROM THE
* CONTENT OF SUCH FIRMWARE AND/OR THE USE MADE BY STUDENTS OF THE CODING
* INFORMATION CONTAINED HEREIN IN CONNECTION WITH THEIR PRODUCTS,PROJECT OR ASSIGNMENTS.
****************************************************************************************************/

#include "rx_glcd.h"	// include GLCD
#include "font.h"
#include "rx_keyscan_4x4.h"
#include "d_stop_watch.h"


extern FONT_DEF Font_System3x6;		
extern FONT_DEF Font_System5x8; 
extern FONT_DEF Font_System7x8;





estate state; 		// state variable deceleration

clock_t tmp_tim;			// temp timer structure
clock_t countup_tim;			// temp timer structure
clock_t countdown_tim;			//temp timer structure count down
clock_t chess_P_One_tim;				//temp chess timer for player one
clock_t chess_P_two_tim;				//temp chess timer for player two

//****************************a collection of strings that can be displayed on the lcd screen******************************************
unsigned char main_menu_1[]="Digital Stop Watch";	// create and initialise array of string
unsigned char main_menu_2[]="press 1 to continue";	// instruction for the user
unsigned char adding[]="press 1 to add";
unsigned char subbing[]="press 3 to subtract";
unsigned char settimeing[]="press 2 to set time";
unsigned char play[]="Play!";
unsigned char time[]="Time set";
unsigned char resetingbutton[]="press 3 to reset";

//*****************Titles of Functions*******************
unsigned char count_down_menu[]="Count Down";
unsigned char count_up_menu[]="Count Up";
unsigned char ches_clk_menu[]="Chess Clock";
//*******************************************************
//*******************the time display and the display of the time set functions***********************
unsigned char clock_dsp[] = "00:00:00";
unsigned char clock_dsptwo[] ="00:00:00";

unsigned char count_down_setH[]="set Hour";
unsigned char count_down_setM[]="set Min";
unsigned char count_down_setS[]="set Sec";

//****************************************************************************************************
//*******************The start and stop messages********************
unsigned char start_message[] = "Start!";
unsigned char stop_message[] = "Stop!";
extern unsigned char Ptwo_win[] = "Player 2 Wins";
extern unsigned char Pone_win[] = "Player 1 Wins";
unsigned char Ptwo_turn[] = "Player 2 turn";
unsigned char Pone_turn[] = "Player 1 turn";
//******************************************************************

unsigned char Player_One[]="Player 1";
unsigned char Player_Two[]="Player 2";
unsigned char Player_Num[]="Player number displayed here";

extern unsigned char countup_flag;			// a flag to start the count up time
extern unsigned char countdown_flag;		// a flag to start the count down time
extern unsigned char chesscountdown_flag;	//a flag to start the count down on the chess clock
extern unsigned char alarm_flag;			// a flag for when the count down alarm goes off


//**********************flags trigger certain code.*************************
//char cnt_down_timer_flag = 0;
//char cnt_up_timer_flag = 0;
//char chess_clock_timer_flag = 0;

char key;	// used to hold the button number pressed.



/* Digital stop watch initialisation */

void d_stop_watch_Init (void)
{

	/* Initialise Graphic Display */
	
	GLCD_Initialise();		// Hardware configuration for GLCD
	GLCD_ClearScreen();	// clear the GLCD
	
	keyscan_4x4_init();	// initialise key pad

//	GLCD_GoTo(0,2);
//	GLCD_WriteString(main_menu_1,Font_System5x8);		// display title
//
//	GLCD_GoTo(0,4);
//	GLCD_WriteString(clock_dsp,Font_System5x8);		// user instruction
//
//	GLCD_GoTo(0,6);
//	GLCD_WriteString(main_menu_2,Font_System5x8);		// user instruction

	/* state initialisation */
	state = menu; 
	
	/* Timer Variable Init */
	//******COUNT UP TIME******
	countup_tim.hour = 0;
	countup_tim.min = 0;
	countup_tim.sec = 0;

	//******COUNT DOWN TIME*******
	countdown_tim.hour = 0;
	countdown_tim.min = 0;
	countdown_tim.sec = 0;

	//******TEMPORARY TIME*******
	tmp_tim.hour = 0;
	tmp_tim.min = 0;
	tmp_tim.sec = 0;

	//*******PLAYER 1 TIME*******
	chess_P_One_tim.hour = 0;
	chess_P_One_tim.min = 0;
	chess_P_One_tim.sec = 0;

	//*******PLAYER 2 TIME*******
	chess_P_two_tim.hour = 0;
	chess_P_two_tim.min = 0;
	chess_P_two_tim.sec = 0;
	//###########################################################

	/* IO port configuration */
	//INITIALISE THE ALARM LED BIT TO AN OUTPUT.
	PORTE.PDR.BYTE = 0xFF;
	
	//###########################################################
	
	/* Timer Configurations */
	SYSTEM.PRCR.WORD = 0xA50B; /* Protect off */
	MPC.PWPR.BIT.B0WI = 0 ;     		/* Unlock protection register */
	MPC.PWPR.BIT.PFSWE = 1 ;    		/* Unlock MPC registers */

	MSTP(TPU1) = 0;      /* Cancel TPU peripheral stop state. */

	/* Timer Control Register (TCR)
	b7:b5   CCLR: Counter Clear Source 1 = TCNT cleared by TGRA
	b4:b3   CKEG: Clock Edge           2 = count at rising edge
	b2:b0   TPSC: Time Prescaler       3 = PCLK/64 */
	TPU1.TCR.BYTE=0x2B;	// PCLK/64,rising edge,count cleared by TGRA looked it up in the manual

		 /* Timer Mode Register (TMDR)
	b6      BFE - TPUm.TGRE operates normally
	b5      BFB - TPUm.TGRB operates normally
	b4      BFA - TPUm.TGRA operates normally
	b3:b0   MD - Normal operation 			*/
	TPU1.TMDR.BYTE=0x00;	// normal operation

		/* Timer I/O Control Register (TIOR)
	b7:b4   IOB - Output compare, output disabled
	b3:b0   IOA - Output compare, output disabled
	*/
	TPU1.TIOR.BYTE=0x00;	// Output disable

	/* Timer Interrupt Enable Register*/
	TPU1.TIER.BYTE=0x01;	// TGRA Interrupt enabled

	/*Prescaler Reload for TGRA */
	TPU1.TGRA= 749;		// generate 1ms interrupt

	TPU1.TCNT=0x0000;

	IR (TPU1, TGI1A);     /* interrupt reset */
	IPR(TPU1, TGI1A) = 3; /* interrupt priority set */
	IEN(TPU1, TGI1A) = 1; /* interrupt enable */

	//starts the tpu1 timer
	TPUA.TSTR.BIT.CST1 = 1;		// start TPU1 timer

	MPC.PWPR.BIT.B0WI = 1 ;     		/* lock protection register */
	MPC.PWPR.BIT.PFSWE = 0 ;    		/* lock MPC registers */
	SYSTEM.PRCR.WORD = 0xA500; /* Protect on */

}

//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//***********************************************MAIN BLOCK OF CODE*****************************************************
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
void d_stop_watch_process (void)
{
	
		
	
		switch(state)
		{
			case menu:			// main menu
				clock_dsp[7] = countup_tim.sec%10+48;	// convert second to ASCII(ones)
				clock_dsp[6] = countup_tim.sec/10+48;   // convert second to ASCII (tens)

				clock_dsp[4] = countup_tim.min%10+48;	// convert min to ASCII(ones)
				clock_dsp[3] = countup_tim.min/10+48;   // convert min to ASCII (tens)

				clock_dsp[1] = countup_tim.hour%10+48;	// convert hour to ASCII(ones)
				clock_dsp[0] = countup_tim.hour/10+48;   // convert hour to ASCII (tens)


				/* display String 'clock_dsp'*/
				GLCD_GoTo(0,2);
				GLCD_WriteString(main_menu_1,Font_System5x8);		// display title

				GLCD_GoTo(0,6);
				GLCD_WriteString(main_menu_2,Font_System5x8);		// user instruction

				/* get key commands from the key pad */
				key  = getcommand();
				switch (key)
				{
					case '1':	// '1' is pressed
					state = cnt_dwn;
					GLCD_ClearScreen();	// clear the GLCD
					GLCD_GoTo(0,2);
					GLCD_WriteString(count_down_menu,Font_System5x8);		// display Count Down Menu
					GLCD_GoTo(0,6);
					GLCD_WriteString(main_menu_2,Font_System5x8);		// user instruction

						break;
					case '2':	// '2' is pressed
						break;
					case '3':	// '3' is pressed
						break;

					default:
						break;
				}

			
			break;
			
			//***************************************************************************
			//*********************Count down Timer**************************************
			//***************************************************************************
			case cnt_dwn:		// count down timer
				clock_dsp[7] = countdown_tim.sec%10+48;	// convert second to ASCII(ones)
				clock_dsp[6] = countdown_tim.sec/10+48;   // convert second to ASCII (tens)

				clock_dsp[4] = countdown_tim.min%10+48;	// convert second to ASCII(ones)
				clock_dsp[3] = countdown_tim.min/10+48;   // convert second to ASCII (tens)

				clock_dsp[1] = countdown_tim.hour%10+48;	// convert second to ASCII(ones)
				clock_dsp[0] = countdown_tim.hour/10+48;   // convert second to ASCII (tens)

				if (countdown_flag == 0)	//checks if the count down flag is equal to 0
				{

					GLCD_GoTo(0,5);				//goes to the 0,6 position on the LCD
					GLCD_WriteString(stop_message,Font_System5x8);		// displays a stop message

				}



				GLCD_GoTo(0,2);
				GLCD_WriteString(count_down_menu,Font_System5x8);		// display Count Down Menu


				GLCD_GoTo(0,4);
				GLCD_WriteString(clock_dsp,Font_System5x8);		//displays the clock on line 4

				GLCD_GoTo(0,6);
				GLCD_WriteString(settimeing,Font_System5x8);		// user instruction

				key  = getcommand();


				switch (key)
				{
					case '1':
					state = cnt_up;
					GLCD_ClearScreen();	// clear the GLCD
					GLCD_GoTo(0,2);
					GLCD_WriteString(count_up_menu,Font_System5x8);		// display Count Down Menu
					GLCD_GoTo(0,6);
					GLCD_WriteString(main_menu_2,Font_System5x8);		// user instruction
						break;
					case '2':
						state = cnt_dwn_setH;
						GLCD_ClearScreen();	// clear the GLCD



						break;
					case '3':
						countdown_tim.sec=0;	//reset count up timer
						countdown_tim.min=0;
						countdown_tim.hour=0;
						break;

					default:
						break;
				}
			
			break;
			//***************************************************************************
			//*****************************Stop watch************************************
			//***************************************************************************
			case cnt_dwn_setH:	// count down set hour
				clock_dsp[7] = countdown_tim.sec%10+48;	// convert second to ASCII(ones)
				clock_dsp[6] = countdown_tim.sec/10+48;   // convert second to ASCII (tens)

				clock_dsp[4] = countdown_tim.min%10+48;	// convert second to ASCII(ones)
				clock_dsp[3] = countdown_tim.min/10+48;   // convert second to ASCII (tens)

				clock_dsp[1] = countdown_tim.hour%10+48;	// convert second to ASCII(ones)
				clock_dsp[0] = countdown_tim.hour/10+48;   // convert second to ASCII (tens)

				GLCD_GoTo(0,2);
				GLCD_WriteString(count_down_setH,Font_System5x8);		// display Count Down Menu

				GLCD_GoTo(0,4);
				GLCD_WriteString(clock_dsp,Font_System5x8);

				GLCD_GoTo(0,5);
				GLCD_WriteString(adding,Font_System5x8);
				GLCD_GoTo(0,6);
				GLCD_WriteString(subbing,Font_System5x8);

				key  = getcommand();
				switch (key)
				{
					case '1':
						countdown_tim.hour++;
						if (countdown_tim.hour>23)
						{
							countdown_tim.hour=0;
						}

						break;
					case '2':
						state = cnt_dwn_setM;
						GLCD_ClearScreen();	// clear the GLCD

						break;
					case '3':
						countdown_tim.hour--;		//takes away 1 from the hour value
						if (countdown_tim.hour <= 0)
						{
							countdown_tim.hour = 23;
						}

						break;
				}
			
			break;
			//**************************************************************************
			case cnt_dwn_setM:	// count down set minute
				clock_dsp[7] = countup_tim.sec%10+48;	// convert second to ASCII(ones)
								clock_dsp[6] = countdown_tim.sec/10+48;   // convert second to ASCII (tens)

								clock_dsp[4] = countdown_tim.min%10+48;	// convert second to ASCII(ones)
								clock_dsp[3] = countdown_tim.min/10+48;   // convert second to ASCII (tens)

								clock_dsp[1] = countdown_tim.hour%10+48;	// convert second to ASCII(ones)
								clock_dsp[0] = countdown_tim.hour/10+48;   // convert second to ASCII (tens)

								GLCD_GoTo(0,2);
								GLCD_WriteString(count_down_setM,Font_System5x8);		// display Count Down Menu

								GLCD_GoTo(0,4);
								GLCD_WriteString(clock_dsp,Font_System5x8);

								GLCD_GoTo(0,5);
								GLCD_WriteString(adding,Font_System5x8);
								GLCD_GoTo(0,6);
								GLCD_WriteString(subbing,Font_System5x8);

								key  = getcommand();

								switch (key)
								{
									case '1':
										// adds 1 to the minute value for countdown_tim and resets it back to 0 if the number exceeds 59
										countdown_tim.min++;
												if (countdown_tim.min>59)
												{
													countdown_tim.min=0;
												}
										break;
									case '2':
										state = cnt_dwn_setS;
										GLCD_ClearScreen();	// clear the GLCD

										break;
									case '3':
										countdown_tim.min--;		//takes away 1 from the min value
										if (countdown_tim.min <= 0)
										{
											countdown_tim.min = 59;
										}

										break;
								}

			break;
			//**************************************************************************
			case cnt_dwn_setS:	// count down set second
				clock_dsp[7] = countdown_tim.sec%10+48;	// convert second to ASCII(ones)
				clock_dsp[6] = countdown_tim.sec/10+48;   // convert second to ASCII (tens)

				clock_dsp[4] = countdown_tim.min%10+48;	// convert second to ASCII(ones)
				clock_dsp[3] = countdown_tim.min/10+48;   // convert second to ASCII (tens)

				clock_dsp[1] = countdown_tim.hour%10+48;	// convert second to ASCII(ones)
				clock_dsp[0] = countdown_tim.hour/10+48;   // convert second to ASCII (tens)

				GLCD_GoTo(0,2);
				GLCD_WriteString(count_down_setS,Font_System5x8);		// display Count Down Menu

				GLCD_GoTo(0,4);
				GLCD_WriteString(clock_dsp,Font_System5x8);

				GLCD_GoTo(0,5);
				GLCD_WriteString(adding,Font_System5x8);
				GLCD_GoTo(0,6);
				GLCD_WriteString(subbing,Font_System5x8);

				key  = getcommand();



				switch (key)
				{
					case '1':
						countdown_tim.sec++;
							if (countdown_tim.sec>59)
							{
								countdown_tim.sec=0;
							}
						break;
					case '2':
						GLCD_ClearScreen();	// clear the GLCD
						state = cnt_dwn;
						GLCD_GoTo(0,6);
						GLCD_WriteString(start_message,Font_System5x8);		// user instruction
						countdown_flag =! countdown_flag;	//triggers flag


						break;
					case '3':
						countdown_tim.sec--;		//takes away 1 from the second value
						if (countdown_tim.sec <= 0)
						{
							countdown_tim.sec = 59;
						}

						break;
				}
			
			break;
			

			//***************************************************************************
			//************************count up timer*************************************
			//***************************************************************************
			case cnt_up:	// count up timer
				clock_dsp[7] = countup_tim.sec%10+48;	// convert second to ASCII(ones)
				clock_dsp[6] = countup_tim.sec/10+48;   // convert second to ASCII (tens)

				clock_dsp[4] = countup_tim.min%10+48;	// convert second to ASCII(ones)
				clock_dsp[3] = countup_tim.min/10+48;   // convert second to ASCII (tens)

				clock_dsp[1] = countup_tim.hour%10+48;	// convert second to ASCII(ones)
				clock_dsp[0] = countup_tim.hour/10+48;   // convert second to ASCII (tens)

				/* display String 'clock_dsp'*/
				GLCD_GoTo(0,4);
				GLCD_WriteString(clock_dsp,Font_System5x8);		// user instruction

				key  = getcommand();
				switch (key)
				{
					case '1':
					state = ches_clk;
					GLCD_ClearScreen();	// clear the GLCD
					GLCD_GoTo(0,2);
					GLCD_WriteString(ches_clk_menu,Font_System5x8);		// display Count Down Menu
					GLCD_GoTo(0,6);
					GLCD_WriteString(main_menu_2,Font_System5x8);		// user instruction
						break;
					case '2':
						countup_flag =!countup_flag;

						break;

					case '3':
						countup_tim.sec=0;	//reset counter up timer
						countup_tim.min=0;
						countup_tim.hour=0;

						break;

					default:
						break;
				}
			
			break;
			
			//***************************************************************************
			//**************************Chess clock**************************************
			//***************************************************************************
			case ches_clk:		// chess clock 
				clock_dsp[7] = chess_P_One_tim.sec%10+48;	// convert second to ASCII(ones)
				clock_dsp[6] = chess_P_One_tim.sec/10+48;   // convert second to ASCII (tens)

				clock_dsp[4] = chess_P_One_tim.min%10+48;	// convert second to ASCII(ones)
				clock_dsp[3] = chess_P_One_tim.min/10+48;   // convert second to ASCII (tens)

				clock_dsp[1] = chess_P_One_tim.hour%10+48;	// convert second to ASCII(ones)
				clock_dsp[0] = chess_P_One_tim.hour/10+48;   // convert second to ASCII (tens)

				clock_dsptwo[7] = chess_P_two_tim.sec%10+48;	// convert second to ASCII(ones)
				clock_dsptwo[6] = chess_P_two_tim.sec/10+48;   // convert second to ASCII (tens)

				clock_dsptwo[4] = chess_P_two_tim.min%10+48;	// convert second to ASCII(ones)
				clock_dsptwo[3] = chess_P_two_tim.min/10+48;   // convert second to ASCII (tens)

				clock_dsptwo[1] = chess_P_two_tim.hour%10+48;	// convert second to ASCII(ones)
				clock_dsptwo[0] = chess_P_two_tim.hour/10+48;   // convert second to ASCII (tens)


				GLCD_GoTo(0,4);
				GLCD_WriteString(clock_dsp,Font_System5x8);		// clock display
				GLCD_GoTo(60,4);
				GLCD_WriteString(clock_dsptwo,Font_System5x8);		// clock display
				GLCD_GoTo(0,5);
				GLCD_WriteString(Player_One,Font_System5x8);		// player number display
				GLCD_GoTo(60,5);
				GLCD_WriteString(Player_Two,Font_System5x8);		// player number display

				GLCD_GoTo(0,6);
				GLCD_WriteString(settimeing,Font_System5x8);		// user instruction

				key  = getcommand();
				switch (key)
				{
					case '1':
					state = menu;
					GLCD_ClearScreen();	// clear the GLCD
					GLCD_GoTo(0,2);
					GLCD_WriteString(main_menu_1,Font_System5x8);		// display Count Down Menu
					GLCD_GoTo(0,6);
					GLCD_WriteString(main_menu_2,Font_System5x8);		// user instruction
						break;
					case '2':
						state = ches_clk_setH;
						GLCD_ClearScreen();	// clear the GLCD
						GLCD_GoTo(0,2);
						GLCD_WriteString(count_down_setH,Font_System5x8);		// display Count Down Menu



						break;
					case '3':

						break;

					default:
						break;
				}

			
			break;
			
			case ches_clk_setH:	// chess clock set hour
				clock_dsp[7] = chess_P_One_tim.sec%10+48;	// convert second to ASCII(ones)
				clock_dsp[6] = chess_P_One_tim.sec/10+48;   // convert second to ASCII (tens)

				clock_dsp[4] = chess_P_One_tim.min%10+48;	// convert second to ASCII(ones)
				clock_dsp[3] = chess_P_One_tim.min/10+48;   // convert second to ASCII (tens)

				clock_dsp[1] = chess_P_One_tim.hour%10+48;	// convert second to ASCII(ones)
				clock_dsp[0] = chess_P_One_tim.hour/10+48;   // convert second to ASCII (tens)

				clock_dsptwo[7] = chess_P_two_tim.sec%10+48;	// convert second to ASCII(ones)
				clock_dsptwo[6] = chess_P_two_tim.sec/10+48;   // convert second to ASCII (tens)

				clock_dsptwo[4] = chess_P_two_tim.min%10+48;	// convert second to ASCII(ones)
				clock_dsptwo[3] = chess_P_two_tim.min/10+48;   // convert second to ASCII (tens)

				clock_dsptwo[1] = chess_P_two_tim.hour%10+48;	// convert second to ASCII(ones)
				clock_dsptwo[0] = chess_P_two_tim.hour/10+48;   // convert second to ASCII (tens)

				GLCD_GoTo(0,2);
				GLCD_WriteString(count_down_setH,Font_System5x8);
				//#######################################################################################
				GLCD_GoTo(0,4);
				GLCD_WriteString(clock_dsp,Font_System5x8);		// clock display player 1
				GLCD_GoTo(60,4);
				GLCD_WriteString(time,Font_System5x8);		// clock display player 2
				GLCD_GoTo(0,5);
				GLCD_WriteString(adding,Font_System5x8);
				GLCD_GoTo(0,6);
				GLCD_WriteString(subbing,Font_System5x8);
				//#######################################################################################
				key  = getcommand();
				switch (key)
				{
					case '1':
						chess_P_One_tim.hour++;
						chess_P_two_tim.hour++;
						if (chess_P_One_tim.hour>23)
						{
							chess_P_One_tim.hour=0;
							chess_P_two_tim.hour=0;
						}

						break;
					case '2':
						state = ches_clk_setM;
						GLCD_ClearScreen();	// clear the GLCD

						break;
					case '3':

						//takes away 1 from the hour value
						chess_P_One_tim.hour--;
						chess_P_two_tim.hour--;

						if (chess_P_One_tim.hour <= 0)
						{
							chess_P_One_tim.hour = 23;
							chess_P_two_tim.hour = 23;
						}

						break;
				}
			break;
			
			case ches_clk_setM:	// chess clock set minute

				clock_dsp[7] = chess_P_One_tim.sec%10+48;	// convert second to ASCII(ones)
				clock_dsp[6] = chess_P_One_tim.sec/10+48;   // convert second to ASCII (tens)

				clock_dsp[4] = chess_P_One_tim.min%10+48;	// convert second to ASCII(ones)
				clock_dsp[3] = chess_P_One_tim.min/10+48;   // convert second to ASCII (tens)

				clock_dsp[1] = chess_P_One_tim.hour%10+48;	// convert second to ASCII(ones)
				clock_dsp[0] = chess_P_One_tim.hour/10+48;   // convert second to ASCII (tens)

				clock_dsptwo[7] = chess_P_two_tim.sec%10+48;	// convert second to ASCII(ones)
				clock_dsptwo[6] = chess_P_two_tim.sec/10+48;   // convert second to ASCII (tens)

				clock_dsptwo[4] = chess_P_two_tim.min%10+48;	// convert second to ASCII(ones)
				clock_dsptwo[3] = chess_P_two_tim.min/10+48;   // convert second to ASCII (tens)

				clock_dsptwo[1] = chess_P_two_tim.hour%10+48;	// convert second to ASCII(ones)
				clock_dsptwo[0] = chess_P_two_tim.hour/10+48;   // convert second to ASCII (tens)

				GLCD_GoTo(0,2);
				GLCD_WriteString(count_down_setM,Font_System5x8);
				//#######################################################################################
				GLCD_GoTo(0,4);
				GLCD_WriteString(clock_dsp,Font_System5x8);		// clock display player 1
				GLCD_GoTo(60,4);
				GLCD_WriteString(time,Font_System5x8);		// clock display player 2
				GLCD_GoTo(0,5);
				GLCD_WriteString(adding,Font_System5x8);
				GLCD_GoTo(0,6);
				GLCD_WriteString(subbing,Font_System5x8);
				//#######################################################################################
				key  = getcommand();
				switch (key)
				{
					case '1':
						chess_P_One_tim.min++;
						chess_P_two_tim.min++;
						if (chess_P_One_tim.min>59)
						{
							chess_P_One_tim.min=0;
							chess_P_two_tim.min=0;
						}

						break;
					case '2':
						state = ches_clk_setS;
						GLCD_ClearScreen();	// clear the GLCD

						break;
					case '3':
						//takes away 1 from the hour value
						chess_P_One_tim.min--;
						chess_P_two_tim.min--;

						if (chess_P_One_tim.min <= 0)
						{
							chess_P_One_tim.min = 59;
							chess_P_two_tim.min = 59;
						}

				}
						break;
			
			break;
			
			
			case ches_clk_setS:	// chess clock set second

				clock_dsp[7] = chess_P_One_tim.sec%10+48;	// convert second to ASCII(ones)
				clock_dsp[6] = chess_P_One_tim.sec/10+48;   // convert second to ASCII (tens)

				clock_dsp[4] = chess_P_One_tim.min%10+48;	// convert second to ASCII(ones)
				clock_dsp[3] = chess_P_One_tim.min/10+48;   // convert second to ASCII (tens)

				clock_dsp[1] = chess_P_One_tim.hour%10+48;	// convert second to ASCII(ones)
				clock_dsp[0] = chess_P_One_tim.hour/10+48;   // convert second to ASCII (tens)

				clock_dsptwo[7] = chess_P_two_tim.sec%10+48;	// convert second to ASCII(ones)
				clock_dsptwo[6] = chess_P_two_tim.sec/10+48;   // convert second to ASCII (tens)

				clock_dsptwo[4] = chess_P_two_tim.min%10+48;	// convert second to ASCII(ones)
				clock_dsptwo[3] = chess_P_two_tim.min/10+48;   // convert second to ASCII (tens)

				clock_dsptwo[1] = chess_P_two_tim.hour%10+48;	// convert second to ASCII(ones)
				clock_dsptwo[0] = chess_P_two_tim.hour/10+48;   // convert second to ASCII (tens)

				GLCD_GoTo(0,2);
				GLCD_WriteString(count_down_setS,Font_System5x8);
				//#######################################################################################
				GLCD_GoTo(0,4);
				GLCD_WriteString(clock_dsp,Font_System5x8);		// clock display player 1
				GLCD_GoTo(60,4);
				GLCD_WriteString(time,Font_System5x8);		// clock display player 2
				GLCD_GoTo(0,5);
				GLCD_WriteString(adding,Font_System5x8);
				GLCD_GoTo(0,6);
				GLCD_WriteString(subbing,Font_System5x8);
				//#######################################################################################
				key  = getcommand();
				switch (key)
				{
					case '1':
						chess_P_One_tim.sec++;
						chess_P_two_tim.sec++;
						if (chess_P_One_tim.sec>59)
						{
							chess_P_One_tim.sec=0;
							chess_P_two_tim.sec=0;
						}

						break;
					case '2':
						state = ches_clk_p1p2_run;
						GLCD_ClearScreen();	// clear the GLCD
						chesscountdown_flag = 0;

						break;
					case '3':
						//takes away 1 from the hour value
						chess_P_One_tim.sec--;
						chess_P_two_tim.sec--;

						if (chess_P_One_tim.sec <= 0)
						{
							chess_P_One_tim.sec = 59;
							chess_P_two_tim.sec = 59;
						}

				}
						break;
			
			break;
			
			case ches_clk_p1p2_run:	// chess clock switch player

				clock_dsp[7] = chess_P_One_tim.sec%10+48;	// convert second to ASCII(ones)
				clock_dsp[6] = chess_P_One_tim.sec/10+48;   // convert second to ASCII (tens)

				clock_dsp[4] = chess_P_One_tim.min%10+48;	// convert second to ASCII(ones)
				clock_dsp[3] = chess_P_One_tim.min/10+48;   // convert second to ASCII (tens)

				clock_dsp[1] = chess_P_One_tim.hour%10+48;	// convert second to ASCII(ones)
				clock_dsp[0] = chess_P_One_tim.hour/10+48;   // convert second to ASCII (tens)

				clock_dsptwo[7] = chess_P_two_tim.sec%10+48;	// convert second to ASCII(ones)
				clock_dsptwo[6] = chess_P_two_tim.sec/10+48;   // convert second to ASCII (tens)

				clock_dsptwo[4] = chess_P_two_tim.min%10+48;	// convert second to ASCII(ones)
				clock_dsptwo[3] = chess_P_two_tim.min/10+48;   // convert second to ASCII (tens)

				clock_dsptwo[1] = chess_P_two_tim.hour%10+48;	// convert second to ASCII(ones)
				clock_dsptwo[0] = chess_P_two_tim.hour/10+48;   // convert second to ASCII (tens)


				//#######################################################################################
				GLCD_ClearScreen();	// clear the GLCD
				GLCD_GoTo(0,4);
				GLCD_WriteString(clock_dsp,Font_System5x8);		// clock display player 1
				GLCD_GoTo(60,4);
				GLCD_WriteString(clock_dsptwo,Font_System5x8);		// clock display player 2
				GLCD_GoTo(0,5);
				GLCD_WriteString(Player_One,Font_System5x8);		// player 1 name tag
				GLCD_GoTo(60,5);
				GLCD_WriteString(Player_Two,Font_System5x8);		// player 2 name tag
				GLCD_GoTo(40,1);
				GLCD_WriteString(play,Font_System5x8);		// player 2 name tag
				//#######################################################################################
				//checks if the time is more than zero and if the flag is 0
				if(chesscountdown_flag == 0 && (chess_P_One_tim.sec > 0 || chess_P_One_tim.min > 0 || chess_P_One_tim.hour || 0))
				{
					GLCD_GoTo(0,2);
					GLCD_WriteString(Pone_turn,Font_System7x8);		// displays player one turn
				}
				//checks if the time is more than zero and if the flag is 1
				if(chesscountdown_flag == 1 && (chess_P_two_tim.sec > 0 || chess_P_two_tim.min > 0 || chess_P_two_tim.hour || 0))
				{
					GLCD_GoTo(0,2);
					GLCD_WriteString(Ptwo_turn,Font_System7x8);		// displays player two turn
				}

				//checks if the time is zero and if the flag is 3
				if (chesscountdown_flag == 3 && chess_P_One_tim.sec == 0 && chess_P_One_tim.min == 0 && chess_P_One_tim.hour == 0)	//checks if the count down flag is equal to 0
				{

					GLCD_GoTo(0,2);				//goes to the 0,6 position on the LCD
					GLCD_WriteString(Ptwo_win,Font_System7x8);		// displays player two win

				}
				//checks if the time is zero and if the flag is 3
				if (chesscountdown_flag == 3 && chess_P_two_tim.sec == 0 && chess_P_two_tim.min == 0 && chess_P_two_tim.hour == 0)	//checks if the count down flag is equal to 0
				{

					GLCD_GoTo(0,2);				//goes to the 0,6 position on the LCD
					GLCD_WriteString(Pone_win,Font_System7x8);		// displays player one win

				}

				GLCD_GoTo(0,6);				//goes to the 0,6 position on the LCD
				GLCD_WriteString(resetingbutton,Font_System5x8);		// displays player one win


				key  = getcommand();
				switch (key)
				{
					case '1':


						break;
					case '2':
						chesscountdown_flag =! chesscountdown_flag;

						break;
					case '3':

						chess_P_One_tim.sec=0;	//reset player 1 timer
						chess_P_One_tim.min=0;
						chess_P_One_tim.hour=0;
						chess_P_two_tim.sec=0;	//reset player 2 timer
						chess_P_two_tim.min=0;
						chess_P_two_tim.hour=0;

						state = ches_clk;
						break;
				}

			break;
					
			
			default:
			break;			
			
		}
	
}



