/*
	Student name: Tinghui Zhang
	Panther ID: 6144880
	~Affirmation of Originality: I affirm that I wrote this program myself without any help 
	from any other people or sources from the internet.
	~Program Description: This program is a binary search tree that will read input and then 
	output the result in in-order from the binary search tree. The sort can be case sensitive
	and case insensitive, depends on -c flag in command line. If an output file coming out with
	-o option, then write into the file, otherwise display like standard output. If an input
	file is given from command line, then read strings from the file, otherwise read from
	keyboard input.
*/

#include <stdio.h>
#include <stdlib.h>
/*
	This is a structure of a node, contains the info of the node, 
	count number, and left and right kid. 
*/
typedef struct Node
{
	char* info;
	int count;
	struct Node* left;
	struct Node* right;
}Node;
/*
	This is a case sensitive string comparator.
	it will compare 2 strings char by char. 
	Returns 1 if string one larger string two, returns -1 if string
	one smaller than string two, returns 0 if equal.
*/
int Comparsion(char stringOne[], char stringTwo[])
{
	int i = 0;
	while (stringOne[i] != '\0')
	{
		if(stringTwo[i] == '\0' || stringOne[i] > stringTwo[i])
			return 1;
		else if(stringOne[i] < stringTwo[i])
			return -1;
		i++;
	}   
	return 0;
}
/*
	This is a case insensitive string comparator.
	It will lower all characters before compare.
	Then, it will compare 2 strings char by char. 
	Returns 1 if string one larger string two, returns -1 if string
	one smaller than string two, returns 0 if equal.
*/
int InsensitiveComparsion(char stringOne[], char stringTwo[])
{
	int i = 0;
	while (stringOne[i] != '\0')
	{
		if(stringTwo[i] == '\0' || tolower(stringOne[i]) > tolower(stringTwo[i]))
			return 1;
		else if(tolower(stringOne[i]) < tolower(stringTwo[i]))
			return -1;
		i++;
	}   
	return 0;
}
/*
	This function will create node with node info key. 
	Assign memory for both node and its info.
	Set left and right kid to be null, and count to be 1.
	returns the new node created by this function. 
*/
Node* CreateNode(char* key)
{
	Node* newNode = (Node*)malloc(sizeof(Node));
	if (newNode == NULL)
		exit(1);
	char* keyPointer = (char*)calloc(100, sizeof(char));
	int i = 0;
	while(key[i] != '\0')
	{
		keyPointer[i] = key[i];
		i++;
	}
	keyPointer[i] = '\0';
	newNode->info = keyPointer;
	newNode->left = NULL;
	newNode->right = NULL;
	newNode->count = 1;
	return newNode;
}
/*
	This function will inset the node to the binary search tree
	with parameter root and key, key will pass to the node info.
	This function contains cFlag passed by parameter, the cFlag
	will determine if it insert case sensitively or insensitively. 
	This function is a recursion, it will rearch the left most or
	right most node recursively.
*/
Node* Insert(Node* root, char* key, int cFlag)
{
	if (cFlag == 1)
	{
		if (root == NULL)
			return(CreateNode(key));
		if(Comparsion(key, root->info) < 0)
			root->left = Insert(root->left, key, cFlag);
		else if(Comparsion(key, root->info) > 0)
			root->right = Insert(root->right, key, cFlag);
		else if(Comparsion(key, root->info) == 0)
			root->count = root->count + 1;
	}
	else
	{
		if (root == NULL)
			return(CreateNode(key));
		if(InsensitiveComparsion(key, root->info) < 0)
			root->left = Insert(root->left, key, cFlag);
		else if(InsensitiveComparsion(key, root->info) > 0)
			root->right = Insert(root->right, key, cFlag);
		else if(InsensitiveComparsion(key, root->info) == 0)
			root->count = root->count + 1;
	}
	return root;
}
/*
	This function will read strings from standard input. 
	Type enter only to stop.
*/
Node* ReadStd (Node* root, int cFlag)
{
	char line[100];
	printf("Please enter your sentence here, null enter to stop: \n");
	fgets(line, 100, stdin);
	while(line[0] != '\n')
	{
		root = Insert(root, line, cFlag);
		fgets(line, 100, stdin);
	}
	return root;
}
/*
	This function will read strings from file, the infile
	in parameter will pass the filename from command line. 
	This file will produce error message if it cannot open file.
*/
Node* ReadFile(Node* root, char* infile, int cFlag, char usage[])
{
	char line[100];
	FILE* in = fopen(infile, "r");
	if(in == NULL)
	{
		printf("Error: cannot open file for input.\n");
		printf("%s", usage);
		exit(1);
	}
	while(fscanf(in, " %[^\n]s", line) != EOF)
	{
		root = Insert(root, line, cFlag);     
	}
	fclose(in);
	return root;
}
/*
	This function will write the strings to standard output.
	The algorithm of this function is similar with in-order display
	algorithm in binary trees. 
	This function will reach the node recursively and then
	print it out. 
*/
void WriteStd(Node* current)
{
	if(current == NULL)
		return;
	WriteStd(current->left);
	printf("%d %s\n",current->count, current->info);
	WriteStd(current->right);
}
/*
	This function will write the strings to the given file.
	The algorithm of this function is similar with in-order display
	algorithm in binary trees. 
	This function will reach the node recursively and then 
	print it into the file. 
*/
void WriteFile(Node* current, char* outfile, char usage[])
{
	FILE* out;         
	if(current == NULL)
		return;
	WriteFile(current->left, outfile, usage);
	out = fopen(outfile, "a");
	if(out == NULL)
	{
		printf("Error: cannot open file for output.\n");
		printf("%s", usage);
		exit(1);
	}
	fprintf(out,"%d %s\n",current->count, current->info);
	fclose(out);
	WriteFile(current->right, outfile, usage);
}
/*
	This function will free all memories that alloced in the processes
	before, this funciton will be put at the end of the main. To make sure
	it is the last step of the whole program. 
	This program will free memories bottom-up in the tree.
*/
void FreeMemories(Node* current)
{
	if(current == NULL)
		return;
	FreeMemories(current->left);
	FreeMemories(current->right);
	free(current->info);
	free(current);
}


