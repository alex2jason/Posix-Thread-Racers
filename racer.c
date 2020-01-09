
#define _BSD_SOURCE
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <pthread.h>
#include "racer.h"
#include "display.h"

long max_delay;

pthread_mutex_t lock;

///Initalizes the racers
void initRacers(long miliseconds) {
	max_delay = miliseconds;
}

///Makes the racer
Racer *makeRacer(char *name, int position) {
	Racer *racer = malloc(sizeof(Racer));
	racer->dist = 0;
	racer->row = position;
	//racer->graphic = "~0=------o>";
	racer->graphic = calloc(MAX_CAR_LEN + 1, sizeof(char));
	char *graphic = "~0=------o>";
	for (unsigned int i = 0; i < strlen(graphic); i++) {
		racer->graphic[i] = graphic[i];
	}
	for (unsigned int offset = 3; offset < strlen(name); offset++) {
		racer->graphic[offset] = name[offset - 3];
	}
	return racer;
}

///Destroys the racer
void destroyRacer(Racer *racer) {
	free(racer);
}

///Moves the racer a space
void moveRacer(Racer *racer) {
	pthread_mutex_lock(&lock);
	for (int xPos = racer->dist; xPos <= MAX_CAR_LEN + racer->dist; xPos++) {
		set_cur_pos(racer->row, xPos);
		put(' ');
	}
	racer->dist++;
	for (int offset = 0; offset < MAX_CAR_LEN; offset++) {
		set_cur_pos(racer->row, racer->dist + offset);
		put(racer->graphic[offset]);
	}
	pthread_mutex_unlock(&lock);
}

///Runs the racer and shit
void *run(void *racer) {
	while (((Racer*)racer)->dist != FINISH_LINE) {
		int delay = rand() % max_delay;
		if (delay < 3) {
			((Racer*)racer)->graphic[1] = 'X';
			destroyRacer(racer);
			return EXIT_FAILURE;
		} else {
			moveRacer(racer);
			usleep(delay);
		}
	}
	destroyRacer(racer);
	return EXIT_SUCCESS;
}
