#include <iostream>
#include <vector>

#include "Grid.h"

using namespace std;

const int GRID_SIZE = 4;

int main(int argc, char* argv[]) {
	bool running = true;
	Grid* grid = new Grid(GRID_SIZE);
	grid->Init();
	grid->SpawnFreshTiles(6);

	while (running) {
		grid->HandleInput();
		//	bool keyPressed = true;
		//	if (keyPressed) {
		//		grid->ShiftCellsTowards(Input::KEY_LEFT);
		//Utility::clearConsole();
		//grid->SpawnFreshTiles(1);
		//grid->Display();
		//	}
		//	running = false;
		//}

		//grid->Clean();
	}
	return 0;
}