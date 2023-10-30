#include <iostream>
#include <vector>

#include "Grid.h"

using namespace std;

const int GRID_SIZE = 4;

int main(int argc, char* argv[]) {
	bool running = true;
	Grid* grid = new Grid(GRID_SIZE);
	grid->Init();
	grid->SpawnFreshTiles(2);
	grid->Display();
	showChooseMoveText();

	while (running) {
		bool keyPressed = grid->HandleInput();
		if (keyPressed) {
			grid->SpawnFreshTiles(1);
			grid->Display();

			if (grid->WinCondition()) {
				showVictoryText();
			}
			else if (grid->LooseCondition()) {
				showDefeatText();
			}
		}
	}
	grid->Clean();
	return 0;
}