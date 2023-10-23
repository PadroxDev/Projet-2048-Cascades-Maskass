#pragma once

#include <iostream>
#include <vector>
#include <set>

using namespace std;

class Grid {
private:
	vector<vector<int>> grid;
	int size;
public:
	Grid(int size);
	~Grid();

	// Getters
	int GetSize() { return size; }
	
	void Init();
	int GetCell(int x, int y);
	void SetCell(int value, int x, int y);
	void Papagnan(int n);
	void Display();
	int GetRandomTileValue();
};