#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

pthread_t tid[2];
int counter;
pthread_mutex_t lock;

void* trythis(void* arg)
{
	// the mutex lock is locked in the function while using the shared resource 'counter'
	// return 0 if successful
	// return -1 if unsuccessful
	pthread_mutex_lock(&lock);
	
	unsigned long i = 0;
	counter += 1;
	printf("\n Job %d has started\n", counter);
	
	for (i = 0; i < (0xFFFFFFFF); i++)
	;
	
	printf("\n Job %d has finished\n", counter);
	
	// the mutex lock is unlocked
	// return 0 if successful
	// return -1 if unsuccessful
	pthread_mutex_unlock(&lock);
	
	return NULL;
}

int main(void)
{
	int i = 0;
	int error;
	
	// a mutex is initialized in the beginning of the main function
	// return 0 if successful
	// return -1 if unsuccessful
	if (pthread_mutex_init(&lock, NULL) != 0) {
		printf("\n mutex init has failed\n");
		return 1;
	}
	
	while (i < 2) {
		error = pthread_create(&(tid[i]), NULL, &trythis, NULL);
		if (error != 0)
			printf("\nThread can't be created :[%s]", strerror(error));
		i++;
	}
	
	pthread_join(tid[0], NULL);
	pthread_join(tid[1], NULL);
	// the mutex lock is destroyed
	// return 0 if successful
	// return -1 if unsuccessful
	pthread_mutex_destroy(&lock);
	
	return 0;
}

