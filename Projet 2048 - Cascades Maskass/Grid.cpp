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
		cout << "|";
		for (int y = 0; y < size; y++) {
			cout << " " << grid[y][x]->GetValue() << " ";
		}
		cout << "|";
		cout << endl;
	}
}

bool Grid::HandleInput() {
	int c;
	switch (( c = _getch())) {
	case Input::KEY_UP:
		ShiftCellsTowards(Input::KEY_UP, &Grid::HandleUpMovement);
		break;
	case Input::KEY_DOWN:
		ShiftCellsTowards(Input::KEY_DOWN, &Grid::HandleDownMovement);
		break;
	case Input::KEY_RIGHT:
		ShiftCellsTowards(Input::KEY_RIGHT, &Grid::HandleRightMovement);
		break;
	case Input::KEY_LEFT:
		ShiftCellsTowards(Input::KEY_LEFT, &Grid::HandleLeftMovement);
		break;
	default:
		return false;
	}
	return true;
}

void Grid::ShiftCellsTowards(int direction, bool (Grid::*moveFunction)(Cell*, Cell*&)){
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
				cout << x << ", " << y << endl;
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
		return true;
	}
	return false;
}

void Grid::SwapCells(Cell** from, Cell** to) {
	Cell** tmp = from;
	*from = *to;
	*to = *tmp;
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