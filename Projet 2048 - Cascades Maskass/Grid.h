#pragma once

#include <iostream>
#include <vector>
#include <functional>
#include <map>
#include <conio.h>
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
	bool HandleInput();
	void ShiftCellsTowards(int direction, bool (Grid::* moveFunction)(Cell*, Cell*&));
	void MoveCell(int x, int y, int direction, bool (Grid::*)(Cell*, Cell*&));
	void BatchResetCells();
	bool CellHasNeighbour(Cell* cell, int direction);
	bool HandleLeftMovement(Cell* cell, Cell*& neighbour);
	bool HandleRightMovement(Cell* cell, Cell*& neighbour);
	bool HandleUpMovement(Cell* cell, Cell*& neighbour);
	bool HandleDownMovement(Cell* cell, Cell*& neighbour);
	void Clean();
	void SwapCells(Cell** from, Cell** to);
};