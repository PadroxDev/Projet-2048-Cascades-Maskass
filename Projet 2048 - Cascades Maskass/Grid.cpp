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
		// Remove cell from emptyCells
		SetCell(cell, value);
	}
}

Cell* Grid::GetRandomEmptyCell() {
	int cellIndex = rand() % emptyCells.size();
	return emptyCells[cellIndex];
}

int Grid::GetRandomTileValue() {
	return rand() % 10 == 0 ? 4 : 2;
};

void Grid::Display() {
	cout << endl;
	for (int x = 0; x < size; x++) {
		for (int y = 0; y < size; y++) {
			cout << grid[x][y]->GetValue();
		}
		cout << endl;
	}
}

void Grid::Clean() {
	delete &grid;
	delete &emptyCells;
}