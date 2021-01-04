/*
	Student name: Tinghui Zhang
	Panther ID: 6144880
	~Affirmation of Originality: I affirm that I wrote this program myself without any help 
	from any other people or sources from the internet.
	~Program Description: This program will either set or clear a single bit in a number
	entered by the user using the binary representation of the number. The user should
	input the original integer value between 1 and 1000 inclusive using a scanf.
*/

#include <stdio.h>
int main()
{
	char doAgain;
	/*
		using do-while loop for the whole operation, the programming will ask
		a number, the bit and the operation during the loop, and will ask for repeat
		at the end of the loop. 
	*/
	do
	{
		int originalInt;
		int bits;
		int newInt = 0;
		char operation;
		printf("Please enter an integer between 1 - 1000: \n");
		scanf("%d", &originalInt);
		// Input validation, will be used if the number entered is invalid
		while(originalInt < 1 || originalInt >  1000)
		{
			printf("The value is over ranged, please enter again(1 - 1000): \n");
			scanf("%d", &originalInt);
		}
		unsigned int unsignInt = originalInt;
		printf("\n");
		
		printf("please enter the bit you want to change(0 - 31): \n");
		scanf("%d", &bits);
		// Input validation, will be used if the number entered is invalid
		while(bits < 0 || bits >  31) //handling exception
		{
			printf("Bit is over ranged, please enter again(0 - 31): \n");
			scanf("%d", &bits);
		}
		printf("\n");
		
		printf("Please enter the operation you want to do to this bit(set -> 's', clear -> 'c')\n");
		scanf(" %c", &operation);
		// Input validation, will be used if the operation entered is invalid
		while(!(operation == 's' || operation == 'c' || operation == 'S' || operation == 'C'))
		{
			printf("Invalid operation, please enter again(set -> 's', clear -> 'c'): \n");
			scanf(" %c", &operation);
		}
		printf("\n");
		/*
			if got 's' from input, the program will set the bit specified by user,
			if got 'c' from input, the program will clear the bit specified by user.
		*/
		if(operation == 's' || operation == 'S')
		{
			newInt = unsignInt | (1 << bits);
			printf("The decimal int after operation is: %d\n", newInt);
		}
		else if(operation == 'c' || operation == 'C')
		{
			newInt = unsignInt & ~(1 << bits);
			printf("The decimal int after operation is: %d\n", newInt);
		}
		/*
			The program will be repeated if the user entered 'y' insensitively.
		*/
		printf("Do you want to do it again?(type 'y' or 'Y' to do it again, else to stop): \n");
		scanf(" %c", &doAgain);
	}while(doAgain == 'y' || doAgain == 'Y');
	return 0;
}