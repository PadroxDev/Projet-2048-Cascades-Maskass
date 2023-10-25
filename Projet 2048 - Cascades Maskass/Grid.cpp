#include "Grid.h"

Grid::Grid(int _size) {
	size = _size;
}

Grid::~Grid()
{}

void Grid::Init() {
	grid.resize(size);

	for (int x = 0; x < size; x++) {
		grid[x].resize(size);
		for (int y = 0; y < size; y++) {
			grid[x][y] = new Cell(x, y);
		}
	}

	emptyCells.resize(pow(size, 2));
	
	for (int x = 0; x < size; x++) {
		for (int y = 0; y < size; y++) {
			emptyCells[x * size + y] = GetCell(x, y);
		}
	}

	srand(time(nullptr));
}

Cell* Grid::GetCell(int x, int y) {
	return grid[x][y];
}

void Grid::SetCell(int x, int y, int value) {
	Cell* cell = GetCell(x, y);
	SetCell(cell, value);
}

void Grid::SetCell(Cell* cell, int value) {
	cell->SetValue(value);
}

void Grid::SpawnFreshTiles(int n) {
	for (int i = 0; i < n; i++)
	{
		Cell* cell = GetRandomEmptyCell();
		int value = GetRandomTileValue();
		
		SetCell(cell, value);
	}
}

Cell* Grid::GetRandomEmptyCell() {
	int cellIndex = rand() % emptyCells.size();
	Cell* out = emptyCells[cellIndex];
	emptyCells.erase(emptyCells.begin() + cellIndex);
	return out;
}

int Grid::GetRandomTileValue() {
	return rand() % 10 == 0 ? 4 : 2;
};

void Grid::Display() {
	cout << endl;
	for (int x = 0; x < size; x++) {
		for (int y = 0; y < size; y++) {
			cout << grid[y][x]->GetValue();
		}
		cout << endl;
	}
}

void Grid::Clean() {
	for (int x = 0; x < size; x++)
	{
		for (int y = 0; y < size; y++)
		{
			delete GetCell(x, y);
		}
	}

	delete &grid;
	delete &emptyCells;
}

static enum ValidCommands {move_up, move_down, move_right, move_left};

void Grid::GetMovement() {
	map<string, ValidCommands> commands;
	commands["up"] = ValidCommands::move_up;
	commands["down"] = ValidCommands::move_down;
	commands["right"] = ValidCommands::move_right;
	commands["left"] = ValidCommands::move_left;

	bool validCommand = false;
	string command;

	while (!validCommand) {
		cout << CHOOSE_MOVE_TEXT << " : ";
		cin >> command;
		Utility::lowerString(command);

		cout << endl << "You entered " << command << endl;

		Utility::clearConsole();
		if (commands.find(command) == commands.end()) {
			cout << "Invalid command ! Please try again !" << endl;
			continue;
		} else {
			cout << "You entered a valid command, processing to move " << command << " !" << endl;
			validCommand = true;
		}
	}

	ValidCommands vCom = commands[command];
	switch (vCom)
	{
	case move_up:
		cout << "Move upwards !";
		break;
	case move_down:
		cout << "Move downwards !";
		break;
	case move_right:
		cout << "Move upwards !";
		break;
	case move_left:

		break;
	}
}

//void Grid::MoveCell() {
//	for (int x = 0; x < size; x++) {
//		for (int y = 0; y < size; y++)
//		{
//			Cell* cell = GetCell(x, y);
//			if (cell->GetValue() == 0) continue;
//
//			while(cell->Position[0] > 0) {
//				Cell* neighbour = GetCell(cell->Position[0] - 1, y);
//				if(neighbour->GetValue() == 0) {
//					cell->Position[0] -= 1;
//					Cell* tmp = grid[x][y];
//					grid[x][y] = grid[x - 1][y];
//					grid[x - 1][y] = tmp;
//					cout << "Supposed to move !";
//				} else if(neighbour->GetValue() == cell->GetValue()) {
//					//cout << "cout << MERGE UWUS AZEA ËZRAPRAZ¨PR ÄZ";
//					cout << "papagnan";
//					neighbour->SetValue(neighbour->GetValue() * 2);
//					cell->SetValue(0);
//					break;
//				} else {
//					cout << "nop";
//					break;
//				}
//			}
//		}
//	}
//}

void Grid::ShiftCellsTowards(string direction) {
	for (int x = 0; x < size; x++) {
		for (int y = 0; y < size; y++)
		{
			MoveCell(x, y);
		}
	}
}

void Grid::MoveCell(int x, int y) {
	Cell* cell = GetCell(x, y);
	if (cell->GetValue() == 0) return;

	bool hasMerged = false;

	while (cell->Position[0] > 0) {
		Cell* neighbour = GetCell(cell->Position[0] - 1, y);

		if (neighbour->GetValue() == 0) {
			cell->Position[0] -= 1;
			Cell* tmp = grid[x][y];
			grid[x-1][y] = grid[x][y];
			grid[x-1][y] = tmp;
			continue;
		}
		else if (cell->GetValue() == neighbour->GetValue() && !hasMerged) {
			hasMerged = true;
			bool mergeSuccess = *cell + *neighbour;
			cout << mergeSuccess;
			continue;
		}
		cout << "Nothing to do !";
		break;
	}
}