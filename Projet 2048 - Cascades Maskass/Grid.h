#pragma once

#include <iostream>
#include <vector>
#include <list>
#include <map>
#include <windows.h>
#include <conio.h>
#include "Cell.h"
#include "Utility.h"
#include "Messages.h"

using namespace std;

class Grid {
private:
	vector<vector<Cell*>> grid;
	list<Cell*> emptyCells;
	int size;
	bool won;
public:
	Grid(int size);
	~Grid();

#pragma region Getters
	int GetSize() { return size; }
	Cell* GetCell(int x, int y);

	/// <summary>
	/// Return a random empty cell on the grid.
	/// <para>If there is no empty cell, return null.</para>
	/// </summary>
	/// <returns></returns>
	Cell* GetRandomEmptyCell();
	
	/// <summary>
	/// Return a random value between 2 and 4. [2: 90%, 4: 10%]
	/// </summary>
	/// <return></return>
	int GetRandomTileValue();
#pragma endregion Getters

#pragma region Setters
	void SetCell(int x, int y, int value);
	void SetCell(Cell* cell, int value);
#pragma endregion Setters

#pragma region Initializers
	/// <summary>
	/// Initialize the grid and all the variables needed for the app to work.
	/// </summary>
	void Init();
#pragma endregion Intializers
	
#pragma region Input
	/// <summary>
	/// Check every arrow keys, if none is pressed return false.
	/// If one arrow was pressed, call ShiftCellsTowards the correct direction.
	/// </summary>
	/// <returns>If one arrow key is pressed</returns>
	bool HandleInput();
#pragma endregion Input

#pragma region Gameplay Mechanics
	/// <summary>
	/// Spawn tiles with a random value from the GetRandomTileValue on an empty cell.
	/// </summary>
	/// <param name="n">Number of fresh tiles to spawn.</param>
	void SpawnFreshTiles(int n);

	/// <summary>
	/// Shift all tiles of the grid towards the same direction.
	/// <para>Also handle Merging</para>.
	/// </summary>
	/// <param name="direction">The direction to move is based on Input::Key.</param>
	/// <param name="moveFunction">This is the Directional Movement method.</param>
	void ShiftTilesTowards(int direction, bool (Grid::* moveFunction)(Cell*, Cell*&));
	
	/// <summary>
	/// Move a cell towards a direction. If the neighbour has the same value, then merge occurs.
	/// </summary>
	/// <param name="x">The x position of the cell on the grid.</param>
	/// <param name="y">The y position of the cell on the grid.</param>
	/// <param name="direction">The direction to move is based on Input::Key.</param>
	/// <param name="moveFunction">This is the Directional Movement method.</param>
	void MoveCell(int x, int y, int direction, bool (Grid::* moveFunction)(Cell*, Cell*&));
	
	/// <summary>
	/// Reset all hasMerged attributes of every cells on the grid.
	/// </summary>
	void BatchResetCells();

	/// <summary>
	/// Check if the given cell has a neighbour, if not, the it will move towards the given direction. 
	/// </summary>
	/// <param name="cell">The cell we want to deal with.</param>
	/// <param name="direction">The direction it should move or merge.</param>
	/// <returns>If the loop should continue or not.</returns>
	bool CellHasNeighbour(Cell* cell, int direction);

	// Directional Movements
	bool HandleLeftMovement(Cell* cell, Cell*& neighbour);
	bool HandleRightMovement(Cell* cell, Cell*& neighbour);
	bool HandleUpMovement(Cell* cell, Cell*& neighbour);
	bool HandleDownMovement(Cell* cell, Cell*& neighbour);
	
	/// <summary>
	/// Check if there is a win.
	/// </summary>
	/// <returns>Loose ?</returns>
	bool WinCondition();

	/// <summary>
	/// Check if there is a loose.
	/// </summary>
	/// <returns>Win ?</returns>
	bool LooseCondition();

	/// <summary>
	/// Display the whole grid following the display format.
	/// </summary>
	void Display();

	/// <summary>
	/// Clean up all the memory to prevent memory leaks.
	/// </summary>
	void Clean();
#pragma endregion Gameplay Mechanics

};