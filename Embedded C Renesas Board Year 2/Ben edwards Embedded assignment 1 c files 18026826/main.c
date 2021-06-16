/******************** (C) COPYRIGHT 2018-2019 University of South Wales *******************************
* File Name          : main.c
* Author             : SS
* Version            : V1.0.1
* Date               : 21-March-2019
* Description        : main program
***************************************************************************************************
* THE PRESENT FIRMWARE WHICH IS FOR GUIDANCE ONLY AIMS AT PROVIDING STUDENTS
* WITH CODING INFORMATION REGARDING THEIR ASSIGNMENT IN ORDER FOR THEM DELIVER TO THE STANDARD.
* AS A RESULT, UNIVERSITY OF SOUTH WALES SHALL NOT BE HELD LIABLE FOR ANY DIRECT,
* INDIRECT OR CONSEQUENTIAL DAMAGES WITH RESPECT TO ANY CLAIMS ARISING FROM THE
* CONTENT OF SUCH FIRMWARE AND/OR THE USE MADE BY STUDENTS OF THE CODING
* INFORMATION CONTAINED HEREIN IN CONNECTION WITH THEIR PRODUCTS,PROJECT OR ASSIGNMENTS.
****************************************************************************************************/

/*********** System Clock Configuration ********************************************
    Clock Description              Frequency
    ----------------------------------------
    Input Clock Frequency............  12 MHz
    PLL frequency (x16).............. 192 MHz
    Internal Clock Frequency.........  96 MHz
    Peripheral Clock Frequency.......  48 MHz
    USB Clock Frequency..............  48 MHz
    External Bus Clock Frequency.....  24 MHz
**********************************************************************************************
*/


#include "iodefine.h"
#include "typedefine.h"
#include "d_stop_watch.h"

/* Private Defines -----------------------------------------------------------*/

/* Extern variables ----------------------------------------------------------*/
//extern FONT_DEF Font_System3x6;	/*uncomment this if needed */
//extern FONT_DEF Font_System5x8;
//extern FONT_DEF Font_System7x8;

/* Private variables ---------------------------------------------------------*/



/* Private function prototypes -----------------------------------------------*/
void main(void);
#ifdef __cplusplus
extern "C" {
void abort(void);
}
#endif




void main(void)
{

/* System Clock has already been configured at this point, Please Refer to the System Clock Configuration for more Details */
 d_stop_watch_Init();		// initialise Stop watch application

	while(1)	// Beginning of super loop
	{
		/* add your code here */

		d_stop_watch_process();		// begin stop watch process task

	} // end of super loop

}	// end of main program

#ifdef __cplusplus
void abort(void)
{

}
#endif
