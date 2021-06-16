#include <stdio.h>
#include <stdlib.h>
#include <math.h>
void main(void); //declaring the main function
void modifyArray(int b[], int size[], int x1[], int x2[]); //declaring function modifyArray
void main(void)
{
	int element_Multi[10]; //assigning arrays for b1, b2 and element_Multi
	int i; //assigning variables for 'i', for the loops, sampleAdd and answer
	float sampleAdd = 0;
	float answer;
	int b1[9];
	int b2[9];
	int elementNum; //elementNum is used to store the int value that the user inputs reprisenting the number of elements the b1, b2 and element_Multi arrays have


	/*********************************************************************************************/
	printf("input your desired number of elements for this equation : "); // asks the user to input a value of the array elements and stores the value in elementNum
	scanf_s("%d", &elementNum);
	/*********************************************************************************************/

	int *myPointer; //assigning a pointer
	for (i = 0; i < elementNum; i++) { // a 'for' loop that takes the inputs from the user and stores them in each element of b1 and b2
		printf("input value for first array of element %d : ", i);
		scanf_s("%d", &b1[i]);
		printf("input value for second array of element %d : ", i);
		scanf_s("%d", &b2[i]);
	}


	modifyArray(element_Multi, elementNum, b1, b2); //calling the function 'modifyArray'
	for (i = 0; i < elementNum; i++) { // a 'for' loop that uses pointers to display the values of elements b1 and b2, putting them in a formula that shows the working out of the multiplication
		myPointer = &b1[i];
		printf("multiplication %d is : %d * ", i, *myPointer);
		myPointer = &b2[i];
		printf("%d = %d \n", *myPointer, element_Multi[i]);
	}

		printf("\n\n*****************************************************\n\n");
	for (i = 0; i < elementNum; i++) { //a 'for' loop to add each multiplied elements in the 'element_Multi' array
		sampleAdd = sampleAdd + element_Multi[i];
	}
	printf("The addition of all the multiplications is : %.1f \n", sampleAdd); //prints the sum of all the multiplied elements
	answer = sampleAdd / elementNum; //finding the answer by dividing sampleAdd by the number of elements that the user input
	printf("The answer of %.1f divided by %d = %.1f \n\n", sampleAdd, elementNum, answer); //prints the answer of the equation
	getch();
}
void modifyArray(int mult[], int size[], int x1[], int x2[]) // the modifyArray function
{
	int j; //created variable 'j' for the 'for' loop
	for (j = 0; j < size; j++) { // a 'for' loop that multiplies each element from x1 and x2 which mirrors b1 and b2
		mult[j] = x1[j] * x2[j];
	}
}