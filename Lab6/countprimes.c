/*
	Student name: Tinghui Zhang
	Panther ID: 6144880
	~Affirmation of Originality: I affirm that I wrote this program myself without any help 
	from any other people or sources from the internet.
	~Program Description: This program will count the number of prime numbers in the numbers
	from 1 to n inclusive where n is a long integer. The value for n which should be set in
	the program using a constant should be 50,000. Each process will test its share of the cases.
	Each process should print out any primes that it finds in a readable manner indicating which
	process found it and the actual prime number found. The master process should end with
	printing a total for the count of the number of primes and the total amount of time
	taken to find all the primes.
	Direction: This program needs mpicc and mpirun to compile and execute the program. 
*/
#include <stdio.h>
#include <mpi.h>
/*
	This funciton will count the number of primes smaller than 50000. 
	This function will check each number between 1 - 50000, to see if it is a prime.
	And then, this function will print out the primes and the id of processes that found the prime
	by following "id - prime" format. 
	This function will return the number of primes found. 
*/
int CountPrime (long n, int id, int p)
{
	long i, j;
	int count = 0, isPrime;
	for(i = 2 + id; i <= n; i = i + p)
    {
    	isPrime = 1;
    	for(j = 2; j < i; j++)
    	{
    		if((i % j ) == 0)
    		{
    			isPrime = 0;
    			count += isPrime;
    		}
    	}
    	count += isPrime;
    	if(isPrime == 1)   /*print if the number is a prime*/
    	{
    	    printf("%2d - %-5ld, ", id, i);
    	    if(count % 10 == 0)
    	        printf("\n");   /*Switch to a newline every 10 numbers. */
    	}
    }
	printf("\n");
	return count;
}

int main(int argc, char* argv[])
{
	int count = 0;            /* Solutions found by this proc */
	double elapsed_time;  /* Time to find, count solutions */
	int global_count;     /* Total number of solutions */
	int i;
	int id;               /* Process rank */
	int p;                /* Number of processes */
	char hostname[1024];
	const long n = 50000;

	MPI_Init (&argc, &argv);   /*Initialize the MPI environment.*/
	MPI_Comm_rank (MPI_COMM_WORLD, &id);   
	MPI_Comm_size (MPI_COMM_WORLD, &p);
	hostname[1023] = '\0';
	gethostname(hostname, 1023);
	printf("MPI rank %d on host %s\n", id, hostname);

	/* Start timer */
	MPI_Barrier (MPI_COMM_WORLD);
	elapsed_time = -MPI_Wtime();
	
	count += CountPrime (n, id, p);  /*calling the function. */

	MPI_Reduce (&count, &global_count, 1, MPI_INT, MPI_SUM, 0, MPI_COMM_WORLD); 

	/* Stop timer */
	elapsed_time += MPI_Wtime();

	MPI_Finalize();
	if (!id)
	{
		printf ("\nExecution time %8.6f\n", elapsed_time);
		fflush (stdout);
		printf ("There are %d primes found.\n", global_count);
	}
	return 0;
}