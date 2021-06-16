#include <stdio.h>
#include <stdlib.h>
#include <math.h>


int num1, num2, f; //declareing the two input variables and the result variable
int logicChoice;	//declaring the selecting AND/OR variable 
char boollogic = 1;	//declaring a boolean variable 

void main(void)
{
	while (1) {


		//display user instructions
		printf_s("Please select the logic gate you wish to simulate by entering the numbers...\n1 - AND Operation\n2- OR Operation\n3 - NAND Operation\n4 - NOR Operation\n5 - ExOR Operation\n\n");	//prints the selection list for the user
		scanf_s("%d", &logicChoice);							//capture the user input and store it in the logicChoice variable


		if (logicChoice == 1)
		{
			//AND gate opperation
			printf_s("--- 2 input 'AND' Gate Operation ---\n\n ");

			while (boollogic == 1)		// a while loop that asks the user to input the correct value if they had first entered the wrong value.
			{
				printf_s("\ninput the first number: ");	//prints a string asking the user to input the first number thats either 1 or 0
				scanf_s("%d", &num1);	//takes the value input by the user and is placed in the num1 variable

				if (num1 > 1) {						// an if statement that checks if the value input by the user is correct and changes the boollogic variable if the entered value is appropriate.
					printf("\nThis is not a logic based number. Please input a logic based number. For example 0 and 1 : ");
				}
				else {
					boollogic = 0;
				}

			}
			boollogic = 1;

			while (boollogic == 1)
			{
				printf_s("\ninput a second number: ");	//prints a string asking the user to input the second number thats either 1 or 0
				scanf_s("%d", &num2);				//takes the value input by the user and is placed in the num2 variable

				if (num1 > 1) {
					printf("\nThis is not a logic based number. Please input a logic based number. For example 0 and 1 : ");
				}
				else {
					boollogic = 0;
				}

			}

			boollogic = 1;

			f = (num1) & (num2);									//preform AND operation
			printf_s("output of an and operation is: %d \n", f);	//dislpays AND operation result
		}
		else if (logicChoice == 2)
		{
			//OR gate opperation
			printf_s("--- 2 input 'OR' Gate Operation ---\n\n ");

			while (boollogic == 1)		// a while loop that asks the user to input the correct value if they had first entered the wrong value.
			{
				printf_s("\ninput the first number: ");	//prints a string asking the user to input the first number thats either 1 or 0
				scanf_s("%d", &num1);	//takes the value input by the user and is placed in the num1 variable

				if (num1 > 1) {						// an if statement that checks if the value input by the user is correct and changes the boollogic variable if the entered value is appropriate.
					printf("\nThis is not a logic based number. Please input a logic based number. For example 0 and 1 : ");
				}
				else {
					boollogic = 0;
				}

			}
			boollogic = 1;

			while (boollogic == 1)
			{
				printf_s("\ninput a second number: ");	//prints a string asking the user to input the second number thats either 1 or 0
				scanf_s("%d", &num2);				//takes the value input by the user and is placed in the num2 variable

				if (num1 > 1) {
					printf("\nThis is not a logic based number. Please input a logic based number. For example 0 and 1 : ");
				}
				else {
					boollogic = 0;
				}

			}
			boollogic = 1;

			f = num1 | num2;									//preform OR operation
			printf_s("output of an or operation is: %d \n", f);	//dislpays OR operation result
		}
		else if (logicChoice == 3)
		{
			//NAND gate opperation
			printf_s("--- 2 input 'NAND' Gate Operation ---\n\n ");

			while (boollogic == 1)		// a while loop that asks the user to input the correct value if they had first entered the wrong value.
			{
				printf_s("\ninput the first number: ");	//prints a string asking the user to input the first number thats either 1 or 0
				scanf_s("%d", &num1);	//takes the value input by the user and is placed in the num1 variable

				if (num1 > 1) {						// an if statement that checks if the value input by the user is correct and changes the boollogic variable if the entered value is appropriate.
					printf("\nThis is not a logic based number. Please input a logic based number. For example 0 and 1 : ");
				}
				else {
					boollogic = 0;
				}

			}
			boollogic = 1;

			while (boollogic == 1)
			{
				printf_s("\ninput a second number: ");	//prints a string asking the user to input the second number thats either 1 or 0
				scanf_s("%d", &num2);				//takes the value input by the user and is placed in the num2 variable

				if (num1 > 1) {
					printf("\nThis is not a logic based number. Please input a logic based number. For example 0 and 1 : ");
				}
				else {
					boollogic = 0;
				}

			}
			boollogic = 1;


			f = (num1) & (num2);									//preform NAND operation
			printf_s("output of an NAND operation is: %d \n", !f);	//dislpays NAND operation result by making the result of AND in 'f' and 'not'ing it with '!'

		}
		else if (logicChoice == 4)
		{
			//NOR gate opperation
			printf_s("--- 2 input 'NOR' Gate Operation ---\n\n ");

			while (boollogic == 1)		// a while loop that asks the user to input the correct value if they had first entered the wrong value.
			{
				printf_s("\ninput the first number: ");	//prints a string asking the user to input the first number thats either 1 or 0
				scanf_s("%d", &num1);	//takes the value input by the user and is placed in the num1 variable

				if (num1 > 1) {						// an if statement that checks if the value input by the user is correct and changes the boollogic variable if the entered value is appropriate.
					printf("\nThis is not a logic based number. Please input a logic based number. For example 0 and 1 : ");
				}
				else {
					boollogic = 0;
				}

			}
			boollogic = 1;

			while (boollogic == 1)
			{
				printf_s("\ninput a second number: ");	//prints a string asking the user to input the second number thats either 1 or 0
				scanf_s("%d", &num2);				//takes the value input by the user and is placed in the num2 variable

				if (num1 > 1) {
					printf("\nThis is not a logic based number. Please input a logic based number. For example 0 and 1 : ");
				}
				else {
					boollogic = 0;
				}

			}
			boollogic = 1;

			f = (num1) | (num2);									//preform NAND operation
			printf_s("output of an NAND operation is: %d \n", !f);	//dislpays NOR operation result by making the result of OR in 'f' and 'not'ing it with '!'


		}
		else if (logicChoice == 5)
		{
			//EXOR gate opperation
			printf_s("--- 2 input 'ExOR' Gate Operation ---\n\n ");

			while (boollogic == 1)		// a while loop that asks the user to input the correct value if they had first entered the wrong value.
			{
				printf_s("\ninput the first number: ");	//prints a string asking the user to input the first number thats either 1 or 0
				scanf_s("%d", &num1);	//takes the value input by the user and is placed in the num1 variable

				if (num1 > 1) {						// an if statement that checks if the value input by the user is correct and changes the boollogic variable if the entered value is appropriate.
					printf("\nThis is not a logic based number. Please input a logic based number. For example 0 and 1 : ");
				}
				else {
					boollogic = 0;
				}

			}
			boollogic = 1;

			while (boollogic == 1)
			{
				printf_s("\ninput a second number: ");	//prints a string asking the user to input the second number thats either 1 or 0
				scanf_s("%d", &num2);				//takes the value input by the user and is placed in the num2 variable

				if (num1 > 1) {
					printf("\nThis is not a logic based number. Please input a logic based number. For example 0 and 1 : ");
				}
				else {
					boollogic = 0;
				}

			}
			boollogic = 1;

			f = num1 ^ num2;									//preform ExOR operation
			printf_s("output of an or operation is: %d \n", f);	//dislpays ExOR operation result


		}
	}
	getch();
}

/*
#include <stdlib.h>

#ifdef _WIN32
#define WINPAUSE system("pause")
#endif

	function()
	{

	
		WINPAUSE;
	}
*/
	