#include "Grid.h"

Grid::Grid(int _size) {
	size = _size;
	won = false;
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

	for (int x = 0; x < size; x++) {
		for (int y = 0; y < size; y++) {
			emptyCells.push_back(GetCell(x, y));
		}
	}

	srand(time(nullptr));
	Utility::initUtility();
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
	if (emptyCells.size() <= 0) return;

	for (int i = 0; i < n; i++)
	{
		Cell* cell = GetRandomEmptyCell();
		int value = GetRandomTileValue();
		
		SetCell(cell, value);
		cout << "Before :" << emptyCells.size();
		emptyCells.remove(cell);
		cout << "After :" << emptyCells.size();
	}
}

Cell* Grid::GetRandomEmptyCell() {
	int cellIndex = rand() % emptyCells.size();
	list<Cell*>::iterator it = emptyCells.begin();
	advance(it, cellIndex);
	Cell* out = *it;
	emptyCells.remove(out);
	return out;
}

int Grid::GetRandomTileValue() {
	return rand() % 10 == 0 ? 4 : 2;
};

void displaySeparationLine() {
	cout << '+';
	for (int i = 0; i < 4; i++)
	{
		Utility::repeatCharacter('-', 4);
		cout << '+';
	}
	cout << endl;
}

void Grid::Display() {
	Utility::clearConsole();
	displaySeparationLine();
	for (int x = 0; x < size; x++) {
		cout << "|";
		for (int y = 0; y < size; y++) {
			int value = GetCell(y, x)->GetValue();

			if (value != 0) {
				Utility::setColorToValue(value);
				cout << value;
				Utility::repeatCharacter(' ', 4 - Utility::countIntegerDigits(value));
				Utility::resetOutputColor();
			}
			else {
				Utility::resetOutputColor();
				cout << "*   ";
			}
			if (y < 3) {
				cout << '|';
			}

		}
		cout << "|" << endl;
		if (x < 3) {
			displaySeparationLine();
		}
	}
	displaySeparationLine();
	cout << endl;
}

bool Grid::HandleInput() {
	int c;
	switch (( c = _getch())) {
	case Input::KEY_UP:
		ShiftTilesTowards(Input::KEY_UP, &Grid::HandleUpMovement);
		break;
	case Input::KEY_DOWN:
		ShiftTilesTowards(Input::KEY_DOWN, &Grid::HandleDownMovement);
		break;
	case Input::KEY_RIGHT:
		ShiftTilesTowards(Input::KEY_RIGHT, &Grid::HandleRightMovement);
		break;
	case Input::KEY_LEFT:
		ShiftTilesTowards(Input::KEY_LEFT, &Grid::HandleLeftMovement);
		break;
	default:
		return false;
	}
	return true;
}

void Grid::ShiftTilesTowards(int direction, bool (Grid::*moveFunction)(Cell*, Cell*&)){
	BatchResetCells();
	if (direction == Input::KEY_UP || direction == Input::KEY_LEFT) {
		for (int x = 0; x < size; x++) {
			for (int y = 0; y < size; y++) {
				MoveCell(x, y, direction, moveFunction);
			}
		}
	}
	else {
		for (int x = size-1; x >= 0; x--) {
			for (int y = size-1; y >= 0; y--) {
				MoveCell(x, y, direction, moveFunction);
			}
		}
	}
}

void Grid::MoveCell(int x, int y, int direction, bool (Grid::*moveFunction)(Cell*, Cell*&)) {
	Cell* cell = GetCell(x, y);
	if (cell->GetValue() == 0) return;

	while (CellHasNeighbour(cell, direction)) {
		Cell* neighbour;
		bool shouldContinue = (this->*moveFunction)(cell, neighbour);
		if (shouldContinue) continue;

		bool hasMerged = *cell + *neighbour;
		if (!hasMerged)
			break;
		
		emptyCells.push_back(neighbour);
		cell->SetHasMerge(true);
		neighbour->SetHasMerge(true);
		continue;
	}
}

