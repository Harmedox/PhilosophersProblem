#include <pthread.h>
#include <stdio.h>
#include <unistd.h>
#include <time.h>
#include <stdlib.h>

//static declaration of number of philosophers
#define no_of_phil 10

void *philosopher(void *);
void think(int);
void pickUp(int);
void eat(int);
void putDown(int);

pthread_mutex_t chopsticks[no_of_phil];
pthread_t philosophers[no_of_phil];
pthread_attr_t attributes[no_of_phil];


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
		pthread_mutex_init(&chopsticks[i], NULL);
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

void *philosopher(void *philosopherNumber) {
	while (1) {
		think(philosopherNumber);
		pickUp(philosopherNumber);
		eat(philosopherNumber);
		putDown(philosopherNumber);
	}
}

void think(int philosopherNumber) {
	int sleepTime = rand() % 10 + 1;
	printf("Philosopher %d will think for %d seconds\n", philosopherNumber, sleepTime);
	sleep(sleepTime);
}

void pickUp(int philosopherNumber) {
	int right = (philosopherNumber + 1) % no_of_phil;
	int left = (philosopherNumber + no_of_phil) % no_of_phil;
	if (philosopherNumber & 1) {
		printf("Philosopher %d is waiting to pick up chopstick %d\n", philosopherNumber, right);
		pthread_mutex_lock(&chopsticks[right]);
		printf("Philosopher %d picked up chopstick %d\n", philosopherNumber, right);
		printf("Philosopher %d is waiting to pick up chopstick %d\n", philosopherNumber, left);
		pthread_mutex_lock(&chopsticks[left]);
		printf("Philosopher %d picked up chopstick %d\n", philosopherNumber, left);
	}
	else {
		printf("Philosopher %d is waiting to pick up chopstick %d\n", philosopherNumber, left);
		pthread_mutex_lock(&chopsticks[left]);
		printf("Philosopher %d picked up chopstick %d\n", philosopherNumber, left);
		printf("Philosopher %d is waiting to pick up chopstick %d\n", philosopherNumber, right);
		pthread_mutex_lock(&chopsticks[right]);
		printf("Philosopher %d picked up chopstick %d\n", philosopherNumber, right);
	}
}

void eat(int philosopherNumber) {
	int eatTime = rand() % 3 + 1;
	printf("Philosopher %d will eat for %d seconds\n", philosopherNumber, eatTime);
	sleep(eatTime);
}

void putDown(int philosopherNumber) {
	printf("Philosopher %d will will put down her chopsticks\n", philosopherNumber);
	pthread_mutex_unlock(&chopsticks[(philosopherNumber + 1) % no_of_phil]);
	pthread_mutex_unlock(&chopsticks[(philosopherNumber + no_of_phil) % no_of_phil]);
}
