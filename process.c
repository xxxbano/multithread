#include <sys/types.h>
#include<stdio.h>
#include <unistd.h>

// Refers to:
// https://www.geeksforgeeks.org/difference-between-process-parent-process-and-child-process/?ref=rp
//
// A process is more than the program code, it includes the following:
// - Program counter
// - Process stack
// - Registers
// - Program code, etc.
//
// On the contrary, program code is only a text section
//
// A process changes its state as it executes.
// The new state partially depends on the current activity of a process.
// The differet states of the process during its execution are:
// - New
// - Ready
// - Running
// - Blocked
// - Terminated
//
// A process control block and process table are associated with each of the processes.
// It contains the following important information about the process:
// - Process state
// - Process number
// - Program counter
// - List of files and registers
// - CPU information
// - Memory information, etc.

// Driver code
//int main()
//{
//	printf ("Before Forking\n");
//	// create a child process
//	fork();
//	// execute two time by parent process and child process.
//	printf ("After Forking\n");
//}

int main()
{
	int pid;
	// 0 is returned to the child process
	// PID of the child process is returnd to the parent process
	pid = fork();
			  
	if (pid == 0) // executed by child process
	{
		printf ("Child : I am the child process\n");
		printf ("Child : Child’s PID: %d\n", getpid());
		printf ("Child : Parent’s PID: %d\n", getppid());

		// code to do in child process
		
	} else { // executed by parent process 
		printf ("Parent : I am the parent process\n");
		printf ("Parent : Parent’s PID: %d\n", getpid());
		printf ("Parent : Child’s PID: %d\n", pid);

		// code to do in parent process
		
	}
}

