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
			grid[x][y] = 0;
		}
	}

	srand(time(nullptr));
}

int Grid::GetCell(int x, int y) {
	return grid[x][y];
}

void Grid::SetCell(int value, int x, int y) {
	grid[x][y] = value;
}

void Grid::Papagnan(int n) {
	// Get a random cell
	set<int> freeCells;
	for (int x = 0; x < size; x++)
	{
		for (int y = 0; y < size; y++)
		{
			int value = GetCell(x, y);
			if (value == 0) {
				freeCells.insert(x * size + y);
			}
		}
	}

	for (int i = 0; i < n; i++)
	{
		int cellPos = rand() % freeCells.size();
		int x = cellPos / size;
		int y = cellPos;
		int value = GetRandomTileValue();
		SetCell(value, x, y);
	}
}

int Grid::GetRandomTileValue() {
	return rand() % 10 == 0 ? 4 : 2;
};

void Grid::Display() {
	cout << endl;
	for (int x = 0; x < size; x++) {
		for (int y = 0; y < size; y++) {
			cout << grid[x][y];
		}
		cout << endl;
	}
}