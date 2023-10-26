#pragma once

#include <vector>

using namespace std;

class Cell {
private:
	int value;
	bool hasMerged;
public:
	vector<int> Position;

	Cell(int x, int y, int value = 0);
	~Cell();

	// Getters
	int GetValue() { return value; }

	// Setters
	void SetValue(int _value);
	void SetHasMerge(bool merged) { hasMerged = merged; }

	bool operator+(Cell& cellToMerge);
};