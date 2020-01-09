
#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <pthread.h>
#include "racer.h"
#include "display.h"

///The main file. it's kind of obvious
int main(int argc, char *argv[]) {
	if (argc < 3) {
		perror("Usage: pt-cruisers [max-speed-delay] name1 name2 [name3...]");
		return EXIT_FAILURE;
	}
	//Used for finding the time for each thread to sleep
	srand(time(NULL));
	
	//Check for the optional delay value and set it if it's valid and exists.
	char **racerNames;
	long delay = strtol(argv[1], NULL, 10);
	int numRacers;
	if (delay == 0) {
		delay = DEFAULT_WAIT;
		racerNames = argv + 1;
		numRacers = argc - 1;
	} else {
		racerNames = argv + 2;
		numRacers = argc - 2;
	}
	Racer *racerList[numRacers];
	initRacers(delay);
	if (numRacers < 2) {
		perror("Usage: pt-cruisers [max-speed-delay] name1 name2 [name3...]");
		return EXIT_FAILURE;
	}

	for (int i = 0; i < numRacers; i++) {
		if (strlen(racerNames[i]) > 6) {
			perror("Error: racer names must not exceed length 6");
			return EXIT_FAILURE;
		} else {
			racerList[i] = makeRacer(racerNames[i], i + 1);
		}

	}
	clear();
	
	pthread_t racerThreads[numRacers];
	for (int i = 0; i < numRacers; i++) {
		pthread_create(&racerThreads[i], NULL, run, racerList[i]);
	}
	for (int i = 0; i < numRacers; i++) {
		pthread_join(racerThreads[i], NULL);
	}
	return EXIT_SUCCESS;
}
