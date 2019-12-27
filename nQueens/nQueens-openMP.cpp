#include "nQueens.h"
#include <omp.h>

extern int placeQueen(data);

int nQueens_openMP(int boardSize) {

	int numSolutions = 0;

	omp_set_num_threads(omp_get_num_procs());	

#pragma omp parallel for reduction(+: numSolutions) schedule(dynamic)
	for (int i = 0; i < boardSize; i++) {
		data boardData = {
			boardSize,							// boardSize
			1,									// currentPos
			new std::vector<int>(boardSize, 0)	// position
		};
		(*boardData.position)[0] = i;
		numSolutions += placeQueen(boardData);
	}

	return numSolutions;
}