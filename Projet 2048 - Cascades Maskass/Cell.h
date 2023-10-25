#pragma once

#include <vector>

using namespace std;

class Cell {
private:
	int value;
public:
	vector<int> Position;

	Cell(int x, int y, int value = 0);
	~Cell();

	// Getters
	int GetValue() { return value; }

	// Setters
	void SetValue(int _value);

	bool operator+(Cell& cellToMerge);
};