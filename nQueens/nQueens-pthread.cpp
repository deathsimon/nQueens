#include <pthread.h>
#include "nQueens.h"

struct setup {
	int boardSize;
	int starting_point;
};

extern int placeQueen(data);

void *placeQueen_pthread(void *arg) {
	setup* info = (setup*)arg;
	int *solutions = (int *)malloc(sizeof(int) * 1);

	data boardData = {
		info->boardSize,						// boardSize
		1,										// currentPos
		new std::vector<int>(info->boardSize, 0)// position
	};

	(*boardData.position)[0] = info->starting_point;

	(*solutions) = placeQueen(boardData);

#ifdef VERBOSE
	std::cout << "Thread " << info->starting_point << " found " << (*solutions) << " possible solutions" << std::endl;
#endif

	pthread_exit((void *)solutions);

	return NULL;
}

int nQueens_pthread(int boardSize){

	int numSolutions = 0;

	std::vector<pthread_t> threads(boardSize);
	pthread_attr_t thread_attr;

	pthread_attr_init(&thread_attr);
	pthread_attr_setdetachstate(&thread_attr, 
		PTHREAD_CREATE_JOINABLE);

	setup* thread_info;
	int* solution;

	for (int i = 0; i < boardSize; i++) {
		thread_info = new setup();
		thread_info->boardSize = boardSize;
		thread_info->starting_point = i;

		pthread_create(&threads[i], &thread_attr, 
			placeQueen_pthread, (void *)thread_info);

		
		pthread_join(threads[i], (void **)&solution);
		numSolutions += *solution;
	}

	//std::cout << "There are " << numSolutions << " possible solutions" << std::endl;

	//pthread_exit(NULL);

	return numSolutions;
}