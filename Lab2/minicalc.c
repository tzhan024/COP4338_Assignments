/*
	Student name: Tinghui Zhang
	Panther ID: 6144880
	~Affirmation of Originality: I affirm that I wrote this program myself without any help 
	from any other people or sources from the internet.
	~Program Description: This is a mini calculator using only the command line options.
	This program include -a, -m, -x command line options, -a is addition, -m is multiplication
	and -x is square of the value. -a and -m need parameters. 
*/

#include <stdio.h>
#include <stdlib.h>

int main(int argc, char **argv)
{
	extern char *optarg;
	int c, err = 0; 
	int mFlag = 0, aFlag = 0, xFlag = 0;
	int aNum, mNum;
	int value;
	static char usage[] = "Usage: minicalc [-a num] [-m num] [-x] value\n";
	/**
		use getopt() to check options in the command line input.
		Take parameters out by using atoi().
		assign 1 to err, if getopt() returns to '?'.
	*/
	while ((c = getopt(argc, argv, "a:m:x")) != -1)
	{
		switch (c) {
		case 'm':
			mFlag = 1;
			mNum = atoi(optarg);
			break;
		case 'a':
			aFlag = 1;
			aNum = atoi(optarg);
			break;
		case 'x':
			xFlag = 1;
			break;
		case '?':
			err = 1;
			break;
		}
	}
	/**
		Print message and stop the program when there has no options
		in the command line, that is, when getopt() returns '?'.
	*/
	if(err == 1)
	{
		printf("Command line needs at least one option.\n");
		fprintf(stderr, usage, argv[0]);
		exit(1);
	}
	/**
		Used to prevent the last option and starting value share the same
		number. For example, "-a 9", this part will avoid 9 be read twice. 
	*/
	if(strcmp(argv[argc - 2], "-a") == 0 || strcmp(argv[argc - 2], "-m") == 0)
	{
		printf("Missing value or parameter.\n");
		fprintf(stderr, usage, argv[0]);
		exit(1);
	}
	value = atoi(argv[argc - 1]);
	/**
		Check if the value is out of range. 
	*/
	if(value < 1 || value > 50)
	{
		printf("Argument value should between 1 to 50.\n");
		fprintf(stderr, usage, argv[0]);
		exit(1);
	}
	double result = value;
	//Square the value at first. 
	if(xFlag == 1)
		result = value * value;
	/**
		Check if the number is out of range.
		When optarg is not a number, atoi() will returns to 0, which is missing argument.
		Do multiplication after squared.
	*/
	if(mFlag == 1)
	{
		if(mNum < 1 || mNum > 10)
		{
			printf("Input parameter for -m missing or not between 1 to 10.\n");
			fprintf(stderr, usage, argv[0]);
			exit(1);
		}
		result = result * mNum;
	}
	/**
		Check if the number is out of range.
		When optarg is not a number, atoi() will returns to 0, which is missing argument. 
		Do addition at the end. 
	*/
	if(aFlag == 1)
	{
		if(aNum < 1 || aNum > 500)
		{
			printf("Input parameter for -a missing or not between 1 to 500.\n");
			fprintf(stderr, usage, argv[0]);
			exit(1);
		}
		result = result + aNum;
	}
	//Print calculation result with 2 decimal places. 
	printf("The calculation result is: %.2lf\n", result);
	exit(0);
}