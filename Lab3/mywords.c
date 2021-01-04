/*
	Student name: Tinghui Zhang
	Panther ID: 6144880
	~Affirmation of Originality: I affirm that I wrote this program myself without any help 
	from any other people or sources from the internet.
	~Program Description: This is a mini calculator using only the command line options.
	This program include -s, -c, -f command line options, -s will sort strings in ASCII order,
	-c will count the number of words in the file, and -f will count the occurance of the substring
	followed after -f. -f need parameters. 
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char **argv)
{
	extern char *optarg;
	int c, err = 0; 
	int cFlag = 0, sFlag = 0, fFlag = 0;
	char* substring;
	FILE* file;
	char fileCpy[30][100];
	static char usage[] = "Usage: mywords [-cs] [-f substring] filename\n";
	/**
		use getopt() to check options in the command line input.
		assign 1 to err, if getopt() returns to '?'.
	*/
	while ((c = getopt(argc, argv, "scf:")) != -1)
	{
		switch (c) {
		case 'c':
			cFlag = 1;
			break;
		case 's':
			sFlag = 1;
			break;
		case 'f':
			fFlag = 1;
			substring = optarg;
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
		fprintf(stderr, usage, argv[0]);
		exit(1);
	}
	/**
		This function will prevent when last flag is "-f" the filename
		and the substring share the same argument. For example, 
		"-f name", name cannot be substring and filename at the same time.
	*/
	if(strcmp(argv[argc - 2], "-f") == 0)
	{
		printf("Error: missing substring or filename.\n");
		fprintf(stderr, usage, argv[0]);
		exit(1);
	}
	/**
		This function will terminal the program if "-f" has no argument.
	*/
	if(strcmp(substring, "-c") == 0 || strcmp(substring, "-s") == 0)
	{
		printf("Error: missing substring.\n");
		fprintf(stderr, usage, argv[0]);
		exit(1);
	}
	//open file.
	file = fopen(argv[argc - 1], "r");
	//terminal if file did not found.
	if(file == NULL)
	{
		printf("Error: cannot open file.\n");
		exit(1);
	}
	int wordNumber = 0;
	int i = 0;
	char ch;
	// store file words in to a array.
	do
	{
		ch = fscanf(file, "%s", fileCpy[wordNumber]);
		wordNumber ++;
	}while(ch != EOF);
	wordNumber --;
	//close file
	fclose(file);
	/**
		print words if there has no options on command line.
	*/
	if(sFlag != 1 && cFlag != 1 && fFlag != 1)
	{
		int i = 0;
		for(i = 0; i < wordNumber; i++)
		{
			printf("%s ", fileCpy[i]);
		}
		printf("\n");
	}
	/**
		if command line got -s flag, sort words in ASCII order.
		Using bubble sort algorithm.
		And then print the sorted words.
	*/
	if(sFlag == 1)
	{
		int i = 0, j = 0, k = 0;
		char temp[30];
		for(i = 0; i < wordNumber - 1; i++)
		{
			for(j = 0; j < wordNumber - i - 1; j++)
			{
				if(strcmp(fileCpy[j], fileCpy[j + 1]) > 0)
				{
					strcpy(temp, fileCpy[j]);
					strcpy(fileCpy[j], fileCpy[j + 1]);
					strcpy(fileCpy[j + 1], temp);
				}
			}
		}
		printf("The words in ASCII order is: \n");
		for(k = 0; k < wordNumber; k++)
		{
			printf("%s\n", fileCpy[k]);
		}
	}
	//print number of words if command line have -c flag.
	if(cFlag == 1)
	{
		printf("The number of words in the file is: %d\n", wordNumber);
	}
	/**
		print occurence of substring if command line have -f flag.
		increment occurence if substring is equals to the word.
	*/
	if(fFlag == 1)
	{
		int i = 0;
		int occurence = 0;
		for(i = 0; i < wordNumber; i++)
		{
			if(strcmp(substring, fileCpy[i]) == 0)
				occurence ++;
		}
		printf("The occurence for word %s is: %d\n", substring, occurence);
	}
}