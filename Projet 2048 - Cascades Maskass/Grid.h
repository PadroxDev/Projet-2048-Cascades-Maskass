#pragma once

#include <iostream>
#include <vector>

#include "Cell.h"

using namespace std;

class Grid {
private:
	vector<vector<Cell*>> grid;
	vector<Cell*> emptyCells;
	int size;
public:
	Grid(int size);
	~Grid();

	// Getters
	int GetSize() { return size; }
	
	void Init();
	Cell* GetCell(int x, int y);
	void SetCell(int x, int y, int value);
	void SetCell(Cell* cell, int value);
	void SpawnFreshTiles(int n);
	Cell* GetRandomEmptyCell();
	int GetRandomTileValue();
	void Display();
	void Clean();
};