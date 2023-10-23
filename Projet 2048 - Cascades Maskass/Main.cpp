#include <iostream>
#include <vector>

#include "Grid.h"

using namespace std;

const int GRID_SIZE = 4;

int main(int argc, char* argv[]) {
	Grid* grid = new Grid(GRID_SIZE);
	grid->Init();
	
	grid->Display();
	grid->Papagnan(2);
	grid->Display();
	delete grid;

	return 0;
}