#include "Cell.h"

#include <iostream>

Cell::Cell(int x, int y, int _value) {
	position.resize(2);
	position[0] = x;
	position[1] = y;
	value = _value;
}

Cell::~Cell()
{}

void Cell::SetValue(int _value) {
	value = _value;
}

bool Cell::operator+(Cell* cellToMerge) {
	if (cellToMerge->value != value) return false;

	value *= 2;
	cellToMerge->value = 0;
	return true;
}