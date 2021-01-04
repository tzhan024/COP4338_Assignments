/*
	Student name: Tinghui Zhang
	Panther ID: 6144880
	~Affirmation of Originality: I affirm that I wrote this program myself without any help 
	from any other people or sources from the internet.
	~Program Description: This program will be piped between 2 kid processes, one to execute
	'ls -al' and the other to execute 'grep minishell.c'. After the forks, the original
	parent process waits for both child processes to finish before it terminates. The parent
	should print out the pid of each child after it finishes. The standard output of 'ls -al'
	process should be piped to the input to the 'grep minishell.c' process.
*/
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
int main()
{
	int pid1, pid2, status;
	int fd[2];
	pipe(fd);
	/*
		This part will handle the first kid of the whole process.
		It will run the 'ls -al' part and pass the result to the second child 
		by using dup2().
		Close the unused end of the pipe.
	*/
	switch (pid1 = fork())
	{
		case 0: 
			dup2(fd[1], 1);	
			close(fd[0]); 		
			execlp("/bin/ls", "ls", "-al", NULL);
			perror("exec failed");
		default: 
			break;
		case -1:
			perror("fork failed");
			exit(1);
	}
	/*
		This part will handle the first kid of the whole process.
		It will run the 'grep minishell.c' part by receiving the result from the first kid 
		by using dup2().
		Close the unused end of the pipe.
	*/
	switch (pid2 = fork())
	{
		case 0: 
			dup2(fd[0], 0);
			close(fd[1]);
			execlp("/bin/grep", "grep", "minishell.c", 0);
			perror("exec failed");
		default:
			break;
		case -1:
			perror("fork failed");
			exit(1);
	}
	// close the ends.
	close(fd[0]);
	close(fd[1]);
	
	//wait for children to finish their processes, and then print out the pids.
	int w;
	do
	{
		w = wait(&status);
	}while(w != -1);
	fprintf(stderr, "child %d exits with %d\n", pid1, status);
	fprintf(stderr, "child %d exits with %d\n", pid2, status);
	exit(0);
}