int main(int argc, char** argv)
{
	extern char *optarg;
	int c, err = 0;     
	int cFlag = 0, oFlag = 0;
	char* outfile = NULL;
	Node* root = NULL ;
	static char usage[] = "Usage: % bstsort [-c] [-o output_file_name] [input_file_name]\n";
	/*
		use getopt() to check options in the command line input.
		assign 1 to err, if getopt() returns to '?'.
	*/
	while ((c = getopt(argc, argv, "co:")) != -1)
	{
		switch (c) {
		case 'c':
			cFlag = 1;
			break;
		case 'o':
			oFlag = 1;
			outfile = optarg;
			break;
		case '?':
			err = 1;
			break;
		}
	}
	if(err == 1)
	{
		printf("Error: wrong option or wrong usage.\n");
		printf("%s", usage);
		exit(1);
	}
	/*
		If last argument on command line is "bstsort", that means
		no argument, and it will go to both read and write to std.
	*/
	if(Comparsion(argv[argc - 1], "bstsort") == 0)
	{
		root = ReadStd(root, cFlag);
		WriteStd(root);
	}
	else
	{
		/*
			This part will output to a file.
			if no input file specified, read from keyboard,
			otherwise read from the file.
		*/
		if(oFlag == 1)
		{
			if(Comparsion(argv[argc - 1], "-c") == 0 || Comparsion(argv[argc - 1], outfile) == 0)
			{
				root = ReadStd(root, cFlag);
				WriteFile(root, outfile, usage);
			}
			else if(Comparsion(argv[argc - 1], "-c") != 0 && Comparsion(argv[argc - 1], outfile) != 0)
			{
				root = ReadFile(root, argv[argc - 1], cFlag, usage);
				WriteFile(root, outfile, usage);
			}
		}
		/*
			This part will output to standard output.
			if no input file specified, read from keyboard,
			otherwise read from the file.
		*/
		else if(oFlag != 1)
		{
			if(Comparsion(argv[argc - 1], "-c") == 0)
			{
				root = ReadStd(root, cFlag);
				WriteStd(root);
			}
			else if(Comparsion(argv[argc - 1], "-c") != 0)
			{
				root = ReadFile(root, argv[argc - 1], cFlag, usage);
				WriteStd(root);
			}
		}
	}
	//free all memories after all steps above are done!
	FreeMemories(root);
	return 0;
}