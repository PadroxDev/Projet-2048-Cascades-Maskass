#include "Cell.h"

#include <iostream>

Cell::Cell(int x, int y, int _value) {
	hasMerged = false;
	Position.resize(2);
	Position[0] = x;
	Position[1] = y;
	value = _value;
}

Cell::~Cell()
{}

void Cell::SetValue(int _value) {
	value = _value;
}

bool Cell::operator+(Cell& cellToMerge) {
	if (value != cellToMerge.value) return false;
	if (hasMerged || cellToMerge.hasMerged) return false;

	value *= 2;
	cellToMerge.value = 0;
	return true;
}