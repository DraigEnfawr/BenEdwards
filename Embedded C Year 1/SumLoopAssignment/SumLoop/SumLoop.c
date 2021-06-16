#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#ifdef _WIN32
#define WINPAUSE system("pause")
#endif
/*

*********************************+++FIRST VERSION OF THE SUM LOOP+++*****************************************

int counter;			//assigned the variable counter as an int
float Sum = 0;			//assigned the variable sum as a float initialised to 0
float x1 = 0, x2 = 0;	//assigned the variables x1 and x2 as a float initialised to 0
float max_num = 10;		//assigned the variable max_num as a float initialised to 10
float answer = 0;		//assigned the variable answer as a float initialised to 0
void main(void)
{
	for (counter = 1; counter <= max_num; counter++)			//this for loop will continue to loop, while 'counter' is less than or equal to the variable 'max_num', incrementing 'counter' by one before each loop 
	{
		printf_s("\ninput value for x1: ");			//asks the user to input an input for the variable x1
		scanf_s("%f", &x1);					//takes the users input and stores it in the variable x1
		printf_s("input value for x2: ");
		scanf_s("%f", &x2);

		Sum += (x1*x2);				//multiply the two inputs by the user and adds it to the Sum variable 
		printf_s("%f", Sum);		//prints out the value of sum from the equasion above
			

		//Sum = Sum + counter;
		//printf_s("%d\n", Sum);
		//Or you could do...
		//sum += counter

	}
	
	
	answer = Sum / (1 / max_num);
	printf_s("\n%f", answer);
	WINPAUSE;
}
*****************************************************************************************************************
*/

void main(void);
void modifyArray(int b[], int size[]);
void modifyElement(int c);
int correlation(int x1[], int x2[], int N);      //my correlation function



void main(void)
{
	int my_array[9];
	int i;
	int b;
	int sampleAdd = 0;
	int answer;
	int x1[] = { 4, 2, -1, 3, -2, -6, -5, 4, 5 };
	int x2[] = { -4, 1, 3, 7, 4, -2, -8, -2, 1 };

	printf("input a number to add to an array");
	unsigned char *myPointer;		//assigning pointer
	for (i = 0; i < 10; i++) {
		scanf_s("%d", &b);
		printf("%d", b);
	}

	modifyArray(my_array, 9, x1, x2);


	for (i = 0; i < 9; i++) {
		printf("%d", my_array[i]);
	}
	printf("\n\n***********\n\n");

	for (i = 0; i < 9; i++) {
		sampleAdd = sampleAdd + my_array[i];
	}
printf("%d", sampleAdd);

}

void modifyArray(int mult[], int size[], int x1[], int x2[]) 
{
	int j;
	for (j = 0; j < size; j++) {
		mult[j] = x1[j] * x2[j];
		printf("%d \n", mult[j]);
	}

}






/*unsigned char *my_pointer;		//declare pointer variable
unsigned char a = 5;		//declar normal variable

my_pointer = &a;		// assign address of a variable to my_pointer

printf("value of a is : %d", a);
printf("address of a is : %d", &a);
*/









/*void main(void)
{
	unsigned char *my_pointer;		//declare pointer variable
	unsigned char a = 5;		//declar normal variable
	unsigned char b = 100;

	my_pointer = &a;		// assign address of a variable to my_pointer

	printf("value of a is : %d \n", a);
	printf("address of a is : %d \n", &a);
	printf("address stored within pointer variable my_pointer is : %d \n", my_pointer);
	printf("data stored within pointer variable my_pointer is : %d \n", *my_pointer);
	printf("value of b is : %d \n", b);
	printf("address of b is : %d \n", &b);
	my_pointer = &b;
	printf("address stored within pointer variable my_pointer is : %d \n", my_pointer);
	printf("data stored within pointer variable my_pointer is : %d \n", *my_pointer);
	*my_pointer = 110;
	printf("value of b is : %d \n", b);
}*/