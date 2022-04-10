#include <pthread.h>
#include <stdio.h>
#include <unistd.h>

// Declaration of thread condition variable
pthread_cond_t cond1 = PTHREAD_COND_INITIALIZER;

// declaring mutex
pthread_mutex_t lock = PTHREAD_MUTEX_INITIALIZER;

int done = 1;

// Thread function
void* foo() {

	static int counter = 0;

	// acquire a lock
	pthread_mutex_lock(&lock);
	counter++;
	if (done == 1) {
	
	// let's wait on condition variable cond1
	done = 2;
	printf("Waiting on condition variable cond1. counter:%d, done:%d\n",counter, done);
	// thread 1 wait for cond1 and sleep here.
	// wait thread 2 to unlock mutex???
	pthread_cond_wait(&cond1, &lock);
	counter++;
	counter++;
	}
	else {
	
	// Let's signal condition variable cond1
	printf("Signaling condition variable cond1. counter:%d, done:%d\n",counter, done);
	pthread_cond_signal(&cond1);
	counter++;
	}
	
	// release lock
	pthread_mutex_unlock(&lock);
	
	printf("Returning thread. counter:%d, done:%d\n",counter, done);
	
	return NULL;
}

// Driver code
int main()
{
	pthread_t tid1, tid2;
	
	// Create thread 1
	pthread_create(&tid1, NULL, foo, NULL);
	
	// sleep for 1 sec so that thread 1
	// would get a chance to run first
	sleep(1);
	
	// Create thread 2
	pthread_create(&tid2, NULL, foo, NULL);
	
	// wait for the completion of thread 2
	pthread_join(tid2, NULL);
	
	return 0;
}

