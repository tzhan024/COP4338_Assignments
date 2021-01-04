/*
	Student name: Tinghui Zhang
	Panther ID: 6144880
	~Affirmation of Originality: I affirm that I wrote this program myself without any help 
	from any other people or sources from the internet.
	~Program Description: This program contains 6 hard-coded courses, course credits and their
	grades, the program will compute the grade point earned for each course, and the current GPA
	for this student. Then, the program will output all of these information into a formatted table. 
*/

#include <stdio.h>
int main()
{
	// 6 is the number of course and 10 is the length of the Strings. 
	char courses[6][10] = {"COP4338", "COP4555", "CGS3095", "CDA4101", "MAD3512", "CAP4770"};
	int courseCredits[6] = {3, 3, 3, 3, 3, 3};
	double courseGrades[6] = {3.67, 4.00, 4.00, 3.00, 3.33, 4.00};
	int totalCredits = 0;
	double totalPointsEarned = 0;
	printf("Student Name: Tinghui Zhang\n");
	printf("Panther ID: 6144880\n");
	printf("------------------------------------------------------\n");
	printf("|Course    | Credits |   Grade|   Grade Points Earned|\n");
	//Printing the table using for loop.
	int i = 0;
	for(i = 0; i < 6; ++i)
	{
		printf("------------------------------------------------------\n");
		printf("|%-10s|%5d    |%8.2lf|%22.2lf|\n", courses[i], courseCredits[i], courseGrades[i], courseCredits[i] * courseGrades[i]);
		//increment total credits and total points in every iteration.
		totalCredits += courseCredits[i];
		totalPointsEarned += courseCredits[i] * courseGrades[i];
	}
	printf("------------------------------------------------------\n");
	printf("|%-10s|%5d    |%8s|%22.2lf|\n", "Total", totalCredits, "\0", totalPointsEarned);
	printf("------------------------------------------------------\n");
	//Calculates and prints the current GPA.
	printf("Current GPA: %.2lf\n", totalPointsEarned / totalCredits);
	return 0;
}
