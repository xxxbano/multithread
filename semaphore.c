
// Refers to
// https://www.geeksforgeeks.org/dining-philosopher-problem-using-semaphores/
// https://legacy.cs.indiana.edu/classes/p415-sjoh/hw/project/dining-philosophers/index.htm
//
//

#include <pthread.h>
#include <semaphore.h>
#include <stdio.h>
#include <unistd.h>

#define N 5
#define THINKING 2
#define HUNGRY 1
#define EATING 0
#define LEFT (phnum + 4) % N
#define RIGHT (phnum + 1) % N

// hold philosopher's states
int state[N];
int phil[N] = { 0, 1, 2, 3, 4 };

// semaphore
sem_t mutex; // init to 1 -> eat oportunity
sem_t S[N];	 // init to 0 -> fork in hand

// if phnum philosopher in hungry state and neighbor philosophers are not in eating state
// set phnum philosopher in eating state and unlock S[phnum]
void test(int phnum)
{
	// current philosopher is hungry
	// left and right philosophers are not eating 
	if (state[phnum] == HUNGRY
		&& state[LEFT] != EATING
		&& state[RIGHT] != EATING) {
		// state that eating
		state[phnum] = EATING;
		
		sleep(2);
		
		printf("Philosopher %d takes fork %d and %d\n",
		phnum + 1, LEFT + 1, phnum + 1);
		
		printf("Philosopher %d is Eating\n", phnum + 1);
		
		// sem_post(&S[phnum]) has no effect
		// during takefork
		// used to wake up hungry philosophers
		// during putfork
		//
		// int sem_post(sem_t *sem)
		// - increments (unlock) the semaphore pointed to by sem
		// - if the semaphore's value consequently becomes greater than 0, 
		// 	 then another process or thread blocked in a sem_wait() call will be woken up and proceed to lock the semaphore
		sem_post(&S[phnum]);
	}
}

// take up chopsticks
// - try lock mutex semaphore -> lock spaghetti eat opportunity
// - set phnum philosipher in hungry state  -> change state from thinking to hungry
// - run test function for phnum philosipher-> if neighbors are not eating, enter eating state
// 											-> unlock S[phnum] semaphore
// - unlock mutex semaphore	  -> unlock spaghetti eat opportunity
// - try lock S[phnum] semaphore -> lock S[phnum] semaphore to try to put down forks
void take_fork(int phnum)
{

	// sem_wait(sem_t * sem)
	// - decrements (lock) the semaphore pointed to by sem
	// - if the semaphore's value is greater than 0, then the decrement procedds, and the function returns immediately
	// - if the semaphore currently has the value 0, then the call blocks until either it becomes possible to perform the decrement.
	//
	// check spaghetti is available for eating
	// wait if it is not available
	sem_wait(&mutex);
	
	// state that hungry
	state[phnum] = HUNGRY;
	
	printf("Philosopher %d is Hungry\n", phnum + 1);
	
	// eat if neighbours are not eating
	test(phnum);
	
	// int sem_post(sem_t *sem)
	// - increments (unlock) the semaphore pointed to by sem
	// - if the semaphore's value consequently becomes greater than 0, 
	// 	 then another process or thread blocked in a sem_wait() call will be woken up and proceed to lock the semaphore
	sem_post(&mutex);
	
	// if unable to eat wait to be signalled
	sem_wait(&S[phnum]);
	
	sleep(1);
}

// put down chopsticks
// - try lock mutex semaphore -> lock spaghetti eat opportunity
// - set phnum philosipher in thinking state -> change state from eating to thinking
// - run test function for left philosipher -> let the philosipher eat if possible
// - run test function for right philosipher-> let the philosipher eat if possible
// - unlock mutex semaphore -> unlock spaghetti eat opportunity
void put_fork(int phnum)
{

	sem_wait(&mutex);
	
	// state that thinking
	// means 
	// - philosipher takes no fork
	// - neighbor philosiphers could eat now, test them and put them in eat state if possible
	state[phnum] = THINKING;
	
	printf("Philosopher %d putting fork %d and %d down\n",
			phnum + 1, LEFT + 1, phnum + 1);
	printf("Philosopher %d is thinking\n", phnum + 1);
	
	test(LEFT);
	test(RIGHT);
	
	sem_post(&mutex);
}

// philosopher thread loops forever
// take fork and then put fork
// go through thinking -> hungry -> eating -> thinking
//  - each philosopher try to take forks
//  	- the philosopher try to lock the spaghetti eat opportunity
//  	- when philosopher get the eat opportunity, then enter hungry state
//  	- the philosopher try to eat the spaghetti 
//  		- enter eating state 
//  		- unlock S[phnum] semaphore -> means the philosopher finished eating and can put down forks now
//  	- the philosopher unlock the spaghetti eat opportunity
//  	- the philosopher lock S[phnum] semaphore ->  wait the philosopher to finish eating
//  - each philosopher try to put down forks
//  	- the philosopher try to lock the spaghetti eat opportunity
//  	- when philosopher get the eat opportunity, then enter thinking state
//  	- the philosopher let his neighbors to eat
//  	- the philosopher unlock the spaghetti eat opportunity
//
void* philosopher(void* num)
{

	while (1) {
		int* i = num;
		
		sleep(1);
		
		take_fork(*i);
		
		sleep(0);
		
		put_fork(*i);
	}
}

int main()
{

	int i;
	pthread_t thread_id[N];
	
	// sem_init(sem_t *sem, int pshared, unsigned int value)
	// - sem_t *sem: initializes semaphore at the address pointed to by sem
	// - int pshared: 
	// 		- 0 indicates the semaphore is shared between the threads of a process
	// 		- nonzeoro indicates the semaphore is shared between processes
	// - unsigned int value: specifies the initial value for the semaphore
	//
	// initialize the semaphores
	// - semaphore mutex is initialized to 1 and shared between the threads of a process
	sem_init(&mutex, 0, 1);
	
	for (i = 0; i < N; i++)
		// - semaphore S[] is initialized to 0 and shared between the threads of a process
		sem_init(&S[i], 0, 0);
	
	for (i = 0; i < N; i++) {
		// create N philosopher processes
		pthread_create(&thread_id[i], NULL, philosopher, &phil[i]);
		
		printf("Philosopher %d is thinking\n", i + 1);
	}
	
	for (i = 0; i < N; i++)
		pthread_join(thread_id[i], NULL);
}

