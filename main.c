#include <pthread.h>
#include <stdio.h>
#include <unistd.h>
#include <time.h>
#include <stdlib.h>

//static declaration of number of philosophers
#define no_of_phil 5

void *philosopher(void *);
void think(int);
void pickup_forks(int);
void eat(int);
void return_forks(int);

pthread_mutex_t forks[no_of_phil];
pthread_t philosophers[no_of_phil];
pthread_attr_t attributes[no_of_phil];
pthread_cond_t condition[no_of_phil]


int main(int argc, char *argv[]) {
	
	if (argc < 2)
	{
		printf("Missing number of philosophers\n");
		return(1);
	}
	
	else
	{
		//printf("%s", argv[1]);
		//no_of_phil = atoi(argv[1]);
		//printf("no of phil: %ld", no_of_phil);
		//return(0);
		
	}

	int i;
	srand(time(NULL));
	for (i = 0; i < no_of_phil; ++i) {
		pthread_mutex_init(&forks[i], NULL);
	}

	for (i = 0; i < no_of_phil; ++i) {
		pthread_attr_init(&attributes[i]);
	}
	
	for (i = 0; i < no_of_phil; ++i) {
		pthread_create(&philosophers[i], &attributes[i], philosopher, (void *)(i));
	}

	for (i = 0; i < no_of_phil; ++i) {
		pthread_join(philosophers[i], NULL);
	}
	return 0;
}

//define philosopher activities
//allow the program to run indefinitely
void *philosopher(void *philosopher_number) {
	while (1) {
		think(philosopher_number);
		pickup_forks(philosopher_number);
		eat(philosopher_number);
		return_forks(philosopher_number);
	}
}

//define time to think with thread sleep
//random period between one and 3 seconds
void think(int philosopher_number) {
	int sleepTime = rand() % 3 + 1;
	printf("Philosopher %d will think for %d seconds\n", philosopher_number, sleepTime);
	sleep(sleepTime);
}

//obtain mutex lock on forks to the right and left of the philosopher
//print the state of the philosopher as the locks are obtained
void pickup_forks(int philosopher_number) {
	int right = (philosopher_number + 1) % no_of_phil;
	int left = (philosopher_number + no_of_phil) % no_of_phil;
	if (philosopher_number & 1) {
		//obtain the fork on the right, then the left fork
		printf("Philosopher %d is waiting to pick up fork %d\n", philosopher_number, right);
		pthread_mutex_lock(&forks[right]);
		printf("Philosopher %d picked up fork %d\n", philosopher_number, right);
		printf("Philosopher %d is waiting to pick up fork %d\n", philosopher_number, left);
		pthread_mutex_lock(&forks[left]);
		printf("Philosopher %d picked up fork %d\n", philosopher_number, left);
	}
	else {
		//obtain the fork on the left, then the right fork
		printf("Philosopher %d is waiting to pick up fork %d\n", philosopher_number, left);
		pthread_mutex_lock(&forks[left]);
		printf("Philosopher %d picked up fork %d\n", philosopher_number, left);
		printf("Philosopher %d is waiting to pick up fork %d\n", philosopher_number, right);
		pthread_mutex_lock(&forks[right]);
		printf("Philosopher %d picked up fork %d\n", philosopher_number, right);
	}
}

//defin philosopher eat time
//random time between one and 3 seconds
void eat(int philosopher_number) {
	int eatTime = rand() % 3 + 1;
	printf("Philosopher %d will eat for %d seconds\n", philosopher_number, eatTime);
	sleep(eatTime);
}

//invoked when philosopher is done eating
//releases mutex on both forks
void return_forks(int philosopher_number) {
	printf("Philosopher %d will will put down forks\n", philosopher_number);
	pthread_mutex_unlock(&forks[(philosopher_number + 1) % no_of_phil]);
	pthread_mutex_unlock(&forks[(philosopher_number + no_of_phil) % no_of_phil]);
}
