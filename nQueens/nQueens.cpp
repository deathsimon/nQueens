#include <time.h>
#include "nQueens.h"

//#define PTHREAD
//#define OPENMP

extern int nQueens_pthread(int);
extern int nQueens_openMP(int);

inline bool validPlacement(data boardData, int target) {
	bool valid = true;
	for (int i = 0; i < boardData.currentPos; i++) {
		if ((*boardData.position)[i] == target
			|| abs((*boardData.position)[i] - target) == (boardData.currentPos - i)) {
			valid = false;
			break;
		}
	}
	return valid;
}

int placeQueen(data boardData) {
	if (boardData.currentPos == boardData.boardSize) {
		return 1;
	}

	int totalSum = 0;
	for (int i = 0; i < boardData.boardSize; i++) {
		if (validPlacement(boardData, i)) {
			(*boardData.position)[boardData.currentPos] = i;
			boardData.currentPos += 1;
			totalSum += placeQueen(boardData);
			boardData.currentPos -= 1;
		}
	}
	return totalSum;
}

int nQueens(int boardSize) {

	int numSolutions = 0;

	data boardData = {
		boardSize,							// boardSize
		0,									// currentPos
		new std::vector<int>(boardSize, 0)	// position
	};

	for (int i = 0; i < boardSize; i++) {
		(*boardData.position)[0] = i;
		boardData.currentPos += 1;
		numSolutions += placeQueen(boardData);
		boardData.currentPos -= 1;
	}

	return numSolutions;
}

int main(int argc, char* argv[]) {		
	int boardSize = 0;
	int numSolutions = 0;

	while (boardSize <= 0 
		|| boardSize > 20) {
		std::cout << "Please enter the size of the board [1 - 20]:";
		std::cin >> boardSize;
	};

	clock_t startTtime = clock();
#ifdef PTHREAD
	numSolutions = nQueens_pthread(boardSize);
#else
#ifdef OPENMP
	numSolutions = nQueens_openMP(boardSize);
#else
	numSolutions = nQueens(boardSize);
#endif
#endif
	clock_t endTime = clock();
	
	std::cout << "There are " << numSolutions 
		<< " possible solutions" << std::endl;
	std::cout << "Time consumption:" 
		<< static_cast<double>(endTime - startTtime)/ CLOCKS_PER_SEC 
		<< std::endl;

	return 0;
}