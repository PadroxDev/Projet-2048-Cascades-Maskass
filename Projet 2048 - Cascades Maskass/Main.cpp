#include <iostream>
#include <vector>

#include "Grid.h"

using namespace std;

const int GRID_SIZE = 4;

int main(int argc, char* argv[]) {
	bool running = true;
	Grid* grid = new Grid(GRID_SIZE);
	grid->Init();
	grid->SpawnFreshTiles(8);
	grid->Display();
	grid->ShiftCellsTowards(Input::KEY_DOWN, &Grid::HandleDownMovement);
	grid->Display();

	while (running) {
		bool keyPressed = grid->HandleInput();
		if (keyPressed) {
			Utility::clearConsole();
			grid->Display();
			grid->SpawnFreshTiles(1);
		}
	}
	grid->Clean();
	return 0;
}