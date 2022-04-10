
/*
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>  //Header file for sleep(). man 3 sleep for details.
#include <pthread.h>
  
// A normal C function that is executed as a thread 
// when its name is specified in pthread_create()
void *myThreadFun(void *vargp)
{
	sleep(1);
	printf("Printing GeeksQuiz from Thread \n");
	return NULL;
}
               
int main()
{
	// an integer used to identify the thread in the system
	pthread_t thread_id;
	printf("Before Thread\n");
	// create a thread
	// - 1st argument is a pointer to thread_id which is set by this function
	// - 2nd arg. specifies attributes. NULL indicates default attributes
	// - 3rd arg. is name of funciton to be executed for the thread to be created
	// - 4th arg. is used to pass arguments to the function
	pthread_create(&thread_id, NULL, myThreadFun, NULL);

	// the equivalent of wait() for processes.
	// suspend the execution of the currently running thread until the particular thread you want to terminated, 
	// after that it resumes its execution.
	// Useful where you have to wait until a particular thread completes its execution
	pthread_join(thread_id, NULL);
	printf("After Thread\n");
	exit(0);
}
*/


#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>
  
// Let us create a global variable to change it in threads
int g = 0;
  
// The function to be executed by all threads
void *myThreadFun(void *vargp)
{
	// Store the value argument passed to this thread
	int *myid = (int *)vargp;
	          
	// Let us create a static variable to observe its changes
	static int s = 0;
	                    
	// Change static and global variables
	++s; ++g;
	                              
	// Print the argument, static and global variables
	printf("Thread ID: %d, Static: %d, Global: %d\n", *myid, ++s, ++g);
}
                                        
int main()
{
	int i;
	pthread_t tid;
	                                                  
	// Let us create three threads
	for (i = 0; i < 3; i++)
		// create a thread
		// - 1st argument is a pointer to thread_id which is set by this function
		// - 2nd arg. specifies attributes. NULL indicates default attributes
		// - 3rd arg. is name of funciton to be executed for the thread to be created
		// - 4th arg. is used to pass arguments to the function
		pthread_create(&tid, NULL, myThreadFun, (void *)&tid);
	                                                                    
	// terminate the thread that is called
	// if you call it from your main thread, the main thread is terminated and your spawned threads continue execution.
	// So anything you write after pthread_exit() in the mian thread will not be executed.
	// This will be usefull in a scenario in which your main thread has to just spawn threads.
	pthread_exit(NULL);
	// won't come here because of pthread_exit()
	printf("test");
	return 0;
}
