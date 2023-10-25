#pragma once

#include <iostream>
#include <vector>
#include <map>
#include "Cell.h"
#include "Utility.h"
#include "Messages.h"

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
	void GetMovement();
	void ShiftCellsTowards(string direction);
	void MoveCell(int x, int y);
	//void SwapCells(Cell**& from, Cell**& to);
	void Clean();
};