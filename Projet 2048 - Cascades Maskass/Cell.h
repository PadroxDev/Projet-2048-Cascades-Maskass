#pragma once

#include <vector>

using namespace std;

class Cell {
private:
	vector<int> position;
	int value;
public:
	Cell(int x, int y, int value = 0);
	~Cell();

	// Getters
	vector<int> GetPosition() { return position; }
	int GetValue() { return value; }

	// Setters
	void SetValue(int _value);

	bool operator+(Cell* cellToMerge);
};