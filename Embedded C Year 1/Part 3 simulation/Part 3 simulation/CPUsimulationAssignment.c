#include <stdio.h>
#include <conio.h>
/********************************************************************************************************************************/
char IR;
char Operand;
char AddressMode;
char OpCode;
int i = 0;
unsigned char PC, MAR, MBR, source;
unsigned char D0 = 0;
unsigned char memory[16] = { 0x13, 0x0A, 0x23, 0x33, 0x41, 0x52, 0x68, 0xEF, 0x81, 0xE0, 0x0A, 0x03, 0x08, 0x0F, 0, 0 };
unsigned char run = 1;
void main(void); //declaring function main
void main(void)
{
	/********************************************************************************************************************************/
	/*beginnin of the CPU simulation*/
	PC = 0; //initialising the variable PC
	while (run == 1) { // a while loop that loops the program while the varibale 'run' is equal to '1'
		i++;
		MAR = PC;
		PC = PC + 1;
		MBR = memory[MAR];
		IR = MBR;


		/*decode and display operand*/
		Operand = IR & 0x0F; // mask IR with 0x0F(b00001111)

		printf("\n########### Loop %d #############\n\nOperand is : %d", i, Operand);
		/*decode and display addressing mode*/

		AddressMode = IR & 0x10; // shift 4 bits to the right

		printf("\nAddress Mode is : %d", AddressMode >> 4); //mask IR with 0x10(b00010000) and shift 4 bits to the right
		/*decode and display Op-code*/

		OpCode = (IR & 0xE0) >> 5; // mask IR with 0xE0(b11100000) and shift right by 5

		printf("\nOpCode is : %d\n\n################################\n", OpCode);
		if (AddressMode == 1) { //an if statment to check if the addressMode is 1 or 0
			source = Operand; //mode = 1
		}
		else
		{
			source = memory[Operand]; //mode = 0
		}

		/* process OP code */
		switch (OpCode) { //a switch statement to search for a case that matches the OpCode value and executes it
		case 0x00:
			D0 = source;
			break;
		case 0x01:
			memory[Operand] = D0;
			break;
		case 0x02:
			D0 = D0 + source;
			break;
		case 0x03:
			PC = Operand;
			break;
		case 0x04:
			if (D0 = 0) { //checks to see if D0 = 0
				PC = Operand;
			}
			break;
		case 0x05:
			printf("Instruction not found");
			break;
		case 0x06:
			printf("Instruction not found");
			break;
		case 0x07:
			run = 0; // initialises run = 0 to end the loop
			break;
		}
	}
	printf("\n\n********End of CPU simulation********");
	getchar();
	/***************************************************************************************************************************************/
}