bool Grid::CellHasNeighbour(Cell* cell, int direction) {
	switch (direction) {
		case Input::KEY_UP:
			return cell->Position[1] > 0;
			break;
		case Input::KEY_DOWN:
			return cell->Position[1] < (size-1);
			break;
		case Input::KEY_RIGHT:
			return cell->Position[0] < (size-1);
			break;
		case Input::KEY_LEFT:
			return cell->Position[0] > 0;
			break;
	}
}

bool Grid::HandleLeftMovement(Cell* cell, Cell*& neighbour) {
	int x = cell->Position[0];
	int y = cell->Position[1];
	neighbour = GetCell(x - 1, y);

	if (neighbour->GetValue() == 0) {
		Cell* tmp = grid[x][y];
		grid[x][y] = grid[x-1][y];
		grid[x-1][y] = tmp;
		cell->Position[0] -= 1;
		neighbour->Position[0] += 1;
		return true;
	}
	return false;
}

bool Grid::HandleRightMovement(Cell* cell, Cell*& neighbour) {
	int x = cell->Position[0];
	int y = cell->Position[1];
	neighbour = GetCell(x + 1, y);

	if (neighbour->GetValue() == 0) {
		Cell* tmp = grid[x][y];
		grid[x][y] = grid[x+1][y];
		grid[x + 1][y] = tmp;
		cell->Position[0] += 1;
		neighbour->Position[0] -= 1;
		return true;
	}
	return false;
}

bool Grid::HandleUpMovement(Cell* cell, Cell*& neighbour) {
	int x = cell->Position[0];
	int y = cell->Position[1];
	neighbour = GetCell(x, y - 1);

	if (neighbour->GetValue() == 0) {
		Cell* tmp = grid[x][y];
		grid[x][y] = grid[x][y-1];
		grid[x][y - 1] = tmp;
		cell->Position[1] -= 1;
		neighbour->Position[1] += 1;
		return true;
	}
	return false;
}


bool Grid::HandleDownMovement(Cell* cell, Cell*& neighbour) {
	int x = cell->Position[0];
	int y = cell->Position[1];
	neighbour = GetCell(x, y + 1);

	if (neighbour->GetValue() == 0) {
		Cell* tmp = grid[x][y];
		grid[x][y] = grid[x][y + 1];
		grid[x][y + 1] = tmp;
		cell->Position[1] += 1;
		neighbour->Position[1] -= 1;
		return true;
	}
	return false;
}

bool Grid::WinCondition() {
	if (won) return false;
	for (int x = 0; x < size; x++) {
		for (int y = 0; y < size; y++) {
			Cell* cell = GetCell(x, y);
			if (cell->GetValue() == 2048) {
				won = true;
				return true;
			}
		}
	}
	return false;
}

bool Grid::LooseCondition() {
	for (int x = 0; x < size; x++) {
		for (int y = 0; y < size; y++) {
			Cell* cell = GetCell(x, y);
			if (cell->GetValue() == 0)
				return false;
			
			// Get all adjacents to check if they are mergeable
			vector<Cell*> adjs;
			if (x > 0) // Left
				adjs.push_back(GetCell(x - 1, y));
			if (x < 3) // Right
				adjs.push_back(GetCell(x + 1, y));
			if (y > 0) // Top
				adjs.push_back(GetCell(x, y - 1));
			if (y < 3) // Bottom
				adjs.push_back(GetCell(x, y + 1));

			for (int i = 0; i < adjs.size(); i++)
			{
				if (adjs[i]->GetValue() == cell->GetValue())
					return false;
			}
		}
	}
	return true;
}

void Grid::BatchResetCells() {
	for (int x = 0; x < size; x++)
	{
		for (int y = 0; y < size; y++)
		{
			Cell* cell = GetCell(x, y);
			cell->SetHasMerge(false);
		}
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
}