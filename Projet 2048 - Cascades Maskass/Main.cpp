#include <iostream>
#include <vector>

#include "Grid.h"

using namespace std;

const int GRID_SIZE = 4;

int main(int argc, char* argv[]) {
	Grid* grid = new Grid(GRID_SIZE);
	grid->Init();
	
	grid->SpawnFreshTiles(2);
	grid->Display();
	grid->getMovement();
	
	grid->Clean();
	return 0;
}